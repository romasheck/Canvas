#include "CanvasMaster.hpp"

namespace gui
{
    CanvasMaster* CanvasMasterCtor(sf::Vector2f size)
    {
        static CanvasMaster canvas_master(size);

        return &canvas_master;
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

    void CanvasMaster::createClearButtom(coordinate size, coordinate location)
    {
        auto butt_ptr = new ClearButtom(*canvas_ptr_, this, size, location);
        pushWidget(butt_ptr);
    }
}