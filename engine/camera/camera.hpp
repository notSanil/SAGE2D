#pragma once
#include <iostream>

#include "../transform/point.hpp"

class Camera{
private:
    Point pos{0, 0};

    static Camera* instance;

    int maxWidth, maxHeight;
    int viewPortWidth, viewPortHeight;

    int max(int a, int b) const;
    int min(int a, int b) const;
    void setPosX(int val);
    void setPosY(int val);
    Camera(Point const &gameDimensions, Point const &windowDims);

public:
    static Camera* create(Point gameDimensions, Point windowDims);
    static Camera* get();
    Point convertToGameCoords(Point const &objPos) const;
    void moveBy(Point const &delPos);
    void moveTo(Point const &pos);
    static void destroyCamera();
    Point getPos() const;
};
