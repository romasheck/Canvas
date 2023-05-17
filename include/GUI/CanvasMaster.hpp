#ifndef CANVASMASTER_HPP
#define CANVASMASTER_HPP

#include <iostream>
#include <memory.h>

#include "Widget.hpp"
#include "Canvas.hpp"
#include "CWidget.hpp"
#include "CollorRegulator.hpp"
#include "InstrumentalPanel.hpp"
#include "Cleaner.hpp"


namespace gui
{
    //  SINGLE TYPE
    class CanvasMaster;
    CanvasMaster* CanvasMasterCtor(sf::Vector2f size);
    //Main Widget
    //Contain other and catch every Event
    class CanvasMaster final: public WidgetMaster 
    {
    private:
        Canvas* canvas_ptr_;//cratch!

    private:
        /// @brief Ctor with creating window with title "Canvas"
        /// @param size - absolute size of window (ex.:1920*1080)
        CanvasMaster(sf::Vector2f size):
        Widget(nullptr, {1, 1}, {0, 0}),
        WidgetMaster(size, "Canvas") 
        {};

        CanvasMaster(const CanvasMaster&) = delete;

    public:
        //create all his Widgets
        void createAll();

    private:
        //void loop() 

    private:
        void createCanvas(coordinate size, coordinate location);
        void createPanel(coordinate size, coordinate location);
        void createCleaner(coordinate size, coordinate location);
        /*
        void createColorRegulator(sf::Color color, coordinate size, coordinate location)
        {
            auto color_reg_ptr = new ColorRegulator(color, *canvas_ptr_, (Widget*)this, size, location);
            pushWidget(std::move(color_reg_ptr));
        }*/
        friend CanvasMaster* CanvasMasterCtor(sf::Vector2f);  
    };
}

#endif