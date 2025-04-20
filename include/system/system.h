#pragma once
#include "registry/registry.h"
#include "gpu/gpu.h"
#include <unordered_map>
#include <iostream>
#include "eventmanager/eventmanager.h"
#include <algorithm>
#include "settings/settings.cpp"

using namespace EVENTS;
using namespace REG;
using namespace GPU;



namespace SYSTEMS{
    typedef enum sys{
        INSTANCEUR,
        RENDERER,
        TRANSFORMER,
        PHYSICS,
        COLLISION,
        INPUT,
        MVT,
        CAMERA_CONTROL,
    } SYSTEM;
    class System{

        
        public:
            inline System(EventManager& e, REG::Registry& r) : em(e), reg(r) {}
            virtual void onInit() = 0;
            virtual void onStart() = 0;
            virtual void update() = 0;
            virtual void ondestroy() = 0;

            virtual SYSTEM getId() = 0;

            inline void subscribe(EventType e, Callback c){em.subscribe(e, c);}
            inline void publish(Event* e){ em.publish(e);}

            friend std::ostream& operator<<(std::ostream& o, System& s){
                o << s.getId();
                return o;
            }
            EventManager& em;
            REG::Registry& reg;
    };
    class Instanceur : public System{
        public:
            Instanceur(EventManager& e, REG::Registry& r) : System(e, r) {std::cout << "INSTANCIATION INSTANCEE"<<std::endl;subscribe(INSTANCIATION, Callback([this] (Event* event){handleEvent(event);}));}
            inline void onInit() override {}
            inline void onStart() override{}
            inline void update() override {}
            inline void ondestroy() override {}
            inline SYSTEM getId() {return INSTANCEUR;}

            inline int instance( int entity){
                reg.addComponent<Instances>(entity);
                
                Instances* inst = dynamic_cast<Instances*> (reg.getComponent<Instances>(entity));
                if (!inst->instances->len()) inst->instances->append(entity);
                int e = reg.createEntity();
                inst->instances->append(e);
                return e;

            }

            inline void handleEvent(Event* event){

                
                Instanciation* i = dynamic_cast<Instanciation*>(event);
                int new_entity = instance(i->entity);

                Transform* t = dynamic_cast<Transform*> (reg.getComponent<Transform>(new_entity));
                t->position = i->position;


                em.publish(new TransformUpdate(new_entity));
            }
    };

    class Transformer : public System {
   
        public:
            Transformer(EventManager& e, REG::Registry& r) : System(e, r) {std::cout<<"TRANSFORMER TRANSFORMANT"<<std::endl;subscribe(TRANSFORM_UPDATE,Callback([this] (Event* event) {updateMatrix( (dynamic_cast<TransformUpdate*> (event))->x );}));};
            ~Transformer() = default;
        

            void onInit() override;
            inline void onStart() override {};
            inline void update() override {};
            inline void ondestroy() override{};
            inline SYSTEM getId() override {return TRANSFORMER;};

            inline vec3 getPosition( int entity){return reg.getComponent<Transform>(entity)->position;}
            inline vec3 getRotation(int entity){return reg.getComponent<Transform>(entity)->rotation;}
            inline vec3 getScale(int entity){return reg.getComponent<Transform>(entity)->scale;}

            void setPosition(int entity, const vec3& v);
            void setRotation(int entity, const vec3& v);
            void setScale(int entity, const vec3& v);
            void updateMatrix( int& x);
        

        };
        class Mvt : public System{
            float speed = 1;
            Transform* cam_trans;
            public:

            inline Mvt(EventManager& e, REG::Registry& r) : System(e, r){std::cout << "mvt howa hadak" << std::endl;subscribe(KEYBOARD_INPUT, Callback([this] (Event* event){handleEvent(event);}));}
            inline void onInit() override {cam_trans =reg.getComponent<Transform>(reg.getEntities<Camera>()->get(0));};
            inline void onStart() override {}
            inline void update() override{}
            inline void ondestroy() override{}
    
