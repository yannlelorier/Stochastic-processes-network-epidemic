#include "GraphViewer.h"
#include <iostream>
#include <string>

GraphViewer::GraphViewer(std::string window_title, std::string font_name, void (*menu)(AVLGraph<int> *), AVLGraph<int> * graph) : window(sf::VideoMode(800, 600), window_title), menu_thread(menu, graph){
    // change the position of the window (relatively to the desktop)
    window.setPosition(sf::Vector2i(700, 100));

    // Load the font
    font.loadFromFile(font_name);

    // Store the reference to the graph
    graph_pointer = graph;

    // Prepare all the drawable elements
    configure();
}

void GraphViewer::configure(){
    // Configure the title object
    title.setFont(font);
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::Blue);
    title.setPosition(sf::Vector2f(20, 10));

    // Configure the info object
    info.setFont(font);
    info.setCharacterSize(24);
    info.setFillColor(sf::Color::Green);
    info.setPosition(sf::Vector2f(20, 80));

    // Configure node data text
    data.setFont(font);
    data.setCharacterSize(node_font_size);
    data.setFillColor(sf::Color::Black);
    data.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Configure height text
    height.setFont(font);
    height.setCharacterSize(height_font_size);
    height.setFillColor(sf::Color::Blue);
    height.setStyle(sf::Text::Bold);

    // Create a circle with a visible edge
    circle.setRadius(node_radius);
    circle.setPointCount(32);
    circle.setFillColor(sf::Color::Red);
    circle.setOutlineThickness(3.f);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}

void GraphViewer::windowListener(){
    menu_thread.launch();

    while(window.isOpen()){
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    std::cout << "Window closed. Exiting the program." << std::endl;
                    exit(0);
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::R){
                        resetScale();
                    }
                    /*
                    if (event.key.code == sf::Keyboard::Add)
                        speed+=10;
                    if (event.key.code == sf::Keyboard::Subtract)
                        speed-=10;
                        */
                    break;
                case sf::Event::MouseWheelMoved:
                    // The scrollwheel scales the nodes
                    if (event.mouseWheel.delta > 0 && circle.getRadius() < 300){
                        // Increment the scale
                        changeScale(1);
                    }
                    else if (event.mouseWheel.delta < 0 && circle.getRadius() > 0.5){
                        // Decrement the scale
                        changeScale(-1);
                    }
                    break;
                default:
                    // Do nothing with the events that are not yet handled
                    ;
            }
        }

        mainDraw();
    }
}

void GraphViewer::resetScale(){
    // Reset the size of the node circles
    circle.setRadius(node_radius);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    // Reset the spacing between the circles
    h_offset = 40;
    v_offset = 60;
    // Reset the size of the font in the nodes
    node_font_size = 24;
    data.setCharacterSize(node_font_size);
    // Reset the size of the font in the node heights
    height_font_size = 14;
    height.setCharacterSize(height_font_size);
}

void GraphViewer::changeScale(int multiplier){
    // Change the radius of the node circles
    int radius = circle.getRadius();
    radius += scale_factor * multiplier;
    // Update the configuration for the drawing of the node circles
    circle.setRadius(radius);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    // Update the offset values to draw the tree correctly
    h_offset += scale_factor * 2 * multiplier;
    v_offset += scale_factor * 2 * multiplier;
    // Update the size of the font inside of the nodes
    node_font_size += font_scale_factor * multiplier;
    data.setCharacterSize(node_font_size);
    // Update the size of the height text beside the nodes
    height_font_size += font_scale_factor * multiplier;
    height.setCharacterSize(height_font_size);
}

void GraphViewer::mainDraw()
{
    // Keep track of the time elapsed since the last frame
    elapsed_time = clock.restart();
    total_time += elapsed_time;
    // Clean the window
    window.clear(sf::Color::White);

    // Draw all the elements
    drawTitle();
    drawGraph();

    // Draw everything
    window.display();
}

void GraphViewer::drawTitle(){
    std::string radius_text;
    radius_text = std::to_string(circle.getRadius());
    radius_text = radius_text.substr(0, radius_text.length()-5);
    title.setString("Graph Viewer\nTime elapsed: " + std::to_string(total_time.asSeconds()));
    info.setString( "Radius: " + radius_text +"\nFont size: " + std::to_string(node_font_size));

    window.draw(title);
    window.draw(info);
}


void GraphViewer::drawGraph(){
//TODO Draw node ()iterative
    //draw graph connections
    AVLGraph<int> * avlPtr = getGraphPointer();
    //TODO soft-code the 7
    std::vector<GraphNode<int> * > connecteds;
    std::vector<GraphNode<int> * > nodes;
    std::vector<Edge<int> * > * graph = avlPtr->getSimulationGraph();
    for (int i = 0; i < graph->size(); i++){
        connecteds = (*graph)[i]->getConnectedNodes();
        if (std::find(nodes.begin(), nodes.end(), connecteds[0])==nodes.end())
            nodes.push_back(connecteds[0]);
        if (std::find(nodes.begin(), nodes.end(), connecteds[1])==nodes.end())
            nodes.push_back(connecteds[1]);
        connecteds.clear();
    }

    for (int i = 0; i < 7; i++){
        drawNode(nodes[i], nodes[i]->getPos());
    }
}


void GraphViewer::drawNode(GraphNode<int> * node, const sf::Vector2f & position){
    // Set the position of the circle
    circle.setPosition(position);

    //color based on the infected
    if (node->isInfected())
        circle.setFillColor(sf::Color(255,0,0));
    else
        circle.setFillColor(sf::Color(0,0,255));
    window.draw(circle);

    // Set the text of the node
    data.setString(std::to_string(node->getindex()));
    // Center the origin of the text
    sf::FloatRect textRect = data.getLocalBounds();
    // Set the position of the text
    data.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    data.setPosition(position);
    window.draw(data);

    // Set a new position for the height text
    sf::Vector2f position_offset(circle.getRadius(), circle.getRadius());
    // Set the height of the node
    height.setString(std::to_string(node->getHeight()));
    // Center the origin of the text
    textRect = height.getLocalBounds();
    // Set the position of the text
    height.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    height.setPosition(position + position_offset);
    window.draw(height);
}

// Draw the lines between the nodes.
// Receives the coordinates of the two nodes to link
void GraphViewer::drawLine(const sf::Vector2f & origin, const sf::Vector2f & destination){
    // Create new points
    sf::Vector2f o1, o2, o3, d1, d2, d3;
    // Copy the origin and destination points
    o1 = o2 = o3 = origin;
    // Add offsets to give width to the lines
    o1.x -= 1;
    o3.x += 1;
    d1 = d2 = d3 = destination;
    d1.x -= 1;
    d3.x += 1;
    // Define a series of 6 vertices
    sf::Vertex line[] = {
        sf::Vertex(o1, sf::Color::Black),
        sf::Vertex(d1, sf::Color::Black),
        sf::Vertex(o2, sf::Color::Black),
        sf::Vertex(d2, sf::Color::Black),
        sf::Vertex(o3, sf::Color::Black),
        sf::Vertex(d3, sf::Color::Black)
    };
    // Draw 3 lines, using the 6 vertices
    window.draw(line, 6, sf::Lines);
}
