#pragma once
#include <iostream>
#include "maths/vec.h"

using namespace MATH;

namespace EVENTS{

    typedef enum Type {
        KEYBOARD_INPUT, 
        TRANSFORM_UPDATE,
        CAMERA_TRANSFORM_UPDATE,
        MOUSE_MOVE,
        INSTANCIATION,
    }EventType;

    struct Event{
        EventType type;
        
        virtual ~Event() {};

        friend std::ostream& operator<<(std::ostream& o, const Event e){
            o << e.type;
            return o;
        }
    };

    struct CameraTransformUpdate : public Event{
        CameraTransformUpdate() {type = CAMERA_TRANSFORM_UPDATE;}
    };

    struct TransformUpdate : Event {
        TransformUpdate(int entity){x = entity; type = TRANSFORM_UPDATE;}
        int x;
    };

    struct KeyPressEvent : public Event{
        KeyPressEvent(int k) {key = k; type = KEYBOARD_INPUT;}

        int key;

    };

    struct MouseMoveEvent : public Event {
        double xPos, yPos;
    
        MouseMoveEvent(double x, double y) {
            xPos = x;
            yPos = y;
            type = MOUSE_MOVE;
        }
    };

    struct KeyReleaseEvent : public Event{
        KeyReleaseEvent(int k) {key = k;type = KEYBOARD_INPUT;}
        int key;
    };

    struct Instanciation : public Event{
        int entity;
        vec3 position;

        inline Instanciation(int ent, vec3 pos){type = INSTANCIATION;entity = ent; position = pos;}
        
    };
}