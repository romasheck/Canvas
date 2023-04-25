#include "CanvasMaster.hpp"

namespace gui
{
    void CanvasMaster::drawAll()
    {
        for (const auto& widget_ptr: widgets_)
        {
            widget_ptr->draw();
        }

        window_ptr->display();
    }

    void CanvasMaster::loop()
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

    void CanvasMaster::createCanvas(coordinate size, coordinate location)
    {
        canvas_ptr_ = new Canvas(this, size, location);
        pushWidget(canvas_ptr_);
    }

    void CanvasMaster::createPanel(coordinate size, coordinate location)
    {
        auto panel_ptr = new Panel(*canvas_ptr_, this, size, location);
        pushWidget(panel_ptr);

        panel_ptr->createAll();
    }
}