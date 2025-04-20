#pragma once 
#include "system/system.h"
#include "utilite/dataStruct.h"
#include <string>
using namespace DATASTRUCT;

namespace SYSTEMS{



    class Layer {
        DynamicList<System*> systems;
        std::string d_name;

    public:

        template<typename T, typename... Args>
        Layer(T el, Args... args, REG::Registry& r, EventManager& em) requires std::is_same_v<T, SYSTEM> {
            systems = new DynamicList<System*>();
            addSystem(el, args..., r, em);

        }

        Layer(SYSTEM el, REG::Registry& r, EventManager& em) {
            systems = new DynamicList<System*>();
            addSystem(el, r, em);

        }

        template<typename T, typename... Args>
        Layer(T el, Args... args) requires std::is_same_v<T, System*>{
            systems = new DynamicList<System*>();
            addSystem(el, args...);
        }

        inline void addSystem() { }
    
        
        template<typename T, typename... Args>
        inline void addSystem(T el, Args... args) requires std::is_same_v<T, System*>{
            systems.append(el);
            addSystem(args...);
        }

        template<typename T, typename... Args>
        inline void addSystem(T el, Args... args, REG::Registry& r, EventManager& em) requires std::is_same_v<T, SYSTEM>{
            addSystem(el, r, em);
            addSystem(args...);
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
        void updateAllSystems();
        void shutdown();//????
    };
}