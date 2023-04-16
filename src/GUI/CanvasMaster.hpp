#ifndef CANVASMASTER_HPP
#define CANVASMASTER_HPP

#include <iostream>
#include <memory.h>

#include "Widget.hpp"
#include "CanvasWidget.hpp"
#include "CWidgets.hpp"

namespace gui
{
    class CanvasMaster final: public WidgetMaster 
    {
    private:
        Canvas* canvas_ptr_;

    public:
        CanvasMaster(sf::Vector2f size):
        Widget(nullptr, {1, 1}, {0, 0}),
        WidgetMaster(size, "Canvas")
        //WidgetManager(nullptr, size, {0, 0}),
        {};

    public:
        void createAll()
        {
            createCanvas({0.7, 0.8}, {0.1, 0.1});
            createColorRegulator (sf::Color::Green, {0.1, 0.1}, canvas_ptr_->location_+canvas_ptr_->size_ - coordinate(0, 0.1));
            createColorRegulator (sf::Color::Red, {0.1, 0.1}, canvas_ptr_->location_ + canvas_ptr_->size_ - coordinate(0, 0.2));
        }

        void drawAll()
        {
            for (const auto& widget_ptr: widgets)
            {
                widget_ptr->draw();
            }
        }

        void loop()
        {
            while (window_ptr->isOpen())
            {
                
                //drawAll();
                
                sf::Event event;
                while (window_ptr->pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window_ptr->close();
                    }
                    else
                    {
                        catchEvent(event);
                    }
                    /*if (canvas_ptr_->catchEvent(event) == true)
                    {
                        //std::cout<<"someone catch event"<<std::endl;
                        continue;
                    }
                    else
                    {
                        for (auto widget: widgets)
                        {
                            if (widget->catchEvent(event))
                            {
                                continue;
                            }
                        }
                        if (event.type == sf::Event::Closed)
                        {
                            window_ptr->close();
                        }
                    }*/
                }

                window_ptr->display();
                sf::sleep(sf::milliseconds(500));
            }
        }

    private:
        enum
        {
            CANVAS_PLACE = 0,
        };

        void createCanvas(coordinate size, coordinate location)
        {
            canvas_ptr_ = new Canvas(this, size, location);
            pushWidget(canvas_ptr_);
        }

        void createColorRegulator(sf::Color color, coordinate size, coordinate location)
        {
            auto color_reg_ptr = new ColorRegulator(color, *canvas_ptr_, (Widget*)this, size, location);
            pushWidget(std::move(color_reg_ptr));
        }
    };
}

#endif