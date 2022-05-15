#include "Sage/engine.hpp"
#include "scenes/splash.hpp"

int main(int argv, char **argc){
    Engine engine(600, 600, "Game Name");
    sceneManager* manager = sceneManager::get();
    manager->changeCurrentScene<splash>();
    manager->run();
    return 0;
}