#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iomanip>
#include "GraphNode.h"

template <class T>
class AVLGraph {
    private:
		std::vector<GraphNode<int> > nodes;
        // TreeNode<T> * root = nullptr;
        int indent_increase = 6;


    public:
        AVLGraph () {}
        ~AVLGraph () { clear(); }
        void clear  ();
        // void insert (T _data);
        void insert(GraphNode<T> * _node);
};

template <class T>
void AVLGraph<T>::clear()
{
    //TODO clear graph
	nodes.clear();
}

template <class T>
void AVLGraph<T>::insert(GraphNode<T> * _node)
{
    //TODO insert node
	nodes.push_back(*_node);
}

#endif
