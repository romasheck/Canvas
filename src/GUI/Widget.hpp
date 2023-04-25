#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "gui_lib.hpp"
#include "coordinate.hpp"
#include "Pixel.hpp"
#include "Events.hpp"
//#include "GrShapes.hpp"
#include <iostream>
#include <memory.h>

namespace gui
{
    class Widget;
    class WidgetManager;
    class WidgetMaster;
//==========================================================================
    class WidBox //rectangle that has local coord and size in loc coord sys
    {
    public://do these public -> get.. & set.. are useless
        coordinate location_;
        coordinate size_;

    public:
        void setSize(const coordinate size) {size_ = size;} //useless
        coordinate getSize () const {return size_;}//useless

        void setLocation(const coordinate location) {location_ = location;}//useless
        coordinate getLocation () const {return location_;}//useless

        bool inMe (const coordinate position) const;//position in widBox?

        coordinate rtAngle() const;//return right top angle of WidBox
        coordinate ltAngle() const;//return left top angle of WidBox
    };
//==========================================================================
    class Widget : public WidBox //WidBox which can be drawn, can catch events (sp. click) and has parent
    {
    protected:
        WidgetManager * parent_;

    public:
        Widget(WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        parent_(parent)
        {
            setSize(size);
            setLocation(location);
        }
        //ban simple CopyCtor
        Widget(const Widget& widget) = delete;
        //virtual Dtor 
        virtual ~Widget() = default;

    public:
        virtual bool catchEvent(const sf::Event event);
        
        virtual bool catchClick (Click click);
    
    public:
        virtual void draw(); //default: draw blue rectangle in W
        
        virtual void close();

    public:
        //turn local coordinate into abcolute pixels coordinate system FOR CALLING SFML-FUNCTIONS 
        virtual coordinate locationToPosition(coordinate location) const;
        
        //return absolute pixels position of left top angle FOR CALLING SFML-FUNCTIONS
        coordinate getPosition() const;
        
        //return real size of object in pixels FOR CALLING SFML-FUNCTIONS
        coordinate getSizeInPixels () const;

    public:
        void dumpMe (const char* name) const;
    };
//==========================================================================
    class WidgetManager: virtual public Widget //Widget which contain several other
    {
    protected:
        std::vector<Widget*> widgets_;

    public:
        WidgetManager(WidgetManager* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        Widget(parent, size, location)
        {};
        ~WidgetManager() override
        {
            for (const auto& widget_ptr: widgets_)
            {
                delete widget_ptr;
            }
        }

    public:
        //void close() override;
        virtual void reDrawSig();

    public:
        bool catchEvent(const sf::Event event) override; // still useless shit
        //calculates whether his box is clicked, if yes, sends the click to his widgets
        bool catchClick (Click click) override;

    public:
        void pushWidget(Widget* widget_ptr);
        void popWidget();
        void rmWidget(Widget* widget_ptr);

    public:
        coordinate locationToPosition(coordinate location) const override;
        //turn absolute position to local coordinate FOR CLICK
        virtual coordinate positionToLocation(coordinate position) const;
    };
//==========================================================================
    class WidgetMaster: public WidgetManager //Base for MainWidget and HAS NOT parent (nullptr)
    {
    private:
        coordinate scale_;
        bool needReDraw;

    public:
        WidgetMaster(sf::Vector2f size, const char* window_name);

    public:
        coordinate locationToPosition (coordinate location) const override;

        coordinate positionToLocation (coordinate position) const override;

    public:
        bool catchEvent(const sf::Event event) override;//still can catch only Click

        bool catchClick(Click click) override;//recalc pixel pos to loc coord and pass click to his widgets
    
    public:
        void reDrawSig() override;

    public:
        void loop();

    public:
        void drawAll();
    };
}

#endif