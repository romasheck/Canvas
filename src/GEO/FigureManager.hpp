#ifndef FIGURE_MANAGER_HPP_DEFINED
#define FIGURE_MANAGER_HPP_DEFINED

#include "Figure.hpp"

namespace geo
{
    class FigureMaster
    {
    public:
        std::vector<Figure*> figures_;

    public:
        FigureMaster()
            {};
        ~FigureMaster()
        {
            for (const auto& figure_ptr: figures_)
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

    };


}

#endif