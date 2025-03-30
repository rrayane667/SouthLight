#include <iostream>

#include "engine.h"
using namespace ENGINE;

//assets f scene manager = component stocké

int main(int, char**){


    Engine stpKhdm(GL_TYPE);

    stpKhdm.addSystem(TRANSFORM);
    stpKhdm.addSystem(RENDERER);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for(int k = 0; k < 10; k++) {
                int object = stpKhdm.createEntity();
    
                stpKhdm.addComponent<Mesh>(object);
                Mesh* mesh = dynamic_cast<Mesh*>(stpKhdm.getComponent<Mesh>(object));
                mesh->ressource = 0;
    
                Transform* t = dynamic_cast<Transform*>(stpKhdm.getComponent<Transform>(object));
                t->scale = vec3(1.0f, 1.0f, 1.0f);
                

                t->position = vec3(
                    75.0f * i/9 - 32.5f,  // x ranges from -10 to +10
                    75.0f * j/9 - 32.5f,  // y ranges from -10 to +10
                    10.0f + 100.0f * k/9    // z ranges from 5 to 30
                );
            }
        }
    }


    //t->rotation = vec3(0.0f,0.0f,1.5f);
    stpKhdm.addComponent<Camera>(stpKhdm.createEntity());

    
    stpKhdm.run();



    
}
