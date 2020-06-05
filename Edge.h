#ifndef EDGE_H
#define EDGE_H

#include "GraphNode.h"

template<typename T>
size_t 
Counter<T>::count = 0;

class Edge{
    int index;
    GraphNode<int> * connected_to[2];
    double tau;
    //constructor
    Edge(GraphNode<int> * _node1, GraphNode<int> * _node2) 
    {
        tau = 0.4;
        index = howMany() - 1;
        if (_node1->getindex() < _node2->getindex())
        {
            connected_to[0] = _node1;
            connected_to[1] = _node2;
        }else
        {
            connected_to[0] = _node2;
            connected_to[1] = _node1;
        }
    
    }
    //no method for setting edge needed because the connections are made upon object creation
    
    //Change the infection rate for a connection
    void setTau(double _tau) { tau = _tau; }

    //Count how many objects have been created
    static size_t howMany() { return Counter<Edge>::howMany(); }
    private:
        Counter<Edge> c;
};

#endif