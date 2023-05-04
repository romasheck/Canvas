#include "Widget.hpp"

namespace gui
{
//======================================================
    bool WidBox::inMe (const coordinate position) const
    {
        if (position.x_ > location_.x_ && \
            position.x_ < (location_.x_ + size_.x_) &&\
            position.y_ > location_.y_ && \
            position.y_ < (location_.y_ + size_.y_))
        {
            return true;
        }
        return false;
    }

    coordinate WidBox::rtAngle() const //return right top angle of WidBox
    {
        return location_ + size_;
    }

    coordinate WidBox::ltAngle() const
    {
        return location_ + coordinate(0, size_.y_);
    }

    coordinate WidBox::rbAngle() const
    {
        return location_ + coordinate(size_.x_, 0);
    }
//======================================================
    void Widget::viewInit(const std::string& texture_path, const std::string& text)
    {
        sf::Sprite sprite_;
        sprite_.setPosition(getPosition());
        
        sf::Texture bad_view;
        bad_view.loadFromFile("assets/textures/maxresdefault.jpg");
        
        sprite_.setTexture(bad_view);
        sprite_.scale({getSizeInPixels().x_/(bad_view.getSize()).x, getSizeInPixels().y_/bad_view.getSize().y});

        window_ptr->draw(sprite_);

        sf::Font font;
        font.loadFromFile("assets/fonts/FFF_Tusj.ttf");
        sf::Text error_msg;
        error_msg.setFont(font);
        error_msg.setString("Ha-ha!");
        error_msg.setCharacterSize((locationToPosition(rtAngle())-getPosition()).x_*2/3);
        error_msg.setPosition(getPosition() - getSizeInPixels()/3);
    }
    
    void Widget::draw() //default: draw blue rectangle in W
    {
        sf::Sprite sprite_;
        sprite_.setPosition(getPosition());
        
        sf::Texture bad_view;
        bad_view.loadFromFile("assets/textures/maxresdefault.jpg");
        
        sprite_.setTexture(bad_view);
        sprite_.scale({getSizeInPixels().x_/(bad_view.getSize()).x, getSizeInPixels().y_/bad_view.getSize().y});

        window_ptr->draw(sprite_);

        sf::Font font;
        font.loadFromFile("assets/fonts/Raleway-Black.ttf");
        sf::Text error_msg;
        error_msg.setFont(font);
        error_msg.setColor(sf::Color::Yellow);
        error_msg.setString("H");
        //error_msg.setCharacterSize(getSizeInPixels().x_/error_msg.getString().getSize());
        error_msg.setCharacterSize(200);
        //error_msg.setPosition(getPosition() + coordinate(getSizeInPixels().x_/3, getSizeInPixels().y_/2));
        auto pos = parent_->locationToPosition({0.05, 0.95});
        error_msg.setPosition(pos.x_, pos.y_);
        printf("text must be o (%f, %f) with size %d\n", error_msg.getPosition().x, error_msg.getPosition().y, error_msg.getCharacterSize());
        //std::cout<<"text\n";
        window_ptr->draw(error_msg);
        /*sf::RectangleShape bad_view_;

        bad_view_.setSize(getSizeInPixels());
        bad_view_.setPosition(getPosition());
        bad_view_.setFillColor(sf::Color::Blue);

        window_ptr->draw(bad_view_);*/
    }

    void Widget::close()
    {
        parent_->rmWidget(this);
        parent_->reDrawSig();

        delete this;
    }

    bool Widget::catchEvent(const sf::Event event)
    {
        return false;
    }

    bool Widget::catchClick (Click click)
    {
        return false;
    } 

    coordinate Widget::locationToPosition(coordinate location) const
    {
        return parent_->locationToPosition(location);
    }

    coordinate Widget::getSizeInPixels () const
    {
        return cabs(Widget::locationToPosition(rtAngle()) - Widget::locationToPosition(location_)); 
    }

    coordinate Widget::getPosition() const
    {
        return Widget::locationToPosition(ltAngle());
    }

