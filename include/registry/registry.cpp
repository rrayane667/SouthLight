#include "registry/registry.h"

namespace REG{

    int Registry::createEntity(){
        std::cout << "creating entity"<<std::endl;
        hierarchy->append(3);
        addComponent<Visibilite>(hierarchy->len());
        addComponent<Transform>(hierarchy->len());
        std::cout << "entity created"<<std::endl;
        std::cout <<std::endl;
        //ajout des component dans les sparse sets correspondants
        return hierarchy->len();
        

    }

    void Registry::destroyEntity(int entity_id){
        hierarchy->remove(entity_id);
        for(auto& x:*compReg){
            x.second.remove(entity_id);
        }

    }

    
    Registry::Registry(){
        total_nbr = 1;
        std::cout << "Constructing Registry..." << std::endl;
        hierarchy = new DynamicList<int>();
        compReg = new std::unordered_map<std::string,SparseSet<Component*>>;
        std::cout << "Registry constructed." << std::endl;
        std::cout << std::endl;
    }

    Registry::~Registry(){
        delete hierarchy;
        delete compReg;

    }

}

