// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include "XMLParser.hpp"

#include <assert.h>

#include <string>

XMLParser::XMLParser() {
}  // end default constructor

XMLParser::~XMLParser() {
    clear();
}  // end deconstructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString) {
    return false;
}  // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput() {
    return false;
}

void XMLParser::clear() {
    elementNameBag.clear();
    parseStack.clear();
    tokenizedInputVector.clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const {
    return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &inputString) const {
    return elementNameBag.contains(inputString);
}

int XMLParser::frequencyElementName(const std::string &inputString) const {
    return elementNameBag.getFrequencyOf(inputString);
}
