#ifndef GUI_LIB_HPP
#define GUI_LIB_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
namespace gui
{
    /*
    One-window program need one window_ptr
    Useage off global var usefull, but danger there
    This must be const, but only MainWidget can
    */
    sf::RenderWindow* window_ptr;
}

#endif