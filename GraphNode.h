#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <iostream>

template <class T>
class GraphNode {
    private:
        T data;
        int height = 1;
        GraphNode<T> * left = nullptr;
        GraphNode<T> * right = nullptr;
    public:
        GraphNode () {}
        GraphNode (T _data) { data = _data; }
        ~GraphNode () { left = nullptr; right = nullptr; }
        void setData (T _data) { data = _data; }
        T getData () { return data; }
        void setLeft (GraphNode<T> * _node) { left = _node; }
        void setRight (GraphNode<T> * _node) { right = _node; }
        GraphNode<T> * getLeft () { return left; }
        GraphNode<T> * getRight () { return right; }
        void setHeight (int _height) { height = _height; }
        int getHeight () { return height; }
};
#endif