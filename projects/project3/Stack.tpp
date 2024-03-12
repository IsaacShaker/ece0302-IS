//   Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <cstddef>
#include <iostream>

#include "Node.hpp"
#include "Stack.hpp"

template <class ItemType>
Stack<ItemType>::Stack() {
    headPtr = nullptr;
    currentSize = 0;
}  // end default constructor

template <class ItemType>
Stack<ItemType>::~Stack() {
    clear();
}  // end destructor

template <class ItemType>
bool Stack<ItemType>::isEmpty() const {
    if (currentSize == 0) {
        return true;
    }
    return false;
}  // end isEmpty

template <class ItemType>
int Stack<ItemType>::size() const {
    return currentSize;
}  // end size

template <class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem) {
    // create a new node and set item
    Node<ItemType>* newNode = nullptr;
    try {
        newNode = new Node<ItemType>;
        newNode->setItem(newItem);
    } catch (const std::bad_alloc& e) {
        return false;
    }

    // insert node at head
    newNode->setNext(headPtr);
    headPtr = newNode;

    // increase size of stack
    currentSize++;

    return true;
}  // end push

template <class ItemType>
ItemType Stack<ItemType>::peek() const {
    if (headPtr == nullptr) {
        // throw logic error if stack is empty
        throw std::logic_error("trying to access an empty stack, peek requires the stack to not be empty");
    }
    return headPtr->getItem();
}  // end peek

template <class ItemType>
bool Stack<ItemType>::pop() {
    // check if there is anything to pop
    if (headPtr == nullptr) {
        return false;
    }

    // delete head node
    Node<ItemType>* currNode = headPtr;
    headPtr = headPtr->getNext();
    delete currNode;

    // decrease size
    currentSize--;

    return true;
}  // end pop

template <class ItemType>
void Stack<ItemType>::clear() {
    // delete all nodes
    Node<ItemType>* currNode = headPtr;
    while (currNode != nullptr) {
        headPtr = headPtr->getNext();
        delete currNode;
        currNode = headPtr;
    }

    currentSize = 0;
}  // end clear
