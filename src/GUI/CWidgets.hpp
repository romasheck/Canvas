#ifndef CWIDGETS_HPP
#define CWIDGETS_HPP

#include "CanvasWidget.hpp"

namespace gui
{
//==========================================================================
    class ColorRegulator: public Clickable, public CWidget
    {
        private:
            const sf::Color choisenColor_; // the color of ColorReg and color after exhange 
            sf::RectangleShape view_;  // the view of ColorRegulator
        
        public:
            ColorRegulator(const sf::Color choisenColor, Canvas& canvas_ptr, Widget* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
            Widget(parent, size, location),
            Clickable(parent, size, location),
            CWidget(canvas_ptr, parent, size, location),
            choisenColor_(choisenColor)
            {
                view_.setFillColor(choisenColor_);
                view_.setPosition(getPosition());
                view_.setSize(getSizeInPixels());
            }

        public: 
            void draw()
            {
                window_ptr->draw(view_);
            }

        private:
            void respond2Click() override
            {
                //std::cout<<"ColorRegulator must exchange color"<<std::endl;
                canvas_.setCurrentColor(choisenColor_);
            }
        
    };
//==========================================================================
    class Panel: public CWidgetManager
    {
    private:
        sf::RectangleShape background_;

    public:
        Panel(Canvas& canvas, Widget* parent, coordinate size = {0.3, 0.3}, coordinate location = {0.f, 0.f}):
        CWidgetManager(canvas, parent, size, location),
        Widget(parent, size, location)
        {
            background_.setFillColor(sf::Color::Magenta);
            background_.setSize(getSizeInPixels());
            background_.setPosition(getPosition());
        };

    public:
        void createAll()
        {
            //location = loc_canv + sz_canv - sz_ColorReg.y_
            createColorRegulator (sf::Color::Green, {0.7, 0.35}, \
            {0.1, 0.55} );
            //location = loc_canv + sz_canv - 2*sz_ColorReg.y_
            createColorRegulator (sf::Color::Red, {0.7, 0.4}, \
            {0.1, 0.1} );
        }

    public:
        void draw() override
        {
            window_ptr->draw(background_);

            for (const auto& widget_ptr: widgets_)
            {
                widget_ptr->draw();
            }
        }

    private:
        void createColorRegulator(sf::Color color, coordinate size, coordinate location)
        {
            auto color_reg_ptr = new ColorRegulator(color, canvas_, (Widget*)this, size, location);
            pushWidget(std::move(color_reg_ptr));
        }
    };
//==========================================================================
}

#endif