#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP

#include "Widget.hpp"

namespace gui
{
    class Clickable: virtual public Widget //Widget which must react on click
    {
        protected:
            coordinate clickLocation_;

        protected:
            virtual void respond2Click()
            {};
            virtual bool clickMe()
            {
                return inMe(clickLocation_);
            }
            
        public:
            Clickable(WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
            Widget(parent, size, location)
            {};

        public:
            bool catchEvent(const sf::Event event) override
            {
                /*if (event.type == sf::Event::MouseButtonPressed)
                {
                    clickLocation_ = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (clickMe() == true)
                    {
                        respond2Click();
                        return true;
                    }
                }*/
                return false;
            }
            bool catchClick (Click click) override
            {
                clickLocation_ = click.location_;

                if (clickMe() == true)
                {
                    respond2Click();
                    return true;
                }

                return false;
            }
    };
}

#endif