#include "FigureManager.hpp"

namespace geo
{
    Figure* FigureManager::whichFig(Point point)
    {
        Circle cir(PointRad, point);

        for (auto figure_ptr: figures_)
        {
            if (figure_ptr->type_ == Figure::DOT)
            {
                if(CirDotBool((Figure*)&cir, figure_ptr))  // функция пересечения КРУГА(не окружности) и точки
                    return figure_ptr;
            }
        }

        TwoPoints IsctDots(0, 0, 0, 0, 0);

        for (auto figure_ptr: figures_)
        {
            if (figure_ptr->type_ != Figure::DOT)
            {
                IsctDots = findIsctDots[cir.type_][figure_ptr->type_]((Figure*)&cir, figure_ptr);

                if (IsctDots.nop_ != 0)
                    return figure_ptr;
            }
        }
        
    }

    int FigureManager::IntersectWithAll(Figure* fig)
    {smn
        int IsctCunt = 0;
        TwoPoints retval(0, 0, 0, 0, 0);

        Figure* figure_ptr = NULL;

        int vec_size = std::size(figures_);

        for (int i = 0 ; i < vec_size ; i++)
        {
            figure_ptr = figures_[i];

            if (figure_ptr->type_ == Figure::DOT)
                continue;

            retval = findIsctDots[fig->type_][figure_ptr->type_](fig, figure_ptr);

            switch(retval.nop_)
            {
                case 0:
                {
                    break;
                }   
                case 1:
                {
                    Dot* new_dot_ptr = new Dot(retval.p1_); 

                    pushFigure((Figure*)new_dot_ptr);

                    IsctCunt += 1;
                    break;
                }
                case 2:
                {
                    Dot* new_dot1_ptr = new Dot(retval.p1_);
                    Dot* new_dot2_ptr = new Dot(retval.p2_);

                    pushFigure((Figure*)new_dot1_ptr);
                    pushFigure((Figure*)new_dot2_ptr);

                    IsctCunt += 2;
                    break;
                }   
                default:
                    assert(0 && "Something goes wrong, check findIsctDots return value!!\n");
            }
        }

        return IsctCunt;
    }

    Line* FigureManager::makeLine(Point p1, Point p2)
    {
        Line* new_line = new Line(p1, p2);
        pushFigure((Figure*)new_line);

        return new_line;
    }

    Circle* FigureManager::makeCircle(float rad, Point p)
    {
        Circle* new_circle = new Circle(rad, p);
        pushFigure((Figure*)new_circle);

        return new_circle;
    }

    Circle* FigureManager::makeCircle (Point cntr, Point p)            // Создание окружности по точке центра и точке на окружности
    {
        return makeCircle(distance(cntr, p), cntr);
    }

    Circle* FigureManager::makeCircle (Point cntr, Point p1, Point p2) // Создание окружности по точке центра и двум точкам, расстояние между которыми = радиус
    {
        return makeCircle(distance(p1, p2), cntr);
    }

    Dot* FigureManager::makeDot(Point p)
    {
        Dot* new_dot = new Dot(p);
        pushFigure((Figure*)new_dot);

        return new_dot;
    }

    void FigureManager::debugPrintFigures()
    {
        printf("---------------------------------------------\n");
        for (auto figure_ptr: figures_)
        {
            DebugPrintFigure(figure_ptr);
        }
        printf("---------------------------------------------\n");
    }
}