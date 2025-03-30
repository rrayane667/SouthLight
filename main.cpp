#include <iostream>

#include "engine.h"
using namespace ENGINE;

//assets f scene manager = component stocké

int main(int, char**){


    Engine stpKhdm(GL_TYPE);

    stpKhdm.addSystem(TRANSFORM);
    stpKhdm.addSystem(RENDERER);

    int object = stpKhdm.createEntity();


    stpKhdm.addComponent<Mesh>(object);
    Mesh* mesh = dynamic_cast<Mesh*> (stpKhdm.getComponent<Mesh>(object));
    mesh->ressource = 0;

    Transform* t = dynamic_cast<Transform*> (stpKhdm.getComponent<Transform>(object));
    t->scale = vec3(0.2f,0.2f,0.2f);
    t->position = vec3(0.0f,-2.0f,10.0f);
    //t->rotation = vec3(0.0f,0.0f,1.5f);
    stpKhdm.addComponent<Camera>(stpKhdm.createEntity());

    
    stpKhdm.run();



    
}
