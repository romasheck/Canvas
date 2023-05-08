#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <iostream>

#include "gui_lib.hpp"
#include "Widget.hpp"
#include "Clickable.hpp"

namespace gui
{   
    class Pen
    {
    private:
        coordinate location_;
        uint8_t mode;
        uint8_t type;

        sf::Time lastInteraction;       
    };

    class Canvas final : public Clickable
    {
    private:
        sf::Color currentColor_;
        //sf::Color fillColor;
        sf::Sprite background_;
        // std::vector<sf::CircleShape*> stains;
        sf::CircleShape currentStain_;
        //Pen pen_;

        sf::Time lastInteraction;       
        #define PAUSE sf::Time(sf::milliseconds(1))

    public:
        enum ModeGroups: unsigned char
        {
            GEOMETRIC = 1 << 0,
            COSMETIC = 1 << 1, 
            DEFAULT = 0,

        };
        enum PenMode: unsigned char
        {
        //GeometricInstruments
            Dot             = 1 << 2 | GEOMETRIC, 
            Ruler           = 2 << 2 | GEOMETRIC,   //make line, req 2 dots
            CircleSolution  = 3 << 2 | GEOMETRIC,   //make circle, req 2 dots for define radius and 1 as center
            CircleArbitary  = 4 << 2 | GEOMETRIC,   //make circle, req 2 dot as center and point of circle
        //CosmeticInstruments
            Pencil          = 6 << 2 | COSMETIC,    //drow small circle
        //Default (0b00000000)
            Default         = 0 << 2 | DEFAULT      //nothing
        };

        PenMode penMode_;

    public:
        Canvas(WidgetManager* parent, coordinate size, coordinate location);

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