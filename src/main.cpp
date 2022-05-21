#include "Sage/engine.hpp"
#include "scenes/splash.hpp"

int main(int argv, char **argc){
    Engine engine(940, 540, "Game Name");
    sceneManager::changeCurrentScene<splash>();
    engine.run();
    return 0;
}