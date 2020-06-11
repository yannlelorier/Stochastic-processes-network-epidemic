/*------------------------------------------------- Gillespie.cpp --------
    |   Purpose: Serves as the main function, reads the file from the 
    |       .txt input file and then runs the Gillespie algorithm through
    |       the described graph. Throughout the script there are multiple
    |       functions that are described in the following lines.
    |
    |   Functions:
    |       main() - Main driver function
    |       menu() - Runs the selection menu.
    |       readGraph() - Reads the .txt file.
    |       nodeCoordinates() - Based on the number of nodes, it assigns a
    |           set of coordinates for each node.
    |       setRandomInfected() - Sets a random number of nodes to be 
    |           infected and randomly chooses nodes to set the respective
    |           status.
    |       gillespie() - Runs the Gillespie algorithm over the graph. The
    |           inputs are the following: the graph, recovery rate (gamma),
    |           initial infections and max number of iterations for the
    |           simulation.
    |       getAtRisk() - Calculates if a node is next to an infected
    |           neighbor.
    |       getInfected() - Calculates if a node is infected.
    |
    |   Developers:  
    |       Carlos García - https://github.com/cxrlos
    |       Victor Coeto - https://github.com/vcoetoG
    |       Yann Le Lorier - https://github.com/yannlelorier
    |
    *-------------------------------------------------------------------*/

#include "GraphViewer.h"

int interrupted = 0; // Variable used by the signal handler

void menu(AVLGraph<int> * tree);
int gillespie(std::vector<Edge<int> * > * _graph, double tau ,double _gamma, int _max_t, int graphSize, int sleepSize);

void usage(char *argv[]){
    std::cout << "Usage:\n\t" << argv[0] <<  " -i <inputFilename>\n";
    exit(1);
}

char * optParser(int argc, char *argv[]){ // Receives the input file as a line argument
    int c;
    char * filename = NULL;
    while ((c = getopt (argc, argv, "i:")) != -1){
        switch (c){
            case 'i':
                filename = optarg;
                break;
            
            default:
                usage(argv);
                break;
        }
    }
    return filename;
}

void readGraph(const char * filename, std::vector<Edge<int> * > * graph, std::vector<GraphNode<int> * > * nodeVec){
    FILE * file = NULL;
    char buffer[100];
    int nodes = 0;
    int nodeFrom = 0;
    int nodeTo = 0;

    file = fopen(filename, "r");

    if (!file){
        std::cerr << "\nUnable to open file " << filename << "\n";
        exit(1);
    }

    fgets(buffer, 100, file);

    int createdNodes = 0;
    fscanf(file, "%d\n", &nodes);


    while (createdNodes < nodes){
        nodeVec->push_back(new GraphNode<int>);
        createdNodes++;
    }

    createdNodes = 0;
    std::cout << "nodeVec size" << nodeVec->size() << std::endl;

    while (fscanf(file, "%d %d\n", &nodeFrom, &nodeTo) != EOF){
        graph->push_back(new Edge<int> ((*nodeVec)[nodeFrom], (*nodeVec)[nodeTo]));
        createdNodes++;
    }
}

void nodeCoordinates(double xCenter, double yCenter, double radius, int steps, std::vector<GraphNode<int> * > * graph){ 
	static double PI = 4*atan(1);
	double change = (2*PI)/steps;
	double circleCounter = change;
    double x,y;
    sf::Vector2f pos;
    steps = 0;
    x = y = 0;

	for(; circleCounter <= 2*PI; circleCounter += change){
        x = xCenter + (radius * (cos(circleCounter)));
		y = yCenter + (radius * (sin(circleCounter)));
        pos = sf::Vector2f(x,y);
        (*graph)[steps]->setPos(pos);
        std::cout << std::fixed << std::setprecision(20) << "Node " << steps <<  "\tX = " <<  pos.x << "\nY = " << pos.y << "\n" << std::endl;
        steps ++;
	}
} 

void setRandomInfected(std::vector<GraphNode<int> * > * nodes){
    srand(time(NULL));
    int no_infected = rand()%(nodes->size());
    int randIndex = 0;
    for (int i = 0; i < no_infected; i++){
        srand(time(NULL));
        randIndex = rand()%no_infected;
        (*nodes)[randIndex]->infect();
    }
}

void getAtRisk(std::vector<Edge<int> * > * graph, int * susc, std::vector<GraphNode<int> * > * at_risk){

    for (int i = 0; i < graph->size(); i++){
        std::vector<GraphNode<int> * > nodes = (*graph)[i]->getConnectedNodes();
        if (nodes[0]->isInfected() && std::find(at_risk->begin(), at_risk->end(), nodes[1])==at_risk->end()){
            at_risk->push_back(nodes[1]);
            (*susc)--;
            nodes[1]->neighborInfected();
        } else if (nodes[1]->isInfected() && std::find(at_risk->begin(), at_risk->end(), nodes[0])==at_risk->end()){    
            at_risk->push_back(nodes[0]);
            (*susc)--;
            nodes[0]->neighborInfected();
        } nodes.clear();
    }
}

