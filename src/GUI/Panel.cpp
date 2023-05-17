#include "../../include/GUI/Panel.hpp"
#include <iostream>

namespace gui
{/*
    void Panel::draw()
    {
        context_ptr->window().draw(background_);

        for (const auto& widget_ptr: widgets_)
        {
            widget_ptr->draw();
        }
    }

    void Panel::createColorRegulator(sf::Color color, coordinate size, coordinate location)
    {
        auto color_reg_ptr = new ColorRegulator(color, canvas_, this, size, location);
        pushWidget(std::move(color_reg_ptr));
    }
*/
    Panel::Panel(Canvas& canvas, WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        CWidgetManager(canvas, parent, size, location),
        SimpleView(TEXTURE_ID::Panel, "../assets/textures/magenta_rectangle.jpg", parent, size, location),
        Widget(parent, size, location)
        {};

    void Panel::draw()
    {
        SimpleView::draw();
        WidgetManager::draw();
    }
}