#include "limited_size_bag.hpp"

template <typename T>
LimitedSizeBag<T>::LimitedSizeBag() {
    size = 0;
}

template <typename T>
bool LimitedSizeBag<T>::add(const T& item) {
    // check if there is space
    if (size == maxsize) {
        return false;
    }

    // add to first empty spot
    bag_contents[size] = item;
    size++;

    return true;
}

template <typename T>
bool LimitedSizeBag<T>::remove(const T& item) {
    // check if item in bag
    // if it is there, get its index
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (bag_contents[i] == item) {
            index = i;
            break;
        }
    }

    // if item not found, index will be -1, therfore exit function
    if (index == -1) {
        return false;
    }

    // swap the item with last item in the bag and decrement size
    // The item is still there in memory but it serves as a garbage value to be overriden later
    // when an item is added
    bag_contents[index] = bag_contents[size - 1];
    size--;

    return true;
}

template <typename T>
bool LimitedSizeBag<T>::isEmpty() const {
    if (size == 0) {
        return true;
    }

    return false;
}

template <typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const {
    return size;
}

template <typename T>
bool LimitedSizeBag<T>::contains(const T& item) const {
    for (int i = 0; i < size; i++) {
        if (bag_contents[i] == item) {
            return true;
        }
    }

    return false;
}

template <typename T>
void LimitedSizeBag<T>::clear() {
    // set size to zero
    // all the items in the array become garbage values to be overriden later.
    size = 0;
}

template <typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T& item) const {
    int frequency = 0;

    // count how many times item was found in the bag
    for (int i = 0; i < size; i++) {
        if (bag_contents[i] == item) {
            frequency++;
        }
    }

    return frequency;
};
