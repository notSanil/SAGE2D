#pragma once

struct Point
{
    int x, y;
    Point(int x, int y) : 
        x(x), y(y) 
    {}

    Point() {
        x = 0;
        y = 0;
    }

    operator int* ()
    {
        return &x;
    }
};

namespace Sage {
    template<typename T>
    struct Vec2
    {
        T x, y;
        operator T* ()
        {
            return &x;
        }
    };
}