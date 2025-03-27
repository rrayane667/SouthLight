#include "engine.h"
#include<iostream>
#include <string>
#include <unordered_map>
#include <tuple>

using namespace REG;


namespace ENGINE{
    Engine::Engine(RENDERER_TYPE type) : SysMan(), EvMan(), Reg(), RessMan() {
        s = Settings::getInstance();
        s->setRenderer(type);
       gpu =  GraphicsDevice::getInstance();
    }

    ProcessedMesh Engine::freeProcessedMesh(ProcessedMesh* mesh) {
        delete[] mesh->vertices;
        delete[] mesh->indices;
        mesh->vertexCount = 0;
        mesh->indexCount = 0;
    }

    ProcessedMesh Engine::processMesh(const MeshData& d) {
        struct KeyHasher {
            size_t operator()(const std::tuple<float,float,float,float,float,float>& k) const {
                auto hash = std::hash<float>();
                size_t seed = 0;
                seed ^= hash(std::get<0>(k)) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                seed ^= hash(std::get<1>(k)) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                seed ^= hash(std::get<2>(k)) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                seed ^= hash(std::get<3>(k)) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                seed ^= hash(std::get<4>(k)) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                seed ^= hash(std::get<5>(k)) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                return seed;
            }
        };
    
        std::unordered_map<std::tuple<float,float,float,float,float,float>, unsigned int, KeyHasher> hash;
        unsigned int uniqueCount = 0;
    
        for(size_t i = 0; i < d.faces->len(); ++i) {
            auto& face = d.faces->get(i);
            MATH::vec3 v = d.vertices->get(static_cast<int>(face.first));
            MATH::vec3 n = d.normals->get(static_cast<int>(face.second));
            auto key = std::make_tuple(v.x, v.y, v.z, n.x, n.y, n.z);
            if(hash.find(key) == hash.end()) hash[key] = uniqueCount++;
        }
    
        ProcessedMesh result;
        result.vertexCount = uniqueCount;
        result.indexCount = d.faces->len();
        result.vertices = new float[result.vertexCount * 6];
        result.indices = new unsigned int[result.indexCount];
    
        hash.clear();
        unsigned int currentIndex = 0;
    
        for(size_t i = 0; i < d.faces->len(); ++i) {
            auto& face = d.faces->get(i);
            MATH::vec3 v = d.vertices->get(static_cast<int>(face.first));
            MATH::vec3 n = d.normals->get(static_cast<int>(face.second));
            auto key = std::make_tuple(v.x, v.y, v.z, n.x, n.y, n.z);
    
            if(hash.find(key) == hash.end()) {
                float* ptr = result.vertices + (currentIndex * 6);
                ptr[0] = v.x; ptr[1] = v.y; ptr[2] = v.z;
                ptr[3] = n.x; ptr[4] = n.y; ptr[5] = n.z;
                hash[key] = currentIndex++;
            }
    
            result.indices[i] = hash[key];
        }
    
        return result;
    }

    void Engine::processMeshes() {
        List<int>* entities = Reg.getEntities<Mesh>();
        
        for(auto& id : *entities) {
            Mesh* mesh = dynamic_cast<Mesh*>(Reg.getComponent<Mesh>(id));
            MeshData* data = dynamic_cast<MeshData*>(RessMan.getData(mesh->ressource));
            
            ProcessedMesh processed = processMesh(*data);
            
            mesh->vao = gpu->createVertexArray();
            gpu->bindVertexArray(mesh->vao);
    
            mesh->vbo = gpu->createVertexBuffer(processed.vertices, processed.vertexCount * 6 * sizeof(float));
            gpu->structBuffer(0, 3, 6, 0);
            gpu->structBuffer(1, 3, 6, 3);
            
            mesh->ebo = gpu->createIndexBuffer(processed.indices, processed.indexCount * sizeof(unsigned int));
            
            freeProcessedMesh(&processed);
        }
        
        delete entities;
    }

    void Engine::processMaterials(){
        std::cout << " Compiling shaders...";
        List<int>* entities_list = Reg.getEntities<Mesh>();

        for(auto& x:(*entities_list)){
            
            
            try{
                Material* mat;
                mat = Reg.getComponent<Material>(x);

                std::string vert = (dynamic_cast<RESSOURCES::ShaderData*> (RessMan.getData(mat->vert_index)))->shader;
                std::string frag = (dynamic_cast<RESSOURCES::ShaderData*> (RessMan.getData(mat->vert_index)))->shader;


                mat->shader = gpu->createShader(vert, frag);
                mat->is_loaded = true;

            }
            catch(...){

                Reg.addComponent<Material>(x);
                (Reg.getComponent<Material>(x))->shader = Settings::getDefaultShader() ;
                (Reg.getComponent<Material>(x))->is_loaded = true;
            }


        }
        delete entities_list;
    }


    void Engine::onInit(){
        //default shader. will be stored in settings class
        const char* default_vert_shader = "#version 330 core\n"
                                        "layout (location = 0) in vec3 aPos;\n"
                                        "void main()\n"
                                        "{\n"
                                        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                        "}\0";

        const char* default_frag_shader = "#version 330 core\n"
                                            "out vec4 FragColor; \n"
                                            "void main()\n"
                                            "{\n"
                                            "	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
                                            "}\n";

        Settings::setDefaultShader(gpu->createShader(default_vert_shader, default_frag_shader));
        processMaterials();
        processMeshes();
        SysMan.initAllSystems();
    }

    void Engine::onStart(){
        SysMan.startAllsystems();
    }

    void Engine::onUpdate(){
        SysMan.updateAllSystems();
    }

    void Engine::onExit(){

        SysMan.shutdown();
    }

    void Engine::run(){
        onInit();
        onStart();
        // loop update

        onExit();
        
    }


}