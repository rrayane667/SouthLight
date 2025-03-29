#include <iostream>

#include "engine.h"
using namespace ENGINE;

//assets f scene manager = component stocké

int main(int, char**){


    Engine stpKhdm(GL_TYPE);

    stpKhdm.addSystem(RENDERER);

    int object = stpKhdm.createEntity();

    stpKhdm.addComponent<Mesh>(object);
    Mesh* mesh = dynamic_cast<Mesh*> (stpKhdm.getComponent<Mesh>(object));
    mesh->ressource = 1;
    
    stpKhdm.run();

    std::cout << "Hello, from Engine!\n";

    
}
