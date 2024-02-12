#define CATCH_CONFIG_MAIN
#include "array_list.hpp"
#include "catch.hpp"

// force class expansion
template class ArrayList<int>;

TEST_CASE("Test Default Constructor", "[ArrayList]") {
    ArrayList<int> list;
    REQUIRE(list.getLength() == 0);
}

TEST_CASE("Test Copy Constructor", "[ArrayList]") {
    ArrayList<int> list;
    list.insert(0, -1);

    ArrayList<int> list_copy(list);

    REQUIRE(list_copy.getEntry(0) == -1);
}

TEST_CASE("Test Copy Assignment", "[ArrayList]") {
    ArrayList<int> list;
    list.insert(0, -1);

    ArrayList<int> list_copy;

    list_copy = list;

    REQUIRE(list_copy.getEntry(0) == -1);
}

TEST_CASE("Test isEmpty function", "[ArrayList]") {
    ArrayList<int> list;
    list.insert(0, -1);

    REQUIRE_FALSE(list.isEmpty());

    list.remove(0);

    REQUIRE(list.isEmpty());
}

TEST_CASE("Test getLength function", "[ArrayList]") {
    ArrayList<int> list;
    list.insert(0, -1);

    REQUIRE(list.getLength() == 1);

    list.remove(0);

    REQUIRE(list.isEmpty() == 0);
}

TEST_CASE("Test insert function", "[ArrayList]") {
    ArrayList<int> list;
    // test shifting and dynamic memory allocation
    REQUIRE(list.insert(0, -1));
    REQUIRE(list.insert(1, 3));
    REQUIRE(list.insert(1, 2));
    REQUIRE(list.insert(1, 1));

    REQUIRE(list.getLength() == 4);
    REQUIRE(list.getEntry(1) == 1);
    REQUIRE(list.getEntry(2) == 2);
    REQUIRE(list.getEntry(3) == 3);

    // test invalid positions
    REQUIRE_FALSE(list.insert(5, 4));
    REQUIRE_FALSE(list.insert(-2, 9));
}

TEST_CASE("Test remove function", "[ArrayList]") {
    ArrayList<int> list;
    // test shifting and dynamic memory allocation
    list.insert(0, -1);
    list.insert(1, 3);
    list.insert(1, 2);
    list.insert(1, 1);

    // test shifting
    REQUIRE(list.remove(2));
    REQUIRE(list.getEntry(2) == 3);
    REQUIRE(list.getLength() == 3);

    // test invalid positions
    REQUIRE_FALSE(list.remove(5));
    REQUIRE_FALSE(list.remove(-2));
}

TEST_CASE("Test clear function", "[ArrayList]") {
    ArrayList<int> list;
    // test shifting and dynamic memory allocation
    list.insert(0, -1);
    list.insert(1, 3);
    list.insert(1, 2);
    REQUIRE(list.getLength() == 3);

    list.clear();
    REQUIRE(list.getLength() == 0);
}

TEST_CASE("Test getEntry function", "[ArrayList]") {
    ArrayList<int> list;
    // test shifting and dynamic memory allocation
    list.insert(0, -1);
    REQUIRE(list.getEntry(0) == -1);
}

TEST_CASE("Test setEntry function", "[ArrayList]") {
    ArrayList<int> list;
    // test shifting and dynamic memory allocation
    list.insert(0, -1);
    list.setEntry(0, 4);
    REQUIRE(list.getEntry(0) == 4);
}
