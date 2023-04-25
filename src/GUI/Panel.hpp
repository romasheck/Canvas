#ifndef PANEL_HPP
#define PANEL_HPP

#include "CollorRegulator.hpp"

namespace gui
{
    class Panel: public CWidgetManager
    {
    private:
        sf::RectangleShape background_;

    public:
        Panel(Canvas& canvas, Widget* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
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
            //location = loc_canv + sz_canv - sz_ColorReg.y_
            createColorRegulator (sf::Color::Green, {0.7, 0.35}, \
            {0.1, 0.55} );
            //location = loc_canv + sz_canv - 2*sz_ColorReg.y_
            createColorRegulator (sf::Color::Red, {0.7, 0.4}, \
            {0.1, 0.1} );
        }

    public:
        void draw() override;

    private:
        void createColorRegulator(sf::Color color, coordinate size, coordinate location);
    };
}

#endif