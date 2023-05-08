#pragma once

#include "Widget.hpp"
#include <iostream>


namespace gui
{
    class SimpleView : virtual public Widget
    {
    private:
        sf::Sprite view_;
        TEXTURE_ID id_;

    public:
        SimpleView(const TEXTURE_ID id, const std::string&, WidgetManager*, coordinate, coordinate);

        void draw() override;
    };
}