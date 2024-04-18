#ifndef FRONTIER_QUEUE_HPP
#define FRONTIER_QUEUE_HPP

#include <vector>

#include "state.hpp"

template <typename T>
class frontier_queue {
   public:
    /* Returns true if the frontier is empty, else false
     */
    bool empty();

    /* push a State with value p, cost, and heuristic into the frontier.
     * This should be a O(log n) operation
     * You will need to create a state from the passed inputs, and then add it to the queue.
     */
    void push(const T &p, std::size_t cost, std::size_t heur);

    /* pop the state from the frontier with the smallest f-cost
     * This should be a O(log n) operation
     */
    State<T> pop();

    /* Returns true if the value T p is in the frontier
     * This may be at most an O(n) operation
     */
    bool contains(const T &p);

    /* Replaces a state if the path cost is lower.
     * The frontier must still be a valid min heap after replacement.
     * This should be at most a O(n) operation.
     */
    void replaceif(const T &p, std::size_t cost);

   private:
    // array based implementaion of min heap
    std::vector<State<T>> queue;
    void heapRebuild(int nodeIndex);
    void bubbleUp(int &nodeIndex);
    bool isLeaf(int &nodeIndex) const;
};

#include "frontier_queue.tpp"

#endif
