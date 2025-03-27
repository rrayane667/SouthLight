#include "system/system.h"
#include "settings/settings.cpp"
using namespace REG;


namespace SYSTEMS{
    
    Renderer::Renderer(){
        
        gpu = GraphicsDevice::getInstance();

        
    }   

    void Renderer::onInit(REG::Registry& reg){
        //init : load ressource into gpu based on the component/ stores vao into component
        //compile shader construct hash table of entities using same shaders
        List<int>* entities_list = reg.getEntities<Mesh>();

        
        for(auto& x:(*entities_list)){
            unsigned int shadeur = (reg.getComponent<Material>(x))->shader ;
            if (entities.find(shadeur) == entities.end()){

                entities[shadeur] = new DynamicList<int>;
                
            }
            entities[shadeur]->append(x);
        }
        

        
    }

    void Renderer::onStart(REG::Registry& reg){}

    void Renderer::update(REG::Registry& reg){
        for(const auto& keyvalue: entities){

            unsigned int shadeur = keyvalue.first;
            List<int>* entite = keyvalue.second;
            gpu->useShader(shadeur);
            for(const auto& x:(*entite)){

                glClearColor(0.168f, 0.112f, 0.255f, 1.0f);
                gpu->bindVertexArray(reg.getComponent<Mesh>(x)->vao);
                gpu->drawIndexed(reg.getComponent<Mesh>(x)->vertex_count);

                glfwSwapBuffers(window);


            }

        }
    }


}