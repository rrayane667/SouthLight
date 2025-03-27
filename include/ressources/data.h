#pragma once
#include "utilite/dataStruct.h"
#include "maths/vec.h"

using namespace DATASTRUCT;

namespace RESSOURCES
{
    struct Data {
        virtual ~Data() = default;
        virtual Data* clone() const= 0;

        

    };
    struct MeshData : public Data{
        ~MeshData() override{
            delete vertices, UV, normals, faces;
        }

        MeshData* clone() const override;
        MeshData(const MeshData& m_data);
        MeshData() ;
        MeshData& operator=(const MeshData&);

        List<MATH::vec3> *vertices;
        List<MATH::vec2> *UV;
        List<MATH::vec3> *normals;
        List<paire<float, float>> *faces;

        int object_ressource_index;

        bool is_uv = false;
        bool is_normal = false;
    };

    struct ShaderData : public Data{
        inline ShaderData(const ShaderData& sd){shader =sd.shader;}
        inline Data* clone() const override{
            ShaderData* sd = new ShaderData(*this);
            return sd;
        }
        std::string shader;
    };


} 
