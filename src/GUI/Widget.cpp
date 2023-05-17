#include "../../include/GUI/Widget.hpp"
#include "../../include/GUI/Context.hpp"

namespace gui
{

    Context* Widget::context_ptr;
    Widget* Widget::last_active_;

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
    /*void Widget::viewInit(const std::string& texture_path, const std::string& text)
    {
        sf::Sprite sprite_;
        sprite_.setPosition(getPosition());
        
        sf::Texture bad_view;
        bad_view.loadFromFile("assets/textures/maxresdefault.jpg");
        
        sprite_.setTexture(bad_view);
        sprite_.scale({getSizeInPixels().x_/(bad_view.getSize()).x, getSizeInPixels().y_/bad_view.getSize().y});

        context_ptr->window().draw(sprite_);

        sf::Font font;
        font.loadFromFile("assets/fonts/FFF_Tusj.ttf");
        sf::Text error_msg;
        error_msg.setFont(font);
        error_msg.setString("Ha-ha!");
        error_msg.setCharacterSize((locationToPosition(rtAngle())-getPosition()).x_*2/3);
        error_msg.setPosition(getPosition() - getSizeInPixels()/3);
    }*/

    void Widget::draw() //default: draw fucking troll face with text: "Ha-ha!"
    {   
        //TEXTURE
        sf::Sprite view_;
        view_.setPosition(getPosition());
        
        sf::Texture bad_view = context_ptr->getTexture(TEXTURE_ID::Default);
        
        view_.setTexture(bad_view);
        view_.scale({getSizeInPixels().x_/(bad_view.getSize()).x, getSizeInPixels().y_/bad_view.getSize().y});

        context_ptr->window().draw(view_);

        //TEXT
        sf::Font font = context_ptr->getFont(FONT_ID::DEFAULT);
        sf::Text error_msg("Ha-ha!", font);
        error_msg.setColor(sf::Color::Yellow);
        
        coordinate text_lbAngle = coordinate(0.1f, 0.1f)*size_ + location_; 
        coordinate text_LocalSize = coordinate(0.5, 0.5) * size_;

        coordinate text_pSize = cabs(locationToPosition(text_lbAngle + text_LocalSize) - locationToPosition(text_lbAngle));
        coordinate text_pos = locationToPosition(text_lbAngle + coordinate(0, text_LocalSize.y_));

        sf::FloatRect textRect = error_msg.getLocalBounds();

        error_msg.setScale(text_pSize.x_/ (textRect.width + textRect.left), text_pSize.y_ / (textRect.height + textRect.top));
        
        error_msg.setPosition(text_pos.x_, text_pos.y_);

        context_ptr->window().draw(error_msg);
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

    void Widget::updateActive()
    {
        if (this != last_active_)
        {
            last_active_->loseActive();
            last_active_ = this;
        }
        return;
    }

    void Widget::loseActive()
    {
        ;
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

    void WidgetManager::draw()
    {
        for(const auto& widgtet_ptr: widgets_)
        {
            widgtet_ptr->draw();
        }
    }
//======================================================
    WidgetMaster::WidgetMaster(sf::Vector2f size, const char* window_name):
    WidgetManager(nullptr, {1, 1}, {0, 0}),
    Widget(nullptr, {1, 1}, {0, 0}),
    needReDraw(false)
    {
        //window_ptr = new sf::RenderWindow(sf::VideoMode(size.x, size.y), window_name);
        //scale_ = coordinate((float)context_ptr->window().getSize().x, (float)context_ptr->window().getSize().y);
        
        context_ptr = new Context;

        context_ptr->window().create(sf::VideoMode(size.x, size.y), window_name);
        context_ptr->window().setFramerateLimit(60);
        scale_ = coordinate((float)context_ptr->window().getSize().x, (float)context_ptr->window().getSize().y);

        context_ptr->addFont(FONT_ID::DEFAULT, "../assets/fonts/Raleway-Black.ttf");
        context_ptr->addTexture(TEXTURE_ID::Default, "../assets/textures/maxresdefault.jpg");
        PRINT_LINE
        context_ptr->sf_clock_ptr->restart();
        PRINT_LINE
        //push MouseMaster

        last_active_ = this;
    }

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
        if (context_ptr->mouse_ptr->isMyEvent(event))
        {
            if (catchClick(Click(context_ptr->mouse_ptr->position)))
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
        
        while (context_ptr->window().isOpen())
        {
            if (needReDraw)
            {
                context_ptr->window().clear();
                drawAll();
            }

            while (context_ptr->window().pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    context_ptr->window().close();
                }
                else
                {
                    catchEvent(event);
                }
            }
            //std::cout<<"display\n";
            context_ptr->window().display();
        }
    }

    void WidgetMaster::drawAll()
    {
        for (const auto& widget_ptr: widgets_)
        {
            widget_ptr->draw();
        }

        //context_ptr->window().display();

        needReDraw = false;
    }
}