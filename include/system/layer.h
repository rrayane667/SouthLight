#pragma once 
#include "system/system.h"
#include "utilite/dataStruct.h"
#include <string>
using namespace DATASTRUCT;

namespace SYSTEMS{



    class Layer {
        DynamicList<System*> systems;
        std::string d_name;
        int layer_index;

    public:

        template<typename T, typename... Args>
        Layer(REG::Registry& r, EventManager& em, int layer, T el, Args... args) requires std::is_same_v<T, SYSTEM> {
            systems = new DynamicList<System*>();
            layer_index = layer;
            addSystem(el, args..., r, em);

        }

        Layer( int layer) {
            systems = new DynamicList<System*>();
            layer_index = layer;
        }

        Layer(SYSTEM el, REG::Registry& r, EventManager& em, int layer) {
            systems = new DynamicList<System*>();
            layer_index = layer;
            addSystem(el, r, em);

        }

        template<typename T, typename... Args>
        Layer(int layer, T el, Args... args) requires std::is_same_v<T, System*>{
            systems = new DynamicList<System*>();
            layer_index = layer;
            addSystem(el, args...);
        }

        inline void addSystem() { }
    
        
        template<typename T, typename... Args>
        inline void addSystem(T el, Args... args) requires std::is_same_v<T, System*>{
            systems.append(el);
            addSystem(args...);
        }

        template<typename T, typename... Args>
        inline void addSystem(REG::Registry& r, EventManager& em, T el, Args... args) requires std::is_same_v<T, SYSTEM>{
            addSystem(el, r, em);
            addSystem(r, em, args...);
        }

        inline System* get(int system_index){
            return systems.get(system_index);
        }

        inline int getSize(){
            return systems.len();
        }

        void addSystem(SYSTEM s, REG::Registry& r, EventManager& em);

        void initAllSystems();
        void startAllsystems();
        //ajouter fonction poiur process events lier a cette couche??
        void updateAllSystems();
        void shutdown();//????

        friend std::ostream& operator<<(std::ostream& o, Layer& l){
            o << "Layer " << l.layer_index << "-" << l.d_name<<" : " << std::endl;
            for(auto& x: l.systems){
                o << *x << std::endl;
            }
            return o;
        }
    };
}