#ifndef PANEL_HPP
#define PANEL_HPP

#include "CollorRegulator.hpp"
#include "ModeButtons.hpp"

namespace gui
{
    class Panel: public CWidgetManager
    {
    private:
        sf::RectangleShape background_;

    public:
        Panel(Canvas& canvas, WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        CWidgetManager(canvas, parent, size, location),
        Widget(parent, size, location)
        {
            background_.setFillColor(sf::Color::Magenta);
            background_.setSize(getSizeInPixels());
            background_.setPosition(getPosition());
        };

    public:
        void createAll()
        {
            auto bDot_ptr = new DotButton(canvas_, this, coordinate{0.5, 0.5}, coordinate{0.1, 0.1});
            pushWidget ((Widget*)bDot_ptr);
        }

    public:
        void draw() override;

    private:
        
        void createColorRegulator(sf::Color color, coordinate size, coordinate location);
    };
}

#endif