    void Widget::dumpMe (const char* name) const
    {
        printf("Widget %s\n", name);

        location_.printMe("location");
        size_.printMe("size");

        rtAngle().printMe("rtAngle loc");
        ltAngle().printMe("ltAngle loc");

        getPosition().printMe("position");
        getSizeInPixels().printMe("szInPxls");
        
        locationToPosition(location_).printMe("lbAngle");
        locationToPosition(rtAngle()).printMe("rtAngle");   
    }
//======================================================
    bool WidgetManager::catchEvent(const sf::Event event) // still useless shit
    {
        bool catched = false;

        for (auto it = widgets_.rbegin(); it != widgets_.rend(); ++it)
        {
            catched = (*it)->catchEvent(event);
            if (catched == false)
            {
                continue;
            }
            else
            {
                break;
            }
        }

        return catched;
    }

    bool WidgetManager::catchClick (Click click)
    {
        bool catched = false;

        if (inMe(click.location_))
        {
            click.location_ = positionToLocation(click.location_);

            for (auto it = widgets_.rbegin(); it != widgets_.rend(); ++it)
            {
                catched = (*it)->catchClick(click);
                if (catched == false)
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
        }

        return catched;
    }

    void WidgetManager::pushWidget(Widget* widget_ptr)
    {
        widgets_.push_back(widget_ptr);
    }

    void WidgetManager::popWidget()
    {
        widgets_.pop_back();
    }

    void WidgetManager::rmWidget(Widget* widget_ptr)
    {
        widgets_.erase(std::remove(widgets_.begin(),\
                        widgets_.end(), widget_ptr), widgets_.end());
    }

    coordinate WidgetManager::locationToPosition(coordinate location) const
    {

        location.transmit (location_, size_);//transmit into parent system
        
        return parent_->locationToPosition(location);
    }

    coordinate WidgetManager::positionToLocation(coordinate position) const
    {
        return (position - location_)/size_;
    }

    void WidgetManager::reDrawSig()
    {
        parent_->reDrawSig();
    }
//======================================================
    WidgetMaster::WidgetMaster(sf::Vector2f size, const char* window_name):
    WidgetManager(nullptr, {1, 1}, {0, 0}),
    Widget(nullptr, {1, 1}, {0, 0}),
    needReDraw(false)
    {
        window_ptr = new sf::RenderWindow(sf::VideoMode(size.x, size.y), window_name);
        scale_ = coordinate((float)window_ptr->getSize().x, (float)window_ptr->getSize().y);
    
        context_ptr = new Context;
        context_ptr->window_ptr->create(sf::VideoMode(size.x, size.y), window_name);
    };

    WidgetMaster::~WidgetMaster()
    {
        delete context_ptr;
    }
    
    coordinate WidgetMaster::locationToPosition (coordinate location) const
    {
        location.y_ = 1 - location.y_;// make y_ upsidedown

        location = location*scale_;// multiply coordinate (from 0 to 1) on amount of pixels in side

        return location;
    }

    coordinate WidgetMaster::positionToLocation (coordinate position) const
    {
        position = position/scale_;// dev position in pixels on amount of pixels in side
        
        position.y_ = 1 - position.y_;// make y_ upsidedown

        return position;
    }

    bool WidgetMaster::catchEvent(const sf::Event event) //still can catch only Click
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (catchClick(Click(event)))
            {
                return true;
            }
        }
        return false;
    }

    bool WidgetMaster::catchClick(Click click)//recalc pixel pos to loc coord and pass click to his widgets
    {
        bool catched = false;

        click.location_ = positionToLocation(click.location_);

        for (auto it = widgets_.rbegin(); it != widgets_.rend(); ++it)
        {
            catched = (*it)->catchClick(click);
            if (catched == false)
            {
                continue;
            }
            else
            {
                break;
            }
        }

        return catched;
    }

    void WidgetMaster::reDrawSig()
    {
        //std::cout<<"redraw sig in master\n";
        needReDraw = true;
    }

    void WidgetMaster::loop()
    {
        sf::Event event;
        
        while (window_ptr->isOpen())
        {
            if (needReDraw)
            {
                //std::cout<<"redrawing"<<std::endl;
                //window_ptr->display();
                window_ptr->clear();
                drawAll();
                //window_ptr->display();
                //std::cout<<"redrawing end\n";
            }
    
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
            //std::cout<<"display\n";
            window_ptr->display();
            sf::sleep(sf::milliseconds(10));//delay
        }
    }

    void WidgetMaster::drawAll()
    {
        for (const auto& widget_ptr: widgets_)
        {
            widget_ptr->draw();
        }

        //window_ptr->display();

        needReDraw = false;
    }
}