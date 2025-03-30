#pragma once
#include "registry/registry.h"
#include "gpu/gpu.h"
#include <unordered_map>
#include <iostream>

using namespace REG;
using namespace GPU;

namespace SYSTEMS{
    class System{
        public:

            virtual void onInit(REG::Registry& reg) = 0;
            virtual void onStart(REG::Registry& reg) = 0;
            virtual void update(REG::Registry& reg) = 0;
            virtual void ondestroy() = 0;

            virtual int getId() = 0;

            friend std::ostream& operator<<(std::ostream& o, System& s){
                o << s.getId();
                return o;
            }
    };


    class Renderer : public System{
        //GLFWwindow* window;
        GraphicsDevice* gpu;

        std::unordered_map<unsigned int, List<int>*> entities;
        public:

            Renderer();
            ~Renderer() = default;


            void onInit(REG::Registry& reg) override;
            inline void onStart(REG::Registry& reg) {}
            void update(REG::Registry& reg) override;
            inline void ondestroy() {}

            inline int getId() override{return 0;}
    };


    typedef enum sys{
        RENDERER,
        PHYSICS,
        COLLISION
    } SYSTEM;

    struct SystemFactory{

        static System* createSystem(SYSTEM type);
    };
}