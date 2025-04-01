#pragma once
#include "utilite/dataStruct.h"
#include "maths/vec.h"

#include "stb_image.h"

using namespace DATASTRUCT;

namespace RESSOURCES
{
    struct Data {
        virtual ~Data() = default;
        virtual Data* clone() const= 0;
        std::string name = "default";
        

    };
    struct MeshData : public Data{
        inline ~MeshData() override {
            delete vertices;
            delete UV;
            delete normals;
            delete faces;
        }

        MeshData* clone() const override;
        MeshData(const MeshData& m_data);
        MeshData() ;
        MeshData& operator=(const MeshData&);

        

        List<MATH::vec3> *vertices;
        List<MATH::vec2> *UV;
        List<MATH::vec3> *normals;
        List<float> *faces;

        int object_ressource_index;

        bool is_uv = false;
        bool is_normal = false;
    };

    struct ShaderData : public Data{
        inline ShaderData(){ shaderString = nullptr;test = "test";}
        inline ShaderData(const ShaderData& sd){shaderString =sd.shaderString;}
        inline Data* clone() const override{
            ShaderData* sd = new ShaderData(*this);
            return sd;
        }
        std::string test;
        const char* shaderString;
    };

    struct TextureData : public Data{
        inline TextureData() {data = nullptr;}
        inline TextureData(const TextureData& td) {data = td.data;}
        inline ~TextureData() override {stbi_image_free(data);}
        inline Data* clone() const override{
            TextureData* td = new TextureData(*this);
            return td;
        }
        unsigned char* data ;
        int width, height, nrchannels;
    };


} 
