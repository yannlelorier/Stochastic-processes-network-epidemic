/*
    Example of using a class with SFML functions
    To compile link the libraries:
         -lsfml-graphics -lsfml-window -lsfml-system
*/

//TODO gillespie implementation here
//use std::exponential_distribution for per-edge tau (infection rate)

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "GraphViewer.h"
#include "AVLGraph.h"
#include "Edge.h"

// Define a maximum limit for the random numbers
#define MAX 200

void menu(AVLGraph<int> * tree);
void insertPresets(AVLGraph<int> * tree);
void test_graph();
void edge_test();
int gillespie(std::vector<GraphNode<int> > _graph, double _gamma, int * initial_infected_nodes, int _max_t);
std::vector<GraphNode<int> * > getAtRisk(std::vector<Edge<int> * > * graph, int graphSize);
std::vector<GraphNode<int> * > getInfected(std::vector<Edge<int> * > * graph, int graphSize);
// void setRandomInfected(std::vector<Edge<int> * > * graph, std::vector<GraphNode<int> * > * infected);
// void insertRandom(AVLTree<int> * tree);

int main()
{
    // AVLGraph<int> tree;
    // GraphViewer viewer("Covid-19 Simulation", "JosefinSans-Regular.ttf", &menu, &tree);

    // viewer.windowListener();

    //dev purposes only
    
    //setting nodes
    GraphNode<int> node0;
    GraphNode<int> node1;
    GraphNode<int> node2;
    GraphNode<int> node3;
    GraphNode<int> node4;
    GraphNode<int> node5;

    //initial infections
    node0.infect();
    node2.infect();

    //setting connections

    Edge<int> edge0 (&node0, &node1);
    Edge<int> edge1 (&node1, &node4);
    Edge<int> edge2 (&node4, &node2);
    Edge<int> edge3 (&node2, &node5);
    Edge<int> edge4 (&node2, &node3);
    std::vector<Edge<int> * > graph = {&edge0, &edge1, &edge2, &edge3, &edge4};

    std::vector<GraphNode<int> * > infected;

    infected = getInfected(&graph, 6);



    // gillespie(&graph, 0.4, infected, 5);

    // test_graph();
    
    return 0;
}

