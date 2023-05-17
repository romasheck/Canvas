#pragma once

#include "CWidget.hpp"

namespace gui
{
    class ModeButton: public CWidget, public Clickable
    {
    private:
        const CanvasPenMode type_;

    public:
        ModeButton(CanvasPenMode type, Canvas& canvas, WidgetManager* parent, coordinate size, coordinate location);

    protected:
        void respond2Click() override;
    };

}