#include "../../include/GUI/Canvas.hpp"

namespace gui
{
    Projector::Projector(Canvas& canvas):
        canvas_(canvas),
        geometry_(),
        buff_{CanvasPenMode::Default, false, nullptr, nullptr},
        RT(0, 0)
        {
            buff_.processing = CanvasPenMode::Default;

            canvasScale_ = canvas_.getSizeInPixels();

            RT = transmitToMyCS(coordinate(1, 1));
        };

    bool Projector::processPen(const PenMode mode, const coordinate loc)
    {
        if (!(mode & CanvasModeGroups::GEOMETRIC))
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
            if (nearest_fig_ptr != nullptr)
                coord = geometry_.dotOnClosestFig(coord, nearest_fig_ptr);

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
        case CanvasPenMode::CircleArbitary:
        {
            if (nearest_fig_ptr == nullptr)
            {
                printf ("circle?\n");
                break;
            }
            if (nearest_fig_ptr->type_ == geo::Figure::DOT)
            {
                doCircleArbitary((geo::Dot*)nearest_fig_ptr);
            }
            else
            {
                printf ("incorrect CircleArbitary using\n");
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
        if (validatePoint(p))
        {
            auto dot_ptr = geometry_.makeDot(p);

            drawDot(*dot_ptr);
            //PRINT_LINE
        }        
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

                drawDot(*(geo::Dot*)fig_ptr);
            }
        }
    }

    void Projector::doCircleArbitary(const geo::Dot* fig)
    {
        if (buff_.processing != CircleArbitary)
        {
            buff_.processing = CircleArbitary;
            //PRINT_LINE
            buff_.dot1_ptr = fig;
            //PRINT_LINE
            //drawDot(*nearest_fig_ptr);//noooooooooo!
        }
        else{
            printf("second dot\n");
            
            buff_.processing = Default;

            auto circle = geometry_.makeCircle(buff_.dot1_ptr->p_, fig->p_);

            drawCircle(*circle);

            auto inter_num = geometry_.IntersectWithAll(circle);

            for (int i = 0; i < inter_num; i++)
            {
                auto fig_ptr = geometry_.getFigureFromEnd(i);

                if (fig->type_ != geo::Figure::DOT)
                {
                    printf ("smth wrong with intersections\n");
                }

                drawDot(*(geo::Dot*)fig_ptr);
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

    bool Projector::validatePoint (const geo::Point p) const
    {
        if (p.y_ >= 0 && p.y_ <= RT.y_)
        {
            if (p.x_ >= 0 && p.x_ <= RT.x_)
            {
                return true;
            }
        }

        return false;
    }

    void Projector::drawLine(geo::Line line)
    {
        geo::Point P1;
        geo::Point P2;

        geo::Point p1(-line.C_/line.A_, 0);
        geo::Point p2(0, -line.C_/line.B_);
        geo::Point p3(-(line.B_*RT.y_ + line.C_)/line.A_, RT.y_);
        geo::Point p4(RT.x_, -(line.A_*RT.x_ + line.C_)/line.B_);

        if (validatePoint(p4))
        {
            P1 = p4;

            if      (validatePoint(p3))
                P2 = p3;
            else if (validatePoint(p2))
                P2 = p2;
            else if (validatePoint(p1))
                P2 = p1;
        }
        else if (validatePoint(p3))
        {
            P1 = p3;

            if      (validatePoint(p1))
                P2 = p1;
            else if (validatePoint(p2))
                P2 = p2;
        }
        else if (validatePoint(p2))
        {
                P1 = p2;

            if(validatePoint(p1))
                P2 = p1;
        }
        else
            assert(0 && "SHIT HAPPENS! Rerun this app and forget about this line!\n");

        coordinate point1 = canvas_.locToPos(transmitToCanv(P1));
        coordinate point2 = canvas_.locToPos(transmitToCanv(P2));

        sf::VertexArray line_view(sf::Lines);
        line_view.append(sf::Vertex(point1, sf::Color::Red));
        line_view.append(sf::Vertex(point2, sf::Color::Red));

        canvas_.context_ptr->window().draw(line_view);
    }

    void Projector::drawCircle(geo::Circle circle)
    {
        auto cntr_ = canvas_.locToPos(transmitToCanv(circle.cntr_));



        sf::VertexArray lines(sf::LinesStrip);
        int numSteps = 100;
        float angleStep = 2 * 3.14159f / numSteps;
        
        for (int i = 0; i <= numSteps; ++i)
        {
            float angle = angleStep * i;
            float x = cntr_.x_ + circle.rad_ * cos(angle);
            float y = cntr_.y_ + circle.rad_ * sin(angle);
            lines.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Blue));
        }

        canvas_.context_ptr->window().draw(lines);
        /*
        auto pos = canvas_.getPosition();
        auto sz = canvas_.getSizeInPixels();

        sf::FloatRect canvasBox(pos, sz);

        sf::CircleShape circle_view;

        sf::View canvasBound;
        canvasBound.reset(canvasBox);

        circle_view.setRadius(circle.rad_);
        circle_view.setPosition(canvas_.locToPos(transmitToCanv(circle.cntr_)) - coordinate(circle.rad_, circle.rad_));
        circle_view.setOutlineColor(sf::Color::Red); // цвет контура окружности
        circle_view.setOutlineThickness(2); // толщина контура окружности
        circle_view.setPointCount(100 + circle.rad_);
        circle_view.setFillColor(sf::Color::Transparent);

        ((coordinate)canvasBound.getSize()).printMe("bound");

        

        canvas_.context_ptr->window().setView(canvasBound);
        canvas_.context_ptr->window().draw(circle_view);
        canvas_.context_ptr->window().setView(canvas_.context_ptr->window().getDefaultView());
        */
    }

    void Projector::reDraw()
    {
        for (const auto fig_ptr: geometry_.figures_)
        {
            if (fig_ptr->type_ == geo::Figure::DOT)
            {
                drawDot(*((geo::Dot*)fig_ptr));
            }
            if (fig_ptr->type_ == geo::Figure::LINE)
            {
                drawLine(*((geo::Line*)fig_ptr));
            }
            if (fig_ptr->type_ == geo::Figure::CIRCLE)
            {
                drawCircle(*((geo::Circle*)fig_ptr));
            }
        }
    }

    void Projector::flush()
    {
        geometry_.flushFig();
    }


}