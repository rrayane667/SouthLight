#pragma once 
#include "eventmanager/eventmanager.h"
#include "ressources/ressourcemanager.h"
#include "system/systemmanager.h"
#include "registry/registry.h"

using namespace EVENTS;
using namespace REG;
using namespace RESSOURCES;
using namespace SYSTEMS;

namespace ENGINE {

    class Engine {
        SystemManager SysMan;
        EventManager EvMan;
        Registry Reg;
        RessourceManager RessMan;
        SceneManager SceneMan;
        public:
            Engine();
            void onInit();
            void onStart();
            void onUpdate();
            void onExit();
    };

}