#include <iostream>

#include "engine.h"
using namespace ENGINE;

//assets f scene manager = component stocké

int main(int, char**){


    Engine stpKhdm(GL_TYPE);

    stpKhdm.addSystem(INSTANCEUR);
    stpKhdm.addSystem(TRANSFORMER);
    stpKhdm.addSystem(RENDERER);
    

    int object = stpKhdm.createEntity();
    stpKhdm.addComponent<Mesh>(object);
    Mesh* mesh = dynamic_cast<Mesh*>(stpKhdm.getComponent<Mesh>(object));
    mesh->ressource = 0;
    Transform* t = dynamic_cast<Transform*>(stpKhdm.getComponent<Transform>(object));
    t->scale = vec3(1.0f, 1.0f, 1.0f);
    t->position = vec3(
        0,  
        0,  
        0   
    );
    

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for(int k = 0; k < 10; k++) {

    
                
                
                stpKhdm.duplicate(object, vec3(
                    75.0f * i/9 - 32.5f,  
                    75.0f * j/9 - 32.5f,  
                    10.0f + 100.0f * k/9  
                ));
                
                
            }
        }
    }
    std::cout<<"TEST"<<std::endl;

    //t->rotation = vec3(0.0f,0.0f,1.5f);
    stpKhdm.addComponent<Camera>(stpKhdm.createEntity());

    
    stpKhdm.run();



    
}
