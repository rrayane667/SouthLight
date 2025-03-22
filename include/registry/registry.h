#pragma once
#include <iostream>
#include "utilite/dataStruct.h"
#include "registry/component.cpp"
#include <unordered_map>
#include <string>

using namespace DATASTRUCT;


namespace REG{
    
    class Registry{
        List<int> *hierarchy;//list de bitmask
        std::unordered_map<std::string,SparseSet<Component*>> *compReg;// list s[entity_id] contient index dans d 

        public:
            Registry();
            ~Registry();
            void createEntity();
            void destroyEntity(int entity_id);

            inline int entitiesCount() {return hierarchy->len();}

            inline bool checkEntity(int entity) {return entity < hierarchy->len(); }
            
            template <typename T>
            void addComponent(int entity_id);
            
            template <typename T>
            T* getComponent(int entity_id);

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
    void Registry::addComponent(int entity_id){
        if(compReg->find(T::getComponentId()) == compReg->end()){
            (*compReg)[T::getComponentId()] = SparseSet<Component*>();
        }
        (*compReg)[T::getComponentId()].set(entity_id,new T());
    }

    template <typename T>
    T* Registry::getComponent(int entity_id){
        if(compReg->find(T::getComponentId()) == compReg->end()){
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

