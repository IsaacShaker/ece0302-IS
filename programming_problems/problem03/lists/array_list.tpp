#include <iostream>
#include <new>

#include "array_list.hpp"

#define LIST_EXPANSION_INCREMENT 1

template <typename T>
ArrayList<T>::ArrayList() {
    itemCount = 0;
    listSize = 0;
}

template <typename T>
ArrayList<T>::~ArrayList() {
    delete[] listContents;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs) {
    // check if bag is being assigned to itself
    if (this == &rhs) {
        return;
    }

    // make new array
    itemCount = rhs.getLength();
    listSize = rhs.listSize;

    // wrap in try catch to make memory safe
    // exit program if memory couldn't be allocated
    try {
        listContents = new T[listSize];
    } catch (const std::bad_alloc& e) {
        std::cout << "couldn't allocate memory for array list" << std::endl;
        std::cout << "exiting ..." << std::endl;
        exit(EXIT_FAILURE);
    }

    // copy all items into new array
    for (int i = 0; i < itemCount; i++) {
        listContents[i] = rhs.listContents[i];
    }
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList rhs) {
    // create copy of rhs with copy constructor
    // rhs is pased by value so already done for us

    // perform swap with temp
    swap(rhs);

    return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList& rhs) {
    // perform the content swap
    T* temp = listContents;
    listContents = rhs.listContents;
    rhs.listContents = temp;

    // set size accordingly
    itemCount = rhs.getLength();
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept {
    if (itemCount == 0) {
        return true;
    }

    return false;
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept {
    return itemCount;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item) {
    // check if position is valid
    if (position < 0 || position > itemCount) {
        return false;
    }

    // increase size of list if no more space
    if (itemCount == listSize) {
        try {
            // if there is no space, create bigger array
            // copy contents into array
            // adjust maxsize
            T* tempListContents = new T[listSize + LIST_EXPANSION_INCREMENT];

            listSize += LIST_EXPANSION_INCREMENT;

            // copy all items into new array
            for (int i = 0; i < itemCount; i++) {
                tempListContents[i] = listContents[i];
            }

            // delete old array and set it equal to temp
            delete[] listContents;
            listContents = tempListContents;
        } catch (const std::bad_alloc& e) {
            return false;
        }
    }

    // perform shifting to make room for insertion (to the right)
    for (int i = itemCount - 1; i >= position; i--) {
        listContents[i + 1] = listContents[i];
    }

    // perform addition
    listContents[position] = item;
    itemCount++;
    return true;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position) {
    // check if postion is valid
    if (position < 0 || position > listSize - 1) {
        return false;
    }

    // perform shifting to the left to fill in gap
    for (int i = position; i > itemCount - 1; i++) {
        listContents[i] = listContents[i + 1];
    }

    // adjust itemcount to account for removal
    itemCount--;
    return false;
}

template <typename T>
void ArrayList<T>::clear() {
    itemCount = 0;
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
    // check if postion is valid
    if (position < 0 || position > listSize - 1) {
        return T();
    }

    return listContents[position];
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
    // check if postion is valid
    if (position < 0 || position > listSize - 1) {
        return;
    }

    listContents[position] = newValue;
}
