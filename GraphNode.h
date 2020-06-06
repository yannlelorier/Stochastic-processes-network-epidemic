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
        int height = 1;
        bool infected;
        Counter<GraphNode<int> > c;
    public:
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
};
#endif
