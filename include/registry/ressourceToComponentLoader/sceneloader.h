#pragma once
#include "ressources/ressourcemanager.h"
#include "registry/registry.h"
#include "registry/ressourceToComponentLoader/componentloader.h"
using namespace RESSOURCES;


namespace REG{
    
        class SceneLoader{

            public:
                SceneLoader() = default;
                ~SceneLoader() = default;
                void createScene(Registry& reg, RESSOURCES::RessourceManager& ress_man, int scene_index);
                void exportScene(Registry& reg, int scene_index, RESSOURCES::RessourceManager& ress_man);
        };
}