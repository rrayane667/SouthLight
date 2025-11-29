#include "system/layer.h"


namespace SYSTEMS{


    void Layer::addSystem(SYSTEM s, REG::Registry& r, EventManager& em){

        if(s== RENDERER){
            System* sys = new Renderer(layer_index);
            systems.append(sys);

        }
        if(s==TRANSFORMER){
            System* sys = new Transformer(layer_index);
            systems.append(sys);
        }
        if(s==INSTANCEUR){

            System* sys = new Instanceur(layer_index);
            systems.append(sys);
        }
        if(s==INPUT){
            System* sys = new InputReading(layer_index);
            systems.append(sys);
        }
        if(s==MVT){
            System* sys = new Mvt(layer_index);
            systems.append(sys);
        }
        if(s==CAMERA_CONTROL){
            System* sys = new CameraController(layer_index);
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