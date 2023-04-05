#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gui.hpp"
#include <iostream>

namespace gui
{

    class Widget
    {
    private:
        std::vector<pixel> pixels;

    public:
        //void draw() const; Managers role
        std::vector<pixel> getPixels() const {
            return pixels;
        }
        virtual void fillPixels() = 0;
        
        void close();
    };

}

#endif