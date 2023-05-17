#include "../../include/GUI/ModeButtons.hpp"
#include "../../include/GUI/Canvas.hpp"

namespace gui
{
#define MAKE_CLASS_DEFINITION(class_name, type, path)                                                   \
    class_name::class_name(Canvas& canvas, WidgetManager* parent, coordinate size, coordinate location):\
        Widget(parent, size, location),                                                                 \
        ModeButton(CanvasPenMode:: type, canvas, parent, size, location),                                               \
        SimpleView(TEXTURE_ID:: class_name, path, parent, size, location)                                            \
        {};

    MAKE_CLASS_DEFINITION(DotButton, Dot, "../assets/textures/Dot.png")
    MAKE_CLASS_DEFINITION(RulerButton, Ruler, "../assets/textures/Ruler.png")
    MAKE_CLASS_DEFINITION(CircleArbitaryButton, CircleArbitary, "../assets/textures/CircleArbitary.png")
    MAKE_CLASS_DEFINITION(CircleSolutionButton, CircleSolution, "../assets/textures/CircleSoution.png")

}
