#include "Sage/engine.hpp"
#include "scenes/splash.hpp"

int main(int argv, char **argc){
    Engine engine(600, 600, "Game Name");
    sceneManager::changeCurrentScene<splash>();
    engine.run();
    return 0;
}