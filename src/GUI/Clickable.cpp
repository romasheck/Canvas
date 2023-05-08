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
            respond2Click();
            return true;
        }

        return false;
    }
}