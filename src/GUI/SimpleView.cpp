#include "../../include/GUI/SimpleView.hpp"

namespace gui
{
    SimpleView::SimpleView (const TEXTURE_ID id, const std::string& path2texture, WidgetManager* parent, coordinate size, coordinate location):
        Widget(parent, size, location),
        id_(id)
    {
        view_.setPosition(getPosition());
        
        context_ptr->addTexture(id_, path2texture);
        sf::Texture texture = context_ptr->getTexture(id_);         
        view_.setTexture(texture);
        
        view_.scale({getSizeInPixels().x_/(texture.getSize()).x, getSizeInPixels().y_/texture.getSize().y});
    }

    void SimpleView::draw()
    {
        view_.setTexture(context_ptr->getTexture(id_));
        
        context_ptr->window().draw(view_);
    }
    
}