#pragma once
#include "utilite/dataStruct.h"
#include "system.h"
#include "registry/registry.h"
#include <unordered_map>
#include "system/layer.h"

using namespace DATASTRUCT;

namespace SYSTEMS{
    struct Mappin2d{
        int x, y;// x = quelle layer ?? y = quel systeme dans la layer??
        Mappin2d(int a, int b) {x = a; y = b;}
        Mappin2d(){}
    };

    class SystemManager{
        EventManager& em;

        DynamicList<Layer*> systems;
        std::unordered_map<SYSTEM, Mappin2d> systems_map;

        public:

            template<typename T, typename... Args>
            inline void createLayer(REG::Registry& r, T el, Args... args) requires std::is_same_v<T, System*>{
                int layer_index = systems.len();
                systems.append(new Layer(layer_index ,el, args...));
            }

            inline SystemManager(EventManager& e) : em(e){systems.append(new Layer(0)); std::cout << "System manager constructed" << std::endl;std::cout << std::endl;};

            void addSystem(System* s, int layer_index);


            // ajoute les systemes a une couche specifique
            template<typename T, typename... Args>
            inline void addSystem(REG::Registry& r, int layer_index, T s, Args... args) requires std::is_same_v<T, SYSTEM>{


                if(!systems.len()) {systems.append(new Layer( r, em, layer_index, s, args...) );return;}

                (systems.get(layer_index)->addSystem(args, r, em), ...);
            }

            // ajoute un systeme a une couche specifique
            void addSystem(SYSTEM s, REG::Registry& r, int layer_index);
            

            inline System* getSystem(SYSTEM s){ return (systems.get(systems_map[s].x))->get(systems_map[s].y);}


            


            void initAllSystems();
            void startAllsystems();
            void updateAllSystems();
            void shutdown();//????
    };
}