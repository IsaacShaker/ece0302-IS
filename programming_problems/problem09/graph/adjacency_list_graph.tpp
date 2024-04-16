#include "adjacency_list_graph.hpp"

template <typename LabelType>
AdjacencyListGraph<LabelType>::AdjacencyListGraph() {
    numEdges = 0;
}

template <typename LabelType>
int AdjacencyListGraph<LabelType>::getNumVertices() const {
    return adjacencyList.size();
}

template <typename LabelType>
int AdjacencyListGraph<LabelType>::getNumEdges() const {
    return numEdges;
}

template <typename LabelType>
bool AdjacencyListGraph<LabelType>::add(LabelType start, LabelType end) {
    // after the inital two vertices are added, one of the labels must already be in the graph, otherwise the addition would create a disconnect
    if (getNumVertices() >= 2 && adjacencyList.count(start) == 0 && adjacencyList.count(end) == 0) {
        return false;
    }
    // self loop
    if (start == end) {
        return false;
    }

    // if start is in the map
    if (adjacencyList.count(start) == 1) {
        // if an edge between start and end exists
        if (adjacencyList[start].count(end) == 1) {
            return false;
        }
    } else {
        adjacencyList[start] = {};
    }
    if (adjacencyList.count(end) == 0) {
        adjacencyList[end] = {};
    }

    adjacencyList[start].insert(end);
    adjacencyList[end].insert(start);

    numEdges++;
    return true;
}

template <typename LabelType>
bool AdjacencyListGraph<LabelType>::remove(LabelType start, LabelType end) {
    // check if edge exists
    if (adjacencyList.count(start) == 0 || adjacencyList[start].count(end) == 0) {
        return false;
    }

    // remove edge from set
    adjacencyList[start].erase(end);
    adjacencyList[end].erase(start);

    // remove vertices if they are no longer connected to anything
    if (adjacencyList[start].empty()) {
        adjacencyList.erase(start);
    }
    if (adjacencyList[end].empty()) {
        adjacencyList.erase(end);
    }
    numEdges--;
    return true;
}

template <typename LabelType>
void AdjacencyListGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

template <typename LabelType>
void AdjacencyListGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}