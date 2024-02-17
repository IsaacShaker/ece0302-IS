#include <stack>
#include <string>
using std::stack;
using std::string;

#include <cctype>  // for isalpha
#include <iostream>

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
    return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
    int first = 0;

    if ((first > last)) {
        return -1;
    }

    char ch = s[last];
    if (isalpha(ch)) {
        return last;
    } else {
        if (isoperator(ch)) {
            int lastEnd = endPost(s, last - 1);
            if (lastEnd > -1) {
                return endPost(s, lastEnd - 1);
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }
}

bool isPost(string s) {
    int firstChar = endPost(s, s.size() - 1);

    return (firstChar == 0);
}

void convert(string &postfix, string &prefix) {
    // check if valid post before attempting to convert
    if (isPost(postfix) == false) {
        return;
    }

    // perform conversion
    // read postfix from left to right
    stack<string> post_to_pre;
    string arith_operator, operand1, operand2, temp;

    for (int i = 0; i < postfix.size(); i++) {
        // check if character is an operator
        if (isoperator(postfix[i])) {
            arith_operator = postfix[i];
            operand1 = post_to_pre.top();
            post_to_pre.pop();
            operand2 = post_to_pre.top();
            post_to_pre.pop();

            post_to_pre.push(arith_operator + operand2 + operand1);
        } else {
            // convet the character to string to avoid errors
            temp = postfix[i];
            post_to_pre.push(temp);
        }
    }

    // concatonate all strings in the stack to make final prefix form
    postfix = "";
    while (post_to_pre.empty() == false) {
        postfix += post_to_pre.top();
        post_to_pre.pop();
    }
}
