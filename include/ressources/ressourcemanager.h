#pragma once
#include "ressource.h"
#include "utilite/dataStruct.h"
#include <string>


using namespace DATASTRUCT;

namespace RESSOURCES{

    class RessourceManager{

        int isLoaded(int ressource_index); //index in path list

        SparseSet<Ressource*> Ressources;
        std::string manifest_path = std::string("C:/Users/ORDI/Desktop/openGL/Ressource directory/manifest.txt");
        List<paire<std::string, int> >* Paths;

        public:
            void get(int ressource_index);
            void unload(int ressource_index);
            void unloadAll();
            RessourceManager();
            ~RessourceManager();
            void update(int ressource_index);
    
    };

}