#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <iostream>

#include "gui_lib.hpp"
#include "Widget.hpp"
#include "Clickable.hpp"
#include "../GEO/FigureManager.hpp"

namespace gui
{   
    class Canvas;
    class Projector;

    enum CanvasModeGroups: unsigned char
    {
        GEOMETRIC = 1 << 0,
        COSMETIC = 1 << 1,
        ARTISTIC = 1 << 2,
        DEFAULT = 0,
        GROUP = GEOMETRIC + COSMETIC + ARTISTIC
    };
    enum CanvasPenMode: unsigned char
    {
    //GeometricInstruments
        Dot             = 1 << 3 | GEOMETRIC, 
        Ruler           = 2 << 3 | GEOMETRIC,   //make line, req 2 dots
        CircleSolution  = 3 << 3 | GEOMETRIC,   //make circle, req 2 dots for define radius and 1 as center
        CircleArbitary  = 4 << 3 | GEOMETRIC,   //make circle, req 2 dot as center and point of circle
    //ArtisticInstruments
        Pencil          = 6 << 3 | ARTISTIC,    //drow small circle
    //Default (0b00000000)
        Default         = 0 << 3 | DEFAULT      //nothing
    };

    typedef unsigned char PenMode;

    class Projector final
    {
    public:
        Projector(Canvas& canvas);

    public:
        bool processPen(const PenMode mode, const coordinate loc);

        bool ctrlZ();

    private:
        geo::Point transmitToMyCS(const coordinate) const;
        coordinate transmitToCanv(const geo::Point) const;

    private:
        void addDot(geo::Point p);
        void doRuler(const geo::Dot* fig);
        void doCircleArbitary(const geo::Dot* fig);
        void doCircleSolution(const geo::Dot* fig);

    private:
        void drawDot (geo::Dot dot);
        void drawCircle (geo::Circle circle);
        void drawLine (geo::Line line);

    private:
        bool validatePoint (const geo::Point p) const;

    private:
        Canvas& canvas_;
        coordinate canvasScale_;
        geo::FigureManager geometry_;
        geo::Point RT;
    
    private:
        typedef struct{
            CanvasPenMode processing;
            bool is2step;
            const geo::Dot* dot1_ptr;
            const geo::Dot* dot2_ptr;
        }Buffer;
        Buffer buff_;   
    };

    class Canvas final : public Clickable
    {
        friend Projector;
    private:
        sf::Color currentColor_;
        //sf::Color fillColor;
        sf::Sprite background_;
        // std::vector<sf::CircleShape*> stains;
        sf::CircleShape currentStain_;
        //Pen pen_;
        Projector projector_;

        sf::Time lastInteraction;       
        #define PAUSE sf::Time(sf::milliseconds(1))

    public:
        PenMode penMode_;

    public:
        Canvas(WidgetManager* parent, coordinate size, coordinate location);

    public:
        void setCurrentColor(sf::Color cur_color);

    private:
        void respond2Click() override;

    private:
        //any locations is coordinate in canvas parent system
        //but coordinate in canvas system is needed
        //this func transmit locations into coordinate in canvas system 
        coordinate locloc(const coordinate location) const;

        coordinate colcol(const coordinate loc) const;
        coordinate locToPos(const coordinate loc) const;

    public:
        void draw() override;
    };
//==========================================================================
}

#endif