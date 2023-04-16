#ifndef CANVASMASTER_HPP
#define CANVASMASTER_HPP

#include <iostream>
#include <memory.h>

#include "Widget.hpp"
#include "CanvasWidget.hpp"
#include "CWidgets.hpp"

namespace gui
{
    //Main Widget
    //Contain other and catch every Event
    class CanvasMaster final: public WidgetMaster 
    {
    private:
        Canvas* canvas_ptr_;//cratch!

    public:
        /// @brief Ctor with creating window with title "Canvas"
        /// @param size - absolute size of window (ex.:1920*1080)
        CanvasMaster(sf::Vector2f size):
        Widget(nullptr, {1, 1}, {0, 0}),
        WidgetMaster(size, "Canvas") 
        {};

    public:
        //create all his Widgets
        void createAll()
        {
            createCanvas({0.7, 0.8}, {0.1, 0.1});
            createPanel({0.1, 0.8}, \
                        canvas_ptr_->location_ + canvas_ptr_->size_ - coordinate(0, 0.8));
            //location = loc_canv + sz_canv - sz_ColorReg.y_
            //createColorRegulator (sf::Color::Green, {0.1, 0.1}, \
            {0.5, 0.5});
            /*//location = loc_canv + sz_canv - 2*sz_ColorReg.y_
            createColorRegulator (sf::Color::Red, {0.1, 0.1}, \
            canvas_ptr_->location_ + canvas_ptr_->size_ - coordinate(0, 0.2));
            */
        }
        //draw all his Widgets one time
        void drawAll()
        {
            for (const auto& widget_ptr: widgets_)
            {
                widget_ptr->draw();
                //std::cout<<1<<std::endl;
            }

            window_ptr->display();
        }
        //cycle catching event
        void loop()
        {
            while (window_ptr->isOpen())
            {
                
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
                }

                window_ptr->display();
                sf::sleep(sf::milliseconds(100));//delay
            }
        }

    private:
        void createCanvas(coordinate size, coordinate location)
        {
            //printf("Creating canvas with\n");
            //size.printMe("size");
            //location.printMe("location");
            canvas_ptr_ = new Canvas(this, size, location);
            pushWidget(canvas_ptr_);
        }
        void createPanel(coordinate size, coordinate location)
        {
            auto panel_ptr = new Panel(*canvas_ptr_, this, size, location);
            pushWidget(panel_ptr);

            panel_ptr->createAll();

            //panel_ptr->dumpMe("panel");
            //panel_ptr->locationToPosition(rtAngle()).printMe("rtAngle");

            //panel_ptr->locationToPosition(panel_ptr->location_).printMe("lbAngle");
            //(panel_ptr->locationToPosition(rtAngle()) - panel_ptr->locationToPosition(panel_ptr->location_)).printMe("recal sz");
        }
        
        void createColorRegulator(sf::Color color, coordinate size, coordinate location)
        {
            auto color_reg_ptr = new ColorRegulator(color, *canvas_ptr_, (Widget*)this, size, location);
            pushWidget(std::move(color_reg_ptr));
        }
        
    };
}

#endif