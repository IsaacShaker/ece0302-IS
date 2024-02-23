#ifndef _SORT_HPP
#define _SORT_HPP

#include "linked_list.hpp"

//---------------------
// Bubble Sort !
//---------------------
template <typename T>
LinkedList<T> sort(LinkedList<T> list) {
    int listLength = list.getLength();

    // Keep track of number of swaps and iterations for better performance.
    // If numSwaps stays as zero, we know that the list is sorted.
    // We keep track of iterations because after each iteration, the next greatest item will be correctly placed
    // and there is no need to check for swaps after that point
    int numSwaps, iterations = 0;

    T item1, item2;

    do {
        numSwaps = 0;

        for (int i = 0; i < listLength - 1 - iterations; i++) {
            item1 = list.getEntry(i);
            item2 = list.getEntry(i + 1);

            // swap items if left is greater than right
            if (item1 > item2) {
                list.setEntry(i, item2);
                list.setEntry(i + 1, item1);
                numSwaps++;
            }
        }

        iterations++;
    } while (numSwaps != 0);

    return list;
}

#endif
