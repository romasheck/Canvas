#include "../../include/GEO/Figure.hpp"

namespace geo
{

    bool Point::operator>= (const float t) const
    {
        if (x_ >= t)
        {
            if (y_ >= t)
            {
                return true;
            }
        }

        return false;
    }
//========================= Block of intersection bool funcs =========================

    TwoPoints (*findIsctDots[3][3])(Figure*, Figure*) = 
                             {{&CirCir, &CirLne, &CirDot},
                              {&LneCir, &LneLne, &LneDot},
                              {&DotCir, &DotLne, &DotDot}};

    bool CirLneBool(Figure* cir, Figure* lne)
    {
        Circle* circle = (Circle*) cir;
        Line*   line   = (Line*)   lne;

        float distance = fabsf(line->A_ * circle->cntr_.x_ + line->B_ * circle->cntr_.y_ + line->C_) 
                       / sqrtf(line->A_ * line->A_ + line->B_ * line->B_);

        if (distance <= circle->rad_)  // TODO: Сравнение флоатов!!!!
            return true;
        else
            return false;
    }

    bool CirDotBool(Figure* cir, Figure* dotarg)
    {
        Circle* circle = (Circle*) cir;
        Dot*    dot    = (Dot*) dotarg;

        float distance_sq = powf(dot->p_.x_ - circle->cntr_.x_, 2)
                            + powf(dot->p_.y_ - circle->cntr_.y_, 2);

        if (distance_sq <= powf(circle->rad_, 2))  // TODO: Сравнение флоатов!!!!
            return true;
        else
            return false;
    }

    bool CirCirBool(Figure* circle1, Figure* circle2)
    {
        Circle* cir1 = (Circle*) circle1;
        Circle* cir2 = (Circle*) circle2;

        double sq_distance = (cir2->cntr_.x_ - cir1->cntr_.x_) * (cir2->cntr_.x_ - cir1->cntr_.x_) 
                           + (cir2->cntr_.y_ - cir1->cntr_.y_) * (cir2->cntr_.y_ - cir1->cntr_.y_);
        
        if (sq_distance <= (cir1->rad_ + cir2->rad_) * (cir1->rad_ + cir2->rad_))
            return true;
        else
            return false;
    }

//========================= Block of intersection nonbool funcs =========================

    TwoPoints CirCir(Figure* cir1, Figure* cir2)
    {smn
        Circle* circle1 = (Circle*) cir1;
        Circle* circle2 = (Circle*) cir2;
        TwoPoints retpts(np, np, np, np, 0);

        // Distance between the centers of the circles
        double distance_squared = pow(circle2->cntr_.x_ - circle1->cntr_.x_, 2) + pow(circle2->cntr_.y_ - circle1->cntr_.y_, 2);

        // Check if circles are overlapping or too far apart
        double radius_sum_squared = pow(circle1->rad_ + circle2->rad_, 2);
        double radius_diff_squared = pow(circle1->rad_ - circle2->rad_, 2);
        if (distance_squared - radius_sum_squared > EPSILON || EPSILON < radius_diff_squared - distance_squared)
        {
            // Circles do not intersect
            return retpts;
        }

        float distance = sqrtf(distance_squared);

        // Calculate the distance from the center of circle1 to the intersection line between the two circles
        float a = (powf(circle1->rad_, 2) - powf(circle2->rad_, 2) + distance_squared) / (2 * distance);

        // Calculate the coordinates of the point halfway between the intersection points
        float x2 = circle1->cntr_.x_ + (a * (circle2->cntr_.x_ - circle1->cntr_.x_) / distance);
        float y2 = circle1->cntr_.y_ + (a * (circle2->cntr_.y_ - circle1->cntr_.y_) / distance);

        if (fabs(distance_squared - radius_sum_squared) < EPSILON)
        {
            retpts.p1_.x_ = x2;
            retpts.p1_.y_ = y2;
            retpts.p2_.x_ = x2;
            retpts.p2_.y_ = y2;

            retpts.nop_ = 1;

            return retpts;
        }

        // Calculate the distance from the midpoint to the intersection points
        float h = sqrtf(fabsf(powf(circle1->rad_, 2) - powf(a, 2)));  //TODO: Добавить функцию сравнения с 0 для флотов!!!!

        // Calculate the coordinates of the two intersection points
        retpts.p1_.x_ = x2 + (h * (circle2->cntr_.y_ - circle1->cntr_.y_) / distance);
        retpts.p1_.y_ = y2 - (h * (circle2->cntr_.x_ - circle1->cntr_.x_) / distance);
        retpts.p2_.x_ = x2 - (h * (circle2->cntr_.y_ - circle1->cntr_.y_) / distance);
        retpts.p2_.y_ = y2 + (h * (circle2->cntr_.x_ - circle1->cntr_.x_) / distance);

        if (retpts.p1_.x_ == retpts.p2_.x_ && retpts.p1_.y_ == retpts.p2_.y_)
            retpts.nop_ = 1;
        else
            retpts.nop_ = 2;

        return retpts;
    }