            inline SYSTEM getId() override{return RENDERER;}
            
            inline void handleEvent(Event* event) {
                
                KeyPressEvent* keyevent = dynamic_cast<KeyPressEvent*>(event);
                if (!keyevent) {
                    std::cout << "Received non-key event" << std::endl;
                    return;
                }
                float sensitivity = Settings::getSensi();
                Transform* trans = reg.getComponent<Transform>(reg.getEntities<Camera>()->get(0));
            
                double pitch = trans->rotation.x*3.1415* sensitivity/180;
                double yaw = trans->rotation.y*3.1415* sensitivity/180;
            
                // Calculate camera forward direction from yaw and pitch
                vec3 forward(
                    -cos(pitch) * sin(yaw),
                    -sin(pitch),
                    -cos(pitch) * cos(yaw)
                );
                forward = forward.normalize();
            
                // Calculate right and up vectors
                vec3 worldUp(0, 1, 0);
                vec3 right = forward.cross(worldUp).normalize();
                vec3 up = right.cross(forward).normalize();  // optional, useful for flying
            
                switch (keyevent->key) {
                    case 87: // Z
                        trans->position += forward*speed;
                        break;
                    case 83: // S
                        trans->position -= forward*speed;
                        break;
                    case 68: // D
                        trans->position += right*speed;
                        break;
                    case 65: // A
                        trans->position -= right*speed;
                        break;
                }
            
                if (keyevent->key >= 65 && keyevent->key <= 90) {
                    publish(new CameraTransformUpdate());
                }
            }
        };

        class CameraController : public System {

            float sensitivity = Settings::getInstance()->getSensi();
            float yaw = 0.0f, pitch = 0.0f;
        
        public:
            CameraController(EventManager& e, REG::Registry& r) : System(e,r) {
                subscribe(MOUSE_MOVE, Callback([this](Event* e) { handleMouse(e); }));
                std::cout << "Camera control setup" << std::endl;
            }
        
            void handleMouse(Event* event) {
                
                auto* mouseEvent = dynamic_cast<const MouseMoveEvent*>(event);
                if (!mouseEvent) return;
        
                yaw += static_cast<float>(mouseEvent->xPos) ;
                pitch -= static_cast<float>(mouseEvent->yPos) ;
        

                float sensitivity = Settings::getInstance()->getSensi();
                if (pitch>=90/sensitivity){pitch = 90/sensitivity;}
                if (pitch<=-90/sensitivity){pitch = -90/sensitivity;}

        

                reg.getComponent<Transform>(reg.getEntities<Camera>()->get(0) )->rotation = vec3(pitch, yaw, 0); 
                CameraTransformUpdate* c = new CameraTransformUpdate();
                publish(c);

            }
            void onInit() override {}
            void onStart() override {}
            void update() override {}
            void ondestroy() override {}
            SYSTEM getId() override { return CAMERA_CONTROL; }
        };

        class InputReading : public System {
            GraphicsDevice* gpu;
        
        public:
            inline InputReading(EventManager& e, REG::Registry& r) : System(e, r) { 
                std::cout << "Input System Initialized" << std::endl;
                gpu = GraphicsDevice::getInstance();
            }
        
            void onInit() override {}
            void onStart() override {}
        
            inline void update() override {
                gpu->InputEvents(em);  
                gpu->mouseEvents(em);
            }
        
            inline void ondestroy() override {}
        
            inline SYSTEM getId() override { return INPUT; }
        };


    class Renderer : public System{
        //GLFWwindow* window;
        GraphicsDevice* gpu;

        std::unordered_map<unsigned int, List<int>*> entities;
        Camera* cam;
        Transform* camTrans;
        public:

            Renderer(EventManager& e, REG::Registry& r);
            ~Renderer() = default;


            void onInit() override;
            void onStart();
            void update() override;
            inline void ondestroy() {}

            inline SYSTEM getId() override{return RENDERER;}

            void updateCamera();
    };


    

    struct SystemFactory{

        //static System* createSystem(SYSTEM type);
    };
}