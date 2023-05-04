#ifndef CLEANER_HPP
#define CLEANER_HPP

#include "Clickable.hpp"
#include "CWidget.hpp"

namespace gui
{
    class Cleaner: public Clickable, public CWidget
    {
    private:
        sf::RectangleShape view_;

    public:
        Cleaner(Canvas& canvas, WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
            Widget(parent, size, location),
            Clickable(parent, size, location),
            CWidget(canvas, parent, size, location)
            {
                view_.setFillColor(sf::Color::Cyan);
                view_.setPosition(getPosition());
                view_.setSize(getSizeInPixels());                
            };

        void respond2Click() override
        {
            //std::cout<<"click on clear bottom"<<std::endl;
            parent_->reDrawSig();
        }

        void draw() override
        {
            window_ptr->draw(view_);
        }
    };
}

#endif