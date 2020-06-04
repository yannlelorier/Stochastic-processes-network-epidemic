/*
    Example of using a class with SFML functions
    To compile link the libraries:
         -lsfml-graphics -lsfml-window -lsfml-system
*/

//TODO gillespie implementation here

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GraphViewer.h"
#include "AVLGraph.h"

// Define a maximum limit for the random numbers
#define MAX 200

void menu(AVLGraph<int> * tree);
void insertPresets(AVLGraph<int> * tree);
void test_graph();
// void insertRandom(AVLTree<int> * tree);

int main()
{
    // AVLGraph<int> tree;
    // GraphViewer viewer("Covid-19 Simulation", "JosefinSans-Regular.ttf", &menu, &tree);

    // viewer.windowListener();

    test_graph();
    
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
    //int preset_data[] = {9, 23, 5, 12, 7, 40, 18, 13, 14, 15, 29, 16, 34, 1, 39};
    // int preset_data[] = {17, 36, 45, 144, 44, 38, 178, 139, 199, 166, 70, 32, 178, 129};
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

void test_graph()
{
    //Nodes:
    GraphNode<int> node0(0);
    GraphNode<int> node1(1);
    GraphNode<int> node2(2);
    GraphNode<int> node3(3);

    std::vector<GraphNode <int> > graph = {node0, node1, node2, node3};

    //Connections
    graph[0].setConnection(&node2);
    graph[2].setConnection(&node0);
    graph[1].setConnection(&node2);
    graph[2].setConnection(&node1);
    graph[1].setConnection(&node3);
    graph[3].setConnection(&node1);

    for (int i = 0; i < graph.size(); i++)
    {
        std::cout << "Node " << graph[i].getindex() << " connected to: \n";
        std::vector<Edge> connections = graph[i].getConnections();
        for (int j = 0; j < connections.size(); j++)
        {
            std::cout << "\t- " << "Node " << connections[j].connected_to[1] << std::endl;
        }
        
    }
    

    

}
