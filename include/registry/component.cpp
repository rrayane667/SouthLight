#pragma once
#include "maths/vec.h"
#include <string>
#include <iostream>


using namespace MATH;

namespace REG{
    struct Component{
        int instance_index;
        inline Component(int index){ instance_index = index;}
        virtual void aff(std::ostream& ) = 0;
        friend std::ostream& operator<<(std::ostream& o, Component* c){
            c->aff(o);
            return o;
        }

    };

    struct Visibilite : public Component{
        inline Visibilite(int index) : Component(index) {}
        static inline std::string getComponentId()  {return "Visibilite";}
        bool isActive = true;
        void aff(std::ostream& o) override { 
            o << "Visibilité : " << isActive;
        }
    };

    struct Transform : public Component{
        inline Transform(int index) : Component(index) {}
        static inline std::string getComponentId()  {return "Transform";}
        vec3 position;
        vec3 rotation;
        vec3 scale;
        void aff(std::ostream& o) override { 
            o << "Transform : position =" << position << "rotation = " << rotation << "scale = " << scale ;
        }
    };

    struct Mesh : public Component{
        inline Mesh(int index) : Component(index) {std::cout << "Mesh component created"<<std::endl;
            std::cout <<std::endl;}

        static inline std::string getComponentId()  {return "Mesh";}
        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;

        int vertex_count;
        

        int ressource;
        bool is_loaded;
        void aff(std::ostream& o) override {
            o << "Mesh : " << vao;
        }
    };

 

    struct Material : public Component {
        static inline std::string getComponentId()  {return "Material";}
        inline Material(int index) : Component(index) {}
        inline Material() : Component(-1) {}

        unsigned int* shader;

        int frag_index;
        int vert_index;

        bool is_loaded;

        void aff(std::ostream& o) override {
            o << "Material : " << shader;
        }
    };

    
}