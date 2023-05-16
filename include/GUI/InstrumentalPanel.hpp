#pragma once

#include "ModeButtons.hpp"
#include "Panel.hpp"

namespace gui
{
    class InstrumentalPanel final: public Panel
    {
    public:
        InstrumentalPanel(Canvas& canvas, WidgetManager* parent, coordinate size, coordinate location):
            Panel(canvas, parent, size, location),
            Widget(parent, size, location)
            {
                auto dot_butt_ptr = new DotButton(canvas, this, {0.8, 0.133}, {0.1, 0.8});
                auto rul_butt_ptr = new RulerButton(canvas, this, {0.8, 0.133}, {0.1, 0.6});
                auto cir1_butt_ptr = new CircleArbitaryButton(canvas, this, {0.8, 0.133}, {0.1, 0.4});
                auto cir2_butt_ptr = new CircleSolutionButton(canvas, this, {0.8, 0.133}, {0.1, 0.2});
                
                pushWidget(dot_butt_ptr);
                pushWidget(rul_butt_ptr);
                pushWidget(cir1_butt_ptr);
                pushWidget(cir2_butt_ptr);
            };
    };
}