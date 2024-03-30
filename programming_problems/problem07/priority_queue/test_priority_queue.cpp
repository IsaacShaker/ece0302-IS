#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "list.hpp"
#include "priority_queue.hpp"
#include "sorted_list.hpp"

typedef SortedList<int, List<int>> SortedListType;
typedef PriorityQueue<int, SortedListType> PriorityQueueType;

TEST_CASE("Testing isEmpty", "[priority queue]") {
    PriorityQueueType pq;
    REQUIRE(pq.isEmpty());

    pq.add('a');
    REQUIRE_FALSE(pq.isEmpty());

    pq.remove();
    REQUIRE(pq.isEmpty());
}

TEST_CASE("Testing remove", "[priority queue]") {
    PriorityQueueType pq;

    pq.add(4);

    pq.remove();

    REQUIRE(pq.isEmpty());
}

TEST_CASE("Testing peek", "[priority queue]") {
    PriorityQueueType pq;

    pq.add(4);

    REQUIRE(pq.peek() == 4);
}

TEST_CASE("Testing add", "[priority queue]") {
    PriorityQueueType pq;

    for (int i = 0; i < 26; i++) {
        pq.add(i);
    }

    for (int i = 25; i >= 0; i--) {
        REQUIRE(pq.peek() == i);
        pq.remove();
    }
}