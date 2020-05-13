#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Covid-19 Simulator");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

// int gillespie(std::vector <int> &, double, double, std::vector<int> &, int);

// int gillespie(std::vector <int> graph, double tau, double gamma, std::vector<int> init_inf, int t_max)
// {
//     int time = 0;
//     int susc = graph.size() - graph.size();
//     int infe = init_inf.size();
//     int recov = 0;

//     std::vector <int> infected_nodes = init_inf;
//     std::vector <int> susceptible_nodes;




// }

// void graphRep(std::vector<int> g){
//     for (int i = 0; i < g.size(); i++)
//     {
//         std::cout << "Graph node %d, with neighbor"
//     }
    
// }