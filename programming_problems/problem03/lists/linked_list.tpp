#include <new>

#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList() {
    headPtr = nullptr;
    tailPtr = nullptr;
    itemCount = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x) : LinkedList<T>::LinkedList() {
    Node<T>* curNodePtr = x.headPtr;
    T tempItem;

    // perfrom deep copy
    while (curNodePtr != nullptr) {
        tempItem = curNodePtr->getItem();

        // insert at tail
        insert(itemCount, tempItem);
        curNodePtr = curNodePtr->getNext();
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x) {
    // make use of copy constructor by passing by value
    // swap contents of copied object
    // deconstructor will take care of rest
    swap(x);
    return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList& x) {
    std::swap(headPtr, x.headPtr);
    std::swap(itemCount, x.itemCount);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept {
    if (itemCount == 0) {
        return true;
    }
    return false;
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept {
    return itemCount;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item) {
    // check for valid position
    if (position < 0 || position > itemCount) {
        return false;
    }

    // allocate memory for new node
    Node<T>* newNodePtr;

    try {
        newNodePtr = new Node<T>;
        newNodePtr->setItem(item);
    } catch (const std::bad_alloc& e) {
        return false;
    }

    // perform insertion
    if (position == 0) {
        // insert at head
        newNodePtr->setNext(headPtr);
        if (headPtr == nullptr) {
            tailPtr = newNodePtr;
        }
        headPtr = newNodePtr;
    } else if (position == itemCount) {
        // insert at tail
        // no need to check if head ptr is null due to the position constraint
        tailPtr->setNext(newNodePtr);
        tailPtr = newNodePtr;
    } else {
        Node<T>* prevNodePtr = headPtr;
        // traverse linked list
        for (int i = 0; i < position - 1; i++) {
            prevNodePtr = prevNodePtr->getNext();
        }

        newNodePtr->setNext(prevNodePtr->getNext());
        prevNodePtr->setNext(newNodePtr);
    }

    itemCount++;
    return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position) {
    if (position < 0 || position > itemCount - 1) {
        return false;
    }

    Node<T>* curNodePtr = nullptr;

    if (position == 0) {
        // delete and update head
        curNodePtr = headPtr;
        headPtr = headPtr->getNext();
    } else {
        // traverse linked list
        Node<T>* prevNodePtr = headPtr;
        for (int i = 0; i < position - 1; i++) {
            prevNodePtr = prevNodePtr->getNext();
        }

        curNodePtr = prevNodePtr->getNext();
        prevNodePtr->setNext(curNodePtr->getNext());

        if (position == itemCount - 1) {
            tailPtr = prevNodePtr;
        }
    }

    // delete the now isolated node
    delete curNodePtr;

    itemCount--;

    return true;
}

template <typename T>
void LinkedList<T>::clear() {
    Node<T>* curNodePtr = headPtr;
    // iteratively delete the nodes (from the head to tail)
    // recursive implementaion would be from tail and backtrack to head;
    while (curNodePtr != nullptr) {
        headPtr = headPtr->getNext();
        delete curNodePtr;
        curNodePtr = headPtr;
    }

    headPtr = nullptr;
    tailPtr = nullptr;
    itemCount = 0;
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const {
    if (position < 0 || position > itemCount - 1) {
        return T();
    }

    Node<T>* curNodePtr = headPtr;

    // traverse nodes to get to correct position
    for (int i = 0; i < position; i++) {
        curNodePtr = curNodePtr->getNext();
    }

    return curNodePtr->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue) {
    if (position < 0 || position > itemCount - 1) {
        return;
    }

    Node<T>* curNodePtr = headPtr;

    // traverse nodes to get to correct position
    for (int i = 0; i < position; i++) {
        curNodePtr = curNodePtr->getNext();
    }

    curNodePtr->setItem(newValue);
}
