#include "test.hpp"


Dummy::Dummy(Point const pos){
    this -> pos = pos;
    animator.setFrameColumnsRows(6, 4);
}

void Dummy::draw(){
    animator.renderCurrentFrameWithCamera(pos);
    animator.moveToNextFrame();
}

void Dummy::step(float deltaTime){
}

void Dummy::event(){
}

GameObject* __stdcall Dummy::CreateObjectFn(Point const pos){
    return new Dummy(pos);
}

Dummy::~Dummy(){
    animator.free();
}

