#include "systemmanager.h"
#include "utilite/dataStruct.h"

using namespace DATASTRUCT;

namespace SYSTEMS{
   void SystemManager::addSystem(System* s, int layer_index){
    SYSTEM t = s->getId();
    if(systems_map.find(t) != systems_map.end()) return;
    systems.get(layer_index)->addSystem(s);
    systems_map[t] = Mappin2d(layer_index, systems[layer_index]->getSize() -1);
      
   }

   void SystemManager::addSystem(SYSTEM s, REG::Registry& r, int layer_index){
        if(systems_map.find(s) != systems_map.end()) return;
        (systems.get(layer_index))->addSystem(s, r, em);
        systems_map[s] = Mappin2d(layer_index, (systems.get(layer_index))->getSize()-1);
    } 


   void SystemManager::initAllSystems(){
    for(auto& x:systems){
        
        x->initAllSystems();
    }
   }

   void SystemManager::startAllsystems(){
    for(auto& x:systems){
        
        x->startAllsystems();
    }
   }
   
   void SystemManager::updateAllSystems(){
    for(auto& x:systems){
        
        x->updateAllSystems();
    }
   }

   void SystemManager::shutdown(){
    for(auto& x:systems){
        
        x->shutdown();
    }
   }
}