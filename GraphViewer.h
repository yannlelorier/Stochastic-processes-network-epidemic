#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AVLGraph.h"

class GraphViewer {
    private:
        // Drawable elements
        sf::RenderWindow window;
        sf::Font font;
        sf::Text title;
        sf::Text info;
        sf::Text data;
        sf::Text height;
        sf::CircleShape circle;
        sf::Event event;
        // Thread object
        sf::Thread menu_thread;
        // Time variables
        sf::Clock clock;
        sf::Time elapsed_time;
        sf::Time total_time;
        // Tree variables
        AVLGraph<int> * graph_pointer = nullptr;

        // Additional variables for drawing 
        int node_radius = 25;
        int global_node_x = 100;
        int global_node_y = 200;
        int h_offset = 40;
        int v_offset = 60;
        int scale_factor = 2;
        int node_font_size = 24;
        int height_font_size = 14;
        int font_scale_factor = 5;

        // General drawing methods
        void configure();
        void mainDraw();
        void drawTitle();

        // Methods for drawing the tree
        void resetScale();
        void changeScale(int multiplier);
        void drawGraph();
        // sf::Vector2f recursiveDrawTree(GraphNode<int> * _root, int node_y);
        void drawNode(GraphNode<int> * node, const sf::Vector2f & position);
        void drawLine(const sf::Vector2f & origin, const sf::Vector2f & destination);
    public:
        // Constructor
        GraphViewer (std::string window_title, std::string font_name, void (*menu)(AVLGraph<int> *), AVLGraph<int> * tree);
        //TreeViewer (std::string window_name, std::string font_name);
        AVLGraph<int> * getGraphPointer() {return graph_pointer;}
        // Public method to start the drawing process
        void windowListener();
};
