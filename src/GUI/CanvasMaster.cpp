#include "../../include/GUI/CanvasMaster.hpp"

namespace gui
{
    CanvasMaster* CanvasMasterCtor(sf::Vector2f size)
    {
        static CanvasMaster canvas_master(size);

        return &canvas_master;
    }

    void CanvasMaster::createAll()
    {
        createCanvas({1.0, 1.0}, {0, 0});
        createPanel({0.07, 0.6}, {0.91, 0.3});
        createCleaner({0.045, 0.045}, {0.005, 0.905});
    }
    
    void CanvasMaster::createCanvas(coordinate size, coordinate location)
    {
        canvas_ptr_ = new Canvas(this, size, location);
        pushWidget(canvas_ptr_);
    }

    void CanvasMaster::createPanel(coordinate size, coordinate location)
    {
        auto panel_ptr = new InstrumentalPanel(*canvas_ptr_, this, size, location);
        pushWidget(panel_ptr);
    }

    void CanvasMaster::createCleaner(coordinate size, coordinate location)
    {
        auto butt_ptr = new Cleaner(*canvas_ptr_, this, size, location);
        pushWidget(butt_ptr);
    }
}