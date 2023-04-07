#ifndef CWIDGETS_HPP
#define CWIDGETS_HPP

#include "CanvasWidget.hpp"

namespace gui
{
//==========================================================================
    class ColorRegulator: public Clickable, public CWidget
    {
        private:
            const sf::Color choisenColor_;
            sf::RectangleShape view_;
        
        public:
            ColorRegulator(const sf::Color choisenColor, Canvas& canvas_ptr, Widget* parent, sf::Vector2f size = {10.f, 10.f}, sf::Vector2f location = {0.f, 0.f}):
            Widget(parent, size, location),
            Clickable(parent, size, location),
            CWidget(canvas_ptr, parent, size, location)
            {
                view_.setFillColor(choisenColor_);
                view_.setPosition(getLocation());
                view_.setSize(getSize());
            }

        public: 
            void draw()
            {
                window_ptr->draw(view_);
            }

        private:
            void respond2Click(const sf::Vector2f clickPosition)
            {
                canvas_.setCurrentColor(choisenColor_);
            }
        
    };
//==========================================================================
}

#endif