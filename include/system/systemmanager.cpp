#include "systemmanager.h"
#include "utilite/dataStruct.h"

using namespace DATASTRUCT;

namespace SYSTEMS{
   void SystemManager::addSystem(System* s){
    systems.append(s);
   }

   void SystemManager::addSystem(SYSTEM s){
    if(s== RENDERER){
        System* sys = new Renderer;
        systems.append(sys);
    }
    if(s==TRANSFORM){
        System* sys = new Transformer;
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