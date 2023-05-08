#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "gui_lib.hpp"
#include "coordinate.hpp"
#include <iostream>

namespace gui
{   
    class WidgetMaster;

    enum class MouseButtonStates
    {
        //CLICK,
        PRESSED,
        REALESED
    };

    enum class MouseEvents
    {
        MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
        MouseWheelScrolled,     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
        MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
        MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
        MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
        MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
        MouseLeft,              ///< The mouse cursor left the area of the window (no data)
        DEFAULT
    };

    class Mouse
    {
        friend WidgetMaster;

    private:
        MouseButtonStates rightState;
        MouseButtonStates leftState;
        MouseButtonStates wheelState;

        coordinate position;

        int wheelDelta;

        bool moved;

    private:
        bool isMyEvent(sf::Event event);

    private:
        void pressButton(MouseButtonStates&);

    public:
        Mouse():rightState(MouseButtonStates::REALESED),
                leftState(MouseButtonStates::REALESED),
                wheelState(MouseButtonStates::REALESED),
                wheelDelta(0),
                moved(false)
                {};

    public:
        MouseButtonStates getRight() const;
        MouseButtonStates getLeft() const;
        MouseButtonStates getWheel() const;

        int getWheelDelta() const;

        bool isMoved() const;
    };
}

#endif