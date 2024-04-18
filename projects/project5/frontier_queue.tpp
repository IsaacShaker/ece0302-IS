#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() {
    if (queue.empty()) {
        throw std::logic_error("queue is empty, trying to access memory that does not exist");
    }

    // remove and save the root element (smallest f-cost)
    State<T> poppedState = queue[0];     // smallest f-cost state
    queue[0] = queue[queue.size() - 1];  // replace root with last element
    queue.pop_back();                    // remove the last element

    // rebuild the heap
    heapRebuild(0);

    return poppedState;
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {
    // Place newData at the bottom of the tree
    int newDataIndex = queue.size();
    State<T> newState(p, cost, heur);
    queue.push_back(newState);

    // Make new item bubble up to the appropriate spot in the tree
    bubbleUp(newDataIndex);
}

template <typename T>
bool frontier_queue<T>::empty() {
    return (queue.size() == 0);
}

template <typename T>
bool frontier_queue<T>::contains(const T &p) {
    // currently O(N)
    bool found = false;
    for (int i = 0; i < queue.size(); i++) {
        if (queue[i].getValue() == p) {
            found = true;
            break;
        }
    }
    return found;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {
    // find the state that has p
    // currently O(N)
    bool found = false;
    int nodeIndex = 0;
    for (int i = 0; i < queue.size(); i++) {
        if (queue[i].getValue() == p) {
            found = true;
            nodeIndex = i;
            break;
        }
    }

    if (found == false) {
        return;
    }

    // existing state has lower path cost, so do nothing
    if (queue[nodeIndex].getPathCost() <= cost) {
        return;
    }

    queue[nodeIndex].updatePathCost(cost);
    // bubble the node up
    bubbleUp(nodeIndex);
}

template <typename T>
void frontier_queue<T>::bubbleUp(int &nodeIndex) {
    bool inPlace = false;
    while ((nodeIndex >= 0) && !inPlace) {
        int parentIndex = (nodeIndex - 1) / 2;
        if (queue[nodeIndex].getFCost() >= queue[parentIndex].getFCost())
            inPlace = true;
        else {
            State<T> temp = queue[nodeIndex];
            queue[nodeIndex] = queue[parentIndex];
            queue[parentIndex] = temp;

            nodeIndex = parentIndex;
        }
    }
}

// Converts a semiheap rooted at index nodeIndex into a heap.
template <typename T>
void frontier_queue<T>::heapRebuild(int nodeIndex) {
    // Recursively trickle the item at index nodeIndex down to its proper position by
    // swapping it with its larger child, if the child is larger than the item.
    // If the item is at a leaf, nothing needs to be done.
    if (isLeaf(nodeIndex)) {
        return;
    }

    // The root must have a child, . . . find smaller child
    int leftChildIndex = 2 * nodeIndex + 1;
    int rightChildIndex = leftChildIndex + 1;
    int smallerChildIndex = rightChildIndex;  // Assume right child exists and is the smaller

    // Check whether right child exists; if so, is left child smaller?
    // If no right child, left one is smaller
    if ((smallerChildIndex >= queue.size()) || (queue[leftChildIndex].getFCost() < queue[rightChildIndex].getFCost())) {
        smallerChildIndex = leftChildIndex;  // Assumption was wrong
    }
    if (queue[nodeIndex].getFCost() > queue[smallerChildIndex].getFCost()) {
        State<T> temp = queue[nodeIndex];
        queue[nodeIndex] = queue[smallerChildIndex];
        queue[smallerChildIndex] = temp;
        // Transform the semiheap rooted at smallerChildIndex into a heap
        heapRebuild(smallerChildIndex);
    }
}

template <typename T>
bool frontier_queue<T>::isLeaf(int &nodeIndex) const {
    int leftChildIndex = 2 * nodeIndex + 1;
    int rightChildIndex = leftChildIndex + 1;

    // is leaf if left and right index are out of range
    if (leftChildIndex >= queue.size() && rightChildIndex >= queue.size()) {
        return true;
    }
    return false;
}