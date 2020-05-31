#include <iostream>
#include <string>
#include <vector>
#include "GraphNode.h"
#include "GraphViewer.h"


int gillespie(std::vector<GraphNode<int> > &graph, double tau, double gamma, std::vector<int> inf_nodes, int t_max);

int main()
{
    // int nodes = 4;
    // std::vector<GraphNode<int> > graph; //the initial graph, each node representing a person
    // double tau = 0.4; //transmission rate
    // double gamma = 0.4; //recovery rate
    // std::vector<int> inf_nodes = {1, 2}; //index of the infected nodes
    // int t_max = 4; //how many iterations of the algorithm is going to be run
    // gillespie(graph, tau, gamma, inf_nodes, t_max);

    std::vector<GraphNode <int> > graph;

    GraphViewer viewer("Covid-19 Simulator", "JosefinSans-Regular.ttf", &menu, &graph);

    viewer.windowListener();

    return 0;
}

int gillespie(std::vector<GraphNode<int> > &graph, double tau, double gamma, std::vector<int> inf_nodes, int t_max)
{
    int time = 0; //iteration through time
    int tot_sus = MAX_NODES - inf_nodes.size(); //S
    int tot_inf = inf_nodes.size(); //I
    int tot_rec = 0; //R

    //TODO continue algorithm implementation
    

    return 0;
}

void menu(std::vector<GraphNode <int>> * graph)
{
    GraphNode<int> * node = nullptr;
    int number;
    char ans = 'a';
    bool found = false;

    while (ans != 'q')
    {
        std::cout << "\n== Covid-19 Simulator ==\n";
        std::cout << "\ts. Slow the simulation\n";
        std::cout << "\tv. Speed the simulation\n";
        std::cout << "\tc. Clear the graph\n";
        std::cout << "\ti. Get the number of infected nodes\n";
        std::cout << "\tr. Get the number of recovered nodes\n";
        std::cout << "\tu. Get the number of susceptible nodes\n";
        std::cout << "\tq. Quit the program\n";
        std::cout << "Enter your selection: ";
        std::cin >> ans;

        switch (ans)
        {
            case 's':
            //TODO slow simulation
                std::cout << "Slowing simulation\n";
                // std::cout << "\tEnter the number to search for: ";
                // std::cin >> number;
                // found = tree->search(number);
                // std::cout << "\tNumber: " << number << " was " << (found ? "found" : "NOT found") << " in the tree" << std::endl;
                break;
            case 'v':
                //TODO speed simulation
            case 'c':
                // GRAPH->clear();
                break;
            case 'i':
                //TODO print infected nodes
                break;
            case 'u':
                //TODO print susceptible nodes
                break;
            case 'r':
                //TODO print recovered nodes
                break;
            case 'q':
                std::cout << "See you later" << std::endl;
                exit(0);
                break;
            default:
                std::cout << "Invalid option. Try again ..." << std::endl;
                break;
        }
    }
}