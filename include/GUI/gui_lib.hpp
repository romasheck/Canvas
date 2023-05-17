#ifndef GUI_LIB_HPP
#define GUI_LIB_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

//#include "Context.hpp"

namespace gui
{
    #define PRINT_LINE //printf ("I am on the line %d\n", __LINE__);
    /*
    One-window program need one window_ptr
    Useage off global var usefull, but danger there
    This must be const, but only MainWidget can create window
    Because of it tihs can not be const
    */
    //extern sf::RenderWindow* window_ptr;
}

#endif