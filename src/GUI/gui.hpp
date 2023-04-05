#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>

namespace gui
{
    enum
    {
        WINDOW_WIDTH = 1200,
        WINDOW_HEIGHT = 800    
    };

    class pixel : private sf::RectangleShape
    {
    public:
        pixel(const sf::Vector2f position, const sf::Color color)
        {   
            setSize({1.f, 1.f});
            setPosition(position);
            setFillColor(color);
        };
    public:
        using RectangleShape::getFillColor;
        using RectangleShape::setFillColor;
        using RectangleShape::getPosition;
        using RectangleShape::setPosition;
    };

    class WManager: private sf::RenderWindow
    {
    private:
        Layer layers[2];
        //sf::RenderWindow& window;
    public:
        WManager(const int w_width, const int w_height, const char* title)
        {
            RenderWindow(sf::VideoMode(w_width, w_height), title);
        }
    };

    class Mouse
    {

    };

    class Layer
    {
    private:
        std::vector<Widget> Widgets_;

    public:

    };
};

#endif