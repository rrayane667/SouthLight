#pragma once
#include "ressource.h"
#include "utilite/dataStruct.h"
#include <string>
#include "ressources/utility/ressourceutility.h"
#include <unordered_map>

using namespace DATASTRUCT;

namespace RESSOURCES{

    class RessourceManager{

        //index in path list
        inline bool isLoaded(int ressource_index){
            return Ressources[ressource_index]->isLoaded();
        } 

        SparseSet<Ressource*> Ressources;
        const std::string manifest_path = std::string("C:/Users/ORDI/Desktop/openGL/RessourceDirectory/manifest.txt");
        List<Trio<std::string>>* Paths;

        std::unordered_map<std::string,std::unordered_map<std::string,Ressource* (AbstractFactory::*) (std::string path, int ressource_index)>> FactoriesFunc;
        std::unordered_map<std::string,AbstractFactory*> Factories;

        public:
        
            Ressource* get(int ressource_index);
            void createRessource(int ressource_index);
            void load(int ressource_index);
            void unload(int ressource_index);
            void unloadAll();
            RessourceManager();
            ~RessourceManager();
            void update(int ressource_index); // a implementer
    
    };
}