#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <iostream>
#define MAX_NODES 10

struct Edge;

template <class T>
class GraphNode {
    private:
        T index;
        bool infected;
        std::vector<Edge> connections;
        int height;

    public:
        GraphNode (T _index) { index = _index; infected = false; connections = {}; }
        GraphNode (bool is_inf) { infected = is_inf; }
        ~GraphNode () {}
        T getIndex () { return index; }
        int getHeight () { return height; }
        bool isInfected () { return infected; }
        void * getConnections () { return connections; }
        void setIndex (T _index) { index = _index; }
        void infect () { infected = true; }
        void recover () { infected = false; }
};

struct Edge {
    GraphNode<int> connected_to[2];
    double tau;
    double gamma;
};
#endif
