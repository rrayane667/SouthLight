#pragma once
#include "utilite/dataStruct.h"
#include "maths/vec.h"
#include <unordered_map>
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

    struct MaterialArchetypeData : public Data{
        inline MaterialArchetypeData() {vert_index = 3; frag_index = 4; shader_name = "default shader";}
        inline MaterialArchetypeData(const MaterialArchetypeData& td) {
            vert_index = td.vert_index;
            frag_index = td.frag_index;
            shader_name = td.shader_name;
            expected_input = td.expected_input;
        }
        inline ~MaterialArchetypeData() override {}
        inline Data* clone() const override{
            MaterialArchetypeData* td = new MaterialArchetypeData(*this);
            return td;
        }
        std::string shader_name;
        std::unordered_map<std::string, char> expected_input;
        int frag_index;
        int vert_index;

    };

    struct GameObjectData : public Data{
        inline GameObjectData() = default;
        inline GameObjectData(std::string& j) {json_game_object_data =j ;}
        inline GameObjectData(const GameObjectData& td) {json_game_object_data = td.json_game_object_data;}
        inline ~GameObjectData() override {}
        inline Data* clone() const override{
            GameObjectData* td = new GameObjectData(*this);
            return td;
        }

        std::string json_game_object_data;
    };
    struct ComponentData : public Data{
        inline ComponentData() = default;
        inline ComponentData(const ComponentData& td) {json_component_data = td.json_component_data;}
        inline ~ComponentData() override {}
        inline Data* clone() const override{
            ComponentData* td = new ComponentData(*this);
            return td;
        }
        std::string component_type;

        std::string json_component_data;
    };
    struct SceneData : public Data{
        inline SceneData() {gameobjects = new DynamicList<int>();};
        inline SceneData(const SceneData& td) {*gameobjects = *td.gameobjects;}
        inline ~SceneData() override {}
        inline Data* clone() const override{
            SceneData* td = new SceneData(*this);
            return td;
        }
        List<int>* gameobjects;
    };





} 
