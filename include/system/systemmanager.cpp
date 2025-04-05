#include "systemmanager.h"
#include "utilite/dataStruct.h"
#include "system/scripts/mvt.h"
using namespace DATASTRUCT;

namespace SYSTEMS{
   void SystemManager::addSystem(System* s){
    SYSTEM t = s->getId();
    if(systems_map.find(t) != systems_map.end()) return;
    systems.append(s);
    systems_map[t] = s;
      
   }

   void SystemManager::addSystem(SYSTEM s, REG::Registry& r){
      if(systems_map.find(s) != systems_map.end()) return;
    if(s== RENDERER){
        System* sys = new Renderer(em, r);
        systems.append(sys);
        systems_map[s] = sys;
    }
    if(s==TRANSFORMER){
        System* sys = new Transformer(em, r);
        systems.append(sys);
    }
    if(s==INSTANCEUR){
        System* sys = new Instanceur(em, r);
        systems.append(sys);
    }
    if(s==INPUT){
        System* sys = new InputReading(em, r);
        systems.append(sys);
    }
    if(s==MVT){
        System* sys = new Mvt(em, r);
        systems.append(sys);
    }
    if(s==CAMERA_CONTROL){
        System* sys = new CameraController(em, r);
        systems.append(sys);
    }

    
   }


   void SystemManager::initAllSystems(){
    for(auto& x:systems){
        
        x->onInit();
    }
   }

   void SystemManager::startAllsystems(){
    for(auto& x:systems){
        
        x->onStart();
    }
   }
   
   void SystemManager::updateAllSystems(){
    for(auto& x:systems){
        
        x->update();
    }
   }

   void SystemManager::shutdown(){
    for(auto& x:systems){
        
        x->ondestroy();
    }
   }
}