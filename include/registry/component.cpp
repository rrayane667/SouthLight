#pragma once
#include "maths/vec.h"
#include <string>
#include <iostream>


using namespace MATH;

namespace REG{
    struct Component{
        virtual void aff(std::ostream& ) = 0;
        friend std::ostream& operator<<(std::ostream& o, Component* c){
            c->aff(o);
            return o;
        }



    };

    struct Visibilite : public Component{
        static inline std::string getComponentId()  {return "Visibilité";}
        bool isActive = true;
        void aff(std::ostream& o) override { 
            o << "Visibilité";
        }
        
    };

    struct Transform : public Component{
        static inline std::string getComponentId()  {return "Transform";}
        vec3 position;
        vec3 rotation;
        vec3 scale;
        void aff(std::ostream& o) override { 
            o << "Transform";
        }
    };
}