#ifndef _PROBLEM_
#define _PROBLEM_

#include <set>
#include <string>
#include <vector>

#include "lib/image.h"

typedef struct {
    std::size_t r;
    std::size_t c;
} s;

class Problem {
   public:
    // constructor - load image from file
    Problem(std::string input_file);
    // constructor - load from existing image data structure
    Problem(Image<Pixel> &newImage);

    // returns the
    s initial();
    bool goal(s currState);
    std::vector<s> actions(s);

   private:
    Image<Pixel> image;
    s initState;
    std::set<s> exitPoints;

    void findInitial();
    void findGoals();
};

#include "Problem.cpp"

#endif