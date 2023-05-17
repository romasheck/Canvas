#include "../../include/GUI/Canvas.hpp"

namespace gui
{
    Canvas::Canvas(WidgetManager* parent, coordinate size, coordinate location):
        Clickable(parent, size, location),
        Widget(parent, size, location),
        currentColor_(sf::Color::Red),
        penMode_(CanvasPenMode::Default),
        projector_(*this)
    {
        background_.setPosition(getPosition());
        Widget::context_ptr->addTexture(TEXTURE_ID::Paper, "../assets/textures/white-texture.jpg");
        sf::Texture texture = context_ptr->getTexture(TEXTURE_ID::Paper);         
        background_.setTexture(texture);
        background_.scale({getSizeInPixels().x_/(texture.getSize()).x, getSizeInPixels().y_/texture.getSize().y});
        
        currentStain_.setFillColor(sf::Color::Red);
        currentStain_.setRadius(10);
    }

    void Canvas::setCurrentColor(sf::Color cur_color)
    {
        currentColor_ = cur_color;
    }

    void Canvas::respond2Click()
    {   
        sf::Time currentTime = context_ptr->getTime();

        if (simpleLeftClick())
        {
            if (!(penMode_ & ARTISTIC))
            {
                projector_.processPen(penMode_, locloc(clickLocation_));
            }
            else
            {
                if (penMode_ == CanvasPenMode::Pencil)
                {
                    if (context_ptr->mouse().getLeft() == MouseButtonStates::PRESSED)
                    {
                        sf::Vector2f clickPosition = locationToPosition(clickLocation_);
                        
                        if (/*currentTime - lastInteraction > PAUSE &&*/
                            dist(clickPosition, currentStain_.getPosition()) > 10)
                        {
                            currentStain_.setFillColor(currentColor_);
                            currentStain_.setPosition(clickPosition - sf::Vector2f{currentStain_.getRadius(), currentStain_.getRadius()});
                            context_ptr->window().draw(currentStain_);
                        
                            lastInteraction = currentTime;
                        }
                    }
                }
            }
        }

        if (penMode_ & DEFAULT)
        {
            if (context_ptr->mouse().getLeft() == MouseButtonStates::PRESSED
                && currentTime - lastInteraction > sf::Time(sf::milliseconds(500)))
            {
                printf ("choose instrument\n");

                lastInteraction = context_ptr->getTime();
            }
        }    
    }

    void Canvas::draw()
    {
        background_.setTexture(context_ptr->getTexture(TEXTURE_ID::Paper));
        //return;
        Widget::context_ptr->window().draw(background_);
        //std::cout<<1<<std::endl;
        //printf ("canvas\n");

        projector_.reDraw();
    }

    coordinate Canvas::locloc (const coordinate location) const
    {
        auto res = (location - location_)/size_; 

        //res.printMe("res in locloc");

        return res;
    }

    coordinate Canvas::colcol (const coordinate loc) const
    {
        auto res = (loc*size_) + location_;

        //res.printMe("res in colcol");

        return res;
    }

    coordinate Canvas::locToPos(const coordinate loc) const
    {
        return locationToPosition(colcol(loc));
    }

    void Canvas::flush()
    {
        //draw();
        projector_.flush();

        parent_->reDrawSig();
    }
}