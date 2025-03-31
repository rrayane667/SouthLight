#pragma once
#include "registry/registry.h"
#include "gpu/gpu.h"
#include <unordered_map>
#include <iostream>
#include "eventmanager/event.h"

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
    class Instanceur : public System{
        public:
            inline void onInit(REG::Registry& reg) override {}
            inline void onStart(REG::Registry& reg) override{}
            inline void update(REG::Registry& reg) override {}
            inline void ondestroy() override {}
            inline int getId() {return 2;}

            inline void instance(REG::Registry& reg, int entity){
                reg.addComponent<Instances>(entity);
                Instances* inst = dynamic_cast<Instances*> (reg.getComponent<Instances>(entity));
                inst->instances->append(reg.createEntity());
            }
    };

    class Transformer : public System {
        public:
            Transformer() = default;
            ~Transformer() = default;
        

            void onInit(REG::Registry& reg) override;
            inline void onStart(REG::Registry& reg) override {};
            inline void update(REG::Registry& reg) override {};
            inline void ondestroy() override{};
            inline int getId() override {return 1;};

            inline vec3 getPosition(REG::Registry& reg, int entity){return reg.getComponent<Transform>(entity)->position;}
            inline vec3 getRotation(REG::Registry& reg, int entity){return reg.getComponent<Transform>(entity)->rotation;}
            inline vec3 getScale(REG::Registry& reg, int entity){return reg.getComponent<Transform>(entity)->scale;}

            void setPosition(REG::Registry& reg, int entity, const vec3& v);
            void setRotation(REG::Registry& reg, int entity, const vec3& v);
            void setScale(REG::Registry& reg, int entity, const vec3& v);
        
        private:
            //callback pour event manager
            //void onTransformUpdated(const Event& event);
            void updateMatrix(REG::Registry& reg, int& x);
        

        };


    class Renderer : public System{
        //GLFWwindow* window;
        GraphicsDevice* gpu;

        std::unordered_map<unsigned int, List<int>*> entities;
        Camera* cam;
        Transform* camTrans;
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
        INSTANCEUR,
        RENDERER,
        TRANSFORM,
        PHYSICS,
        COLLISION
    } SYSTEM;

    struct SystemFactory{

        static System* createSystem(SYSTEM type);
    };
}
