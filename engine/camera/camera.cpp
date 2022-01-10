#include "camera.hpp"

int Camera::max(int a, int b){
    return a > b ? a : b;
}

int Camera::min(int a, int b){
    return a > b ? b : a;
}


void Camera::setPosX(int val){
    pos.x = max(0, val);
    pos.x = min(pos.x, maxWidth - viewPortWidth);
}

void Camera::setPosY(int val){
    pos.y = max(0, val);
    pos.y = min(pos.y, maxHeight - viewPortHeight);
}

Camera::Camera(Point const gameDimensions, Point const windowDims){
    maxWidth = gameDimensions.x;
    maxHeight = gameDimensions.y;

    viewPortWidth = windowDims.x;
    viewPortHeight = windowDims.y;

    if (viewPortWidth > maxWidth || viewPortHeight > maxHeight){
        //Exception to be thrown here
        std::cout << "DIMENSIONS OF SCENE SMALLER THAN WINDOW!\n";
    }
}

Camera* Camera::create(Point gameDimensions, Point windowDims){
    instance = new Camera(gameDimensions, windowDims);
    return instance;
}

Camera* Camera::get(){
    return instance;
}

Point Camera::convertToGameCoords(Point const &objPos) const{
    return Point(objPos.x - pos.x, objPos.y - pos.y);
}

void Camera::move(Point const &delPos){
    setPosX(pos.x + delPos.x);
    setPosY(pos.y + delPos.y);
}

void Camera::destroyCamera(){
    delete instance;
}

Point Camera::getPos(){
    return pos;
}

Camera* Camera::instance = nullptr;
