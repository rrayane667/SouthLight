#pragma once
#include "utilite/dataStruct.h"
#include "system.h"

using namespace DATASTRUCT;

namespace SYSTEMS{
    class SystemManager{
        DynamicList<System*> systems;

        public:
            SystemManager();
            void addSystem(System* s);

            void initAllSystems();
            void startAllsystems();
            void updateAllSystems();
            void shutdown();//????
    };
}