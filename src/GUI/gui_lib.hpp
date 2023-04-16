#ifndef GUI_LIB_HPP
#define GUI_LIB_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
namespace gui
{
    /*
    One-window program need one window_ptr
    Useage off global var usefull, but danger there
    This must be const, but only MainWidget can create window
    Because of it tihs can not be const
    */
    sf::RenderWindow* window_ptr;
    /*
    namespace Color//wtf?
    {
        #define White   sf::Color::White;
        #define Black   sf::Color::Black;
        #define Red     sf::Color::Red;
        #define Blue    sf::Color::Blue;
        #define Green   sf::Color::Green;
        #define Magenta sf::Color::Magenta;
        #define Yellow  sf::Color::Yellow;
        #define Gray    sf::Color(100, 100, 100);
    }
    */
}

#endif