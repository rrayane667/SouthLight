#include "engine.h"
#include<iostream>
#include <string>
#include <unordered_map>
#include <tuple>
#include <functional>
#include <vector>
#include <cstring>

using namespace REG;



namespace ENGINE{
    

    Engine::Engine(RENDERER_TYPE type) : SysMan(), EvMan(), Reg(), RessMan() {
        std::cout << "CStarting Engine..." << std::endl;
        s = Settings::getInstance();
        s->setRenderer(type);
       gpu =  GraphicsDevice::getInstance();
       std::cout << "Engine khdam" << std::endl;
       std::cout << std::endl;
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

    for (size_t i = 0; i < d.faces->len(); ++i) {
        auto& face = d.faces->get(i);

        MATH::vec3 v = d.vertices->get(static_cast<int>(face.first));
        MATH::vec3 n = d.normals->get(static_cast<int>(face.second));

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

void Engine::processInstances() {
    List<int>* entities = Reg.getEntities<Instances>();

    for (auto& id : *entities) {
        Instances* inst = Reg.getComponent<Instances>(id);
        Mesh* mesh = Reg.getComponent<Mesh>(id);
        float* buffer = new float[16 * inst->instances->len()];
        float* copy = buffer;

        for (auto& x : *(inst->instances)) { 
            std::memcpy(copy, Reg.getComponent<Transform>(x)->model.list, 16*sizeof(float));
            copy += 16;

        }

        gpu->bindVertexArray(mesh->vao);
        gpu->createVertexBuffer(inst->instanceBuffer, buffer, 16*inst->instances->len());
        delete[] buffer; 


        gpu->structBuffer(2, 4, 16*sizeof(float), 0);
        gpu->structBuffer(3, 4, 16*sizeof(float), 4);
        gpu->structBuffer(4, 4, 16*sizeof(float), 8);
        gpu->structBuffer(5, 4, 16*sizeof(float), 12);

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
    
            gpu->createVertexBuffer(mesh->vbo, processed->vertices, processed->vertexCount * 6 * sizeof(float));
            gpu->structBuffer(0, 3, 6, 0);
            gpu->structBuffer(1, 3, 6, 3);
            
            gpu->createIndexBuffer(mesh->ebo, processed->indices, processed->indexCount * sizeof(unsigned int));
            mesh->vertex_count = processed->indexCount;

            freeProcessedMesh(processed);
            

        }
        
        delete entities;
    }

    void Engine::processMaterials(){

        List<int>* entities_list = Reg.getEntities<Mesh>();

        for(auto& x:(*entities_list)){
            
            
            try{
                Material* mat;
                mat = Reg.getComponent<Material>(x);

                const char* vert = (dynamic_cast<RESSOURCES::ShaderData*> (RessMan.getData(mat->vert_index)))->shaderString;
                const char* frag = (dynamic_cast<RESSOURCES::ShaderData*> (RessMan.getData(mat->frag_index)))->shaderString;

                mat->shader = new unsigned int;
                gpu->createShader(mat->shader, vert, frag);
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
        std::cout <<std::endl;
        std::cout << "Creating default material"<<std::endl;
        //default shader. will be stored in settings class
        const char* default_vert_shader = "#version 330 core\n"
                                          "layout (location = 0) in vec3 aPos;\n"
                                          "layout (location = 1) in vec3 n;\n"
                                          "layout (location = 2) in mat4 instanceMatrix;\n"  
                                          "out float light;\n"
                                          "uniform mat4 projection;\n"
                                          "uniform mat4 view;\n"
                                          "void main()\n"
                                          "{\n"
                                          "   mat3 normalMatrix = mat3(transpose(inverse(instanceMatrix)));\n"
                                          "   vec3 worldNormal = normalize(normalMatrix * n);\n"
                                          "   light = dot(n, -1*normalize((instanceMatrix*vec4(aPos.x, aPos.y, aPos.z, 1.0)).xyz));\n"  
                                          "   if(light<0){\n"
                                          "       light = 0;\n"
                                          "   }\n"
                                          "   gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);\n"
                                          "}\n\0";

        const char* default_frag_shader = "#version 330 core\n"
                                            "in float light;\n"
                                            "out vec4 FragColor; \n"
                                            "void main()\n"
                                            "{\n"
                                            "	FragColor = vec4(1.0f*light, 0.0f*light, 1.0f*light, 1.0f); \n"
                                            "}\n";

        gpu->createShader(Settings::getDefaultShader(), default_vert_shader, default_frag_shader);
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
        SysMan.initAllSystems(Reg);
        std::cout << "systemes initialisé"<<std::endl;
        std::cout <<std::endl;

        std::cout << "traitement des instances"<<std::endl;
        std::cout <<std::endl;
        processInstances();
    }

    void Engine::duplicate(int entity, const vec3& v){
        Instanceur *inst = dynamic_cast<Instanceur*> (SysMan.getSystem(INSTANCEUR));

        inst->instance(Reg, entity);

        Transform* t = dynamic_cast<Transform*> ( Reg.getComponent<Transform>(Reg.entitiesCount()));
        t->position = v;

    }

    void Engine::setScale(float& x, float& y, float& z){

    }

    void Engine::onStart(){
        SysMan.startAllsystems(Reg);
    }

    void Engine::onUpdate(){
        SysMan.updateAllSystems(Reg);
    }

    void Engine::onExit(){

        SysMan.shutdown(Reg);
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
            processEvents();
            onUpdate();
            
        }

        onExit();
        
    }
    void Engine::processEvents(){
        gpu->events();
    }


}