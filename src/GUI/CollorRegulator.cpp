#include "../../include/GUI/CollorRegulator.hpp"

namespace gui
{
    ColorRegulator::ColorRegulator(const sf::Color choisenColor, Canvas& canvas, WidgetManager* parent, coordinate size, coordinate location):
            Widget(parent, size, location),
            Clickable(parent, size, location),
            CWidget(canvas, parent, size, location),
            choisenColor_(choisenColor)
            {
                view_.setFillColor(choisenColor_);
                view_.setPosition(getPosition());
                view_.setSize(getSizeInPixels());
            }

    void ColorRegulator::draw()
    {
        context_ptr->window().draw(view_);
    }

    void ColorRegulator::respond2Click()
    {
        //std::cout<<"ColorRegulator must exchange color"<<std::endl;
        canvas_.setCurrentColor(choisenColor_);
    }
}