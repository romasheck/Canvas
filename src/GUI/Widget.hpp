#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gui_lib.hpp"
#include "Pixel.hpp"
//#include "GrShapes.hpp"
#include <iostream>

namespace gui
{
//==========================================================================
    class WidBox
    {
    private:
        sf::Vector2f location_;
        sf::Vector2f size_;
        //friend class Widget;

    public:
        void setSize(const sf::Vector2f size) {size_ = size;}
        sf::Vector2f getSize () const {return size_;}

        void setLocation(const sf::Vector2f location) {location_ = location;}
        sf::Vector2f getLocation () const {return location_;}

        bool clickMe (sf::Vector2f click_position)
        {
            if (click_position.x > location_.x && \
                click_position.x < (location_.x + size_.x) &&\
                click_position.y > location_.y && \
                click_position.y < (location_.y + size_.y))
            {
                return true;
            }
            return false;
        }     
    };
//==========================================================================
    class Widget : virtual public WidBox
    {
    protected:
        Widget const * parent_;

    public:
        Widget(Widget* parent, sf::Vector2f size = {10.f, 10.f}, sf::Vector2f location = {0.f, 0.f}):
        parent_(parent)
        {
            setSize(size);
            setLocation(location);
        }
        //ban simple CopyCtor
        Widget(const Widget& widget) = delete;
        /*
        Widget(const Widget& widget, Widget const * parent): 
        parent_(parent)
        {
            setSize(widget.getSize());
            setLocation(widget.getLocation());
        }
        */
    
    public:
        virtual bool catchEvent(const sf::Event event)
        {
            return false;
        }
    };
//==========================================================================
    class WidgetManager: virtual public Widget
    {
    protected:
        std::vector<Widget*> widgets;

    public:
        WidgetManager(Widget* parent, sf::Vector2f size = {10.f, 10.f}, sf::Vector2f location = {0.f, 0.f}):
        Widget(parent, size, location)
        {};

    public:
        bool catchEvent(const sf::Event event)
        {
            bool catched = false;
            for (const auto& widget_ptr : widgets)
            {
                catched = widget_ptr->catchEvent(event);
                if (catched == false)
                {
                    continue;
                }
                else
                {
                    break;
                }
            }

            return catched;
        }

    public:
        void pushWidget(sf::Vector2f size = {10.f, 10.f}, sf::Vector2f location = {0.f, 0.f})
        {
            widgets.push_back(new Widget(this, size, location));
        }
        void popWidget()
        {
            widgets.pop_back();
        }
    };
//==========================================================================
}

#endif