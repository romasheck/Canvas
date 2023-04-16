#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <iostream>

#include "gui_lib.hpp"
#include <cmath>

namespace gui
{

class coordinate
    {
    public:
        float x_, y_;

    public:
        coordinate(float x, float y):
        x_(x), y_(y)
        {};
        coordinate(const coordinate& coord):
        x_(coord.x_),y_(coord.y_)
        {};
        coordinate() {x_ = 0; y_ = 0;}

    public:
        
        coordinate operator + (coordinate right) const//a+b
        {
            return coordinate(x_+right.x_, y_+right.y_);
        }
        coordinate operator - (coordinate right) const//a-b
        {
            return coordinate(x_-right.x_, y_-right.y_);
        }
        coordinate operator * (coordinate right) const
        {
            return coordinate(x_*right.x_, y_*right.y_);
        }
        coordinate operator / (coordinate right) const
        {
            return coordinate(x_/right.x_, y_/right.y_);
        }

        bool operator == (coordinate right) const
        {
            return (x_ == right.x_) && (y_ == right.y_);
        }
        bool operator != (coordinate right) const
        {
            return (x_ != right.x_, y_ != right.y_);
        }

        coordinate operator = (coordinate right)
        {
            x_ = right.x_;
            y_ = right.y_;
            
            return *this;
        }

        void transmit (coordinate shift, coordinate scale)
        {
            *this = shift + coordinate(x_*scale.x_, y_*scale.y_);
        }

        operator sf::Vector2f() const 
        {
            return sf::Vector2f(x_, y_);
        }
    };

    inline coordinate operator - (const coordinate right)//-a
    {
        return coordinate(-right.x_, -right.y_);
    }
    inline coordinate operator * (const float scalar, const coordinate coord)
    {
        return coordinate(scalar*coord.x_, scalar*coord.y_);
    }
    inline coordinate operator / (const coordinate coord, const float scalar)
    {
        if (scalar != 0)
        {
            return coordinate(coord.x_/scalar, coord.y_/scalar);
        }

        return coordinate(0, 0);
    }

    inline coordinate cabs(const coordinate arg)
    {
        return coordinate(abs(arg.x_), abs(arg.y_));
    }
}

#endif