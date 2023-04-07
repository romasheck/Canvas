#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gui_lib.hpp"
#include "Pixel.hpp"
//#include "GrShapes.hpp"
#include <iostream>
#include <memory.h>


//TODO WidgetManager need method CreateWidget
//TODO all Widgets can be drowen, it should contain virtual method draw() 
//TODO specialize event: MoseEvent, Other
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

        bool inMe (const sf::Vector2f position)
        {
            if (position.x > location_.x && \
                position.x < (location_.x + size_.x) &&\
                position.y > location_.y && \
                position.y < (location_.y + size_.y))
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
        Widget * parent_;
        //auto& parent() {return parent_;}

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

    public:
        virtual void draw()
        {
            sf::RectangleShape bad_view_;
            bad_view_.setSize(getSize());
            bad_view_.setPosition(getLocation());
            bad_view_.setFillColor(sf::Color::Blue);
            window_ptr->draw(bad_view_);
        }

    //friend WidgetManager;
    };
//==========================================================================
    class WidgetManager: virtual public Widget
    {
    protected:
        //std::vector<std::unique_ptr<Widget>> widgets;
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
        //void pushWidget(std::unique_ptr<Widget> new_widget_ptr)
        void pushWidget(Widget* widget_ptr)
        {
            widgets.push_back(widget_ptr);
        }
        void popWidget()
        {
            widgets.pop_back();
        }
    };
//==========================================================================
    class WidgetMaster: virtual public WidgetManager
    {
    public:
        WidgetMaster(sf::Vector2f size):
        WidgetManager(nullptr, size, {0, 0}),
        Widget(nullptr, size, {0, 0})
        {};
    };
}

#endif