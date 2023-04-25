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
            ColorRegulator(const sf::Color choisenColor, Canvas& canvas_ptr, WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
            Widget(parent, size, location),
            Clickable(parent, size, location),
            CWidget(canvas_ptr, parent, size, location),
            choisenColor_(choisenColor)
            {
                view_.setFillColor(choisenColor_);
                view_.setPosition(getPosition());
                view_.setSize(getSizeInPixels());
            }

        public: 
            void draw()
            {
                window_ptr->draw(view_);
            }

        private:
            void respond2Click() override
            {
                //std::cout<<"ColorRegulator must exchange color"<<std::endl;
                canvas_.setCurrentColor(choisenColor_);
            }
        
    };
}

#endif