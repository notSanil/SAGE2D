#include "splash.hpp"

#include "level1.hpp"
#include "objects/test.hpp"
#include "Sage/Events/KeyEvent.h"

splash::splash(){
    GameObject* test = new Dummy(Point{500, 0});
    GameObject* test2 = new Dummy(Point{500, 300});
    objects.push_back(test2);
    objects.push_back(test);

    for (int i = 0; i < 5000; ++i){
        GameObject* obj = new Dummy(Point(i / 600, i % 600));
        objects.push_back(obj);
    }
}

void splash::on_render(){
    Renderer::StartScene();

    for (auto &object: objects){
        object -> draw();
    }
}

void splash::on_event(Sage::Event& e)
{
    Sage::Dispatcher dispatcher(e);
    dispatcher.Dispatch<Sage::KeyPressedEvent>(std::bind(&splash::KeyPressedCallback, this, std::placeholders::_1));
}

void splash::on_step(const float deltaTime)
{
}

splash::~splash(){
    for (auto &object: objects){
        delete object;
    }
    objects.clear();
    Camera::destroyCamera();
}

void splash::KeyPressedCallback(Sage::KeyPressedEvent& e)
{
    switch (e.GetKeyCode())
    {
    case Sage::KeyCode::d:
        cam->moveBy(Point{ speed, 0 });
        break;

    case Sage::KeyCode::w:
        cam->moveBy(Point{ 0, -speed });
        break;

    case Sage::KeyCode::a:
        cam->moveBy(Point{ -speed, 0 });
        break;

    case Sage::KeyCode::s:
        cam->moveBy(Point{ 0, speed });
        break;

    case Sage::KeyCode::l:
        sceneManager::changeCurrentScene<Level1>();
        break;

    case Sage::KeyCode::i:
        cam->moveTo(Point(800, 800));
        break;

    default:
        break;
    }
    SAGE_INFO("Key {0}, pressed {1} times", (int)e.GetKeyCode(), e.GetRepeatCount());
}
