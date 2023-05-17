#include "../../include/GUI/Cleaner.hpp"

namespace gui
{
    Cleaner::Cleaner(Canvas& canvas, WidgetManager* parent, coordinate size, coordinate location):
            Widget(parent, size, location),
            Clickable(parent, size, location),
            CWidget(canvas, parent, size, location)
            {
                //view_.setFillColor(sf::Color::Cyan);
                view_.setPosition(getPosition());
                context_ptr->addTexture(TEXTURE_ID::Cleaner, "../assets/textures/cleaner.jpeg");
                sf::Texture texture = context_ptr->getTexture(TEXTURE_ID::Cleaner);         
                view_.setTexture(texture);
                view_.scale({getSizeInPixels().x_/(texture.getSize()).x, getSizeInPixels().y_/texture.getSize().y});
            
            };

    void Cleaner::respond2Click()
    {
        //std::cout<<"click on clear bottom"<<std::endl;
        canvas_.flush();
        //parent_->reDrawSig();
    }

    void Cleaner::draw()
    {
        //sf::Texture texture = context_ptr->getTexture(TEXTURE_ID::CLEANER);         
        view_.setTexture(context_ptr->getTexture(TEXTURE_ID::Cleaner));
        //view_.scale({getSizeInPixels().x_/(texture.getSize()).x, getSizeInPixels().y_/texture.getSize().y});
        
        context_ptr->window().draw(view_);

        //view_.scale();       
    }
}

