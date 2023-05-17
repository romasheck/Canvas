#include "../../include/GUI/Canvas.hpp"

namespace gui
{
    Projector::Projector(Canvas& canvas):
        canvas_(canvas),
        geometry_(),
        buff_{CanvasPenMode::Default, false, nullptr, nullptr}
        {
            buff_.processing = CanvasPenMode::Default;

            canvasScale_ = canvas_.getSizeInPixels();
        };

    bool Projector::processPen(const PenMode mode, const coordinate loc)
    {
        if (!(mode and CanvasModeGroups::GEOMETRIC))
        {
            printf ("this action in developing\n");
            return false;
        }

        geo::Point coord = transmitToMyCS(loc);
        //PRINT_LINE
        geo::Figure* nearest_fig_ptr = geometry_.whichFig(coord);      
        //PRINT_LINE
        switch (mode)
        {
        case CanvasPenMode::Dot:
        {
            printf ("dot mode\n");

            addDot(coord);

            break;
        }
        case CanvasPenMode::Ruler:
        {
            if (nearest_fig_ptr == nullptr)
            {
                printf ("ruler?\n");
                break;
            }
            //PRINT_LINE
            if (nearest_fig_ptr->type_ == geo::Figure::DOT)
            {
                doRuler((geo::Dot*)nearest_fig_ptr);
            }
            else
            {
                printf ("incorrect ruler using\n");
            }
            
            break;
        }
        default:
            break;
        }

        return true;
    }

    void Projector::addDot(geo::Point p)
    {
        auto dot_ptr = geometry_.makeDot(p);

        drawDot(*dot_ptr);
        //PRINT_LINE
    }

    void Projector::doRuler(const geo::Dot* fig)
    {
        //PRINT_LINE
        if (buff_.processing != Ruler)
        {
            buff_.processing = Ruler;
            //PRINT_LINE
            buff_.dot1_ptr = fig;
            //PRINT_LINE
            //drawDot(*nearest_fig_ptr);//noooooooooo!
        }
        else{
            printf("second dot\n");
            
            buff_.processing = Default;

            auto line = geometry_.makeLine(buff_.dot1_ptr->p_, fig->p_);

            drawLine(*line);

            auto inter_num = geometry_.IntersectWithAll(line);

            for (int i = 0; i < inter_num; i++)
            {
                auto fig_ptr = geometry_.getFigureFromEnd(i);

                if (fig->type_ != geo::Figure::DOT)
                {
                    printf ("smth wrong with intersections\n");
                }

                drawDot(*(geo::Dot*)fig);
            }
        }
    }

    geo::Point Projector::transmitToMyCS (const coordinate loc) const
    {
        auto point = loc*canvasScale_; 

        return geo::Point(point.x_, point.y_);
    }
    coordinate Projector::transmitToCanv(const geo::Point p) const
    {
        return coordinate(p.x_/canvasScale_.x_, p.y_/canvasScale_.y_);
    }

    void Projector::drawDot(geo::Dot dot)
    {
        sf::CircleShape dot_view;

        const float radius = 20;

        dot_view.setRadius(radius);
        dot_view.setFillColor(sf::Color::Blue);

        auto px_coord = canvas_.locToPos(transmitToCanv(dot.p_));
        dot_view.setPosition(px_coord - coordinate(radius, radius));

        //canvas_.locToPos(p).printMe("dot");

        canvas_.context_ptr->window().draw(dot_view);
    }

    void Projector::drawLine(geo::Line line)
    {
        
    }
}