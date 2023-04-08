#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

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
        Canvas(Widget* parent, sf::Vector2f size, sf::Vector2f location):
        Clickable(parent, size, location),
        Widget(parent, size, location),
        currentColor_(sf::Color::Red)
        {
            area_.setFillColor(sf::Color::White);
            area_.setSize(getSize());
            area_.setPosition(getLocation());
            currentStain_.setFillColor(sf::Color::Red);
            currentStain_.setRadius(30);
        }

    public:
        void setCurrentColor(sf::Color cur_color)
        {
            currentColor_ = cur_color;
        }

    private:
        void respond2Click() override
        {
            std::cout<<"begin responding to click"<<std::endl;
            currentStain_.setFillColor(currentColor_);
            currentStain_.setPosition(clickPosition_);
            // stains.push_back(new sf::CircleShape());
            window_ptr->draw(currentStain_);
            std::cout<<"stain must be on the"<<" "<<clickPosition_.x<<" "<<clickPosition_.y<<std::endl;
        }

    public:
        void draw() override
        {
            window_ptr->draw(area_);
        }
    };
//==========================================================================
    class CWidget : virtual public Widget
    {
    protected:
        Canvas& canvas_;
    public:
        CWidget(Canvas& canvas, Widget* parent, sf::Vector2f size = {10.f, 10.f}, sf::Vector2f location = {0.f, 0.f}):
        Widget(parent, size, location),
        canvas_(canvas){};
    };
//==========================================================================
    class CWidgetManager : public WidgetManager, public CWidget
    {
    public: 
        CWidgetManager(Canvas& canvas, Widget* parent, sf::Vector2f size = {10.f, 10.f}, sf::Vector2f location = {0.f, 0.f}):
        Widget(parent, size, location),
        CWidget(canvas, parent, size, location),
        WidgetManager(parent, size, location)
        {};
    };
}

#endif