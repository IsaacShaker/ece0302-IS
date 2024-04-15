#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "adjacency_list_graph.hpp"
#include "catch.hpp"

TEST_CASE("Test Construction", "[construction]") {
    AdjacencyListGraph<int> listGraph;
    REQUIRE(listGraph.getNumVertices() == 0);
}
