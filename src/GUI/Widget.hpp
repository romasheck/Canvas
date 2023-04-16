#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gui_lib.hpp"
#include "coordinate.hpp"
#include "Pixel.hpp"
#include "Events.hpp"
//#include "GrShapes.hpp"
#include <iostream>
#include <memory.h>

namespace gui
{
//==========================================================================
    class WidBox //rectangle that has local coord and size in loc coord sys
    {
    public://do these public -> get.. & set.. are useless
        coordinate location_;
        coordinate size_;

    public:
        void setSize(const coordinate size) {size_ = size;} //useless
        coordinate getSize () const {return size_;}//useless

        void setLocation(const coordinate location) {location_ = location;}//useless
        coordinate getLocation () const {return location_;}//useless

        bool inMe (const coordinate position)//position in widBox?
        {
            if (position.x_ > location_.x_ && \
                position.x_ < (location_.x_ + size_.x_) &&\
                position.y_ > location_.y_ && \
                position.y_ < (location_.y_ + size_.y_))
            {
                return true;
            }
            return false;
        }

        coordinate rtAngle() const //return right top angle of WidBox
        {
            return location_ + size_;
        }
        coordinate ltAngle() const //return left top angle of WidBox
        {
            return location_ + coordinate(0, size_.y_);
        }
    };
//==========================================================================
    class Widget : public WidBox //WidBox which can be drawn, can catch events (sp. click) and has parent
    {
    protected:
        Widget * parent_;

    public:
        Widget(Widget* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        parent_(parent)
        {
            setSize(size);
            setLocation(location);
        }
        //ban simple CopyCtor
        Widget(const Widget& widget) = delete;
    
        virtual bool catchEvent(const sf::Event event)
        {
            return false;
        }
        virtual bool catchClick (Click click)
        {
            return false;
        }
    
        virtual void draw() //default: draw blue rectangle in W
        {
            sf::RectangleShape bad_view_;

            bad_view_.setSize(sizeInPixels());
            bad_view_.setPosition(getPosition());
            bad_view_.setFillColor(sf::Color::Blue);

            window_ptr->draw(bad_view_);
        }

        //turn local coordinate into abcolute pixels coordinate system FOR CALLING SFML-FUNCTIONS 
        virtual coordinate locationToPosition(coordinate location) const
        {
            return parent_->locationToPosition(location);
        }
        //return absolute pixels position of left top angle FOR CALLING SFML-FUNCTIONS
        coordinate getPosition() const
        {
            return Widget::locationToPosition(ltAngle());
        }
        //return real size of object in pixels FOR CALLING SFML-FUNCTIONS
        coordinate sizeInPixels () const
        {
            return cabs(locationToPosition(rtAngle()) - locationToPosition(location_)); 
        }
    };
//==========================================================================
    class WidgetManager: virtual public Widget //Widget which contain several other, hasn`t parent
    {
    protected:
        std::vector<Widget*> widgets;

    public:
        WidgetManager(Widget* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        Widget(parent, size, location)
        {};

    public:
        bool catchEvent(const sf::Event event) override // still useless shit
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
        //calculates whether his box is clicked, if yes, sends the click to his widgets
        bool catchClick (Click click) override
        {
            bool catched = false;

            if (inMe(click.location_))
            {
                click.location_ = positionToLocation(click.location_);

                for (const auto& widget_ptr : widgets)
                {
                    catched = widget_ptr->catchClick(click);

                    if (catched == false)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            return catched;
        }

    public:
        void pushWidget(Widget* widget_ptr)
        {
            widgets.push_back(widget_ptr);
        }
        void popWidget()
        {
            widgets.pop_back();
        }

    public:
        coordinate locationToPosition(coordinate location) const override
        {
            location.transmit (location_, size_);//transmit into parent system
            
            return parent_->locationToPosition(location);
        }
        //turn absolute position to local coordinate FOR CLICK
        virtual coordinate positionToLocation(coordinate position) const
        {
            return (position - location_)/size_;
        }
    };
//==========================================================================
    class WidgetMaster: public WidgetManager //Base for MainWidget
    {
    private:
        coordinate scale_;
    public:
        WidgetMaster(sf::Vector2f size, const char* window_name):
        WidgetManager(nullptr, {1, 1}, {0, 0}),
        Widget(nullptr, {1, 1}, {0, 0})
        {
            window_ptr = new sf::RenderWindow(sf::VideoMode(size.x, size.y), window_name);
            scale_ = coordinate((float)window_ptr->getSize().x, (float)window_ptr->getSize().y);
            //printf("scale is (%f, %f)\n", scale_.x_, scale_.y_);
        };

        coordinate locationToPosition (coordinate location) const override
        {
            location.y_ = 1 - location.y_;// make y_ upsidedown

            location = location*scale_;// multiply coordinate (from 0 to 1) on amount of pixels in side

            return location;
        }

        coordinate positionToLocation (coordinate position) const override
        {
            position = position/scale_;// dev position in pixels on amount of pixels in side
            
            position.y_ = 1 - position.y_;// make y_ upsidedown

            return position;
        }

        bool catchEvent(const sf::Event event) override //still can catch only Click
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (catchClick(Click(event)))
                {
                    return true;
                }
            }
            return false;
        }

        bool catchClick(Click click) override //recalc pixel pos to loc coord and pass click to his widgets
        {
            bool catched = false;

            click.location_ = positionToLocation(click.location_);

            for (const auto& widget_ptr : widgets)
            {
                catched = widget_ptr->catchClick(click);
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
    };
}

#endif