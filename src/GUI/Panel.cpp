#include "../../include/GUI/Panel.hpp"

namespace gui
{
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
}