#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gui_lib.hpp"
#include "coordinate.hpp"
#include "Pixel.hpp"
#include "Events.hpp"
//#include "GrShapes.hpp"
#include <iostream>
#include <memory.h>


//TODO WidgetManager need method CreateWidget// realy?
//TODO all Widgets can be drowen, it should contain virtual method draw() //done, check it 

//TODO specialize event: MoseEvent, Other
//TODO make local coordinate system for every widget manager (it requers class coordinate?)
namespace gui
{
//==========================================================================
    class WidBox
    {
    public:
        coordinate location_;
        coordinate size_;
        //friend class Widget;

    public:
        void setSize(const coordinate size) {size_ = size;}
        coordinate getSize () const {return size_;}

        void setLocation(const coordinate location) {location_ = location;}
        coordinate getLocation () const {return location_;}

        bool inMe (const coordinate position)
        {
            if (position.x_ > location_.x_ && \
                position.x_ < (location_.x_ + size_.x_) &&\
                position.y_ > location_.y_ && \
                position.y_ < (location_.y_ + size_.y_))
            {
                //std::cout<<"inMe: click was my"<<std::endl;
                return true;
            }
            return false;
        }

        coordinate rtAngle() const
        {
            return location_ + size_;
        }
        coordinate ltAngle() const
        {
            return location_ + coordinate(0, size_.y_);
        }

        /*coordinate transmitedLocation(coordinate shift, coordinate scale) const
        {
            return (shift + ());
        }*/    
    };
//==========================================================================
    class Widget : public WidBox
    {
    protected:
        Widget * parent_;
        //auto& parent() {return parent_;}

    public:
        Widget(Widget* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
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
    
        virtual bool catchEvent(const sf::Event event)
        {
            return false;
        }
        virtual bool catchClick (Click click)
        {
            return false;
        }
    
        virtual void draw()
        {
            sf::RectangleShape bad_view_;
            bad_view_.setSize(sizeInPixels());
            bad_view_.setPosition(locationToPosition(location_));
            bad_view_.setFillColor(sf::Color::Blue);
            window_ptr->draw(bad_view_);
        }

        virtual coordinate locationToPosition(coordinate location) const
        {
            //std::cout<<"call from W"<<std::endl;

            return parent_->locationToPosition(location);
        }
        coordinate getPosition() const
        {
            return locationToPosition(ltAngle());
        }
        coordinate sizeInPixels () const
        {
            //coordinate result = locationToPosition(rtAngle());
            //printf ("locRTA is (%f, %f)\n", result.x_, result.y_);
            return cabs(locationToPosition(rtAngle()) - locationToPosition(location_)); 
        }

        //virtual coordinate positionToLocation (coordinate position) const
        //{

        //}
    //friend WidgetManager;
    };
//==========================================================================
    class WidgetManager: virtual public Widget
    {
    protected:
        //std::vector<std::unique_ptr<Widget>> widgets;
        std::vector<Widget*> widgets;

    public:
        WidgetManager(Widget* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        Widget(parent, size, location)
        {};

    public:
        bool catchEvent(const sf::Event event) override
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
        //void pushWidget(std::unique_ptr<Widget> new_widget_ptr)
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
            //std::cout<<"call from WM"<<std::endl;
            location.transmit (location_, size_);
            
            return parent_->locationToPosition(location);
        }

        virtual coordinate positionToLocation(coordinate position) const
        {
            return (position - location_)/size_;
        }
    };
//==========================================================================
    class WidgetMaster: public WidgetManager
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
            //std::cout<<"call from WMaster"<<std::endl;
            location.y_ = 1 - location.y_;
            //coordinate scale(window_ptr->getSize().x, window_ptr->getSize().y);
            //std::cout<<"meow"<<std::endl;
            //printf("scale is (%f, %f)\n", scale_.x_, scale_.y_);
            location = location*scale_;
            //printf("location is (%f, %f)\n", location.x_, location.y_);
            //printf("scale is (%f, %f)\n", scale.x_, scale.y_);
            return location;
        }

        coordinate positionToLocation (coordinate position) const override
        {
            position = position/scale_;
            position.y_ = 1 - position.y_;

            return position;
        }

        bool catchEvent(const sf::Event event) override
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

        bool catchClick(Click click) override
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