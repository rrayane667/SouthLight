#include "system/system.h"

using namespace REG;


namespace SYSTEMS{
    
    Renderer::Renderer(EventManager& e, REG::Registry& r) : System(e, r) {
        std::cout << std::endl;
        std::cout << "Creating Renderer"<<std::endl;
        
        gpu = GraphicsDevice::getInstance();
        std::cout << "RENDERER tsawb"<<std::endl;
        std::cout<<std::endl;

        
    }   
    void Renderer::updateCamera(){
        float sensitivity = Settings::getInstance()->getSensi();
        for(const auto& keyvalue: entities){
            mat4 view = mat4::view(
                camTrans->position, camTrans->rotation.x*3.1415* sensitivity/180, camTrans->rotation.y*3.1415* sensitivity/180
            );

            List<int>* entite = keyvalue.second;
            unsigned int* shadeur = (reg.getComponent<Material>(entite->get(0)))->shader;

            gpu->setUniform(*shadeur, "view", view.list);
        }
    }

    void Renderer::onInit(){
        subscribe(CAMERA_TRANSFORM_UPDATE, Callback([this](Event* event){updateCamera();}));
        //init : load ressource into gpu based on the component/ stores vao into component
        //compile shader construct hash table of entities using same shaders
        List<int>* entities_list = reg.getEntities<Mesh>();
        cam = reg.getComponent<Camera>( reg.getEntities<Camera>()->get(0));
        camTrans = reg.getComponent<Transform>( reg.getEntities<Camera>()->get(0));

        //std::cout << *entities_list << std::endl;

        std::cout << "initialisation du Renderer"<<std::endl;
        for(auto& x:(*entities_list)){
            unsigned int* shadeur = ((reg.getComponent<Material>(x))->shader) ;
            if (entities.find(*shadeur) == entities.end()){

                entities[*shadeur] = new DynamicList<int>;
                
            }
            entities[*shadeur]->append(x);
        }
        

        
    }

    void Renderer::onStart(){
        for(const auto& keyvalue: entities){

            mat4 projection;
            if (cam->projection == PERSPECTIVE) projection = mat4::perspective(cam->cp->fov, cam->cp->ratio,cam->cp->n ,cam->cp->f );
            else projection = mat4::orthographic(cam->co->r, cam->co->l, cam->co->t, cam->co->b, cam->co->n, cam->co->f);
            
            mat4 view = mat4::view(
                camTrans->position, 0, 0
            );
            
            
            List<int>* entite = keyvalue.second;
            unsigned int* shadeur = (reg.getComponent<Material>(entite->get(0)))->shader;
            gpu->useShader(*shadeur);
            gpu->setUniform(*shadeur, "view", view.list);
            gpu->setUniform(*shadeur, "projection", projection.list);
            
        }
    }


    void Renderer::update(){

        
        
        for(const auto& keyvalue: entities){
            

            List<int>* entite = keyvalue.second;
            unsigned int* shadeur = (reg.getComponent<Material>(entite->get(0)))->shader;
            gpu->useShader(*shadeur);

            gpu->color();
            for(const auto& x:(*entite)){



                gpu->events();
                
                gpu->bindVertexArray(reg.getComponent<Mesh>(x)->vao);
                int i =0;
                for(auto& x: reg.getComponent<Material>(entite->get(0))->tex_components ){
                    
                    gpu->bindTexture(*x.second, i);
                    gpu->setUniform(*shadeur, x.first, i++);
                    
                }
                

                if(reg.hasComponent<Instances>(x)) gpu->drawInstanced(reg.getComponent<Mesh>(x)->vertex_count, reg.getComponent<Instances>(x)->instances->len() );
                else{
                    
                    gpu->setUniform(*shadeur, "model", (reg.getComponent<Transform>(x)->model).list);
                    gpu->drawIndexed(reg.getComponent<Mesh>(x)->vertex_count);
                }
                
                
                


            }
            gpu->swapBuffers();

        }
    }


}