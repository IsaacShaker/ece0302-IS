#define CATCH_CONFIG_MAIN
#include "array_list.hpp"
#include "catch.hpp"

// force class expansion
template class ArrayList<int>;

TEST_CASE("Test", "[ArrayList]") {
    ArrayList<int> list;
}
