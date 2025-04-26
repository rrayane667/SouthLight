#include "registry/ressourceToComponentLoader/componentloader.h"


using namespace RESSOURCES;
using json = nlohmann::json;

namespace REG{
    


    void MeshLoader::loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man) {
        Data& data = *ress_man.getData(index);
        try {
            //if component data
            ComponentData& m_data = dynamic_cast<ComponentData&>(data);
            loadComponent(reg, entity, m_data);

        } catch (const std::bad_cast& e) {
            //if mesh data
            loadComponent(reg, entity, data);
        }
        
            
    }

    void MeshLoader::loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man) {
        json j = json::parse(data.json_component_data);
        loadComponent(reg, entity, j, ress_man);
    }

    struct TupleHash {
        template <typename Tuple>
        std::size_t operator()(const Tuple& tuple) const {
            return std::apply([](auto&&... args) -> std::size_t {
                std::size_t seed = 0;
              
                ((seed ^= std::hash<std::decay_t<decltype(args)>>{}(args) + 0x9e3779b9 + (seed << 6) + (seed >> 2)), ...);
                return seed;
            }, tuple);
        }
    };

    void MeshLoader::freeProcessedMesh(ProcessedMesh* mesh) {
        delete[] mesh->vertices;
        delete[] mesh->indices;
        mesh->vertexCount = 0;
        mesh->indexCount = 0;
        delete mesh;
    }

    ProcessedMesh* MeshLoader::processMesh(const MeshData& d){
        std::unordered_map<std::tuple<float, float, float, float, float, float>, unsigned int, TupleHash> vertexMap;
        std::vector<float> vertexBuffer;
        std::vector<unsigned int> indexBuffer;

        unsigned int currentIndex = 0;

        int n = (!d.is_normal && !d.is_uv)?1:((d.is_normal && d.is_uv)?3:2);

        for (int i = 0; i < d.faces->len(); i+=n) {

            
            MATH::vec3 v = d.vertices->get(d.faces->get(i));
            MATH::vec3 n = vec3(0,0,0);
            MATH::vec2 uv;

            if(d.is_normal && d.is_uv){


                uv = d.UV->get(d.faces->get(i+1));
                n = d.normals->get(d.faces->get(i+2));
            }
            else{

                if(d.is_normal) n = d.normals->get(d.faces->get(i+1));
                else uv = d.UV->get(d.faces->get(i+1));
            }

            auto key = std::make_tuple(v.x, v.y, v.z, n.x, n.y, n.z);

            auto it = vertexMap.find(key);
            if (it == vertexMap.end()) {
                
                vertexMap[key] = currentIndex;
                vertexBuffer.push_back(v.x);
                vertexBuffer.push_back(v.y);
                vertexBuffer.push_back(v.z);
                vertexBuffer.push_back(n.x);
                vertexBuffer.push_back(n.y);
                vertexBuffer.push_back(n.z);
                if (d.is_uv) {
                    vertexBuffer.push_back(uv.x);
                    vertexBuffer.push_back(uv.y);
                }
                indexBuffer.push_back(currentIndex);
                ++currentIndex;
            } else {
            
                indexBuffer.push_back(it->second);
            }
        }

        ProcessedMesh* result = new ProcessedMesh;
        
        result->vertexCount = static_cast<unsigned int>(vertexBuffer.size() / 6);
        result->indexCount = static_cast<unsigned int>(indexBuffer.size());


        // Allocate and copy vertex data
        result->vertices = new float[vertexBuffer.size()];
        std::memcpy(result->vertices, vertexBuffer.data(), vertexBuffer.size() * sizeof(float));

        // Allocate and copy index data
        result->indices = new unsigned int[indexBuffer.size()];
        std::memcpy(result->indices, indexBuffer.data(), indexBuffer.size() * sizeof(unsigned int));

        //for(auto& x:vertexBuffer) std::cout << x <<std::endl;
        //for(auto& x:indexBuffer) std::cout << x <<std::endl;

        return result;
    }
    void MeshLoader::loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) {
        reg.addComponent<Mesh>(entity);
        loadComponent(reg, entity, *ress_man.getData(j["mesh_ressource_index"]));
    }

    void MeshLoader::loadComponent(Registry& reg, int entity, RESSOURCES::Data& data){
            Mesh* mesh = dynamic_cast<Mesh*>(reg.getComponent<Mesh>(entity));
            
            try {
                MeshData& m_data = dynamic_cast<MeshData&>(data);
                ProcessedMesh* processed = processMesh(m_data);
            
                gpu->createVertexArray(mesh->vao);
                gpu->bindVertexArray(mesh->vao);

                if (!m_data.is_normal && !m_data.is_uv){
                    gpu->createVertexBuffer(mesh->vbo, processed->vertices, processed->vertexCount * 3 * sizeof(float));
                    gpu->structBuffer(0, 3, 3, 0);

                }else if(m_data.is_normal && m_data.is_uv){gpu->createVertexBuffer(mesh->vbo, processed->vertices, processed->vertexCount * 9 * sizeof(float));
                    
                    //vertex
                    gpu->structBuffer(0, 3, 8, 0);
                    //uv
                    gpu->structBuffer(6, 2, 8, 3);
                    //normal
                    gpu->structBuffer(1, 3, 8, 5);

                }else {
                    gpu->createVertexBuffer(mesh->vbo, processed->vertices, processed->vertexCount * 6 * sizeof(float));
                    gpu->structBuffer(0, 3, 6, 0);
                    
                    if (m_data.is_normal) gpu->structBuffer(1, 3, 6, 3);
                    else gpu->structBuffer(1, 2, 6, 3);
                }
                
                gpu->createIndexBuffer(mesh->ebo, processed->indices, processed->indexCount * sizeof(unsigned int));
                mesh->vertex_count = processed->indexCount;

                freeProcessedMesh(processed);
    
            } catch (const std::bad_cast& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return;
            }
            
            

    }

    json& MeshLoader::exportjson(Registry& reg, int entity){
        json j;
        Mesh* mesh = dynamic_cast<Mesh*>(reg.getComponent<Mesh>(entity));
        j["mesh_ressource_index"] = mesh->ressource;
        return j;
    }
    void MeshLoader::exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant){
        json j = exportjson(reg, entity);
        ComponentData* data = new ComponentData;
        data->component_type = "Mesh";
        data->json_component_data = j.dump(4);
        ress_man.exportData(data, "component", variant);
    }

    
}