#include "GraphViewer.h"
#include <iostream>
#include <string>

GraphViewer::GraphViewer(std::string window_title, std::string font_name, void (*menu)(AVLGraph<int> *), AVLGraph<int> * tree) : window(sf::VideoMode(800, 600), window_title), menu_thread(menu, tree)
{
    // change the position of the window (relatively to the desktop)
    window.setPosition(sf::Vector2i(700, 100));

    // Load the font
    font.loadFromFile(font_name);

    // Store the reference to the binary tree
    tree_pointer = tree;

    // Prepare all the drawable elements
    configure();
}

void GraphViewer::configure()
{
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

void GraphViewer::windowListener()
{
    menu_thread.launch();

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    std::cout << "Window closed. Exiting the program." << std::endl;
                    exit(0);
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::R)
					{
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
                    if (event.mouseWheel.delta > 0 && circle.getRadius() < 300)
                    {
                        // Increment the scale
                        changeScale(1);
                    }
                    else if (event.mouseWheel.delta < 0 && circle.getRadius() > 0.5)
                    {
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

void GraphViewer::resetScale()
{
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

void GraphViewer::changeScale(int multiplier)
{
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
    drawTree();

    // Draw everything
    window.display();
}

void GraphViewer::drawTitle()
{
    std::string radius_text;
    // Get the radius as a string
    radius_text = std::to_string(circle.getRadius());
    // Cut the number of decimals shown
    radius_text = radius_text.substr(0, radius_text.length()-5);
    // Change the text displayed
    title.setString("TREE VIEWER\nTime elapsed: " + std::to_string(total_time.asSeconds()));
    info.setString( "Radius: " + radius_text +
                    "\nFont size: " + std::to_string(node_font_size));

    window.draw(title);
    window.draw(info);
}

/*
void GraphViewer::drawAnimatedCircle()
{
    // Create a moving animation
    circle.setPosition(sf::Vector2f(x_pos, y_pos));
    x_pos += speed * direction * elapsed_time.asSeconds();
    if (x_pos <= circle.getRadius() || x_pos >= window.getSize().x-circle.getRadius())
    {
        direction = direction * -1;
    }

    window.draw(circle);
}
*/

void GraphViewer::drawTree()
{
    // Initialize the margin to the left
    global_node_x = 100;
    global_node_y = 200;
    recursiveDrawTree(tree_pointer->getRoot(), global_node_y);
}

// Draw the whole tree using an in-order recursive traversal
sf::Vector2f GraphViewer::recursiveDrawTree(GraphNode<int> * _root, int node_y)
{
    if(_root != nullptr)
    {
        sf::Vector2f node_position;
        sf::Vector2f left_position;
        sf::Vector2f right_position;

        // Draw left branch
        if(_root->getLeft())
        {
            // Draw the circle and data for the node
            left_position = recursiveDrawTree(_root->getLeft(), node_y + v_offset);
        }
        // Compute the position for this node
        node_position = sf::Vector2f(global_node_x, node_y);
        global_node_x += h_offset;
        // Draw right branch
        if(_root->getRight())
        {
            // Draw the circle and data for the node
            right_position = recursiveDrawTree(_root->getRight(), node_y + v_offset);
        }

        // Draw the lines to connect with the children
        if(_root->getLeft())
        {
            // First draw the line so that he node is drawn on top
            drawLine(node_position, left_position);
        }
        if(_root->getRight())
        {
            // First draw the line so that the node is drawn on top
            drawLine(node_position, right_position);
        }

        // Draw the node after the lines connecting it to its sons
        drawNode(_root, node_position);

        return node_position;
    }
    // Return case for an emptry tree (should not be used)
    return sf::Vector2f(0, 0);
}

void GraphViewer::drawNode(GraphNode<int> * node, const sf::Vector2f & position)
{
    // Set the position of the circle
    circle.setPosition(position);
    // Set different colors for leaf or inner nodes
    if (!node->getLeft() && !node->getRight())
        circle.setFillColor(sf::Color::Yellow);
    else
        circle.setFillColor(sf::Color::Red);
    window.draw(circle);

    // Set the text of the node
    data.setString(std::to_string(node->getData()));
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
void GraphViewer::drawLine(const sf::Vector2f & origin, const sf::Vector2f & destination)
{
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
    sf::Vertex line[] =
    {
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