    TwoPoints CirLne(Figure* cir, Figure* lne)
    {smn

        Circle* circle = (Circle*) cir;
        Line* line = (Line*) lne;

        float A = line->A_;
        float B = line->B_;
        float C = line->C_;
        float xc = circle->cntr_.x_;
        float yc = circle->cntr_.y_;
        float r  = circle->rad_;
            
        float distance = fabsf(A * xc + B * yc + C) / sqrtf(A * A + B * B);
        if (distance > r)
        {
            return TwoPoints(np, np, np, np, 0);
        }
        if (A == 0)
        {
            float y = -C / B;
            float x1 = xc + sqrtf(fabsf(r * r - (y - yc) * (y - yc)));
            float x2 = xc - sqrtf(fabsf(r * r - (y - yc) * (y - yc)));

            if (x1 == x2)
                return TwoPoints(x1, y, x2, y, 1);
            else
                return TwoPoints(x1, y, x2, y, 2);

        }
        else if (B == 0)
        {
            float x = -C / A;
            float y1 = yc + sqrtf(fabsf(r * r - (x - xc) * (x - xc)));
            float y2 = yc - sqrtf(fabsf(r * r - (x - xc) * (x - xc)));

            if (y1 == y2)
                return TwoPoints(x, y1, x, y2, 1);
            else
                return TwoPoints(x, y1, x, y2, 2);

        }
        else
        {
            float k = -A / B;
            float b = -C / B;
            float a = k * k + 1;
            float b1 = 2 * k * b - 2 * xc - 2 * k * yc;
            float c = xc * xc + b * b - 2 * b * yc + yc * yc - r * r;
            float D = b1 * b1 - 4 * a * c;
            if (D < 0)
            {
                return TwoPoints(np, np, np, np, 0);
            }
            else if (D == 0)
            {
                float x = -b1 / (2 * a);
                float y = k * x + b;

                return TwoPoints(x, y, x, y, 1);
            }
            else
            {
                float x1 = (-b1 + sqrtf(D)) / (2 * a);
                float y1 = k * x1 + b;
                float x2 = (-b1 - sqrtf(D)) / (2 * a);
                float y2 = k * x2 + b;

                return TwoPoints(x1, y1, x2, y2, 2);
            }
        }
    }

    TwoPoints LneLne(Figure* lne1, Figure* lne2)
    {smn
        Line* line1 = (Line*) lne1;
        Line* line2 = (Line*) lne2;

        float det = line1->A_*line2->B_ - line2->A_*line1->B_;
        if (det == 0)
        {
            // Прямые параллельны или совпадают
            return TwoPoints(Point(np, np), Point(np, np), 0);
        }
        else
        {
            float x = -(line2->B_*line1->C_ - line1->B_*line2->C_) / det;
            float y = -(line1->A_*line2->C_ - line2->A_*line1->C_) / det;

            return TwoPoints(Point(x, y), Point(x, y), 1);
        }
    }

    TwoPoints LneCir(Figure* lne, Figure* cir)
    {smn
        return CirLne(cir, lne);
    }

    TwoPoints DotDot(Figure* dota1, Figure* dota2)
    {smn
        Dot* dot1 = (Dot*) dota1;
        Dot* dot2 = (Dot*) dota2;

        if (dot1->p_.x_ == dot2->p_.x_)
            if(dot1->p_.y_ == dot2->p_.y_)
                return TwoPoints(dot1->p_, dot1->p_, 1);
            else
                return TwoPoints(np, np, np, np, 0);
        
        return TwoPoints(np, np, np, np, 0);
    }

    TwoPoints CirDot(Figure* cirarg, Figure* dotarg)
    {smn
        Circle* cir = (Circle*) cirarg;
        Dot*    dot = (Dot*) dotarg;

        double distanse_sq = powf(cir->cntr_.x_ - dot->p_.x_, 2) + powf(cir->cntr_.y_ - dot->p_.y_, 2);

        if (distanse_sq == cir->rad_ * cir->rad_)
            return TwoPoints(dot->p_, dot->p_, 1);
        else
            return TwoPoints(np, np, np, np, 0);
    }

    TwoPoints DotCir(Figure* dotarg, Figure* cirarg)
    {smn
        return CirDot(cirarg, dotarg);
    }

    TwoPoints LneDot (Figure* lnearg, Figure* dotarg)
    {smn
        Line* lne = (Line*) lnearg;
        Dot*  dot = (Dot*) dotarg;

        float temp = lne->A_ * dot->p_.x_ + lne->B_ * dot->p_.y_ + lne->C_;
    
        if (temp == 0)
            return TwoPoints(dot->p_, dot->p_, 1);
        else
            return TwoPoints(np, np, np, np, 0);
    }

    TwoPoints DotLne (Figure* dotarg, Figure* lnearg)
    {smn
        return LneDot(lnearg, dotarg);
    }

//========================= Block ended =========================

    float distance (Point p1, Point p2)
    {
        float dist = sqrtf((p1.x_-p2.x_) * (p1.x_-p2.x_) + (p1.y_-p2.y_) * (p1.y_-p2.y_) );
    }

    void DebugTwoPoints (TwoPoints pts)
    {
        printf("Первая точка пересечения: (%f;%f)\nВторая точка пресечения:  (%f,%f)\nВсего точек:\t\t  %d\n", pts.p1_.x_, pts.p1_.y_, pts.p2_.x_, pts.p2_.y_, pts.nop_);
    }

    void DebugPrintFigure(Figure* fig)
    {
        switch(fig->type_)
        {
            case Figure::DOT:
            {
                Dot* dot = (Dot*)fig;
                printf("It's dot!\n");
                printf("Point: (%f, %f)\n\n", dot->p_.x_, dot->p_.y_);
                break;
            }    
            case Figure::LINE:
            {
                Line* line = (Line*)fig;
                printf("It's line!\n");
                printf("A = %f, B = %f, C = %f\n\n", line->A_, line->B_, line->C_);
                break;
            }
            case Figure::CIRCLE:
            {
                Circle* cir = (Circle*)fig;
                printf("It's circle\n");
                printf("Rad = %f, Center: (%f, %f)\n\n", cir->rad_, cir->cntr_.x_, cir->cntr_.y_);
                break;
            }
            default:
                assert(0 && "Unknown figure type!\n");
        }
    }
}