#ifndef FIG_HPP_INCLUDED
#define FIG_HPP_INCLUDED

#include "geo_lib.hpp"

#define smn printf("Called %s\n", __func__);

namespace geo
{
    const int np = 333;
    const float EPSILON = 1e-5;

//====================================
    class Point
    {
        public:
            float x_, y_;
        
        public:
            Point(float x, float y)
                {x_ = x; y_ = y;}
    };
//====================================
    class Figure
    {
        public:
            const int type_;
            enum FIG_TYPES
            {
                CIRCLE  = 0,
                LINE    = 1,
                DOT     = 2,
                ERROR   = 3,
            };

        public:
            Figure(const int type):
                type_(type)
                {}
    };
//====================================
    class Circle : public Figure
    {
        public:
            float rad_;
            Point cntr_;

        public:
            Circle(float rad, float x, float y):
                Figure(CIRCLE),
                cntr_(x, y)
                {rad_=rad;}

            Circle(float rad, Point point):
                Figure(CIRCLE),
                cntr_(point.x_, point.y_)
                {rad_=rad;}
    };
//====================================
    class Line : public Figure
    {
        public:
            float A_, B_, C_;

        public:
            Line(float p1x, float p1y, float p2x, float p2y):
                Figure(LINE)
                {
                    A_ = p1y - p2y;
                    B_ = p2x - p1x;
                    C_ = p1x * p2y - p2x * p1y;
                }

            Line(Point p1, Point p2):
                Figure(LINE)
                {
                    A_ = p1.y_ - p2.y_;
                    B_ = p2.x_ - p1.x_;
                    C_ = p1.x_ * p2.y_ - p2.x_ * p1.y_;
                }

            Line(float A, float B, float C):
                Figure(LINE)
                {
                    A_ = A;
                    B_ = B;
                    C_ = C;
                }

        public:
            Dot getDot1() const;
            Dot getDot2() const;
    };
//====================================
    class Dot : public Figure
    {
        public:
            Point p_;

        public:
            Dot(float x, float y):
                Figure(DOT),
                p_(x, y)
                {}

            Dot(Point p):
                Figure(DOT),
                p_(p.x_, p.y_)
                {}
    };
//====================================
    class TwoPoints
    {
        public:
            Point p1_;
            Point p2_;
            int nop_ = 0;

        public:
            TwoPoints(float x1, float y1, float x2, float y2, int nop):
                p1_(x1, y1),
                p2_(x2, y2)
                {nop_ = nop;}

            TwoPoints(Point p1, Point p2, int nop):
                p1_(p1.x_, p1.y_),
                p2_(p2.x_, p2.y_)
                {nop_ = nop;}
    };
//========================= Classes ended, now fuctions =========================

    bool CirLneBool(Figure* cir, Figure* lne);

    bool CirDotBool(Figure* cir, Figure* dotarg);

    bool CirCirBool(Figure* circle1, Figure* circle2);

//========================= Block of intersection funcs =========================

    TwoPoints CirCir(Figure* cir1, Figure* cir2);
    
    TwoPoints CirLne(Figure* cir, Figure* lne);
    
    TwoPoints LneLne(Figure* lne1, Figure* lne2);
   
    TwoPoints LneCir(Figure* lne, Figure* cir);
    
    TwoPoints DotDot(Figure* dota1, Figure* dota2);

    TwoPoints CirDot(Figure* cirarg, Figure* dotarg);

    TwoPoints DotCir(Figure* dotarg, Figure* cirarg);
    
    TwoPoints LneDot (Figure* lnearg, Figure* dotarg);
    
    TwoPoints DotLne (Figure* dotarg, Figure* lnearg);

    extern    TwoPoints (*findIsctDots[3][3])(Figure*, Figure*);

    void      DebugTwoPoints (TwoPoints pts);
    
//========================= Block ended =========================

    float     distance(Point p1, Point p2);

    void      DebugPrintFigure(Figure* fig);

}
#endif