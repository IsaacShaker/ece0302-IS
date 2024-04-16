#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "adjacency_matrix_graph.hpp"
#include "catch.hpp"

typedef AdjacencyMatrixGraph<int> Graph;

TEST_CASE("Test Construction", "[construction]") {
    Graph listGraph;
    REQUIRE(listGraph.getNumVertices() == 0);
    REQUIRE(listGraph.getNumEdges() == 0);
}

TEST_CASE("Test Add", "[add]") {
    Graph listGraph;

    REQUIRE(listGraph.add(1, 3));
    REQUIRE(listGraph.getNumEdges() == 1);
    REQUIRE(listGraph.getNumVertices() == 2);
}

TEST_CASE("Test Add with duplicate", "[add]") {
    Graph listGraph;

    REQUIRE(listGraph.add(1, 3));
    REQUIRE_FALSE(listGraph.add(1, 3));
    REQUIRE_FALSE(listGraph.add(3, 1));
    REQUIRE(listGraph.getNumEdges() == 1);
    REQUIRE(listGraph.getNumVertices() == 2);
}

TEST_CASE("Test Remove", "[remove]") {
    Graph listGraph;

    listGraph.add(1, 3);
    REQUIRE(listGraph.remove(1, 3));

    // test undirectional
    listGraph.add(1, 3);
    REQUIRE(listGraph.remove(3, 1));

    REQUIRE(listGraph.getNumEdges() == 0);
    REQUIRE(listGraph.getNumVertices() == 0);
}

TEST_CASE("Test Remove with non existing", "[remove]") {
    Graph listGraph;

    listGraph.add(1, 3);
    REQUIRE_FALSE(listGraph.remove(2, 3));
}