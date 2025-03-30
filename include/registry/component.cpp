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
        inline Transform(int index) : Component(index) {scale = vec3(0.2f, 0.2f, 0.2f);}
        static inline std::string getComponentId()  {return "Transform";}
        vec3 position = vec3(0.0f, 0.0f, 0.0f);
        vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
        vec3 scale;
        void aff(std::ostream& o) override { 
            o << "Transform : position =" << position << "rotation = " << rotation << "scale = " << scale ;
        }
        mat4 model;

    };

    struct Mesh : public Component{
        inline Mesh(int index) : Component(index) {}

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

    typedef enum c{
        PERSPECTIVE,
        ORTHOGRAPHIQUE
    } ProjectionType;

    struct CameraPerspective{
        float fov = 0.9f, ratio = 800.0f / 600.0f, n = 0.1f, f=100;
    };
    struct CameraOrthographique{
        float r=0, l=0, n=0, t=0, b=0, f=0;
    };
    struct Camera : public Component{
        Camera(int index) : Component(index){cp = new CameraPerspective;}
        static inline std::string getComponentId()  {return "Camera";} 

        ProjectionType projection = PERSPECTIVE;
        
        union{
            CameraPerspective* cp;
            CameraOrthographique* co;
        };
        void aff(std::ostream& o) override { 
            o << "camera : " << projection;
        }
        

    };

    struct Light : public Component{
        float light_intensity;
    };
    

    

    
}