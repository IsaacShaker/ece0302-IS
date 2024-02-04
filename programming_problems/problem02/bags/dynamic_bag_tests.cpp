#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Calling all public members", "[DynamicBag]") {
    DynamicBag<int> b;

    b.add(0);
    b.remove(0);
    b.isEmpty();
    b.getCurrentSize();
    b.clear();
    b.getFrequencyOf(0);
    b.contains(0);
}

TEST_CASE("Test default constructor", "[DynamicBag]") {
    DynamicBag<int> b;

    REQUIRE(b.isEmpty());
    REQUIRE(b.getCurrentSize() == 0);
}

TEST_CASE("Test copy constructor", "[DynamicBag]") {
    DynamicBag<int> b;
    b.add(1);
    b.add(2);
    b.add(3);

    DynamicBag<int> cb(b);

    REQUIRE_FALSE(cb.isEmpty());
    REQUIRE(cb.getCurrentSize() == 3);
    REQUIRE(cb.contains(3));
}

TEST_CASE("Test copy assignment operator", "[DynamicBag]") {
    DynamicBag<int> b;
    b.add(1);
    b.add(2);
    b.add(3);

    DynamicBag<int> cb;

    cb = b;

    REQUIRE_FALSE(cb.isEmpty());
    REQUIRE(cb.getCurrentSize() == 3);
    REQUIRE(cb.contains(3));
}

TEST_CASE("Test add function", "[DynamicBag]") {
    DynamicBag<int> b;

    REQUIRE_FALSE(b.contains(1));
    b.add(1);
    REQUIRE(b.contains(1));
}

TEST_CASE("Test remove function", "[DynamicBag]") {
    DynamicBag<int> b;

    b.add(1);
    b.remove(1);
    REQUIRE_FALSE(b.contains(1));
}

TEST_CASE("Test remove function - Item not in bag", "[DynamicBag]") {
    DynamicBag<int> b;

    b.add(1);
    REQUIRE_FALSE(b.remove(0));
}

TEST_CASE("Test empty function", "[DynamicBag]") {
    DynamicBag<int> b;

    REQUIRE(b.isEmpty());

    b.add(1);
    b.remove(1);
    REQUIRE(b.isEmpty());
}

TEST_CASE("Test getCurrentSize function", "[DynamicBag]") {
    DynamicBag<int> b;

    b.add(1);
    b.add(4);
    b.add(7);
    b.add(9);
    REQUIRE(b.getCurrentSize() == 4);
}

TEST_CASE("Test clear function", "[DynamicBag]") {
    DynamicBag<int> b;

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

TEST_CASE("Test getFrequencyOf function", "[DynamicBag]") {
    DynamicBag<int> b;

    b.add(1);
    b.add(1);
    b.add(1);
    REQUIRE(b.getFrequencyOf(1) == 3);
}

TEST_CASE("Test contains function", "[DynamicBag]") {
    DynamicBag<int> b;

    b.add(1);
    REQUIRE(b.contains(1));
    REQUIRE_FALSE(b.contains(5));
}