#pragma once

struct Point
{
    int x, y;
    Point(int x, int y);
    Point();
    operator int* ()
    {
        return &x;
    }
};

namespace Sage {
    struct Vec2
    {
        float x, y;
        operator float* ()
        {
            return &x;
        }
    };
}