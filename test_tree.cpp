/*
    Example of using a class with SFML functions
    To compile link the libraries:
         -lsfml-graphics -lsfml-window -lsfml-system
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GraphViewer.h"
#include "AVLGraph.h"

// Define a maximum limit for the random numbers
#define MAX 200

void menu(AVLGraph<int> * tree);
void insertPresets(AVLGraph<int> * tree);
void insertRandom(AVLGraph<int> * tree);

int main()
{
    AVLGraph<int> tree;
    GraphViewer viewer("AVL Tree Viewer", "JosefinSans-Regular.ttf", &menu, &tree);

    viewer.windowListener();
    
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
        std::cout << "\n== Binary Tree Test Menu ==\n";
        std::cout << "\tf. Fill the tree with preset data\n";
        std::cout << "\tr. Fill the tree with random data\n";
        std::cout << "\ti. Insert a new number to the tree\n";
        std::cout << "\ts. Search for a number in the tree\n";
        std::cout << "\td. Delete a number from the tree\n";
        std::cout << "\tc. Clear the tree\n";
        std::cout << "\tp. Print the data in the tree In-order\n";
        std::cout << "\tm. Get the smallest number in the tree\n";
        std::cout << "\tl. Get the number of leaves in the tree\n";
        std::cout << "\tq. Quit the program\n";
        std::cout << "Enter your selection: ";
        std::cin >> ans;

        switch (ans)
        {
            case 'f':
                insertPresets(tree);
                break;
            case 'r':
                insertRandom(tree);
                break;
            case 'i':
                std::cout << "\tEnter the new number to insert: ";
                std::cin >> number;
                tree->insert(number);
                break;
            case 's':
                std::cout << "\tEnter the number to search for: ";
                std::cin >> number;
                found = tree->search(number);
                std::cout << "\tNumber: " << number << " was " << (found ? "found" : "NOT found") << " in the tree" << std::endl;
                break;
            case 'd':
                std::cout << "\tEnter the new number to delete: ";
                std::cin >> number;
                tree->remove(number);
                break;
            case 'c':
                tree->clear();
                break;
            case 'p':
                tree->printInOrder();
                break;
            case 'm':
                node = tree->getMin();
                std::cout << "\tSmallest number: " << node->getData() << std::endl;
                break;
            case 'l':
                number = tree->countLeaves();
                std::cout << "\tNumber of leaves: " << number << std::endl;
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

void insertRandom(AVLGraph<int> * tree)
{
    int amount;
    int number;

    // Initialize the random seed. Hopefully this will not be done too often
    srand( (unsigned int) time(NULL) );

    // Input the number of elements to insert
    std::cout << "\tEnter amount of random numbers to insert: ";
    std::cin >> amount;

    std::cout << "\tInserting: ";
    for (int i=0; i<amount; i++)
    {
        // Generate a random number
        number = rand() % MAX + 1;
        std::cout << number << ", ";
        tree->insert(number);
    }
    std::cout << std::endl;
}

void insertPresets(AVLGraph<int> * tree)
{
    //int preset_data[] = {9, 23, 5, 12, 7, 40, 18, 13, 14, 15, 29, 16, 34, 1, 39};
    int preset_data[] = {17, 36, 45, 144, 44, 38, 178, 139, 199, 166, 70, 32, 178, 129};

    int preset_size = sizeof preset_data / sizeof preset_data[0];

    std::cout << "\tInserting: ";
    for (int i=0; i<preset_size; i++)
    {
        std::cout << preset_data[i] << ", ";
        tree->insert(preset_data[i]);
    }
    std::cout << std::endl;
}
