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
    if (adjacencyList.count(start) == 0 || adjacencyList[start].count(end) == 0) {
        return false;
    }

    // if an edge between start and end exists
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