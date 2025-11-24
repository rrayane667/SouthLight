#include <iostream>

#include "engine.h"
using namespace ENGINE;

//assets f scene manager = component stocké



int main(int, char**){


    Engine stpKhdm(GL_TYPE);
    

    

    stpKhdm.addSystem(INSTANCEUR, 0);
    stpKhdm.addSystem(TRANSFORMER, 0);
    stpKhdm.addSystem(RENDERER, 0);
    stpKhdm.addSystem(INPUT, 0);
    stpKhdm.addSystem(MVT, 0);
    stpKhdm.addSystem(CAMERA_CONTROL, 0);
    
    int object = stpKhdm.createEntity();
    std::cout << "Created entity with ID: " << object << std::endl;
    stpKhdm.addComponent<Mesh>(object);
    std::cout << "Added Mesh component to entity ID: " << object << std::endl;
    Mesh* mesh = dynamic_cast<Mesh*>(stpKhdm.getComponent<Mesh>(object));
    std::cout << "Retrieved Mesh component from entity ID: " << object << std::endl;
    mesh->ressource = 0;
    
    Transform* t = dynamic_cast<Transform*>(stpKhdm.getComponent<Transform>(object));
     t->scale = vec3(1.0f, 1.0f, 1.0f)*4;
     t->position = vec3( 0, -2, 20 );


    
    int n=10;
    std::cout << "Starting duplication of object ID: " << object << std::endl;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            for(int k = 0; k <= n; k++){

                stpKhdm.duplicate(object, vec3(100*i/n - (1-i/n)*100, 100*j/n - (1-j/n)*100, 100*k/n - (1-k/n)*100));    

            }
        }
    }
    
    stpKhdm.addComponent<Camera>(stpKhdm.createEntity());

    stpKhdm.run();

}