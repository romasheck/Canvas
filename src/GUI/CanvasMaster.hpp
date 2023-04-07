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
        WidgetMaster(size),
        WidgetManager(nullptr, size, {0, 0}),
        Widget(nullptr, size, {0, 0})
        {
            window_ptr = new sf::RenderWindow(sf::VideoMode(size.x, size.y), "Canvas");
        }

    public:
        void createAll()
        {
            createCanvas({getSize().x-400, getSize().y - 200},\
                        {100, 100});
            //createColorRegulator (sf::Color::Green, {250, 100}, {800, 100});
            //createColorRegulator (sf::Color::Red, {250, 100}, {800, 150});
        }

        void drawAll()
        {
            for (const auto& widget_ptr: widgets)
            {
                widget_ptr->draw();
            }
        }

        void lookupUpdate()
        {
            while (window_ptr->isOpen())
            {
                drawAll();
                sf::Event event;
                while (window_ptr->pollEvent(event))
                {
                    if (canvas_ptr_->catchEvent(event))
                    {
                        continue;
                    }
                    if (event.type == sf::Event::Closed)
                    {
                        window_ptr->close();
                    }
                }

                window_ptr->display();
            }
        }

    private:
        enum
        {
            CANVAS_PLACE = 0,
        };

        void createCanvas(sf::Vector2f canv_size, sf::Vector2f canv_location)
        {
            canvas_ptr_ = new Canvas(this, canv_size, canv_location);
            pushWidget(canvas_ptr_);
        }

        void createColorRegulator(sf::Color color, sf::Vector2f size, sf::Vector2f location)
        {
            auto color_reg_ptr = new ColorRegulator(color, *canvas_ptr_, (Widget*)this, size, location);
            pushWidget(std::move(color_reg_ptr));
        }
    };
}

#endif