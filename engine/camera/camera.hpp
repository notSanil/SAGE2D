#pragma once
#include <iostream>

#include "../transform/point.hpp"

class Camera{
private:
    Point pos{0, 0};

    static Camera* instance;

    int maxWidth, maxHeight;
    int viewPortWidth, viewPortHeight;

    int max(int a, int b){
        return a > b ? a : b;
    }

    int min(int a, int b){
        return a > b ? b : a;
    }


    void setPosX(int val){
        pos.x = max(0, val);
        pos.x = min(pos.x, maxWidth - viewPortWidth);
    }

    void setPosY(int val){
        pos.y = max(0, val);
        pos.y = min(pos.y, maxHeight - viewPortHeight);
    }

    Camera(Point const gameDimensions, Point const windowDims){
        maxWidth = gameDimensions.x;
        maxHeight = gameDimensions.y;

        viewPortWidth = windowDims.x;
        viewPortHeight = windowDims.y;

        if (viewPortWidth > maxWidth || viewPortHeight > maxHeight){
            //Exception to be thrown here
            std::cout << "DIMENSIONS OF SCENE SMALLER THAN WINDOW!\n";
        }
    }

public:
    static Camera* create(Point gameDimensions, Point windowDims){
        instance = new Camera(gameDimensions, windowDims);
        return instance;
    }

    static Camera* get(){
        return instance;
    }

    Point convertToGameCoords(Point const &objPos) const{
        return Point(objPos.x - pos.x, objPos.y - pos.y);
    }

    void move(Point const &delPos){
        setPosX(pos.x + delPos.x);
        setPosY(pos.y + delPos.y);
    }

    static void destroyCamera(){
        delete instance;
    }

    Point getPos(){
        return pos;
    }
};

Camera* Camera::instance = nullptr;

