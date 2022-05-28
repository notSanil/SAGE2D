#include "Sage/engine.hpp"

extern Sage::Engine* CreateApplication();


int main(int argv, char **argc){
    Sage::Engine* engine = CreateApplication();
    engine->run();
    delete engine;
    return 0;
}