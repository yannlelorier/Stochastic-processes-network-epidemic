/*------------------------------------------------- Edge.h ---------------
    |   Purpose: Functions as the constructor for the Edge class and 
    |       defines many functions used to get and set different values.
    |
    |   Developers:  
    |       Carlos García - https://github.com/cxrlos
    |       Victor Coeto - https://github.com/vcoetoG
    |       Yann Le Lorier - https://github.com/yannlelorier
    |
    *-------------------------------------------------------------------*/

#ifndef EDGE_H
#define EDGE_H

#include "GraphNode.h"

template <class T>
class Edge{
    private:
        T index;
        std::vector<GraphNode<int> * > connected_to;
        double tau;
        Counter<Edge> c;
    public: 
        //constructor
        Edge(GraphNode<int> * _node1, GraphNode<int> * _node2) 
        {
            tau = 0.4;
            index = howMany() - 1;
            if (_node1->getindex() < _node2->getindex())
            {
                connected_to.push_back(_node1);
                connected_to.push_back(_node2);
            }else
            {
                connected_to.push_back(_node2);
                connected_to.push_back(_node1);
            }
        
        }
        //no method for setting edge needed because the connections are made upon object creation
        
        //Change the infection rate for a connection
        T getindex() { return index; }
        std::vector<GraphNode<int> * > getConnectedNodes() { return connected_to; }
        double getTau() { return tau; }
        void setTau(double _tau) { tau = _tau; }

        //Count how many objects have been created
        static size_t howMany() { return Counter<Edge>::howMany(); }
};

#endif