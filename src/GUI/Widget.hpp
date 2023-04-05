#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gui_lib.hpp"
#include "Pixel.hpp"
//#include "GrShapes.hpp"
#include <iostream>

namespace gui
{
    class BoundingBox
    {
    private:
        sf::Vector2f location;
        sf::Vector2f size;

    public:
        
    };

    class Widget // : public GrShape
    {
    private:
        Widget* const canvas_ptr;
        const int type;

    public:
        Widget(Widget* const canvas_ptr_, const int type_):
        canvas_ptr(canvas_ptr_), type(type_)
        {};
    
    public:
        struct HandlerInfo
        {
            bool catched = false;
            bool forParent = false;
            int signal = DEFAULT;
        };
        virtual HandlerInfo catchEvent(const sf::Event event) = 0;
    
    public:
        const int type() const {return type;}
        enum TYPES
        {
            SLAVE,
            MASTER,
        };
    };

    class WidgetManager: public Widget
    {
    private:
        std::vector<Widget*> widgets;

    private:
        virtual void reqeustToSignal(int signal);
        enum SIGNALS
        {
            DEFAULT = 0,
        };

    public:

    
    public:
        HandlerInfo catchEvent(const sf::Event event)
        {
            HandlerInfo input_info;
            HandlerInfo output_info;

            for (const auto& widget_ptr : widgets)
            {
                input_info = widget_ptr->catchEvent(event);
                if (input_info.catched = false)
                {
                    continue;
                }
                else
                {
                    output_info.catched = true;
                    if (widget_ptr->type() == SLAVE)
                    {
                        if (input_info.forParent = false)
                        {
                            break;
                        }
                        else{
                            reqeustToSignal(input_info.signal); 
                        }
                    }
                    
                }
            }

            return output_info;
        }
    };
}

#endif