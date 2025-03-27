#pragma once 
#include "eventmanager/eventmanager.h"
#include "ressources/ressourcemanager.h"
#include "system/systemmanager.h"
#include "registry/registry.h"
#include "gpu/gpu.h"
#include "settings/settings.cpp"
#include <vector>

using namespace EVENTS;
using namespace REG;
using namespace RESSOURCES;
using namespace SYSTEMS;
using namespace GPU;

namespace ENGINE {
    

    class Engine {
        SystemManager SysMan;
        EventManager EvMan;
        Registry Reg;
        RessourceManager RessMan;
        GraphicsDevice* gpu;// handles communication with gpu
        //SceneManager SceneMan;

        Settings* s;

        

        void onInit();
        void onStart();
        void onUpdate();
        void onExit();
        ProcessedMesh freeProcessedMesh(ProcessedMesh* mesh);
        public:
            Engine(RENDERER_TYPE type);

            void processMaterials();
            void processMeshes();
            
            ProcessedMesh processMesh(const MeshData& d);

            void run(); // makamlach
            
    };

}