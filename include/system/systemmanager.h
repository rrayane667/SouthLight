#pragma once
#include "utilite/dataStruct.h"
#include "system.h"
#include "registry/registry.h"
#include <unordered_map>
using namespace DATASTRUCT;

namespace SYSTEMS{
    class SystemManager{
        DynamicList<System*> systems;
        std::unordered_map<SYSTEM, System*> systems_map;
        public:
            inline SystemManager() {std::cout << "System manager constructed" << std::endl;std::cout << std::endl;};
            void addSystem(System* s);
            void addSystem(SYSTEM s);

            void initAllSystems(REG::Registry& reg);
            void startAllsystems(REG::Registry& reg);
            void updateAllSystems(REG::Registry& reg);
            void shutdown(REG::Registry& reg);//????
    };
}