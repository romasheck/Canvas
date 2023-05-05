#ifndef PIXEL_HPP
#define PIXEL_HPP

#include "gui_lib.hpp"

namespace gui
{
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
};

#endif