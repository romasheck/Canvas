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

        for (int i = 0 ; i < std::size(figures_) ; i++)
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