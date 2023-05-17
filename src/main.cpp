#include <iostream>

#include "../include/gui.hpp"

int main()
{
    gui::CanvasMaster* canvas_master_ptr = gui::CanvasMasterCtor({1920, 1080});
    PRINT_LINE
    canvas_master_ptr->createAll();
    //gui::Widget* test_widget_ptr = new gui::Widget(canvas_master_ptr, {0.5, 0.3}, {0.2, 0.3});
    //canvas_master_ptr->pushWidget(test_widget_ptr);
    
    canvas_master_ptr->drawAll();

    canvas_master_ptr->loop();
    /*
    gui::CanvasMaster canvas_master({1000, 1000});
    
    canvas_master.createAll();
    canvas_master.drawAll();

    canvas_master.loop();
    */
    return 0;
}