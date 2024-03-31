#include "Problem.hpp"

#include <iostream>

// PUBLIC
//------------------------------------------

// Constructors
Problem::Problem(std::string input_file) {
    try {
        image = readFromFile(input_file);
    } catch (std::runtime_error &error) {
        std::cout << "Error" << std::endl;
        exit(EXIT_FAILURE);
    }

    findInitial();
    findGoals();
}

Problem::Problem(Image<Pixel> newImage) {
    image = newImage;
    findInitial();
    findGoals();
}

// Problem State Operations
s Problem::initial() {
    return initState;
}

// returns true is the state is in a the set (is a possible exit point)
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
    for (size_t r = 0; r < image.height(); r++) {
        for (size_t c = 0; c < image.width(); c++) {
            if (image(r, c) == RED) {
                initState = {r, c};
                break;
            }
        }
    }
    // if it didn't find it
    initState = {0, 0};
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