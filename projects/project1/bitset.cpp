#include "bitset.hpp"

#include <cstdlib>
#include <iostream>

Bitset::Bitset() {
    valid = true;
    bSize = 8;

    arr = new int8_t[bSize];

    for (int i = 0; i < bSize; i++) {
        arr[i] = 0;
    }
}

Bitset::Bitset(intmax_t size) {
    valid = true;
    bSize = size;

    if (bSize <= 0) {
        valid = false;
        return;
    }

    arr = new int8_t[bSize];

    for (int i = 0; i < bSize; i++) {
        arr[i] = 0;
    }
}

Bitset::Bitset(const std::string &value) {
    valid = true;
    bSize = value.size();

    if (bSize <= 0) {
        valid = false;
        return;
    }

    arr = new int8_t[bSize];

    for (int i = 0; i < bSize; i++) {
        if (value[i] == '0') {
            arr[i] = 0;
        } else if (value[i] == '1') {
            arr[i] = 1;
        } else {
            valid = false;
            return;
        }
    }
}

Bitset::~Bitset() {
    bSize = 0;
    valid = false;
    delete[] arr;
}

// Bitset::Bitset(const Bitset &b) = delete {}

// Bitset::Bitset &operator=(const Bitset &b) = delete {}

intmax_t Bitset::size() const {
    return bSize;
}

bool Bitset::good() const {
    return valid;
}

void Bitset::set(intmax_t index) {
    if (index < 0 || index >= bSize) {
        valid = false;
        return;
    }

    arr[index] = 1;
}

void Bitset::reset(intmax_t index) {
    if (index < 0 || index >= bSize) {
        valid = false;
        return;
    }

    arr[index] = 0;
}

void Bitset::toggle(intmax_t index) {
    if (index < 0 || index >= bSize) {
        valid = false;
        return;
    }

    arr[index] = (arr[index] ? 0 : 1);
}

bool Bitset::test(intmax_t index) {
    if (index < 0 || index >= bSize) {
        valid = false;
        return false;
    }

    return arr[index];
}

std::string Bitset::asString() const {
    std::string s = "";

    for (int i = 0; i < bSize; i++) {
        s += (arr[i] ? "1" : "0");
    }

    return s;
}