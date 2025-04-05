#pragma once
#include "utilite/dataStruct.h"
#include "system.h"
#include "registry/registry.h"
#include <unordered_map>
using namespace DATASTRUCT;

namespace SYSTEMS{
    class SystemManager{
        EventManager& em;

        DynamicList<System*> systems;
        std::unordered_map<SYSTEM, System*> systems_map;
        public:
            inline SystemManager(EventManager& e) : em(e){std::cout << "System manager constructed" << std::endl;std::cout << std::endl;};
            void addSystem(System* s);
            void addSystem(SYSTEM s, REG::Registry& r);
            inline System* getSystem(SYSTEM s){return systems_map[s];}

            void initAllSystems();
            void startAllsystems();
            void updateAllSystems();
            void shutdown();//????
    };
}