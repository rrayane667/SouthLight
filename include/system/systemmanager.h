#pragma once
#include "utilite/dataStruct.h"
#include "system.h"
#include "registry/registry.h"
#include <unordered_map>
#include "system/layer.h"

using namespace DATASTRUCT;

namespace SYSTEMS{
    struct Mappin2d{
        int x, y;
        Mappin2d(int a, int b) {x = a; y = b;}
        Mappin2d(){}
    };
    class SystemManager{
        EventManager& em;

        DynamicList<Layer*> systems;
        std::unordered_map<SYSTEM, Mappin2d> systems_map;

        public:

            template<typename T, typename... Args>
            inline void createLayer(T el, Args... args, REG::Registry& r) requires std::is_same_v<T, System*>{
                systems.append(new Layer(el, args..., r));
            }
            inline SystemManager(EventManager& e) : em(e){std::cout << "System manager constructed" << std::endl;std::cout << std::endl;};

            void addSystem(System* s, int layer_index);


            // ajoute les systemes a une couche specifique
            template<typename T, typename... Args>
            inline void addSystem(T s, Args... args,REG::Registry& r, int layer_index) requires std::is_same_v<T, SYSTEM>{


                if(!systems.len()) {systems.append(new Layer(s , args..., r, em) );return;}

                systems.get(layer_index)->addSystem(s ,r, em);
                addSystem(args..., r, layer_index);
            }

            // ajoute un systeme a une couche specifique
            void addSystem(SYSTEM s, REG::Registry& r, int layer_index);
            

            inline System* getSystem(SYSTEM s){ return (systems.get(systems_map[s].x))->get(systems_map[s].y);}

            //ajoute les sytemes a la derniere couche
            template<typename T, typename... Args>
            inline void addSystem(T s, Args... args,REG::Registry& r) requires std::is_same_v<T, SYSTEM>{


                if(!systems.len()) {systems.append(new Layer(s , args..., r, em) );return;}

                systems.get(systems.len()-1)->addSystem(s, args...,r, em);
            }

            


            void initAllSystems();
            void startAllsystems();
            void updateAllSystems();
            void shutdown();//????
    };
}