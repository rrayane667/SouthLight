#include "systemmanager.h"
#include "utilite/dataStruct.h"
using namespace DATASTRUCT;

namespace SYSTEMS{
   void SystemManager::addSystem(System* s){
    systems.append(s);
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
}