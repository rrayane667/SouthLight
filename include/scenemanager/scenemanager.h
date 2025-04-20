#pragma once
#include <unordered_map>
#include "utilite/dataStruct.h"
#include "registry/registry.h"

using namespace REG;
using namespace DATASTRUCT;

namespace SCENES{

    //ressource manager load les scene enregistré format json (soit 
    // stock gameobject + component soit index des gameobject)
    //sceneLoader class va s'occuper de loader la scene (hierarchy + hash table) puis scene manager
    //remplace hierarchy et hash table du registry par jdad


    class SceneManager{
        Queue<std::string> scenes;
        Registry& reg;
        public :

            inline SceneManager(Registry r) : reg(r) {}  
        

    };
}