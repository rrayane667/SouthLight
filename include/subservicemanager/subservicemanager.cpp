#include "subservicemanager.h"

namespace SUBSERVICES{
    alignas(Registry) std::byte SubServiceManager::reg[sizeof(Registry)];
    alignas(RessourceManager) std::byte  SubServiceManager::ress_man[sizeof(RessourceManager)];
    alignas(SystemManager) std::byte  SubServiceManager::sys_man[sizeof(SystemManager)];
    alignas(EventManager) std::byte  SubServiceManager::ev_man[sizeof(EventManager)];
    
    void SubServiceManager::startup(){
        if(is_init) return;
            is_init = true;
        new (&ev_man) EventManager ;
        new (&reg) Registry ;
        new (&ress_man) RessourceManager ;
        EventManager& e = *reinterpret_cast<EventManager*>(&ev_man);
        new (&sys_man) SystemManager(getEventManager());
        
    }
}