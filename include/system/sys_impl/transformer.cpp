#include "system/system.h"

namespace SYSTEMS{

    void Transformer::onInit(){
        List<int>* entities_list = reg.getEntities<Transform>();
        std::cout << "ra transformateur 7adr initialisé" << std::endl;

        for(auto& x:(*entities_list)){
            updateMatrix(x);
        }

        
    }

    bool Transformer::updateMatrix( int& x){


        Transform *t = reg.getComponent<Transform>(x);
        
        t->model = mat4::translation(t->position)*mat4::rotation(vec4(0,0,1,0),t->rotation.z)*mat4::rotation(vec4(0,1,0,0),t->rotation.y)*mat4::rotation(vec4(1,0,0,0),t->rotation.x)*mat4::scale(t->scale);
        return true;
    }

    void Transformer::setPosition(int entity, const vec3& v){
        reg.getComponent<Transform>(entity)->position = v;
        updateMatrix(entity);
    }

    void Transformer::setRotation(int entity, const vec3& v){
        reg.getComponent<Transform>(entity)->rotation = v;
        updateMatrix(entity);
    }

    void Transformer::setScale(int entity, const vec3& v){
        reg.getComponent<Transform>(entity)->scale = v;
        updateMatrix(entity);
    }
}