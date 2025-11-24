#include "registry/registry.h"

namespace REG{

    int Registry::createEntity(){
        int entity_id = hierarchy->len();
        
        hierarchy->append(GameObjectInfo(entity_id, -1,"Entity"+std::to_string(hierarchy->len()+1)));

        addComponent<Visibilite>(entity_id);
        addComponent<Transform>(entity_id);


        //ajout des component dans les sparse sets correspondants
        return entity_id;
        

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
        hierarchy = new DynamicList<GameObjectInfo>();
        compReg = new std::unordered_map<std::string,SparseSet<Component*>>;
        std::cout << "Registry constructed." << std::endl;
        std::cout << std::endl;
    }

    Registry::~Registry(){
        delete hierarchy;
        delete compReg;

    }

}

