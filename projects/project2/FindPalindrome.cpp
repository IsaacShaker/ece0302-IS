#include "FindPalindrome.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define LETTERS_IN_ALPHABET 26

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static string convertToLowerCase(string value) {
    for (int i = 0; i < value.size(); i++) {
        value[i] = tolower(value[i]);
    }
    return value;
}

// helper function to check if string only contians alphabetical characters a-z and A-Z
static bool onlyAlpha(const string& value) {
    for (int i = 0; i < value.size(); i++) {
        if (isalpha(value[i]) == false) {
            return false;
        }
    }
    return true;
}

// helper funciton to convert a vector of strings to one single string (concatonated left to right)
static string vectToString(const vector<string>& stringVect) {
    string res = "";

    for (int i = 0; i < stringVect.size(); i++) {
        res += stringVect[i];
    }

    return res;
}

// helper function to check if a vector contains a string (case ignored)
static bool vectContains(vector<string>& stringVect, const string& value) {
    string valueLowered = convertToLowerCase(value);
    for (int i = 0; i < stringVect.size(); i++) {
        if (valueLowered == convertToLowerCase(stringVect[i])) {
            return true;
        }
    }
    return false;
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string> candidateStringVector,
                                              vector<string> currentStringVector) {
    // BASE CASE: all words have been added to the sentence
    if (candidateStringVector.size() == wordList.size()) {
        // convert the vector to a string and check if it is a palindrome
        if (isPalindrome(vectToString(candidateStringVector))) {
            palindromeSentences.push_back(candidateStringVector);
        }
    }

    vector<string> newCurrStrVect, newCandidateStrVect;

    for (int i = 0; i < currentStringVector.size(); i++) {
        // add word to new canditate string vector
        newCandidateStrVect = candidateStringVector;
        newCandidateStrVect.push_back(currentStringVector[i]);

        // remove the added word from the new current string vector
        newCurrStrVect = currentStringVector;
        newCurrStrVect[i] = newCurrStrVect[newCurrStrVect.size() - 1];
        newCurrStrVect.pop_back();

        // perform second test to see if we should examine this branch
        if (cutTest2(newCandidateStrVect, newCurrStrVect)) {
            // recursive calls to make all possible combinations
            recursiveFindPalindromes(newCandidateStrVect, newCurrStrVect);
        }
    }
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const {
    locale loc;
    // make sure that the string is lower case...
    currentString = convertToLowerCase(currentString);
    // see if the characters are symmetric...
    int stringLength = currentString.size();
    for (int i = 0; i < stringLength / 2; i++) {
        if (currentString[i] != currentString[stringLength - i - 1]) {
            return false;
        }
    }
    return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome() {
    // nothing needs to be initialized, the vectors are already empty
}

FindPalindrome::~FindPalindrome() {
    // no dynamic memory allocation was done
}

int FindPalindrome::number() const {
    return palindromeSentences.size();
}

void FindPalindrome::clear() {
    wordList.clear();
    palindromeSentences.clear();
}

bool FindPalindrome::cutTest1(const vector<string>& stringVector) {
    // convert the vector to a sting
    string value = convertToLowerCase(vectToString(stringVector));

    // make sure the string only contains alphabetical characters (this should be guaranted if this member function is private)
    if (!onlyAlpha(value)) {
        return false;
    }

    // create an array to store the number of times a letter appears in the string (26 possible letters)
    int alphaCount[LETTERS_IN_ALPHABET] = {0};

    // count number of times letters appear in the string
    int index = 0;
    for (int i = 0; i < value.size(); i++) {
        // convert the character to an int for array indexing. a = 97 but should index to 0 (97 - 97 = 0)
        index = value[i] - 'a';
        alphaCount[index]++;
    }

    // count number of odd occurances
    int numOdd = 0;
    for (int i = 0; i < LETTERS_IN_ALPHABET; i++) {
        if ((alphaCount[i] % 2) == 1) {
            numOdd++;
        }
    }

    // if even sized string
    if ((value.size() % 2) == 0) {
        if (numOdd != 0) {
            return false;
        }
    }
    // if odd sized string
    else {
        if (numOdd != 1) {
            return false;
        }
    }

    return true;
}

bool FindPalindrome::cutTest2(const vector<string>& stringVector1,
                              const vector<string>& stringVector2) {
    // convert the vectors to stings
    string value1 = convertToLowerCase(vectToString(stringVector1));
    string value2 = convertToLowerCase(vectToString(stringVector2));

    // make sure the strings only contain alphabetical characters (this should be guaranted if this member function is private)
    if (!onlyAlpha(value1) || !onlyAlpha(value2)) {
        return false;
    }

    // create arrays to store the number of times a letter appears in the strings (26 possible letters)
    int alphaCount1[LETTERS_IN_ALPHABET] = {0};
    int alphaCount2[LETTERS_IN_ALPHABET] = {0};

    // count number of times letters appear in the strings
    int index = 0;
    // for string 1
    for (int i = 0; i < value1.size(); i++) {
        // convert the character to an int for array indexing. a = 97 but should index to 0 (97 - 97 = 0)
        index = value1[i] - 'a';
        alphaCount1[index]++;
    }
    // for string 2
    for (int i = 0; i < value2.size(); i++) {
        index = value2[i] - 'a';
        alphaCount2[index]++;
    }

    // string 1 is smaller
    if (value1.size() < value2.size()) {
        for (int i = 0; i < LETTERS_IN_ALPHABET; i++) {
            if (alphaCount1[i] > alphaCount2[i]) {
                return false;
            }
        }
    }
    // if string 2 is smaller or equal
    else {
        for (int i = 0; i < LETTERS_IN_ALPHABET; i++) {
            if (alphaCount2[i] > alphaCount1[i]) {
                return false;
            }
        }
    }

    return true;
}

bool FindPalindrome::add(const string& value) {
    // validate word
    // word must only contain alphabetical characters and not already be in word list
    if (!onlyAlpha(value) || vectContains(wordList, value)) {
        return false;
    }

    // add word to list
    wordList.push_back(value);

    // before checking possible combinations, perform first check
    if (cutTest1(wordList)) {
        // if test is passed, check permutations
        recursiveFindPalindromes(vector<string>(), wordList);
    }

    return true;
}

bool FindPalindrome::add(const vector<string>& stringVector) {
    // validate words
    // word must only contain alphabetical characters and not already be in word list
    for (int i = 0; i < stringVector.size(); i++) {
        if (!onlyAlpha(stringVector[i]) || vectContains(wordList, stringVector[i])) {
            return false;
        }
    }

    // make sure that the vector of strings being added doesn't contain duplicates
    for (int i = 0; i < stringVector.size(); i++) {
        for (int j = i + 1; j < stringVector.size(); j++) {
            if (convertToLowerCase(stringVector[i]) == convertToLowerCase(stringVector[j])) {
                // it contains duplicates so leave function
                return false;
            }
        }
    }

    // add words to list
    for (int i = 0; i < stringVector.size(); i++) {
        wordList.push_back(stringVector[i]);
    }

    // before checking possible combinations, perform first check
    if (cutTest1(wordList)) {
        // if test is passed, check permutations
        recursiveFindPalindromes(vector<string>(), wordList);
    }

    return true;
}

vector<vector<string>> FindPalindrome::toVector() const {
    return palindromeSentences;
}
