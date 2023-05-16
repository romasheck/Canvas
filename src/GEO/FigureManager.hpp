#ifndef FIGURE_MANAGER_HPP_DEFINED
#define FIGURE_MANAGER_HPP_DEFINED

#include "Figure.hpp"

namespace geo
{
    const float PointRad = 0.3;

    class FigureManager
    {
    public:
        std::vector<Figure*> figures_;

    public:
        FigureManager()
            {};
        ~FigureManager()
        {
            for (auto figure_ptr: figures_)
            {
                delete figure_ptr;
            }
        }

    public:
        void pushFigure(Figure* figure_ptr)
        {
            figures_.push_back(figure_ptr);
        }
        void popFigure()
        {
            figures_.pop_back();
        }

    public:
        Figure* whichFig(Point);

        /// @brief  Находит точки пересечения данной фигуры с остальными и добавляет их в вектор фигур
        /// @param  Figure* данная фигура
        /// @return Колличество точек пересечения
        int     IntersectWithAll(Figure* fig);

        void    debugPrintFigures();

        Line*   makeLine(Point p1, Point p2);

        Circle* makeCircle(float rad, Point p);

        Circle* makeCircle(Point cntr, Point p);

        Circle* makeCircle(Point cntr, Point p1, Point p2);

        Dot*    makeDot(Point p);
    };


}

#endif