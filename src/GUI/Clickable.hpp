#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP

#include "Widget.hpp"

namespace gui
{
    class Clickable: virtual public Widget
    {
        protected:
            sf::Vector2f clickPosition_;

        protected:
            virtual void respond2Click()
            {};
            virtual bool clickMe()
            {
                //std::cout<<"in function clickMe"<<std::endl;
                return inMe(clickPosition_);
            }
            
        public:
            Clickable(Widget* parent, sf::Vector2f size = {10.f, 10.f}, sf::Vector2f location = {0.f, 0.f}):
            Widget(parent, size, location)
            {};

        public:
            bool catchEvent(const sf::Event event) override
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    clickPosition_ = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (clickMe() == true)
                    {
                        respond2Click();
                        return true;
                    }
                }
                return false;
            }
    };
}

#endif