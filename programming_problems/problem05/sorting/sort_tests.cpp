#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "linked_list.hpp"
#include "sort.hpp"

// write your test cases here
TEST_CASE("Test int sorting", "sorting") {
    LinkedList<int> lst;

    lst.insert(0, 100);
    lst.insert(1, 4);
    lst.insert(2, 10);
    lst.insert(3, 25);
    lst.insert(4, 11);

    LinkedList<int> sorted = sort(lst);

    // check sorted list
    REQUIRE(sorted.getEntry(0) == 4);
    REQUIRE(sorted.getEntry(1) == 10);
    REQUIRE(sorted.getEntry(2) == 11);
    REQUIRE(sorted.getEntry(3) == 25);
    REQUIRE(sorted.getEntry(4) == 100);
}

TEST_CASE("Test short list", "sorting") {
    LinkedList<int> lst;

    lst.insert(0, 100);

    LinkedList<int> sorted = sort(lst);

    // check sorted list
    REQUIRE(sorted.getEntry(0) == 100);
}

TEST_CASE("Test long list with duplicates", "sorting") {
    LinkedList<int> lst;

    lst.insert(0, 100);
    lst.insert(1, 4);
    lst.insert(2, 10);
    lst.insert(3, 25);
    lst.insert(4, 11);
    lst.insert(5, 100);
    lst.insert(6, 4);
    lst.insert(7, 10);
    lst.insert(8, 25);
    lst.insert(9, 11);

    LinkedList<int> sorted = sort(lst);

    // check sorted list
    REQUIRE(sorted.getEntry(0) == 4);
    REQUIRE(sorted.getEntry(1) == 4);
    REQUIRE(sorted.getEntry(2) == 10);
    REQUIRE(sorted.getEntry(3) == 10);
    REQUIRE(sorted.getEntry(4) == 11);
    REQUIRE(sorted.getEntry(5) == 11);
    REQUIRE(sorted.getEntry(6) == 25);
    REQUIRE(sorted.getEntry(7) == 25);
    REQUIRE(sorted.getEntry(8) == 100);
    REQUIRE(sorted.getEntry(9) == 100);
}

TEST_CASE("Test char sorting", "sorting") {
    LinkedList<char> lst;

    lst.insert(0, 'z');
    lst.insert(1, 'A');
    lst.insert(2, 'h');
    lst.insert(3, 'a');
    lst.insert(4, 'I');

    LinkedList<char> sorted = sort(lst);

    // check sorted list
    REQUIRE(sorted.getEntry(0) == 'A');
    REQUIRE(sorted.getEntry(1) == 'I');
    REQUIRE(sorted.getEntry(2) == 'a');
    REQUIRE(sorted.getEntry(3) == 'h');
    REQUIRE(sorted.getEntry(4) == 'z');
}
