/*
    Example of using a class with SFML functions
    To compile link the libraries:
         -lsfml-graphics -lsfml-window -lsfml-system
*/

//TODO gillespie implementation here
//use std::exponential_distribution for per-edge tau (infection rate)

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <math.h>
#include <random>
#include "GraphViewer.h"
#include "AVLGraph.h"
#include "Edge.h"

// Define a maximum limit for the random numbers
#define MAX 200

void menu(AVLGraph<int> * tree);
void insertPresets(AVLGraph<int> * tree);
void test_graph();
void nodeCoordinates(double xCenter, double yCenter, double radius, int steps, std::vector<GraphNode<int> * > * graph);
void edge_test();
int gillespie(std::vector<Edge<int> * > * _graph, double tau ,double _gamma, int _max_t, int graphSize); //NOTE graphSize
void getAtRisk(std::vector<Edge<int> * > * graph, int * susc, std::vector<GraphNode<int> * > * at_risk);
void getInfected(std::vector<Edge<int> * > * graph, std::vector<GraphNode<int> * > * infected);
// void setRandomInfected(std::vector<Edge<int> * > * graph, std::vector<GraphNode<int> * > * infected);
// void insertRandom(AVLTree<int> * tree);

int main()
{
    AVLGraph<int> avlGraph;
    //setting nodes
    GraphNode<int> node0;
    GraphNode<int> node1;
    GraphNode<int> node2;
    GraphNode<int> node3;
    GraphNode<int> node4;
    GraphNode<int> node5;
    GraphNode<int> node6;
    std::vector<GraphNode<int> * > nodes = {&node0, &node1, &node2,&node3,&node4,&node5, &node6};

    //initial infections
    node0.infect();
    node2.infect();

    //setting connections

    Edge<int> edge0 (&node0, &node1);
    Edge<int> edge1 (&node1, &node4);
    Edge<int> edge2 (&node4, &node2);
    Edge<int> edge3 (&node2, &node5);
    Edge<int> edge4 (&node2, &node3);
    Edge<int> edge5 (&node6, &node5);
    std::vector<Edge<int> * > graph = {&edge0, &edge1, &edge2, &edge3, &edge4, &edge5};

    avlGraph.setSimulationGraph(&graph);
    nodeCoordinates(50, 50, 50, node6.howMany(), &nodes);
    
    GraphViewer viewer("Covid-19 Simulation", "Font.otf", &menu, &avlGraph);

    viewer.windowListener();

    //dev purposes only
	

    // test_graph();
    
    return 0;
}

