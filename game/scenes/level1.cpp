#include "level1.hpp"
#include "objects/textureTest.hpp"

Level1::Level1(){
    //font = Font::get("assets/fonts/Roboto-Regular.ttf", 24);
    objects.push_back(new TextureTest(Point(100, 100)));
};

void Level1::on_step(const float deltaTime){
}

void Level1::on_render(){
    Renderer::StartScene();
    //Renderer::RenderText(font, "Hello", Sage::Vec4{255, 255, 255, 255}, Point(10, 10));
    for (auto& object: objects)
    {
        object->draw();
    }
}

void Level1::on_event(Sage::Event& e)
{
}

Level1::~Level1(){
    for (auto &object: objects){
        delete object;
    }
    objects.clear();
}
