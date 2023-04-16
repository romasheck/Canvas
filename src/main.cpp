#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <SFML/System/Sleep.hpp>

#include "GUI/gui.hpp"


int main()
{
    gui::CanvasMaster canvas_master({1000, 1000});
    
    canvas_master.createAll();
    canvas_master.drawAll();

    canvas_master.loop();

    return 0;
}