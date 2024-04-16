#ifndef _ADJACENCY_LIST_GRAPH_H_
#define _ADJACENCY_LIST_GRAPH_H_

#include <set>
#include <unordered_map>

#include "abstract_graph.hpp"

template <typename LabelType>
class AdjacencyListGraph : public AbstractGraph<LabelType> {
   public:
    AdjacencyListGraph();

    int getNumVertices() const;

    int getNumEdges() const;

    bool add(LabelType start, LabelType end);

    bool remove(LabelType start, LabelType end);

    void depthFirstTraversal(LabelType start, void visit(LabelType&));

    void breadthFirstTraversal(LabelType start, void visit(LabelType&));

   private:
    std::unordered_map<LabelType, std::set<LabelType>> adjacencyList;
    std::size_t numEdges;
};

#include "adjacency_list_graph.tpp"

#endif
