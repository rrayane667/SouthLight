#pragma once
#include "registry/registry.h"
#include "gpu/gpu.h"
#include <unordered_map>

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
    };


    class Renderer : public System{
        //GLFWwindow* window;
        GraphicsDevice* gpu;

        std::unordered_map<int, List<int>*> entities;
        public:

            Renderer();
            ~Renderer();

            void render(const REG::Registry& reg);

            void onInit(REG::Registry& reg) override;
            void onStart(REG::Registry& reg) override;
            void update(REG::Registry& reg) override;
            void ondestroy() override;

            int getId() override;
    };


    typedef enum sys{
        RENDERER,
        PHYSICS,
        COLLISION
    } SYSTEM;

    class SystemFactory{
        public:

            System* createSystem(SYSTEM type);
    };
}