#include "../../include/GUI/Clickable.hpp"

namespace gui
{
    bool Clickable::clickMe ()
    {
        return inMe(clickLocation_);
    }

    bool Clickable::catchClick (Click click)
    {
        clickLocation_ = click.location_;

        if (clickMe() == true)
        {
            updateActive();
            respond2Click();
            return true;
        }

        return false;
    }

    void Clickable::loseActive()
    {
        wasPressed = false;
    }

    bool Clickable::simpleLeftClick()
    {
        if (context_ptr->mouse().getLeft() == MouseButtonStates::PRESSED)
        {
            if (wasPressed == true)
            {
                return false;
            }
            else
            {
                wasPressed = true;
                return true;
            }
        }
        if(context_ptr->mouse().getLeft() == MouseButtonStates::REALESED)
        {
            wasPressed = false;
            return false;
        }

        return false;
    }
}