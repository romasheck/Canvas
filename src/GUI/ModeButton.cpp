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
        if (context_ptr->mouse().getLeft() == MouseButtonStates::PRESSED)
        {
                
            if (wasPressed == true)
            {
                return;
            }
            else{
                wasPressed = true;
                canvas_.penMode_ = type_;
                //printf ("one of ModeButt was pressed\n");
            }
        }
        if(context_ptr->mouse().getLeft() == MouseButtonStates::REALESED)
        {
            wasPressed = false;
        }
    }
}