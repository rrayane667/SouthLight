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
    mesh->ressource = 9;

    Transform* t = dynamic_cast<Transform*>(stpKhdm.getComponent<Transform>(object));
    t->scale = vec3(1.0f, 1.0f, 1.0f);
    t->position = vec3(
        0,  
        -2,  
        20   
    );
    stpKhdm.addComponent<Material>(object);
    Material* mat = dynamic_cast<Material*>(stpKhdm.getComponent<Material>(object));
    mat->frag_index = 6;
    mat->vert_index = 7;
    unsigned int txtre = 8;

    mat->tex_components["a"] = &txtre;


    stpKhdm.addComponent<Camera>(stpKhdm.createEntity());
    stpKhdm.run();

}
