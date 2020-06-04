#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <iostream>
#include <vector>

template <class T>
class GraphNode;

typedef struct Edge{
    GraphNode<int> * connected_to[2];
    double tau;
    //double gamma;
}edge_t;

template <class T>
class GraphNode {
    private:
        T index;
        GraphNode<int> * self;
        int height = 1;
        bool infected;
        std::vector<Edge> connections;
    public:
        GraphNode () {}
        GraphNode (T _index) { index = _index; infected = false; connections = {}; }
        ~GraphNode () {  } //empty vector
        void setindex (T _index) { index = _index; }
        T getindex () { return index; }
        void setHeight (int _height) { height = _height; }
        int getHeight () { return height; }
        void infect() { infected = true; }
        void recover() { infected = false; }
        std::vector<Edge> getConnections () { return connections; }
        void setConnection (GraphNode<int> * _node) { 
            edge_t newEdge;
            newEdge.connected_to[0] = self;
            newEdge.connected_to[1] = _node;
            newEdge.tau = 0.04;
            connections.push_back(newEdge);
        } //TODO check if this correct?
};



#endif
