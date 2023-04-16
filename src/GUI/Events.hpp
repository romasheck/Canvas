#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "gui_lib.hpp"
#include "coordinate.hpp"

namespace gui
{
    class Click
    {
    public:
        coordinate location_;

    public:
        Click(const sf::Event event):
        location_(event.mouseButton.x, event.mouseButton.y)
        {};
        Click(const coordinate location):
        location_(location)
        {};
    };
}

#endif