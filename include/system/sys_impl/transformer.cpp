#include "system/system.h"

namespace SYSTEMS{

    void Transformer::onInit(REG::Registry& reg){
        List<int>* entities_list = reg.getEntities<Transform>();
        std::cout << "ra transformateur 7adr initialisé" << std::endl;

        for(auto& x:(*entities_list)){
            updateMatrix(reg, x);
        }
    }

    void Transformer::updateMatrix(REG::Registry& reg, int& x){
        Transform *t = reg.getComponent<Transform>(x);
        t->model = mat4::translation(t->position)*mat4::rotation(vec4(0,0,1,0),t->rotation.z)*mat4::rotation(vec4(0,1,0,0),t->rotation.y)*mat4::rotation(vec4(1,0,0,0),t->rotation.x)*mat4::scale(t->scale);

    }

    void Transformer::setPosition(REG::Registry& reg, int entity, const vec3& v){
        reg.getComponent<Transform>(entity)->position = v;
        updateMatrix(reg, entity);
    }

    void Transformer::setRotation(REG::Registry& reg, int entity, const vec3& v){
        reg.getComponent<Transform>(entity)->rotation = v;
        updateMatrix(reg, entity);
    }

    void Transformer::setScale(REG::Registry& reg, int entity, const vec3& v){
        reg.getComponent<Transform>(entity)->scale = v;
        updateMatrix(reg, entity);
    }
}