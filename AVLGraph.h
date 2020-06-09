#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iomanip>
#include "GraphNode.h"
#include "Edge.h"

template <class T>
class AVLGraph {
    private:
		std::vector<Edge<int> * > * graph = nullptr;
        // TreeNode<T> * root = nullptr;
        int indent_increase = 6;


    public:
        AVLGraph () {}
        ~AVLGraph () { clear(); }
        void clear  ();
        void setSimulationGraph(std::vector<Edge<int> * > * _graph) { graph = _graph; }
        std::vector<Edge<int> * > * getSimulationGraph() { return graph; }
};

template <class T>
void AVLGraph<T>::clear()
{
    //TODO clear graph
	graph->clear();
}

#endif
