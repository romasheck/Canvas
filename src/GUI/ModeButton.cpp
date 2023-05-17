#include "../../include/GUI/ModeButton.hpp"

namespace gui
{
    ModeButton::ModeButton(CanvasPenMode type, Canvas& canvas, WidgetManager* parent, coordinate size, coordinate location):
        Widget(parent, size, location),
        Clickable(parent, size, location),
        CWidget(canvas, parent, size, location),
        type_(type)
        {};

    void ModeButton::respond2Click()
    {
        if (simpleLeftClick())
        {
            canvas_.penMode_ = type_;
        }
    }
}