#ifndef COLLORREGULATOR_HPP
#define COLLORREGULATOR_HPP

#include "Clickable.hpp"
#include "CWidget.hpp"

namespace gui
{
    class ColorRegulator: public Clickable, public CWidget
    {
    private:
        const sf::Color choisenColor_; // the color of ColorReg and color after exhange 
        sf::RectangleShape view_;  // the view of ColorRegulator
    
    public:
        ColorRegulator(const sf::Color choisenColor, Canvas& canvas, WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f});

    public: 
        void draw() override;

    private:
        void respond2Click() override;
    
    };
}

#endif