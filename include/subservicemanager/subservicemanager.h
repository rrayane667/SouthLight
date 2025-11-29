#pragma once 
#include "registry/registry.h"
#include "ressources/ressourcemanager.h"
#include "system/systemmanager.h"
#include "eventmanager/eventmanager.h"
#include <new>       
#include <cstddef>
using namespace REG;
using namespace RESSOURCES;
using namespace SYSTEMS;
using namespace EVENTS;

namespace SUBSERVICES{

    class SubServiceManager{
        
        static alignas(Registry) std::byte reg[sizeof(Registry)];
        static alignas(RessourceManager) std::byte  ress_man[sizeof(RessourceManager)];
        static alignas(SystemManager) std::byte  sys_man[sizeof(SystemManager)];
        static alignas(EventManager) std::byte  ev_man[sizeof(EventManager)];

        inline static bool is_init = false;

        public:

        static void startup();

        inline static Registry& getRegistry(){
            if(!is_init) startup();
            return *reinterpret_cast<Registry*>(&reg) ;
        }

        inline static RessourceManager& getRessourceManager(){
            if(!is_init) startup();
            return *reinterpret_cast<RessourceManager*>(&ress_man) ;
        }

        inline static SystemManager& getSystemManager(){
            if(!is_init) startup();
            return *reinterpret_cast<SystemManager*>(&sys_man) ;
        }

        inline static EventManager& getEventManager(){
            if(!is_init) startup();
            return *reinterpret_cast<EventManager*>(&ev_man) ;
        }
    };
}