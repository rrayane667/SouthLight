#include "system/layer.h"


namespace SYSTEMS{


    void Layer::addSystem(SYSTEM s, REG::Registry& r, EventManager& em){

        if(s== RENDERER){
            System* sys = new Renderer(em, r, layer_index);
            systems.append(sys);

        }
        if(s==TRANSFORMER){
            System* sys = new Transformer(em, r, layer_index);
            systems.append(sys);
        }
        if(s==INSTANCEUR){

            System* sys = new Instanceur(em, r, layer_index);
            systems.append(sys);
        }
        if(s==INPUT){
            System* sys = new InputReading(em, r, layer_index);
            systems.append(sys);
        }
        if(s==MVT){
            System* sys = new Mvt(em, r, layer_index);
            systems.append(sys);
        }
        if(s==CAMERA_CONTROL){
            System* sys = new CameraController(em, r, layer_index);
            systems.append(sys);
        }
    }

    void Layer::initAllSystems(){
        for(auto& x:systems){
        
            x->onInit();
        }
    }

    void Layer::startAllsystems(){

        for(auto& x:systems){
            
            x->onStart();
        }
    }

    void Layer::updateAllSystems(){
        
        for(auto& x:systems){
            
            x->update();
        }
       }
    
    void Layer::shutdown(){
        for(auto& x:systems){
            
            x->ondestroy();
        }
    }
}