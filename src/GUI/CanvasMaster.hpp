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
        {//{getSize().x-400, getSize().y - 200}
            createCanvas({0.5, 0.6} ,\
                        {0.15, 0.1});
            createColorRegulator (sf::Color::Green, {0.1, 0.1}, canvas_ptr_->location_+canvas_ptr_->size_);
            createColorRegulator (sf::Color::Red, {0.1, 0.1}, canvas_ptr_->location_ + canvas_ptr_->size_ - coordinate(0, 0.1));
        }

        void drawAll()
        {
            for (const auto& widget_ptr: widgets)
            {
                widget_ptr->draw();
                std::cout<<"Master have drown widget with position "<< widget_ptr->locationToPosition(widget_ptr->location_).x_\
                <<" "<<widget_ptr->locationToPosition(widget_ptr->location_).y_\
                <<" with size in pixels "<< widget_ptr->sizeInPixels().x_\
                <<" "<< widget_ptr->sizeInPixels().y_ <<std::endl;
                std::cout<<"Master have drown widget with location "<< widget_ptr->location_.x_\
                <<" "<<widget_ptr->location_.y_\
                <<" with local size "<< widget_ptr->size_.x_\
                <<" "<< widget_ptr->size_.y_ <<std::endl;
                //printf("rtAngle is (%f, %f)", widget_ptr->rtAngle().x_, widget_ptr->rtAngle().y_);
                printf("\n");
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
                sf::sleep(sf::milliseconds(300));
            }
        }

    private:
        enum
        {
            CANVAS_PLACE = 0,
        };

        void createCanvas(coordinate canv_size, coordinate canv_location)
        {
            canvas_ptr_ = new Canvas(this, canv_size, canv_location);
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