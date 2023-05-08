#include "../../include/GUI/ModeButtons.hpp"
#include "../../include/GUI/Canvas.hpp"

namespace gui
{
#define MAKE_CLASS_DEFINITION(class_name, type, path)                                                   \
    class_name::class_name(Canvas& canvas, WidgetManager* parent, coordinate size, coordinate location):\
        Widget(parent, size, location),                                                                 \
        ModeButton(Canvas::PenMode:: type, canvas, parent, size, location),                                               \
        SimpleView(TEXTURE_ID:: class_name, path, parent, size, location)                                            \
        {};

    MAKE_CLASS_DEFINITION(DotButton, Dot, "assets/textures/black-dot.jpg")
    MAKE_CLASS_DEFINITION(RulerButton, Ruler, "assets/textures/line")

}
