/*------------------------------------------------- GraphNode.cpp --------
    |   Purpose: GraphNode class, contains the constructor as well as
    |       some useful functions to get or set certain values.
    |
    |   Developers:  
    |       Carlos García - https://github.com/cxrlos
    |       Victor Coeto - https://github.com/vcoetoG
    |       Yann Le Lorier - https://github.com/yannlelorier
    |
    *-------------------------------------------------------------------*/

#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <iostream>
#include <vector>
#include "ObjectCounter.h"

template <class T>
class GraphNode {
    private:
        T index;
        int height = 1;
        bool infected;
        double tau;
        int infectedNeighbors;
        sf::Vector2f pos;
        Counter<GraphNode<int> > c;
    public:
        GraphNode (){ // Constructor
            index = howMany() - 1;
            infected = false;
            infectedNeighbors = 0;
            tau = 0.4;
            pos = sf::Vector2f (0,0);
        }

        GraphNode (bool _infected){ index = howMany() - 1; infected = _infected; }
        ~GraphNode () {  } // Empty vector
        void setindex (T _index) { index = _index; }
        T getindex () { return index; }
        void setHeight (int _height) { height = _height; }
        int getHeight () { return height; }
        double getTau() { return tau; }
        void setTau(double _tau) { tau = _tau; }
        bool isInfected() { return infected; }
        void neighborInfected() { infectedNeighbors++; }
        int getInfectedNeigh() {return infectedNeighbors;}
        void setPos(sf::Vector2f _pos) { pos = _pos; }
        sf::Vector2f getPos () {return pos;}
        void infect() { infected = true; }
        void recover() { infected = false; }
        static size_t howMany() { return Counter<GraphNode<int>>::howMany(); }

};
#endif
