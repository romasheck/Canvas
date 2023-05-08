#include "../../include/GUI/ModeButton.hpp"

namespace gui
{
    ModeButton::ModeButton(Canvas::PenMode type, Canvas& canvas, WidgetManager* parent, coordinate size, coordinate location):
        Widget(parent, size, location),
        Clickable(parent, size, location),
        CWidget(canvas, parent, size, location),
        type_(type),
        wasPressed(false)
        {};

    void ModeButton::respond2Click()
    {
        if (wasPressed == false)
        {
            return;
        }
        else{
            wasPressed = true;
            canvas_.penMode_ = type_;
        }
    }
}