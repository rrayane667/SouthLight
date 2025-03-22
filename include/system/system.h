#pragma once
#include "registry/registry.h"


namespace SYSTEMS{
    class System{
        public:

            virtual void onInit(const REG::Registry& reg) = 0;
            virtual void onStart() = 0;
            virtual void update(const REG::Registry& reg) = 0;
            virtual void ondestroy() = 0;

            virtual int getId() = 0;
    };


    class Renderer : public System{
        //GLFWwindow* window;
        public:

            Renderer(RENDERERS r);
            ~Renderer();

            void render(const REG::Registry& reg);

            void onInit(const REG::Registry& reg) override;
            void onStart() override;
            void update(const REG::Registry& reg) override;
            void ondestroy() override;

            int getId() override;
    };

    typedef enum rend{
        GL
    } RENDERERS;

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