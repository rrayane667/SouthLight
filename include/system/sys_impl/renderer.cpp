#include "system/system.h"
#include "settings/settings.cpp"
using namespace REG;


namespace SYSTEMS{
    
    Renderer::Renderer(){
        std::cout << std::endl;
        std::cout << "Creating Renderer"<<std::endl;
        
        gpu = GraphicsDevice::getInstance();
        std::cout << "Renderer tsawb"<<std::endl;
        std::cout<<std::endl;

        
    }   

    void Renderer::onInit(REG::Registry& reg){
        //init : load ressource into gpu based on the component/ stores vao into component
        //compile shader construct hash table of entities using same shaders
        List<int>* entities_list = reg.getEntities<Mesh>();
        cam = reg.getComponent<Camera>( reg.getEntities<Camera>()->get(0));
        camTrans = reg.getComponent<Transform>( reg.getEntities<Camera>()->get(0));

        std::cout << *entities_list << std::endl;

        std::cout << "initialisation du Renderer"<<std::endl;
        for(auto& x:(*entities_list)){
            unsigned int* shadeur = ((reg.getComponent<Material>(x))->shader) ;
            if (entities.find(*shadeur) == entities.end()){

                entities[*shadeur] = new DynamicList<int>;
                
            }
            entities[*shadeur]->append(x);
        }
        

        
    }


    void Renderer::update(REG::Registry& reg){
        mat4 projection;
        if (cam->projection == PERSPECTIVE) projection = mat4::perspective(cam->cp->fov, cam->cp->ratio,cam->cp->n ,cam->cp->f );
        else projection = mat4::orthographic(cam->co->r, cam->co->l, cam->co->t, cam->co->b, cam->co->n, cam->co->f);
        
		    mat4 view = mat4::view(
			    vec4(0.0f, 0.0f, 1.0f, 1.0f), 
			    vec4(camTrans->position.x, camTrans->position.y, camTrans->position.z, 1.0f), 
			    vec4(0.0f, 1.0f, 0.0f, 0.0f)  
            );
        for(const auto& keyvalue: entities){
            
            
            List<int>* entite = keyvalue.second;
            unsigned int* shadeur = (reg.getComponent<Material>(entite->get(0)))->shader;
            gpu->useShader(*shadeur);

            gpu->setUniform(*shadeur, "projection", projection.list);
            gpu->setUniform(*shadeur, "view", view.list);

            for(const auto& x:(*entite)){


                gpu->setUniform(*shadeur, "model", (reg.getComponent<Transform>(x)->model).list);
                gpu->events();
                gpu->color();
                gpu->bindVertexArray(reg.getComponent<Mesh>(x)->vao);
                gpu->drawIndexed(reg.getComponent<Mesh>(x)->vertex_count);
                gpu->swapBuffers();
                


            }

        }
    }


}