#ifndef CWIDGETS_HPP
#define CWIDGETS_HPP

#include "Canvas.hpp"

namespace gui
{
    class CWidget : virtual public Widget //Widget which can affect canvas
    {
    protected:
        Canvas& canvas_;
    public:
        CWidget(Canvas& canvas, Widget* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        Widget(parent, size, location),
        canvas_(canvas){};
    };
//==========================================================================
    class CWidgetManager : public WidgetManager, public CWidget
    {
    public: 
        CWidgetManager(Canvas& canvas, Widget* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        Widget(parent, size, location),
        CWidget(canvas, parent, size, location),
        WidgetManager(parent, size, location)
        {};
    };
}

#endif