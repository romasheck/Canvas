#ifndef CLEANER_HPP
#define CLEANER_HPP

#include "Clickable.hpp"
#include "CWidget.hpp"

namespace gui
{
    class Cleaner: public Clickable, public CWidget
    {
    private:
        sf::Sprite view_;

    public:
        Cleaner(Canvas& canvas, WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f});
        
        void respond2Click() override;
        
        void draw() override;
    };
}

#endif