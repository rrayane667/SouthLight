#pragma once
#include <iostream>
#include "utilite/dataStruct.h"
#include "registry/component.cpp"
#include <unordered_map>
#include <string>

using namespace DATASTRUCT;


namespace REG{

    struct GameObjectInfo{
        int entity_ressource_id = -1;
        int entity_id;
        std::string name = "Entity";
        GameObjectInfo(int entity) : entity_id(entity) {};
        GameObjectInfo(int entity, int ress_id, std::string n) : entity_id(entity), entity_ressource_id(ress_id), name(n) {}
    };
    
    class Registry{
        int total_nbr;
        List<GameObjectInfo> *hierarchy;
        std::unordered_map<std::string,SparseSet<Component*>> *compReg;// list s[entity_id] contient index dans d 

        public:
            Registry();
            ~Registry();
            int createEntity();
            void destroyEntity(int entity_id);

            inline std::unordered_map<std::string,SparseSet<Component*>> * getComponents() const{return compReg;}

            template <typename T>
            inline bool hasComponent(int entity){return ((*compReg).find(T::getComponentId()) != compReg->end()) && ((*compReg)[T::getComponentId()].getIndex(entity)!=-1);}

            inline int entitiesCount() const{return hierarchy->len();}

            inline int getEntityRessourceId(int entity) const {return hierarchy->get(entity).entity_ressource_id;}
            inline std::string getEntityName(int entity) const {return hierarchy->get(entity).name;}

            inline void setEntityRessourceId(int entity, int ressource_id) {hierarchy->get(entity).entity_ressource_id = ressource_id;}
            inline void setEntityName(int entity, std::string name) {hierarchy->get(entity).name = name;}

            //checks if the entity exists
            inline bool checkEntity(int entity)const {return entity < hierarchy->len(); }
            
            template <typename T>
            void addComponent(int entity_id);

            template <typename T>
            List<int>* getEntities() const;

            template <typename T>
            int& getComponentIndex(int entity_id) const;
            
            template <typename T>
            T* getComponent(int entity_id)const;

            template <typename T>
            void removeComponent(int entity_id);

            friend std::ostream& operator<<(std::ostream& o, const Registry& r){
                if (!r.hierarchy)
                    o << "hierarchy is null";
                else
                    o << "hierarchy : " << (*(r.hierarchy)) << std::endl;
                if (!r.compReg)
                    o << "compReg is null";
                else {
                    o << "component " << std::endl;
                    for (auto& x : *r.compReg)
                        o << x.second << std::endl;
                }
                return o;
            }

    };

    template <typename T>
    int& Registry::getComponentIndex(int entity_id)const{
        return (getComponent<T>(entity_id))->instance_index;
    }

    //change to variadic
    template <typename T>
    List<int>* Registry::getEntities() const{
        if(compReg->find(T::getComponentId()) == compReg->end()){
            return nullptr;
        }

        List<int>* l = new DynamicList<int>;


        SparseSet<Component *>& ss = (*compReg)[T::getComponentId()];
        for(int i = 0; i<ss.getSparseLen();i++){
            if (ss.getIndex(i)!=-1){l->append(i);}
        }

        if(!(l->len())) return nullptr;
        return l;
    }
    

    template <typename T>
    void Registry::addComponent(int entity_id){
        if(entity_id >= hierarchy->len()){
            std::cerr << "Error: entity does not exist : " << entity_id << std::endl;
            return;
        }
        if(compReg->find(T::getComponentId()) == compReg->end()){
            (*compReg)[T::getComponentId()] = SparseSet<Component*>();
        }
        if((*compReg)[T::getComponentId()].getIndex(entity_id) !=-1) return;
        (*compReg)[T::getComponentId()].set(entity_id,new T(total_nbr++));
    }

    template <typename T>
    T* Registry::getComponent(int entity_id) const{
        if(compReg->find(T::getComponentId()) == compReg->end()){
            std::cout << T::getComponentId() << "hada makaynch" << std::endl;
            throw std::runtime_error("object doesnt have this component");
            
            
        }
        return static_cast<T*>((*compReg)[T::getComponentId()][entity_id]);
    }

    template <typename T>
    void Registry::removeComponent(int entity_id){
        if(compReg->find(T::getComponentId()) == compReg->end()){
            return;
        }
        delete (*compReg)[T::getComponentId()][entity_id];
        (*compReg)[T::getComponentId()].remove(entity_id);

    }
}
