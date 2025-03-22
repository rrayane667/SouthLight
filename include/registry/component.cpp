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
        static inline std::string getComponentId()  {return "Visibilite";}
        bool isActive = true;
        void aff(std::ostream& o) override { 
            o << "Visibilité : " << isActive;
        }
    };

    struct Transform : public Component{
        static inline std::string getComponentId()  {return "Transform";}
        vec3 position;
        vec3 rotation;
        vec3 scale;
        void aff(std::ostream& o) override { 
            o << "Transform : position =" << position << "rotation = " << rotation << "scale = " << scale ;
        }
    };

    struct Mesh : public Component{
        static inline std::string getComponentId()  {return "Mesh";}
        unsigned int data;
        unsigned int ressource;
        bool is_loaded;
        void aff(std::ostream& o) override {
            o << "Mesh : " << data;
        }
    };

    struct ShaderData {

    };

    struct Material : public Component {
        unsigned int vert_shader;
        unsigned int frag_shader;
        unsigned int prog_shader;

        bool is_vert_loaded;
        bool is_frag_loaded;
        bool is_prog_loaded;
        ShaderData* data;
    };

    
}