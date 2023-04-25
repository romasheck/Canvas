#ifndef GUI_LIB_HPP
#define GUI_LIB_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

namespace gui
{
    /*
    One-window program need one window_ptr
    Useage off global var usefull, but danger there
    This must be const, but only MainWidget can create window
    Because of it tihs can not be const
    */
    extern sf::RenderWindow* window_ptr;
    /*
    class WidgetMaster;
    class Context
    {
        friend WidgetMaster;
    private:
        std::unique_ptr<sf::RenderWindow> window_ptr;
        void init(sf::Vector2f, const char*);

    public:
        sf::RenderWindow window()
    };

    extern Context context;*/
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