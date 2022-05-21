#pragma once

struct Point
{
    int x, y;
    Point(int x, int y);
    Point();
};

namespace Sage {
    struct Vec2
    {
        float x, y;
    };
}