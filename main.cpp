#include <iostream>

#include "engine.h"
using namespace ENGINE;

//assets f scene manager = component stocké



int main(int, char**){


    Engine stpKhdm(GL_TYPE);

    

    stpKhdm.addSystem(INSTANCEUR);
    stpKhdm.addSystem(TRANSFORMER);
    stpKhdm.addSystem(RENDERER);
    stpKhdm.addSystem(INPUT);
    stpKhdm.addSystem(MVT);
    stpKhdm.addSystem(CAMERA_CONTROL);
    
    int object = stpKhdm.createEntity();

    stpKhdm.addComponent<Mesh>(object);
    Mesh* mesh = dynamic_cast<Mesh*>(stpKhdm.getComponent<Mesh>(object));
    mesh->ressource = 0;
    
    Transform* t = dynamic_cast<Transform*>(stpKhdm.getComponent<Transform>(object));
     t->scale = vec3(1.0f, 1.0f, 1.0f)*4;
     t->position = vec3( 0, -2, 20 );


    
    int n=10;
    
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= n; k++){

                stpKhdm.duplicate(object, vec3(30*i/n - 150, 30*j/n - 150, 29*k/n + 10));    

            }
        }
    }
    
    stpKhdm.addComponent<Camera>(stpKhdm.createEntity());

    stpKhdm.run();

}