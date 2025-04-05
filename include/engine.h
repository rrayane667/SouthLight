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
        
        Registry Reg;
        RessourceManager RessMan;
        GraphicsDevice* gpu;// handles communication with gpu
        //SceneManager SceneMan;

        Settings* s;

        

        
        void onStart();
        
        void onExit();
        void freeProcessedMesh(ProcessedMesh* mesh);
        public:
        EventManager EvMan;
        void onInit();
        void onUpdate();
            Engine(RENDERER_TYPE type);

            template <typename T>
            inline Component* getComponent(int entity){return Reg.getComponent<T>(entity);}

            template <typename T>
            inline void addComponent(int entity){return Reg.addComponent<T>(entity);}

            template <typename T>
            inline void removeComponent(int entity){return Reg.removeComponent<T>(entity);}

            inline int createEntity(){return Reg.createEntity();}

            void duplicate(int entity, const vec3& v);

            inline void addSystem(SYSTEM s){return SysMan.addSystem(s, Reg);}

            inline void setScale(float& x, float& y, float& z);

            void processEvents();
            void processMaterials();
            void processMeshes();
            void processInstances();
            void processTextures();
            
            static ProcessedMesh* processMesh(const MeshData& d);

            void run(); // makamlach
            
    };

}