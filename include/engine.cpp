#include "engine.h"
#include<iostream>
#include <string>
#include <unordered_map>
#include <tuple>
#include <functional>
#include <vector>
#include <cstring>
#include "json/json.hpp"
#include <fstream>

using namespace REG;
using json = nlohmann::json;


namespace ENGINE{
    

    Engine::Engine(RENDERER_TYPE type) : EvMan(), SysMan(EvMan), Reg(), RessMan() {
        std::cout << "CStarting Engine..." << std::endl;
        s = Settings::getInstance();
        s->setRenderer(type);
       gpu =  GraphicsDevice::getInstance();
       std::cout << "Engine khdam" << std::endl;
       std::cout << std::endl;
    }

    void Engine::createShader(int frag_ressource_index, int vert_ressource_index, std::string name){

    }

    void Engine::freeProcessedMesh(ProcessedMesh* mesh) {
        delete[] mesh->vertices;
        delete[] mesh->indices;
        mesh->vertexCount = 0;
        mesh->indexCount = 0;
        delete mesh;
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

ProcessedMesh* Engine::processMesh(const MeshData& d) {


  
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

void Engine::processTextures(){
    List<int>* entities = Reg.getEntities<Material>();
    for (auto& id : *entities) {
        int i = 0;
        for(auto& keyvalue:(dynamic_cast<Material*> (getComponent<Material>(id))->tex_components )){

            unsigned int r = *keyvalue.second;
            TextureData* txt = dynamic_cast<TextureData*>(RessMan.getData(r));

            gpu->createTexture(*keyvalue.second, txt->width, txt->height, txt->nrchannels, txt->data);
            gpu->bindTexture(*keyvalue.second, i++);
            RessMan.unload(r);
            

        }

    }

}

void Engine::processInstances() {
    List<int>* entities = Reg.getEntities<Instances>();
    if(entities ==nullptr)return;
    for (auto& id : *entities) {
        
        Instances* inst = Reg.getComponent<Instances>(id);
        Mesh* mesh = Reg.getComponent<Mesh>(id);
        float* buffer = new float[16 * inst->instances->len() ];
        float* copy = buffer;


        for (auto& x : *(inst->instances)) { 
            std::memcpy(copy, Reg.getComponent<Transform>(x)->model.list, 16*sizeof(float));
            copy += 16;

        }



        gpu->bindVertexArray(mesh->vao);
        gpu->createVertexBuffer(inst->instanceBuffer, buffer, 16 * inst->instances->len() * sizeof(float));
        delete[] buffer; 


        gpu->structBuffer(2, 4, 16, 0);
        gpu->structBuffer(3, 4, 16, 4);
        gpu->structBuffer(4, 4, 16, 8);
        gpu->structBuffer(5, 4, 16, 12);

        gpu->instanceDiviseur(2, 1);
        gpu->instanceDiviseur(3, 1);
        gpu->instanceDiviseur(4, 1);
        gpu->instanceDiviseur(5, 1);
    }
}
    

    void Engine::processMeshes() {
        List<int>* entities = Reg.getEntities<Mesh>();
        
        for(auto& id : *entities) {
            Mesh* mesh = dynamic_cast<Mesh*>(Reg.getComponent<Mesh>(id));
            MeshData* data = dynamic_cast<MeshData*>(RessMan.getData(mesh->ressource));
            
            ProcessedMesh* processed = processMesh(*data);
            
            gpu->createVertexArray(mesh->vao);
            gpu->bindVertexArray(mesh->vao);

            if (!data->is_normal && !data->is_uv){
                gpu->createVertexBuffer(mesh->vbo, processed->vertices, processed->vertexCount * 3 * sizeof(float));
                gpu->structBuffer(0, 3, 3, 0);

            }else if(data->is_normal && data->is_uv){gpu->createVertexBuffer(mesh->vbo, processed->vertices, processed->vertexCount * 9 * sizeof(float));
                
                //vertex
                gpu->structBuffer(0, 3, 8, 0);
                //uv
                gpu->structBuffer(6, 2, 8, 3);
                //normal
                gpu->structBuffer(1, 3, 8, 5);

            }else {
                gpu->createVertexBuffer(mesh->vbo, processed->vertices, processed->vertexCount * 6 * sizeof(float));
                gpu->structBuffer(0, 3, 6, 0);
                
                if (data->is_normal) gpu->structBuffer(1, 3, 6, 3);
                else gpu->structBuffer(1, 2, 6, 3);
            }
            
            gpu->createIndexBuffer(mesh->ebo, processed->indices, processed->indexCount * sizeof(unsigned int));
            mesh->vertex_count = processed->indexCount;

            freeProcessedMesh(processed);
            RessMan.unload(mesh->ressource);

        }
        
        delete entities;
    }

    void Engine::processMaterials(){

        List<int>* entities_list = Reg.getEntities<Mesh>();

        for(auto& x:(*entities_list)){
            
            
            try{
                Material* mat;
                mat = Reg.getComponent<Material>(x);

                const char* vert = (dynamic_cast<RESSOURCES::ShaderData*> (RessMan.getData(mat->archetype->vert_index)))->shaderString;
                const char* frag = (dynamic_cast<RESSOURCES::ShaderData*> (RessMan.getData(mat->archetype->frag_index)))->shaderString;

                mat->shader = new unsigned int;
                gpu->createShader(mat->shader, vert, frag);
                mat->is_loaded = true;
                RessMan.unload(mat->archetype->vert_index);
                RessMan.unload(mat->archetype->frag_index);

            }
            catch(...){


                Reg.addComponent<Material>(x);
                if(Reg.hasComponent<Instances>(x)){Reg.getComponent<Material>(x)->shader = Settings::getDefaultShaderInstanced() ; std::cout <<"instance ouais ouais"<<std::endl;}
                
                else (Reg.getComponent<Material>(x))->shader = Settings::getDefaultShader();
                (Reg.getComponent<Material>(x))->is_loaded = true;

            }


        }
        delete entities_list;
    }


    void Engine::onInit(){



        

        std::cout <<std::endl;
        std::cout << "Creating default material"<<std::endl;
        //default shader. will be stored in settings class
        const char* default_vert_shader =(dynamic_cast<ShaderData*> (RessMan.getData(3)))->shaderString;


        const char* default_vert_shader_instancing = (dynamic_cast<ShaderData*> (RessMan.getData(5)))->shaderString;

        const char* default_frag_shader = (dynamic_cast<ShaderData*> (RessMan.getData(4)))->shaderString;

        gpu->createShader(Settings::getDefaultShader(), default_vert_shader, default_frag_shader);
        gpu->createShader(Settings::getDefaultShaderInstanced(), default_vert_shader_instancing, default_frag_shader);
        RessMan.unload(3);
        RessMan.unload(4);
        RessMan.unload(5);
        std::cout << " default material mcha"<<std::endl;

        std::cout <<std::endl;
        std::cout << "processing meshes"<<std::endl;
        
        processMeshes();

        std::cout << "meshes tprocessaw"<<std::endl;

        std::cout << " Compiling shaders...";
        std::cout << "processing materials"<<std::endl;
        processMaterials();
        std::cout <<std::endl;
        std::cout << "materials tprocessaw"<<std::endl;

        std::cout <<std::endl;
        std::cout << "initialising all systems"<<std::endl;
        
        SysMan.initAllSystems();
        std::cout << "systemes initialisé"<<std::endl;
        std::cout <<std::endl;

        std::cout << "processing events"<<std::endl;
        EvMan.processEvents();
        std::cout << "event processé"<<std::endl;
        std::cout <<std::endl;

        

        std::cout << "traitement des instances"<<std::endl;
        std::cout <<std::endl;
        processInstances();
        std::cout << "instances instancé"<<std::endl;
        std::cout <<std::endl;

        std::cout << "traitement des Textures"<<std::endl;
        std::cout <<std::endl;
        processTextures();
        std::cout << "instances Textures"<<std::endl;
        std::cout <<std::endl;
    }

    void Engine::duplicate(int entity, const vec3& v){
        
        EvMan.publish(new Instanciation(entity, v));
        EvMan.processEvents();

    }

    void Engine::setScale(float& x, float& y, float& z){

    }

    void Engine::onStart(){

    
        SysMan.startAllsystems();
        
    }

    void Engine::onUpdate(){
        SysMan.updateAllSystems();
    }

    void Engine::onExit(){

        SysMan.shutdown();
        std::cout << "Engine Shutting down"<<std::endl;
    }

    void Engine::run(){
        std::cout <<std::endl;
        std::cout << "Engine ki jri"<<std::endl;
            
        onInit();
        onStart();
        std::cout <<std::endl;
        std::cout << "main loop"<<std::endl;
        while(gpu->windowCheck()){
            
            onUpdate();
            processEvents();
            
        }

        onExit();
        
    }

    void Engine::storeMaterialArchetype(MaterialArchetype& material){
        json jsonData = nlohmann::json{
            {"shader_name", material.shader_name},
            {"expected_input", material.expected_input},
            {"frag_index", material.frag_index},
            {"vert_index", material.vert_index}
        };
        //TO DO : makhssehach tb9a hardcodé
        std::string path = "C:/Users/ORDI/Desktop/openGL/RessourceDirectory/materialtemplate/"+ material.shader_name;

        std::ofstream outFile(path);

   
        outFile << jsonData.dump(4);
        outFile.close();

        
        RessMan.import("\n"+path, "a", "mat");



    }

    void Engine::processEvents(){
        gpu->events();
        EvMan.processEvents();
    }


}