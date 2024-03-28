#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "list.hpp"
#include "priority_queue.hpp"
#include "sorted_list.hpp"

TEST_CASE("Testing Priority Queue", "[priority queue]") {
    typedef SortedList<int, List<int>> SortedListType;
    typedef PriorityQueue<int, SortedListType> PriorityQueueType;

    PriorityQueueType pq;

    // TODO
}