void menu(AVLGraph<int> * tree)
{
    int number;
    char ans = 'a';

    while (ans != 'q')
    {
        std::cout << "\n== SIR Epidemic - Gillespie Algorithm ==\n";
        std::cout << "\tr. Run the simulation\n"; 
        std::cout << "\ts. Slow the simulation\n"; //TODO slow simulation
        std::cout << "\tc. Clear the tree\n";
        std::cout << "\tp. Pause the simulation\n"; //TODO pause simulation
        std::cout << "\tp. Print the log up to this point\n"; //TODO log
        std::cout << "\tq. Quit the program\n";
        std::cout << "Enter your selection: ";
        std::cin >> ans;

        switch (ans)
        {
            case 'r':
                std::cout << "Running...\n ";
                gillespie(tree->getSimulationGraph(), 0.3, 0.40, 5, 6);
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


//inputs: the graph, recovery rate (gamma), initial infections (pointers to the nodes passed here)
// and max number of iterations for the simulation
int gillespie(std::vector<Edge<int> * > * graph, double tau, double gamma, int maxt, int graphSize)
{

    std::vector<GraphNode<int> * > infectedNodes;
    std::vector<GraphNode<int> * > at_risk = {};

    //Getting initial infections
    getInfected(graph, &infectedNodes);

    std::cout << "Infected Nodes:" << std::endl;

    for (int i = 0; i < infectedNodes.size(); i++)
    {
        std::cout << "\tNode " << infectedNodes[i]->getindex() << std::endl;
    }

    int susc = graphSize - infectedNodes.size(); //susceptible population 
    int infe = infectedNodes.size(); //infected population
    double totalInfectionRate = 0;
    double totalRecoveryRate = 0;
    double totalRate = 0;
    double time;


    // std::cout << "In iteration " << iteration << std::endl;

    getAtRisk(graph, &susc, &at_risk);

    std::cout << "At risk nodes:" << std::endl;
    for (int i = 0; i < at_risk.size(); i++)
    {
        std::cout << "Node" << at_risk[i]->getindex();
        std::cout << " | Changing tau" << std::endl;
        at_risk[i]->setTau(tau*at_risk[i]->getInfectedNeigh());
        totalInfectionRate += at_risk[i]->getTau();
    }
    totalRecoveryRate = gamma * infectedNodes.size();
    totalRate = totalInfectionRate + totalRecoveryRate;
    
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::exponential_distribution<double> expDist (totalRate); //exponential distribution

    time = expDist(generator); //applying exponential distribution

    while (time < maxt && totalRate > 0)
    {
        //taken from  https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::default_random_engine genInt;
        std::uniform_real_distribution<double> realDis(0, totalRate);
        std::uniform_int_distribution<int> intDis(0, infectedNodes.size());

        double r = realDis(gen);
        int randIndex = intDis(genInt);
        if (r < totalRecoveryRate)
        {
            std::cout << "Node " << infectedNodes[randIndex]->getindex() << " has recovered" << std::endl;
            infectedNodes[randIndex]->recover();

            for (int i = 0; i < graph->size(); i++)
            {
                std::vector<GraphNode<int> * > nodes = (*graph)[i]->getConnectedNodes();
                if (nodes[0]==infectedNodes[randIndex])
                {
                    nodes[1]->setTau(nodes[1]->getTau()-tau);
                }
                else if (nodes[1]==infectedNodes[randIndex])
                {    
                    nodes[0]->setTau(nodes[1]->getTau()-tau);
                }
                nodes.clear();
            }
            
            infectedNodes.erase(infectedNodes.begin() + randIndex);
            //or
            infe--;
            getInfected(graph, &infectedNodes); //is this redundant?

        }else
        {
            //TODO extract a node from at_risk with prob=at_risk[i]/totalInfectionRate
            //leaving it as uniform distribution for testing (for now)
            std::uniform_int_distribution<> atRiskDis(0, at_risk.size());
            randIndex = atRiskDis(genInt);
            // std::cout << "randIndex: " << randIndex << std::endl;
            std::cout << "Node " << at_risk[randIndex]->getindex() << " was infected" << std::endl;
            at_risk[randIndex]->infect();
            infe++;
            // at_risk.erase(at_risk.begin() + randomIndex);
            getInfected(graph, &infectedNodes);
            getAtRisk(graph, &susc, &at_risk);

        }
        susc = at_risk.size();
        for (int i = 0; i < at_risk.size(); i++)
        {
            totalInfectionRate += at_risk[i]->getTau();
        }
        
        totalRecoveryRate = gamma * infectedNodes.size();
        totalRate = totalInfectionRate + totalRecoveryRate;
        std::exponential_distribution<double> expDist (totalRate);
        time = expDist(generator);
    }
    std::cout << "End of algorithm..." << std::endl;
    std::cout << "Susceptible population: " << susc << std::endl;
    std::cout << "Infected population: " << infe << std::endl;

    return 0;
}


void getAtRisk(std::vector<Edge<int> * > * graph, int * susc, std::vector<GraphNode<int> * > * at_risk)
{

    for (int i = 0; i < graph->size(); i++)
    {
        std::vector<GraphNode<int> * > nodes = (*graph)[i]->getConnectedNodes();
        if (nodes[0]->isInfected() && std::find(at_risk->begin(), at_risk->end(), nodes[1])==at_risk->end())
        {
            at_risk->push_back(nodes[1]);
            (*susc)--;
            nodes[1]->neighborInfected();
        }
        else if (nodes[1]->isInfected() && std::find(at_risk->begin(), at_risk->end(), nodes[0])==at_risk->end())
        {    
            at_risk->push_back(nodes[0]);
            (*susc)--;
            nodes[0]->neighborInfected();
        }
        nodes.clear();
    }
    
}

void getInfected(std::vector<Edge<int> * > * graph, std::vector<GraphNode<int> * > * infected)
{
    for (int i = 0; i < graph->size(); i++)
    {
        std::vector<GraphNode<int> * > nodes = (*graph)[i]->getConnectedNodes();
        if (nodes[0]->isInfected() && std::find(infected->begin(), infected->end(), nodes[0])==infected->end())
            infected->push_back(nodes[0]);
        else if (nodes[1]->isInfected() && std::find(infected->begin(), infected->end(), nodes[1])==infected->end())
            infected->push_back(nodes[1]);
        nodes.clear();
    }
}

void test_graph()
{
    GraphNode<int> node0;
    GraphNode<int> node1;
    GraphNode<int> node2;
    GraphNode<int> node3;
    GraphNode<int> node4;

    int steps = node0.howMany();

    std::vector<GraphNode<int> * > graph = {&node0, &node1, &node2, &node3, &node4};   
    
    nodeCoordinates(0,0,50,steps, &graph);

    /*
    // node1 {n0}{n1}{n2}
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

    for (int i = 0; i < edge0.howMany()-1; i++){
        std::vector<GraphNode<int> * > nodes = edges[i]->getConnectedNodes();
        std::cout << "Edge " << i << " has index " << edges[i]->getindex() <<  " and nodes " << nodes[0]->getindex() << " " << nodes[1]->getindex() << std::endl;
    }
    */

}

// To change the radius, xCenter and yCenter variables, modify the values in the config.txt file
void nodeCoordinates(double xCenter, double yCenter, double radius, int steps, std::vector<GraphNode<int> * > * graph){ 
	static double PI = 4*atan(1);
	double change = (2*PI)/steps;
	double circleCounter = change;
    double x,y;
    sf::Vector2f pos;
    steps = 0;
    x = y = 0;

	for(circleCounter; circleCounter <= 2*PI; circleCounter += change){
        x = xCenter + (radius * (cos(circleCounter)));
		y = yCenter + (radius * (sin(circleCounter)));
        pos = sf::Vector2f(x,y);
        (*graph)[steps]->setPos(pos);
        std::cout << std::fixed << std::setprecision(20) << "Node " << steps <<  "\tX = " <<  pos.x << "\nY = " << pos.y << "\n" << std::endl;
        steps ++;
	}
}
