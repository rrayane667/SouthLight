#include "ressources/ressourcemanager.h"
#include "ressources/ressource.h"
#include "ressources/utility/ressourceutility.h"
#include <fstream>

using namespace DATASTRUCT;

namespace RESSOURCES{
    RessourceManager::RessourceManager(){
        Ressources = SparseSet<Ressource*>();
        Paths = new DynamicList<paire<std::string, int>>();

        std::ifstream inputFile(manifest_path);

        std::string line;
        
        while(std::getline(inputFile, line)){
            std::string temp = line;
            std::getline(inputFile, line);

            Paths->append(std::pair<std::string, int>(temp, stoi(line)));
        }

    }

    void RessourceManager::get(int ressource_index){
        if (Ressources.getIndex(ressource_index)!=-1) return;

        std::string ressource_path = Paths->get(ressource_index).first;
        int ressource_type = Paths->get(ressource_index).second;

        Ressource* res = RessourceFactory::create(ressource_type, ressource_path, ressource_index);
        Ressources.set(ressource_index, res);

    }
    void RessourceManager::unload(int ressource_index){
        if (Ressources.getIndex(ressource_index)==-1) return;
        Ressources[ressource_index]->unload();
        Ressources.remove(ressource_index);
    }

    RessourceManager::~RessourceManager(){
        delete Paths;
    }

}