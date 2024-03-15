#include <stdexcept>

#include "sorted_linked_list.hpp"

template <typename T>
SortedLinkedList<T>::SortedLinkedList() : LinkedList<T>() {
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(LinkedList<T> unsorted_list) {
    // TODO
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T>& x) : LinkedList<T>(x) {
}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(SortedLinkedList<T> x) {
    LinkedList<T>::operator=(x);
    return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList() {
    // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty() const noexcept {
    return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength() const noexcept {
    return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item) {
    // TODO
}

template <typename T>
void SortedLinkedList<T>::remove(const T& item) {
    if (isEmpty()) throw std::range_error("empty list in remove");

    // TODO
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position) {
    if (isEmpty()) throw std::range_error("empty list in remove");

    // TODO
}

template <typename T>
void SortedLinkedList<T>::clear() {
    LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position) const {
    return LinkedList<T>::getEntry(position);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& item) {
    // TODO
    return 0;
}
