#ifndef CLICKABLE_HPP
#define CLICKABLE_HPP

#include "Widget.hpp"

namespace gui
{
    class Clickable: virtual public Widget //Widget which must react on click
    {
        protected:
            coordinate clickLocation_;

        protected:
            virtual void respond2Click() {};
            //virtual void respond2Press() {};
            //virtual void respond2Realese() {};

            virtual bool clickMe();
            
        public:
            Clickable(WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
            Widget(parent, size, location)
            {};

        public:
            bool catchClick (Click click) override;
    };
}

#endif