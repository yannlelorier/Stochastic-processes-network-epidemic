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
#include "GraphViewer.h"
#include "AVLGraph.h"
#include "Edge.h"

// Define a maximum limit for the random numbers
#define MAX 200

void menu(AVLGraph<int> * tree);
void insertPresets(AVLGraph<int> * tree);
void test_graph();
int gillespie(std::vector<GraphNode<int> > _graph, double _tau, double _gamma, int * initial_infected_nodes, int _max_t);
// void insertRandom(AVLTree<int> * tree);

int main()
{
    // AVLGraph<int> tree;
    // GraphViewer viewer("Covid-19 Simulation", "JosefinSans-Regular.ttf", &menu, &tree);

    // viewer.windowListener();

    // //Nodes:
    // GraphNode<int> node0(0);
    // GraphNode<int> node1(1);
    // GraphNode<int> node2(2);
    // GraphNode<int> node3(3);

    // std::vector<GraphNode <int> > graph = {node0, node1, node2, node3};

    // //Connections
    // graph[0].setConnection(&node2);
    // graph[2].setConnection(&node0);
    // graph[1].setConnection(&node2);
    // graph[2].setConnection(&node1);
    // graph[1].setConnection(&node3);
    // graph[3].setConnection(&node1);
    // double tau = 0.3;
    // double gamma = 0.2;
    // int * inf = nullptr;
    // inf = new int[1];
    // std::cout << "sizeof inf " << sizeof inf << std::endl;
    // for (int i = 0; i < (sizeof inf); i++)
    // {
    //     inf[i] = 0;
    // }
    


    // gillespie(graph, tau, gamma, inf, 5);

    // //freeing memory
    // // delete [] inf;
    // delete[] inf;

    //dev purposes only
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
    GraphNode<int> node0(0);
    GraphNode<int> node1(1);
    GraphNode<int> node2(2);
    GraphNode<int> node3(3);
    
    std::vector<GraphNode<int> > preset_graph = {node0, node1, node2, node3};
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

//inputs: the graph, per-edge transmission rate (tau), recovery rate (gamma), initial infections (index of the nodes passed here)
// and max number of iterations for the simulation
int gillespie(std::vector<GraphNode<int> > _graph, double _tau, double _gamma, int * initial_infecteds, int _max_t)
{
    std::cout << "Simulation goes here" << std::endl;
    for (int i = 0; i < sizeof initial_infecteds; i++)
    {
        std::cout << "Infected " << i << ": " << initial_infecteds[i] << std::endl;
    }
    
    return 0;
}

void test_graph()
{
    GraphNode<int> node0;
    GraphNode<int> node1;
    GraphNode<int> node2;
    GraphNode<int> node3;
    GraphNode<int> node4;

    std::vector<GraphNode<int> * >  nodes;
    nodes.push_back(&node0);
    nodes.push_back(&node1);
    nodes.push_back(&node2);
    nodes.push_back(&node3);
    nodes.push_back(&node4);
    printf("%d\n", nodes[3]->getindex());

    std::cout << node3.howMany() << std::endl;

    for (int i = 0; i < node3.howMany(); i++){
        printf("Node %d has index %d\n",i, nodes[i]->getindex());
    }
}

void edge_test(){

    GraphNode<int> node0;
    GraphNode<int> node1;
    GraphNode<int> node2;
    GraphNode<int> node3;
    GraphNode<int> node4;

    std::vector<Edge<int> > edges;
    Edge<int> edge0 (&node0, &node2);
    Edge<int> edge1 (&node1, &node3);
    Edge<int> edge2 (&node1, &node2);
    Edge<int> edge3 (&node2, &node1);
    Edge<int> edge4 (&node2, &node3);


    for (int i = 0; i < node3.howMany(); i++){
        std::vector<GraphNode<int> > nodes = edges[i].getConnectedNodes();
        std::cout << "Edge" << i << "has index" << edges[i].getindex() <<  "and nodes " << nodes[0] << " " << nodes[1] << std::endl;
    }
}