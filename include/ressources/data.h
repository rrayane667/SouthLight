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
            delete vertices, UV, normals;
        }

        MeshData* clone() const override;
        MeshData(const MeshData& m_data);
        MeshData() ;
        MeshData& operator=(const MeshData&);

        List<MATH::vec3> *vertices;
        List<MATH::vec2> *UV;
        List<MATH::vec3> *normals;
    };
} 
