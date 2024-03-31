#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// #include "Problem.hpp"
#include "lib/image.h"
#include "list.hpp"
#include "queue.hpp"

// this is a state (s) and stores the coordinates of a pixel s.first == pixel row, s.second = pixel column
typedef std::pair<std::size_t, std::size_t> s;

class Problem {
   public:
    // constructor - load image from file
    Problem(std::string input_file);
    // constructor - load from existing image data structure
    Problem(Image<Pixel> newImage);

    // returns the location of the red pixel
    s initial();
    // returns true if currState is a an exitPoint
    bool goal(s currState);
    // returns up to 4 moves the runner can make (left, right, up, down) if available
    std::vector<s> actions(s state);

   private:
    Image<Pixel> image;
    s initState;
    // stores the coordinates
    std::set<s> exitPoints;

    // searches image for the red pixel
    void findInitial();
    // seraches image for exit points (white pixels along the perimiter)
    void findGoals();
};

// PUBLIC
//------------------------------------------

// Constructors
//-------------
Problem::Problem(std::string input_file) {
    // load from file with error handling
    try {
        image = readFromFile(input_file);
    } catch (std::runtime_error &error) {
        std::cerr << "Error - Could not read image file";
        exit(EXIT_FAILURE);
    }

    findInitial();
    findGoals();
}

Problem::Problem(Image<Pixel> newImage) {
    // load from a given image
    image = newImage;
    findInitial();
    findGoals();
}

// Problem State Operations
//-------------------------
s Problem::initial() {
    return initState;
}

// returns true is the state is in a the set (is an exit point)
bool Problem::goal(s state) {
    return exitPoints.count(state);
}

std::vector<s> Problem::actions(s state) {
    std::vector<s> nextStates;

    s prevRow = {state.first - 1, state.second};
    s nextRow = {state.first + 1, state.second};
    s prevCol = {state.first, state.second - 1};
    s nextCol = {state.first, state.second + 1};

    // add the state if it can be explored (white pixel)
    if (image(prevRow.first, prevRow.second) == WHITE) {
        nextStates.push_back(prevRow);
    }
    if (image(nextRow.first, nextRow.second) == WHITE) {
        nextStates.push_back(nextRow);
    }
    if (image(prevCol.first, prevCol.second) == WHITE) {
        nextStates.push_back(prevCol);
    }
    if (image(nextCol.first, nextCol.second) == WHITE) {
        nextStates.push_back(nextCol);
    }

    return nextStates;
}

// PRIVATE
//------------------------------------
void Problem::findInitial() {
    // search image for the red pixel
    int numRed = 0;
    for (size_t r = 0; r < image.height(); r++) {
        for (size_t c = 0; c < image.width(); c++) {
            if (image(r, c) == RED) {
                initState = {r, c};
                numRed += 1;
            } else if (image(r, c) != BLACK && image(r, c) != WHITE) {
                std::cerr << "Error - image contains colors other than black, white, or red";
            }
        }
    }
    // if it didn't find it
    if (numRed != 1) {
        std::cerr << "Error - image does not contain exactly one red pixel";
    }
}

void Problem::findGoals() {
    // search the perimiter for white space
    size_t max_r = image.height() - 1;
    size_t max_c = image.width() - 1;

    // left and right sides
    for (size_t r = 0; r < image.height(); r++) {
        if (image(r, 0) == WHITE) {
            exitPoints.insert({r, 0});
        }
        if (image(r, max_c) == WHITE) {
            exitPoints.insert({r, max_c});
        }
    }

    // top and bottom sides
    // don't look at the corners by setting image.width() - 1 and c = 1
    for (size_t c = 1; c < image.width() - 1; c++) {
        if (image(0, c) == WHITE) {
            exitPoints.insert({0, c});
        }
        if (image(max_r, c) == WHITE) {
            exitPoints.insert({max_r, c});
        }
    }
}

s solve(Problem &maze);

int main(int argc, char *argv[]) {
    // get input/output file names from command line arguments
    if (argc != 3) {
        std::cout << "Usage: pathfinder "
                  << "<first_input_filename> <second_output_filename>\n"
                  << std::endl;
        return EXIT_FAILURE;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    // Read input image from file
    // image.data is an array
    Image<Pixel> image;
    try {
        image = readFromFile(input_file);
    } catch (std::runtime_error &error) {
        std::cerr << "Error - Could not read image file";
        exit(EXIT_FAILURE);
    }

    // initialize the problem
    Problem maze(image);

    // // solve the maze
    s solution = solve(maze);

    // // check if solution valid
    // solve function will return {0, 0} if an invalid solution
    // must also check to make sure that the image didn't also start at {0, 0}, which in that case {0, 0} IS a valid solution
    if (solution.first == 0 && solution.second == 0 && (maze.initial().first != 0 || maze.initial().second != 0)) {
        std::cout << "No Solution Found";
    } else {
        std::cout << "Solution Found";
        image(solution.first, solution.second) = GREEN;
    }

    // Write solution image to file
    try {
        writeToFile(image, output_file);
    } catch (std::runtime_error &error) {
        std::cerr << "Error - Could create output image file";
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

// BFS algorithim to solve the maze
s solve(Problem &maze) {
    s state = maze.initial();

    // handle if start is also an exit point
    if (maze.goal(state)) {
        return state;
    }

    // initialze frontier and add the initial state
    Queue<s, List<s>> frontier;
    frontier.enqueue(state);

    // initialze explored set and add initial state
    // using a set becasue checking if an object is in a set takes O(1) while a list or queue take O(n)
    std::set<s> explored;
    explored.insert(state);

    while (true) {
        if (frontier.isEmpty()) {
            // no solution found
            return {0, 0};
        }

        state = frontier.peekFront();
        frontier.dequeue();

        if (maze.goal(state)) {
            // we are at the solution
            return state;
        }

        std::vector<s> nextStates = maze.actions(state);
        for (int i = 0; i < nextStates.size(); i++) {
            s nextState = nextStates[i];
            // check state has already been explored
            if (explored.count(nextState) == false) {
                frontier.enqueue(nextState);
                // add to the set so we don't add duplicates. checking if something is in a set is much faster than searching a queue or list
                explored.insert(nextState);
            }
        }
    }
}
