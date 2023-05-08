#pragma once

#include "ModeButton.hpp"
#include "SimpleView.hpp"

namespace gui
{
#define MAKE_CLASS_DECLARATION(class_name)                              \
    class class_name final: protected ModeButton, protected SimpleView  \
    {                                                                   \
    public:                                                             \
        class_name(Canvas&, WidgetManager*, coordinate, coordinate);    \
    };
    
    MAKE_CLASS_DECLARATION(DotButton)
    MAKE_CLASS_DECLARATION(RulerButton)
    MAKE_CLASS_DECLARATION(CircleSolutionButton)
    MAKE_CLASS_DECLARATION(CircleArbitaryButton)
    MAKE_CLASS_DECLARATION(PencilButton)

#undef MAKE_CLASS_DECLARATION
}