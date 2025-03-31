#include "systemmanager.h"
#include "utilite/dataStruct.h"

using namespace DATASTRUCT;

namespace SYSTEMS{
   void SystemManager::addSystem(System* s){
    SYSTEM t = s->getId();
    if(systems_map.find(t) != systems_map.end()) return;
    systems.append(s);
    systems_map[t] = s;
      
   }

   void SystemManager::addSystem(SYSTEM s){
      if(systems_map.find(s) != systems_map.end()) return;
    if(s== RENDERER){
        System* sys = new Renderer;
        systems.append(sys);
        systems_map[s] = sys;
    }
    if(s==TRANSFORMER){
        System* sys = new Transformer;
        systems.append(sys);
    }
    if(s==INSTANCEUR){
        System* sys = new Instanceur;
        systems.append(sys);
    }

    
   }


   void SystemManager::initAllSystems(REG::Registry& reg){
    for(auto& x:systems){
        
        x->onInit(reg);
    }
   }

   void SystemManager::startAllsystems(REG::Registry& reg){
    for(auto& x:systems){
        
        x->onStart(reg);
    }
   }
   
   void SystemManager::updateAllSystems(REG::Registry& reg){
    for(auto& x:systems){
        
        x->update(reg);
    }
   }

   void SystemManager::shutdown(REG::Registry& reg){
    for(auto& x:systems){
        
        x->ondestroy();
    }
   }
}