void getInfected(std::vector<Edge<int> * > * graph, std::vector<GraphNode<int> * > * infected){

    for (int i = 0; i < graph->size(); i++){
        std::vector<GraphNode<int> * > nodes = (*graph)[i]->getConnectedNodes();
        if (nodes[0]->isInfected() && std::find(infected->begin(), infected->end(), nodes[0])==infected->end())
            infected->push_back(nodes[0]);
        else if (nodes[1]->isInfected() && std::find(infected->begin(), infected->end(), nodes[1])==infected->end())
            infected->push_back(nodes[1]);
        nodes.clear();
    }
}

int main(int argc, char *argv[]){

    if (argc == 1){
        usage(argv);
    }

    char * filename = optParser(argc, argv);

    AVLGraph<int> avlGraph;
    std::vector<Edge<int> * > graph;
    std::vector<GraphNode<int> * > nodes;
    readGraph(filename, &graph, &nodes);

    setRandomInfected(&nodes);

    avlGraph.setSimulationGraph(&graph);
    nodeCoordinates(400, 300, 100, nodes[0]->howMany(), &nodes);
  
    GraphViewer viewer("Stochastic Epidemic Simulator", "../Work-Sans-1.50/fonts/desktop/WorkSans-Regular.otf", &menu, &avlGraph);
    viewer.windowListener();
    
    return 0;
}

void signals_menu(int signal_num){ // Acknowledge from the menu to end the program (Ctrl-z) TODO or ask to be sure by (Ctrl-c)
    char des;
    if( signal_num == 20){
    std::cout << '\n' << "finishing program..."<< std::endl;
    exit(EXIT_SUCCESS);
    }
    // std::cout <<"\nProcess exited, are you sure? (Y/N)"<< std::endl;
    // std::cin >> des;
    // while(des != 'Y' || des != 'y' || des != 'N' || des != 'n')
    // {
    //     std::cin >> des ;
    // }
    // if (des == 'Y' || des == 'y'){
    //     exit(SIGINT);
    // }
    // else if (des == 'N' || des == 'n')
    // {
    //     std::cout <<"Returning to program..."<< std::endl;
    //     interrupted = 1;
    // }
}

void menu(AVLGraph<int> * tree){
    int sleepSize = 1;
    char ans = 'a';
    std::vector<Edge<int> * > * graph_ptr;
    signal(SIGTSTP, signals_menu);
    // signal(SIGINT, signals_menu);

    while (ans != 'q'){ //while (ans != 'q' && !interrupted)
        std::cout << "\n== SIR Epidemic - Gillespie Algorithm ==\n";
        std::cout << "\tr. Run the simulation\n";
        std::cout << "\tq. Quit the program\n";
        std::cout << "Enter your selection: ";
        std::cin >> ans;
        
        graph_ptr = tree->getSimulationGraph();
        std::thread gillespieThread(gillespie,graph_ptr, 0.3, 0.40, 5, (*graph_ptr)[0]->howMany(), sleepSize);

        switch (ans){
            case 'r':
                std::cout << "Running...\n ";
                gillespieThread.join(); 
                break;
            case 'q':
                std::cout << "See you later" << std::endl;
                exit(EXIT_SUCCESS);
                //break;
            default:
                std::cout << "Invalid option. Try again ..." << std::endl;
                std::cin >> &ans;
        }
    }
}

void signal_gillespie(int signal_num){ 

    if( signal_num == 20){ // Finish with enter Ctrl-z
        std::cout << "Finishing process...\n";
        exit(SIGINT);
    }

    // Send to signaled to save the process and return wat it computed with Ctrl-c
    interrupted = 1;
}

void signaled(std::vector<Edge<int> * > * graph, std::vector<GraphNode<int> * > infectedNodes,std::vector<GraphNode<int> *> at_risk,int susc, double totalRecoveryRate, double totalInfectionRate,int infe){
    getInfected(graph, &infectedNodes);
    getAtRisk(graph, &susc, &at_risk);
    susc = at_risk.size();

    for (int i = 0; i < at_risk.size(); i++){
        totalInfectionRate += at_risk[i]->getTau();
    }

    int totalRate = totalInfectionRate + totalRecoveryRate;
    std::exponential_distribution<double> expDist (totalRate);
    std::cout << "End of algorithm..." << std::endl;
    std::cout << "Susceptible population: " << susc << std::endl;
    std::cout << "Infected population: " << infe << std::endl;
    //exit(SIGINT);
}

