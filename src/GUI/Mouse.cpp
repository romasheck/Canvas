#include "../../include/GUI/Mouse.hpp"

namespace gui
{   
    /*void Mouse::pressButton (MouseButtonStates& button)
    {
        if (button == MouseButtonStates::PRESSED)
        {
            button = MouseButtonStates::PRESSED;
            return;
        }
        if (button == MouseButtonStates::CLICK)
        {
            printf ("ku=ku\n");
            button = MouseButtonStates::PRESSED;
        }
        if (button == MouseButtonStates::REALESED)
        {
            button = MouseButtonStates::CLICK;
        }
    }
    /*#define SET_STATE(BUTTOM_STATE, MODE)                         \
    if (BUTTOM_STATE == PRESSED) {return true;}             \
    if (BUTTOM_STATE == CLICK)                              \
    {                                                       \
        BUTTON_STATE = PRESSED;                             \
    }                                                       \
    if (BUTTON_STATE == REALESED)                           \
    {                                                       \
        BUTTON_STATE = CLICK;                               \
    }*/

    #define BUTTON_STATE(MODE)                              \
    if (event.mouseButton.button == sf::Mouse::Left)        \
        {                                                   \
            leftState = MouseButtonStates::MODE;            \
            return true;                                    \
        }                                                   \
        if (event.mouseButton.button == sf::Mouse::Right)   \
        {                                                   \
            rightState = MouseButtonStates::MODE;           \
            return true;                                    \
        }                                                   \
        if (event.mouseButton.button = sf::Mouse::Middle)   \
        {                                                   \
            wheelState == MouseButtonStates::MODE;          \
            return true;                                    \
        }
        
    bool Mouse::isMyEvent(sf::Event event)
    {
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
        {   
            position = coordinate(event.mouseButton.x, event.mouseButton.y);
            BUTTON_STATE(PRESSED)
            /*if (event.mouseButton.button == sf::Mouse::Left)         
            {                                                    
                pressButton(leftState);           
                return true;                                     
            }                                                    
            if (event.mouseButton.button == sf::Mouse::Right)    
            {                                                    
                pressButton(rightState);           
                return true;                                     
            }                                                    
            if (event.mouseButton.button = sf::Mouse::Middle)    
            {                                                    
                pressButton(wheelState);           
                return true;                                     
            }*/
            return true;
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            position = coordinate(event.mouseButton.x, event.mouseButton.y);
            BUTTON_STATE(REALESED)
            return true;
            break;
        }
        case sf::Event::MouseMoved:
        {   
            position = coordinate(event.mouseMove.x, event.mouseMove.y);
            moved == true;
            return true;
            break;
        }
        case sf::Event::MouseWheelMoved:
        {   
            position = coordinate(event.mouseWheel.x, event.mouseWheel.y);
            wheelDelta = event.mouseWheel.delta;
            return true;
            break;
        }
        case sf::Event::MouseEntered:
        {
            //code
            return true;
            break;
        }
        case sf::Event::MouseLeft:
        {
            //code
            return true;
            break;
        }
        default:
        {
            return false;
            break;
        }
        }
    }
    #undef BUTTON_STATE(MODE)

    MouseButtonStates Mouse::getRight() const
    {
        return rightState;
    }

    MouseButtonStates Mouse::getLeft() const
    {
        return leftState;
    }

    MouseButtonStates Mouse::getWheel() const
    {
        return wheelState;
    }

    int Mouse::getWheelDelta() const
    {
        return wheelDelta;
    }

    bool Mouse::isMoved() const
    {
        return moved;
    }
}