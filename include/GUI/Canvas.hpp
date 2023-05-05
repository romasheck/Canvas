#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <iostream>

#include "gui_lib.hpp"
#include "Widget.hpp"
#include "Clickable.hpp"

namespace gui
{
    class Canvas final : public Clickable
    {
    private:
        sf::Color currentColor_;
        //sf::Color fillColor;
        sf::RectangleShape area_;
        // std::vector<sf::CircleShape*> stains;
        sf::CircleShape currentStain_;

    public:
        Canvas(WidgetManager* parent, coordinate size, coordinate location):
        Clickable(parent, size, location),
        Widget(parent, size, location),
        currentColor_(sf::Color::Red)
        {
            area_.setFillColor(sf::Color::White);
            area_.setSize(getSizeInPixels());
            area_.setPosition(getPosition());
            currentStain_.setFillColor(sf::Color::Red);
            currentStain_.setRadius(30);
        }

    public:
        void setCurrentColor(sf::Color cur_color);

    private:
        void respond2Click() override;

    public:
        void draw() override;
    };
//==========================================================================
}

#endif