#include "registry/registry.h"

namespace REG{

    void Registry::createEntity(){
        hierarchy->append(3);
        addComponent<Visibilite>(hierarchy->len()-1);
        addComponent<Transform>(hierarchy->len()-1);
        //ajout des component dans les sparse sets correspondants

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
    }

    Registry::~Registry(){
        delete hierarchy;
        delete compReg;

    }

}