void menu(AVLGraph<int> * tree)
{
    GraphNode<int> * node = nullptr;
    int number;
    char ans = 'a';
    bool found = false;

    while (ans != 'q')
    {
        std::cout << "\n== SIR Epidemic - Gillespie Algorithm ==\n";
        std::cout << "\tf. Fill the graph with preset data\n";
        std::cout << "\ts. Slow the simulation\n"; //TODO slow simulation
        std::cout << "\tc. Clear the tree\n";
        std::cout << "\tp. Pause the simulation\n"; //TODO pause simulation
        std::cout << "\tp. Print the log up to this point\n"; //TODO log
        std::cout << "\tq. Quit the program\n";
        std::cout << "Enter your selection: ";
        std::cin >> ans;

        switch (ans)
        {
            case 'f':
                insertPresets(tree);
                break;
            case 's':
                std::cout << "Slowing the simulation down...\n ";
                break;
            case 'c':
                tree->clear();
                break;
            case 'p':
                std::cout << "Pausing simulation" << std::endl;
                // tree->printInOrder();
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

// void insertRandom(AVLTree<int> * tree)
// {
//     int amount;
//     int number;

//     // Initialize the random seed. Hopefully this will not be done too often
//     srand( (unsigned int) time(NULL) );

//     // Input the number of elements to insert
//     std::cout << "\tEnter amount of random numbers to insert: ";
//     std::cin >> amount;

//     std::cout << "\tInserting: ";
//     for (int i=0; i<amount; i++)
//     {
//         // Generate a random number
//         number = rand() % MAX + 1;
//         std::cout << number << ", ";
//         tree->insert(number);
//     }
//     std::cout << std::endl;
// }

void insertPresets(AVLGraph<int> * graph)
{
    GraphNode<int> node0;
    GraphNode<int> node1;
    GraphNode<int> node2;
    GraphNode<int> node3;
    
    std::vector<GraphNode<int> > preset_graph = {&node0, &node1, &node2, &node3};
    int preset_size = preset_graph.size();
    // int preset_size = sizeof preset_data / sizeof preset_data[0];

    std::cout << "\tInserting: ";
    for (int i=0; i<preset_size; i++)
    {
        std::cout << preset_graph[i].getindex() << ", ";
        graph->insert(&preset_graph[i]);
    }
    std::cout << std::endl;
}

//inputs: the graph, recovery rate (gamma), initial infections (pointers to the nodes passed here)
// and max number of iterations for the simulation
int gillespie(std::vector<Edge<int> * > * graph, double gamma, std::vector<GraphNode<int> * > * infectedNodes, int maxt, int graphSize)
{
    int susc = graphSize - infectedNodes->size(); //susceptible population
    int infe = infectedNodes->size(); //infected population
    int reco = 0; //recovered population, assuming that at the beginning of the algorithm no people have been recovered.

    int iteration = 0; //actual iteration of the algorithm

    std::vector<GraphNode<int> * > at_risk = getAtRisk(graph, graphSize);


    return 0;
}


std::vector<GraphNode<int> * >  getAtRisk(std::vector<Edge<int> * > * graph, int graphSize)
{
    std::vector<GraphNode<int> * > at_risk;

    for (int i = 0; i < graphSize; i++)
    {
        std::vector<GraphNode<int> * > nodes = (*graph)[i]->getConnectedNodes();
        if (nodes[0]->isInfected() && std::find(at_risk.begin(), at_risk.end(), nodes[1])==at_risk.end())
            at_risk.push_back(nodes[1]);
        else if (nodes[1]->isInfected() && std::find(at_risk.begin(), at_risk.end(), nodes[0])==at_risk.end())
            at_risk.push_back(nodes[0]);
    }

    return at_risk;
    
}

std::vector<GraphNode<int> * > getInfected(std::vector<Edge<int> * > * graph, int graphSize)
{
    std::vector<GraphNode<int> * >  infected;

    for (int i = 0; i < graphSize; i++)
    {
        std::vector<GraphNode<int> * > nodes = (*graph)[i]->getConnectedNodes();
        if (nodes[0]->isInfected() && std::find(infected.begin(), infected.end(), nodes[0])==infected.end())
            infected.push_back(nodes[0]);
        else if (nodes[1]->isInfected() && std::find(infected.begin(), infected.end(), nodes[1])==infected.end())
            infected.push_back(nodes[1]);
    }

    return infected;
}

void test_graph()
{
    GraphNode<int> node0;
    GraphNode<int> node1;
    GraphNode<int> node2;
    GraphNode<int> node3;
    GraphNode<int> node4;

    Edge<int> edge0 (&node0, &node2);
    Edge<int> edge1 (&node0, &node3);
    Edge<int> edge2 (&node1, &node2);
    Edge<int> edge3 (&node2, &node1);
    Edge<int> edge4 (&node2, &node3);
    Edge<int> edge5 (&node1, &node4);
    std::vector<Edge<int> * > edges;
    edges.push_back(&edge0);
    edges.push_back(&edge1);
    edges.push_back(&edge2);
    edges.push_back(&edge3);
    edges.push_back(&edge4);
    edges.push_back(&edge5);

    std::cout << "Edges creation: " <<  edge0.howMany() << std::endl;
    std::cout << "Nodes creation: " <<  node0.howMany() << std::endl;

    for (int i = 0; i < edge0.howMany(); i++){
        std::vector<GraphNode<int> * > nodes = edges[i]->getConnectedNodes();
        std::cout << "Edge " << i << " has index " << edges[i]->getindex() <<  " and nodes " << nodes[0]->getindex() << " " << nodes[1]->getindex() << std::endl;
    }

}
