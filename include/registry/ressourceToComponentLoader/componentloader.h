#pragma once
#include <string>
#include "registry/component.cpp"
#include "registry/registry.h"
#include "json/json.hpp"
#include "ressources/ressourcemanager.h" 
#include "gpu/gpu.h"
#include "ressources/data.h"
using namespace RESSOURCES;
using json = nlohmann::json;
namespace REG{
    struct ProcessedMesh {
        float* vertices;
        unsigned int* indices;
        size_t vertexCount;
        size_t indexCount;
    };

    class ComponentLoader {

        public:
            virtual ~ComponentLoader() = default;
            virtual void loadComponent(Registry& reg, int entity,  int index, RESSOURCES::RessourceManager& ress_man) = 0;   
            virtual void loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) = 0;
            virtual int exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant) = 0;
            virtual json& exportjson(Registry& reg, int entity) = 0;
        };

    class ObjectLoader{
        private:
        //map : Component type - ComponentLoader
            static std::unordered_map<std::string, ComponentLoader*> loaders;
        public:

        ~ObjectLoader(){
            for(auto& loader : loaders){
                delete loader.second;
            }
        }
        inline static void load(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man){
            ComponentData* data = dynamic_cast<ComponentData*>(ress_man.getData(index));
            std::string component_type = data->component_type;
            if(loaders.find(component_type) != loaders.end()){
                
                loaders[component_type]->loadComponent(reg, entity, json::parse(data->json_component_data),ress_man);
            }else{
                std::cerr << "Error: component type not found : " << component_type <<std::endl;
            }
        }

        inline static void load(Registry& reg, int entity, json j, RESSOURCES::RessourceManager& ress_man){


            if(loaders.find(j["type"]) != loaders.end()){
                
                loaders[j["type"]]->loadComponent(reg, entity, j["data"],ress_man);
            }else{
                std::cerr << "Error: component type not found : " << j["type"] <<std::endl;
            }
        }

        inline static json exportjson(Registry& reg, int entity, std::string type){
            if(loaders.find(type) != loaders.end()){
                return loaders[type]->exportjson(reg, entity);
            }
            std::cerr << "Error: component type not found : " << type <<std::endl;
            return json::object();
            
        }

        inline static int exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string type, std::string variant){
            if(loaders.find(type) != loaders.end()){
                return loaders[type]->exportComponent(reg, entity, ress_man, variant);
            }
            std::cerr << "Error: component type not found : " << variant <<std::endl;
            return -1;
            
        }
    };



    class GameobjectLoader : public ComponentLoader{
        void loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man);
        
        public:

        json& exportjson(Registry& reg, int entity) override;
        void loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) override;
        void loadComponent(Registry& reg, int entity,  int index, RESSOURCES::RessourceManager& ress_man) override;
        int exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant) override;
        };
    
    

    class InstancesLoader : public ComponentLoader {
        void loadComponent(Registry& reg, int entity,  RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man);
        
    public:
        json& exportjson(Registry& reg, int entity) override;
        void loadComponent(Registry& reg, int entity,  int index, RESSOURCES::RessourceManager& ress_man) override;
        void loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) override;
        int exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant) override;
    };

    class VisibiliteLoader : public ComponentLoader {
        void loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man);
        
    public:
        json& exportjson(Registry& reg, int entity) override;
        void loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) override;
        void loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man) override;

        int exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant) override;
    };

    class TransformLoader : public ComponentLoader {
        void loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man);
        
    public:
        json& exportjson(Registry& reg, int entity) override;
        void loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) override;
        void loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man ) override;

        int exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant) override;
    };

    //add support for static meshes
    class MeshLoader : public ComponentLoader {
        GPU::GraphicsDevice* gpu = GPU::GraphicsDevice::getInstance();
        ProcessedMesh* processMesh(const MeshData& d);
        void freeProcessedMesh(ProcessedMesh* mesh);
        void loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man);
        void loadComponent(Registry& reg, int entity, RESSOURCES::Data& data);
    public:
        json& exportjson(Registry& reg, int entity) override;
        void loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man ) override;
        void loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) override;
        int exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant) override;
    };

    class MaterialLoader : public ComponentLoader {
        GPU::GraphicsDevice* gpu = GPU::GraphicsDevice::getInstance();
        void loadTexture(int texture_data_index, unsigned int* texture, RESSOURCES::RessourceManager& ress, int slot);
        void loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress);
    public:
        json& exportjson(Registry& reg, int entity) override;
    //only takes ComponentData as input
        void loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress) override;
        void loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) override;
        int exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant) override;
        
    };

    std::unordered_map<std::string, ComponentLoader*> ObjectLoader::loaders = {
        {"Instances", new InstancesLoader()},
        {"Transform", new TransformLoader()},
        {"Mesh", new MeshLoader()},
        {"Material", new MaterialLoader()},
        {"GameObject", new GameobjectLoader()},
        {"Visibilite", new VisibiliteLoader()},
        };
    


}