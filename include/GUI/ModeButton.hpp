#pragma once

#include "CWidget.hpp"

namespace gui
{
    class ModeButton: public CWidget, public Clickable
    {
    private:
        const Canvas::PenMode type_;
        bool wasPressed;

    public:
        ModeButton(Canvas::PenMode type, Canvas& canvas, WidgetManager* parent, coordinate size, coordinate location);

    protected:
        void respond2Click() override;
    };

}