int gillespie(std::vector<Edge<int> * > * graph, double tau, double gamma, int maxt, int graphSize, int sleepSize){
    std::vector<GraphNode<int> * > infectedNodes;
    std::vector<GraphNode<int> * > at_risk = {};
    signal(SIGINT, signal_gillespie);
    signal(SIGTSTP, signal_gillespie);

    getInfected(graph, &infectedNodes); // Getting initial infections

    std::cout << "Infected Nodes:" << std::endl;

    for (int i = 0; i < infectedNodes.size(); i++){
        std::cout << "\tNode " << infectedNodes[i]->getindex() << std::endl;
    }

    int susc = graphSize - infectedNodes.size(); // Susceptible population 
    int infe = infectedNodes.size(); // Infected population
    double totalInfectionRate = 0;
    double totalRecoveryRate = 0;
    double totalRate = 0;
    double time;

    getAtRisk(graph, &susc, &at_risk);
    std::cout << "At risk nodes:" << std::endl;

    for (int i = 0; i < at_risk.size(); i++){
        std::cout << "Node" << at_risk[i]->getindex();
        std::cout << " | Changing tau" << std::endl;
        at_risk[i]->setTau(tau*at_risk[i]->getInfectedNeigh());
        totalInfectionRate += at_risk[i]->getTau();
    }

    totalRecoveryRate = gamma * infectedNodes.size();
    totalRate = totalInfectionRate + totalRecoveryRate;
    
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::exponential_distribution<double> expDist (totalRate);
    time = expDist(generator);

    while (time < maxt && totalRate > 0 && !interrupted){ // Main algorithm loop
        // The following 5 lines are based on https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
        std::random_device rd;
        std::mt19937 gen(rd());
        std::default_random_engine genInt;
        std::uniform_real_distribution<double> realDis(0, totalRate);
        std::uniform_int_distribution<int> intDis(0, infectedNodes.size());

        double r = realDis(gen);
        int randIndex = intDis(genInt);
        if (r < totalRecoveryRate){
            std::cout << "Node " << infectedNodes[randIndex]->getindex() << " has recovered" << std::endl;
            infectedNodes[randIndex]->recover();

            for (int i = 0; i < graph->size(); i++){
                std::vector<GraphNode<int> * > nodes = (*graph)[i]->getConnectedNodes();
                if (nodes[0]==infectedNodes[randIndex]){
                    nodes[1]->setTau(nodes[1]->getTau()-tau);
                } else if (nodes[1]==infectedNodes[randIndex]){    
                    nodes[0]->setTau(nodes[1]->getTau()-tau);
                }
                nodes.clear();
            }
            
            infectedNodes.erase(infectedNodes.begin() + randIndex);
            infe--;
            getInfected(graph, &infectedNodes);
            const auto t0 = std::clock();
            while ((std::clock() - t0) / CLOCKS_PER_SEC < sleepSize){
                int dummy;
                volatile int * pdummy = &dummy;
                for (int i = 0; i < 1000000; i++){
                    *pdummy = i;
                }
            }

        } else {
            std::uniform_int_distribution<> atRiskDis(0, at_risk.size());
            randIndex = atRiskDis(genInt);

            if (!at_risk[randIndex]->isInfected()){
                std::cout << "Node " << at_risk[randIndex]->getindex() << " was infected" << std::endl;
                at_risk[randIndex]->infect();
                infe++;
                at_risk.erase(at_risk.begin() + randIndex);
                getInfected(graph, &infectedNodes);
                getAtRisk(graph, &susc, &at_risk);
                const auto t0 = std::clock();

                while ((std::clock() - t0) / CLOCKS_PER_SEC < sleepSize){
                    int dummy;
                    volatile int * pdummy = &dummy;

                    for (int i = 0; i < 1000000; i++){
                        *pdummy = i;
                    }
                }
            }
        }
        susc = at_risk.size();

        for (int i = 0; i < at_risk.size(); i++){
            totalInfectionRate += at_risk[i]->getTau();
        }
        
        totalRecoveryRate = gamma * infectedNodes.size();
        totalRate = totalInfectionRate + totalRecoveryRate;
        std::exponential_distribution<double> expDist (totalRate);
        time = expDist(generator);
    }

    if (interrupted){
        signaled(graph,infectedNodes,at_risk,susc, totalRecoveryRate, totalInfectionRate, infe);
        interrupted = 0;
    } else {
        std::cout << "End of algorithm..." << std::endl;
        std::cout << "Susceptible population: " << susc << std::endl;
        std::cout << "Infected population: " << infe << std::endl;
    } return 0;
}
