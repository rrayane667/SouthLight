#include "ressources/ressourcemanager.h"
#include "ressources/ressource.h"
#include "utilite/parser.h"
#include <fstream>

using namespace UTILITY;
using namespace DATASTRUCT;

namespace RESSOURCES{
    RessourceManager::RessourceManager(){
        std::cout << "Constructing Ressource manager..." << std::endl;
        Ressources = SparseSet<Ressource*>();
        Paths = new DynamicList<Trio<std::string>>();
        FactoriesFunc["a"]["mesh"] = &AbstractFactory::createMeshData;
        Factories["a"] = new RessourceFactoryTypeA;

        std::ifstream inputFile(manifest_path);
        
        std::string line;
        
        while(std::getline(inputFile, line)){
            List<std::string> *temp = ManifestParser::parse(line);

            Paths->append(Trio<std::string>(temp->get(0), temp->get(1), temp->get(2)));

            delete temp;
        }
        std::cout << "Ressource manager Constructed " << std::endl;
        std::cout << std::endl;
    }

    Ressource* RessourceManager::get(int ressource_index){  // si indice superieur a taille manifest????
        load(ressource_index);
        
        return Ressources[ressource_index];
    }

    void RessourceManager::load(int ressource_index){
        if(ressource_index >= Paths->len()) throw std::runtime_error("zbi ra makaynch had lfichier ");

        if (Ressources.getIndex(ressource_index) ==-1){
            createRessource(ressource_index);
        }
        if(!Ressources[ressource_index]->isLoaded()){
            Ressources[ressource_index]->load();
        }
        
    }

    void RessourceManager::createRessource(int ressource_index){
        if (Ressources.getIndex(ressource_index)!=-1) return;

        std::string ressource_path = (Paths->get(ressource_index))[0];
        std::string ressource_type = (Paths->get(ressource_index))[1];
        std::string ressource_variant = (Paths->get(ressource_index))[2];

        Ressource* res = (Factories[ressource_variant]->*FactoriesFunc[ressource_variant][ressource_type])(ressource_path, ressource_index);//placeholder
        Ressources.set(ressource_index, res);

    }
    void RessourceManager::unload(int ressource_index){
        if (Ressources.getIndex(ressource_index)==-1) return;
        Ressources[ressource_index]->unload();
        Ressources.remove(ressource_index);
    }

    void RessourceManager::unloadAll(){
        int length = Paths->len();
        for (auto i = 0; i<length ; i++){
            unload(i);
        }

    }

    RessourceManager::~RessourceManager(){
        delete Paths;
    }

}