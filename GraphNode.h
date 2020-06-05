#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <iostream>
#include <vector>
#include "ObjectCounter.h"

template<typename T>
size_t 
Counter<T>::count = 0;

template <class T>
class GraphNode {
    private:
        T index;
        GraphNode<int> * self;
        int height = 1;
        bool infected;
        Counter<GraphNode> c;
        // std::vector<Edge> connections;
    public:
        // GraphNode (T _index) { index = _index; infected = false; }
        //default constructor
        GraphNode ()
        {
            index = howMany() - 1;
            infected = false;
        }
        GraphNode (bool _infected)
        { index = howMany() - 1; infected = _infected; }
        ~GraphNode () {  } //empty vector
        void setindex (T _index) { index = _index; }
        T getindex () { return index; }
        void setHeight (int _height) { height = _height; }
        int getHeight () { return height; }
        void infect() { infected = true; }
        void recover() { infected = false; }
        static size_t howMany() { return Counter<GraphNode<int>>::howMany(); }




        //edges are no longer necessary?
        // std::vector<Edge> getConnections () { return connections; }
        // void setConnection (GraphNode<int> * _node) { 
        //     //look for equivalent edge
        //     //if exists, point to that one
        //     //vector<* Edge>

        //     edge_t newEdge;
        //     newEdge.connected_to[0] = self;
        //     newEdge.connected_to[1] = _node;
        //     newEdge.tau = 0.04;
        //     connections.push_back(newEdge);
        // }
};
#endif
