#include "Widget.hpp"

namespace gui
{
    sf::RenderWindow* window_ptr;
//======================================================
    bool WidBox::inMe (const coordinate position)
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

    coordinate WidBox::rtAngle() const //return right top angle of WidBox
    {
        return location_ + size_;
    }

    coordinate WidBox::ltAngle() const
    {
        return location_ + coordinate(0, size_.y_);
    }
//======================================================
    void Widget::draw() //default: draw blue rectangle in W
    {
        sf::RectangleShape bad_view_;

        bad_view_.setSize(getSizeInPixels());
        bad_view_.setPosition(getPosition());
        bad_view_.setFillColor(sf::Color::Blue);

        window_ptr->draw(bad_view_);
    }

    bool Widget::catchEvent(const sf::Event event)
    {
        return false;
    }

    bool Widget::catchClick (Click click)
    {
        return false;
    } 

    coordinate Widget::locationToPosition(coordinate location) const
    {
        return parent_->locationToPosition(location);
    }

    coordinate Widget::getSizeInPixels () const
    {
        return cabs(Widget::locationToPosition(rtAngle()) - Widget::locationToPosition(location_)); 
    }

    coordinate Widget::getPosition() const
    {
        return Widget::locationToPosition(ltAngle());
    }

    void Widget::dumpMe (const char* name) const
    {
        printf("Widget %s\n", name);

        location_.printMe("location");
        size_.printMe("size");

        rtAngle().printMe("rtAngle loc");
        ltAngle().printMe("ltAngle loc");

        getPosition().printMe("position");
        getSizeInPixels().printMe("szInPxls");
        
        locationToPosition(location_).printMe("lbAngle");
        locationToPosition(rtAngle()).printMe("rtAngle");   
    }
//======================================================
    bool WidgetManager::catchEvent(const sf::Event event) // still useless shit
    {
        bool catched = false;

        for (auto it = widgets_.rbegin(); it != widgets_.rend(); ++it)
        {
            catched = (*it)->catchEvent(event);
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

    bool WidgetManager::catchClick (Click click)
    {
        bool catched = false;

        if (inMe(click.location_))
        {
            click.location_ = positionToLocation(click.location_);

            for (auto it = widgets_.rbegin(); it != widgets_.rend(); ++it)
            {
                catched = (*it)->catchClick(click);
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

    void WidgetManager::pushWidget(Widget* widget_ptr)
    {
        widgets_.push_back(widget_ptr);
    }

    void WidgetManager::popWidget()
    {
        widgets_.pop_back();
    }

    coordinate WidgetManager::locationToPosition(coordinate location) const
    {

        location.transmit (location_, size_);//transmit into parent system
        
        return parent_->locationToPosition(location);
    }

    coordinate WidgetManager::positionToLocation(coordinate position) const
    {
        return (position - location_)/size_;
    }
//======================================================
    coordinate WidgetMaster::locationToPosition (coordinate location) const
    {
        location.y_ = 1 - location.y_;// make y_ upsidedown

        location = location*scale_;// multiply coordinate (from 0 to 1) on amount of pixels in side

        return location;
    }

    coordinate WidgetMaster::positionToLocation (coordinate position) const
    {
        position = position/scale_;// dev position in pixels on amount of pixels in side
        
        position.y_ = 1 - position.y_;// make y_ upsidedown

        return position;
    }

    bool WidgetMaster::catchEvent(const sf::Event event) //still can catch only Click
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

    bool WidgetMaster::catchClick(Click click)//recalc pixel pos to loc coord and pass click to his widgets
    {
        bool catched = false;

        click.location_ = positionToLocation(click.location_);

        for (auto it = widgets_.rbegin(); it != widgets_.rend(); ++it)
        {
            catched = (*it)->catchClick(click);
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
}