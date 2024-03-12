// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include "XMLParser.hpp"

#include <assert.h>

#include <string>

//---HELPER FUNCTIONS------------------------------------

// replaces characters in a string with another character (default is a space)
std::string replace(std::string str, const char &replace, const char &fill = ' ') {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == replace) {
            str[i] = fill;
        }
    }

    return str;
}

// removes leading and trailing whitespace from string
std::string trim(const std::string &str, const std::string &whitespace = " \t\n\r") {
    std::size_t strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return "";  // no content

    std::size_t strEnd = str.find_last_not_of(whitespace);
    std::size_t strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

// reduces intermediate whitespace within a string
std::string reduce(const std::string &str, const std::string &fill = " ", const std::string &whitespace = " \t\n\r") {
    // trim first
    std::string result = trim(str, whitespace);

    // replace sub ranges
    std::size_t beginSpace = result.find_first_of(whitespace);
    std::size_t endSpace = 0, range = 0;

    while (beginSpace != std::string::npos) {
        endSpace = result.find_first_not_of(whitespace, beginSpace);
        range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        beginSpace = result.find_first_of(whitespace, beginSpace + fill.length());  // starting from after the whitespace we replaced
    }

    return result;
}

static std::string parseContent(std::string content) {
    // replace '\n', '\r', '\t', with spaces:
    // "hi\t\t there\n" => "hi   there "

    // remove preceding and postcedding spaces:
    // "    hi   there   " => "hi   there"

    // only one space between words:
    // "hi   there" => "hi there"

    return reduce(content);
}

static TokenStruct parseMarkup(std::string markup) {
    TokenStruct token;
    token.tokenString = "";
    // get rid of opening and closing brackets '<' and '>'. store in name
    std::string name = markup.substr(1, markup.size() - 2);

    if (name == "") {
        // invalid, no name
        return token;
    }

    // do some pre processing
    if (name[0] == '?' && name[name.size() - 1] == '?') {
        if (name.size() <= 2) {
            // invalid, name = ? or ??, we want name to be ?...?
            return token;
        }
        name = name.substr(1, name.size() - 2);  // get rid of leading and trailing '?'
        token.tokenType = DECLARATION;
        token.tokenString = name;
        return token;
    } else if (name[name.size() - 1] == '/') {
        if (name.size() <= 1) {
            // invalid name = /, we want name to be .../
            return token;
        }
        name = name.substr(0, name.size() - 1);  // get rid of trailing '/'
        token.tokenType = EMPTY_TAG;
    } else if (name[0] == '/') {
        if (name.size() <= 1) {
            // invalid name = /, we want name to be /...
            return token;
        }
        name = name.substr(1, name.size() - 1);  // get rid of leading '/'
        token.tokenType = END_TAG;
    } else {
        token.tokenType = START_TAG;
    }

    // proccess the name
    // identify first cutoff, separate name from attributes (if there are attributes)
    std::size_t endName = name.find_first_of(" \t\r\n");
    if (endName == 0) {
        // invalid, name begins with whitespace
        return token;
    } else if (endName != std::string::npos) {
        if (token.tokenType == END_TAG) {
            // invalid, end tags should not have any attributes
            return token;
        }
        name = name.substr(0, endName);
    }

    // name is now isolated, check for invalid characters
    for (int i = 0; i < name.size(); i++) {
        if ((name[i] >= '!' && name[i] <= ',') || (name[i] == '/') || (name[i] >= ';' && name[i] <= '@') || (name[i] == '`') || (name[i] >= '{' && name[i] <= '~')) {
            // invalid name
            return token;
        }
    }

    // check for invalid starting character
    if (name[0] == '-' || name[0] == '.' || std::isdigit(name[0])) {
        // invalid name
        return token;
    }

    token.tokenString = name;
    return token;
}

//-------------------------------------------------------

XMLParser::XMLParser() {
}  // end default constructor

XMLParser::~XMLParser() {
    clear();
}  // end deconstructor

bool XMLParser::tokenizeInputString(const std::string &inputString) {
    // start by clearing internal data
    clear();

    // fill the tokenized Input Vector with tokens
    int i = 0, inputLength = inputString.size();

    // analyze the string piece by piece
    // break down into markdown and content
    std::string tempStr = "";
    TokenStruct tempToken;

    while (i < inputLength) {
        // gather content
        tempStr = "";
        while (i < inputLength && inputString[i] != '<') {
            // catch nested angle brackets
            if (inputString[i] == '>') {
                clear();
                return false;
            }

            tempStr += inputString[i];
            i++;
        }

        // temp now contains possible content, parse it and add token if necessary
        tempStr = parseContent(tempStr);
        if (tempStr != "") {
            tempToken.tokenType = CONTENT;
            tempToken.tokenString = tempStr;
            tokenizedInputVector.push_back(tempToken);
        }

        // check if end of input
        if (i >= inputLength) {
            // at this point, input is done and we saw all possible tags
            break;
        }

        // gather tag and everytihing in it
        assert(inputString[i] == '<');
        tempStr = inputString[i];  // tempStr = "<";
        i++;
        while (i < inputLength && inputString[i] != '>') {
            // catch nested angle brackets
            if (inputString[i] == '<') {
                clear();
                return false;
            }

            tempStr += inputString[i];
            i++;
        }

        // check if end of input
        if (i >= inputLength) {
            // at this point, we started a tag but did not finish it, therefore it is invalid
            clear();
            return false;
        }

        assert(inputString[i] == '>');
        tempStr += inputString[i];  // tempStr += ">";
        i++;

        // tempStr now contains possible markup, parse it to see tag type and name
        tempToken = parseMarkup(tempStr);
        // check for invalid markup
        if (tempToken.tokenString == "") {
            clear();
            return false;
        }

        tokenizedInputVector.push_back(tempToken);
    }

    return true;
}  // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput() {
    // check if tokenizaton was successful
    if (tokenizedInputVector.empty()) {
        return false;
    }

    // fills the element name bag
    // uses the parse stack to check validity
    // make the parse stack using the vector

    // if not valid
    // empty the bag
    elementNameBag.clear();
    // empty the stack
    parseStack.clear();
    // keep the vector
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
    // check if invalid xml or unsuccessful tokenization
    // could just check for invalid xml (check for empty bag)
    // doing both makes the exception messages more helpful
    if (tokenizedInputVector.empty()) {
        throw std::logic_error("XML tokenization unsuccessful or have not yet been tokenized");
    } else if (elementNameBag.isEmpty()) {
        throw std::logic_error("XML is not valid or have not yet been parsed");
    }

    return elementNameBag.contains(inputString);
}

int XMLParser::frequencyElementName(const std::string &inputString) const {
    // check if invalid xml or unsuccessful tokenization
    // could just check for invalid xml (check for empty bag)
    // doing both makes the exception messages more helpful
    if (tokenizedInputVector.empty()) {
        throw std::logic_error("XML tokenization unsuccessful or have not yet been tokenized");
    } else if (elementNameBag.isEmpty()) {
        throw std::logic_error("XML is not valid or have not yet been parsed");
    }

    return elementNameBag.getFrequencyOf(inputString);
}
