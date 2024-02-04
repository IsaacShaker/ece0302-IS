#include "dynamic_bag.hpp"

#define BAG_EXPANSION_INCREMENT 50

template <typename T>
DynamicBag<T>::DynamicBag() {
    size = 0;
    // make room for 50 items.
    // as more space is needed, the bag's max size will increase by 50
    // for efficiency purposes
    max_size = 50;
    bag_contents = new T[max_size];
}

template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T>& x) {
    // check if bag is being assigned to itself
    if (this == &x) {
        return;
    }

    // make new array
    size = x.getCurrentSize();
    max_size = x.getMaxSize();
    bag_contents = new T[max_size];

    // copy all items into new array
    for (int i = 0; i < size; i++) {
        bag_contents[i] = x.bag_contents[i];
    }
}

template <typename T>
DynamicBag<T>::~DynamicBag() {
    delete[] bag_contents;
}

template <typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> x) {
    // create copy of x with copy constructor
    DynamicBag temp(x);

    // perform swap with temp
    swap(temp);

    return *this;
}

template <typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x) {
    // perform the content swap
    T* temp = bag_contents;
    bag_contents = x.bag_contents;
    x.bag_contents = temp;

    // set size accordingly
    size = x.getCurrentSize();
    max_size = x.getMaxSize();
}

template <typename T>
bool DynamicBag<T>::add(const T& item) {
    // check if there is space
    if (size == max_size) {
        try {
            // if there is no space, create bigger array
            // copy contents into array
            // adjust maxsize
            T* temp_bag_contents = new T[max_size + BAG_EXPANSION_INCREMENT];

            max_size += BAG_EXPANSION_INCREMENT;

            // copy all items into new array
            for (int i = 0; i < size; i++) {
                temp_bag_contents[i] = bag_contents[i];
            }

            // delete old array and set it equal to temp
            delete[] bag_contents;
            bag_contents = temp_bag_contents;
        } catch (const std::bad_alloc& e) {
            return false;
        }
    }

    // add to first empty spot
    bag_contents[size] = item;
    size++;

    return true;
}

template <typename T>
bool DynamicBag<T>::remove(const T& item) {
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
bool DynamicBag<T>::isEmpty() const {
    if (size == 0) {
        return true;
    }

    return false;
}

template <typename T>
std::size_t DynamicBag<T>::getCurrentSize() const {
    return size;
}

template <typename T>
std::size_t DynamicBag<T>::getMaxSize() const {
    return max_size;
}

template <typename T>
bool DynamicBag<T>::contains(const T& item) const {
    for (int i = 0; i < size; i++) {
        if (bag_contents[i] == item) {
            return true;
        }
    }

    return false;
}

template <typename T>
void DynamicBag<T>::clear() {
    // set size to zero
    // all the items in the array become garbage values to be overriden later.
    size = 0;
}

template <typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T& item) const {
    int frequency = 0;

    // count how many times item was found in the bag
    for (int i = 0; i < size; i++) {
        if (bag_contents[i] == item) {
            frequency++;
        }
    }

    return frequency;
};
