#include "adjacency_matrix_graph.hpp"

template <typename LabelType>
AdjacencyMatrixGraph<LabelType>::AdjacencyMatrixGraph() {
    numEdges = 0;
}

template <typename LabelType>
int AdjacencyMatrixGraph<LabelType>::getNumVertices() const {
    return label_to_index.size();
}

template <typename LabelType>
int AdjacencyMatrixGraph<LabelType>::getNumEdges() const {
    return numEdges;
}

template <typename LabelType>
bool AdjacencyMatrixGraph<LabelType>::add(LabelType start, LabelType end) {
    // check if this edge exists
    if (label_to_index.count(start) == 1 && label_to_index.count(end) == 1) {
        if (adjacencyMatrix[label_to_index[start]][label_to_index[end]] == true) {
            return false;
        }
    }

    // check if label not in map, expand matrix to fit new vertices, or reuse old space from previously removed vertices
    if (label_to_index.count(start) == 0) {
        if (availableIndicies.empty() == false) {
            label_to_index[start] = *(availableIndicies.begin());
            availableIndicies.erase(label_to_index[start]);
        } else {
            label_to_index[start] = adjacencyMatrix.size();
            expandMatrix();
        }
    }
    if (label_to_index.count(end) == 0) {
        if (availableIndicies.empty() == false) {
            label_to_index[end] = *(availableIndicies.begin());
            availableIndicies.erase(label_to_index[end]);
        } else {
            label_to_index[end] = adjacencyMatrix.size();
            expandMatrix();
        }
    }

    // create the edge
    adjacencyMatrix[label_to_index[start]][label_to_index[end]] = true;
    adjacencyMatrix[label_to_index[end]][label_to_index[start]] = true;
    numEdges++;
    return true;
}

template <typename LabelType>
bool AdjacencyMatrixGraph<LabelType>::remove(LabelType start, LabelType end) {
    // check if this edge does not exists
    if (label_to_index.count(start) == 0 || label_to_index.count(end) == 0 || adjacencyMatrix[label_to_index[start]][label_to_index[end]] == false) {
        return false;
    }

    // remove edge from matrix
    adjacencyMatrix[label_to_index[start]][label_to_index[end]] = false;
    adjacencyMatrix[label_to_index[end]][label_to_index[start]] = false;

    // check if vertices are disconnected
    if (checkDisconnect(start)) {
        availableIndicies.insert(label_to_index[start]);
        label_to_index.erase(start);
    }
    if (checkDisconnect(end)) {
        availableIndicies.insert(label_to_index[end]);
        label_to_index.erase(end);
    }

    numEdges--;
    return true;
}

template <typename LabelType>
void AdjacencyMatrixGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

template <typename LabelType>
void AdjacencyMatrixGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}

// PRIVATE HELPER METHODS

template <typename LabelType>
void AdjacencyMatrixGraph<LabelType>::expandMatrix() {
    // increases width and length of matrix by 1 EX: 2x2 --> 3x3
    std::vector<bool> newVect(adjacencyMatrix.size(), false);
    adjacencyMatrix.push_back(newVect);

    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        adjacencyMatrix[i].push_back(false);
    }
}

template <typename LabelType>
bool AdjacencyMatrixGraph<LabelType>::checkDisconnect(LabelType vertice) {
    // check if vertice is diconnected from rest of graph
    int matrixSize = adjacencyMatrix.size();
    bool disconnect = true;

    for (int i = 0; i < matrixSize; i++) {
        if (adjacencyMatrix[label_to_index[vertice]][i] == true) {
            disconnect = false;
            break;
        }
    }
    return disconnect;
}