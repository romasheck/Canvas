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
        createCanvas({0.7, 0.8}, {0.1, 0.1});
        createPanel({0.1, 0.8}, \
                    canvas_ptr_->location_ + canvas_ptr_->size_ - coordinate(0, 0.8));
        createCleaner({0.1, 0.1}, {0.05, 0.85});
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

    void CanvasMaster::createCleaner(coordinate size, coordinate location)
    {
        auto butt_ptr = new Cleaner(*canvas_ptr_, this, size, location);
        pushWidget(butt_ptr);
    }
}