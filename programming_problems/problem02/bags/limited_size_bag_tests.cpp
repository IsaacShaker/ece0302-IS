#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("Calling all public members", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    b.add(0);
    b.remove(0);
    b.isEmpty();
    b.getCurrentSize();
    b.clear();
    b.getFrequencyOf(0);
    b.contains(0);
}

TEST_CASE("Test add function", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    REQUIRE_FALSE(b.contains(1));
    b.add(1);
    REQUIRE(b.contains(1));
}

TEST_CASE("Test add function - More than 100 items", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    for (int i = 0; i < 100; i++) {
        b.add(i);
    }

    REQUIRE_FALSE(b.add(1));
}

TEST_CASE("Test remove function", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    b.add(1);
    b.remove(1);
    REQUIRE_FALSE(b.contains(1));
}

TEST_CASE("Test remove function - Item not in bag", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    b.add(1);
    REQUIRE_FALSE(b.remove(0));
}

TEST_CASE("Test empty function", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    REQUIRE(b.isEmpty());

    b.add(1);
    b.remove(1);
    REQUIRE(b.isEmpty());
}

TEST_CASE("Test getCurrentSize function", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    b.add(1);
    b.add(4);
    b.add(7);
    b.add(9);
    REQUIRE(b.getCurrentSize() == 4);
}

TEST_CASE("Test clear function", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    b.add(1);
    b.add(4);
    b.add(7);
    b.add(9);
    b.clear();
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE_FALSE(b.contains(1));
    REQUIRE_FALSE(b.contains(4));
    REQUIRE_FALSE(b.contains(7));
    REQUIRE_FALSE(b.contains(9));
}

TEST_CASE("Test getFrequencyOf function", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    b.add(1);
    b.add(1);
    b.add(1);
    REQUIRE(b.getFrequencyOf(1) == 3);
}

TEST_CASE("Test contains function", "[LimitedSizeBag]") {
    LimitedSizeBag<int> b;

    b.add(1);
    REQUIRE(b.contains(1));
    REQUIRE_FALSE(b.contains(5));
}