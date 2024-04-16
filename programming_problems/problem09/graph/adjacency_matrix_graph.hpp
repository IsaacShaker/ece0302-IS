#ifndef _ADJACENCY_MATRIX_GRAPH_H_
#define _ADJACENCY_MATRIX_GRAPH_H_

#include <set>
#include <unordered_map>
#include <vector>

#include "abstract_graph.hpp"

template <typename LabelType>
class AdjacencyMatrixGraph : public AbstractGraph<LabelType> {
   public:
    AdjacencyMatrixGraph();

    int getNumVertices() const;

    int getNumEdges() const;

    bool add(LabelType start, LabelType end);

    bool remove(LabelType start, LabelType end);

    void depthFirstTraversal(LabelType start, void visit(LabelType&));

    void breadthFirstTraversal(LabelType start, void visit(LabelType&));

   private:
    // store the vertices as key and their index (for the adjaceny matrix) as a value
    // this allows us to index the vector regardless of the LabelType
    std::unordered_map<LabelType, int> label_to_index;
    // store indexes of removed vertices.
    std::set<int> availableIndicies;
    std::vector<std::vector<bool>> adjacencyMatrix;
    std::size_t numEdges;

    void expandMatrix();
    bool checkDisconnect(LabelType vertice);
};

#include "adjacency_matrix_graph.tpp"

#endif
