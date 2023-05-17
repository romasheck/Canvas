#include "../../include/GEO/FigureManager.hpp"

namespace geo
{
    Figure* FigureManager::getFigureFromEnd(const uint32_t i) const
    {
        if (i >= figures_.size())
        {
            printf ("figures v ahue\n");
            return nullptr;
        }

        auto iter = figures_.size() - i - 1;

        return figures_[iter];
    }

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

        return nullptr;
        
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

    Point FigureManager::dotOnClosestFig(Point p, Figure* fig)
    {
        switch(fig->type_)
        {
            case Figure::DOT:{break;}
            case Figure::CIRCLE:
            {
                Circle cir = *(Circle*) fig;

                float dx = p.x_ - cir.cntr_.x_;
                float dy = p.y_ - cir.cntr_.y_;

                // Находим расстояние от центра окружности до данной точки
                float distance = std::sqrt(dx * dx + dy * dy);

                // Нормализуем вектор, чтобы получить единичный вектор направления
                float unitX = dx / distance;
                float unitY = dy / distance;

                // Находим координаты ближайшей точки на окружности
                float closestX = cir.cntr_.x_ + unitX * cir.rad_;
                float closestY = cir.cntr_.y_ + unitY * cir.rad_;

                // Возвращаем ближайшую точку
                Point closestPoint(0, 0);
                closestPoint.x_ = closestX;
                closestPoint.y_ = closestY;

                return closestPoint;
            }
            case Figure::LINE:
            {
                Line lne = *(Line*) fig;
                Point closestPoint(0, 0);
                float A = lne.A_, B = lne.B_, C = lne.C_;
                float denominator = A * A + B * B;

                // Если прямая вертикальная (A = 0)
                if (std::fabs(A) < 1e-6f)
                {
                    closestPoint.x_ = -C / B;
                    closestPoint.y_ = p.y_;
                }
                // Если прямая горизонтальная (B = 0)
                else if (std::fabs(B) < 1e-6f)
                {
                    closestPoint.x_ = p.x_;
                    closestPoint.y_ = -C / A;
                }
                // В остальных случаях
                else
                {
                    closestPoint.x_ = (B * (B * p.x_ - A * p.y_) - A * C) / denominator;
                    closestPoint.y_ = (A * (-B * p.x_ + A * p.y_) - B * C) / denominator;
                }

                return closestPoint;
            }
            default:
            {
                assert(0 && "Incorrect fig type in func dotOnClosestFig\n");
            }
        }

        return p;
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

    void FigureManager::flushFig()
    {
        while(figures_.size())
            popFigure();
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