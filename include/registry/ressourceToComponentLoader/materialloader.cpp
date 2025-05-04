#include "registry/ressourceToComponentLoader/componentloader.h"


using namespace RESSOURCES;
using json = nlohmann::json;

namespace REG{


        
        void MaterialLoader::loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man) {
            Data& data = *ress_man.getData(index);
            try {
                ComponentData& i_data = dynamic_cast<ComponentData&>(data);
                loadComponent(reg, entity, i_data, ress_man);

            } catch (const std::bad_cast& e) {
                std::cerr << "Error: " << e.what() << "ressource index : " << index<< std::endl;
                return;
            }
            
                
        }
        void MaterialLoader::loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) {
            reg.addComponent<Material>(entity);
            Material* mat = dynamic_cast<Material*>(reg.getComponent<Material>(entity));

            int material_archetype_index = j["mat_archetype_index"];
            mat->archetype_index_ressource = material_archetype_index;

            MaterialArchetype* mat_archetype = dynamic_cast<MaterialArchetype*>(ress_man.getData(material_archetype_index));

            const char* vert = (dynamic_cast<RESSOURCES::ShaderData*> (ress_man.getData(mat->archetype->vert_index)))->shaderString;
            const char* frag = (dynamic_cast<RESSOURCES::ShaderData*> (ress_man.getData(mat->archetype->frag_index)))->shaderString;

            mat->shader = new unsigned int;
            gpu->createShader(mat->shader, vert, frag);
            mat->is_loaded = true;
            ress_man.unload(mat->archetype->vert_index);
            ress_man.unload(mat->archetype->frag_index);
            mat->archetype = mat_archetype;
            int i =0;
            for(auto& x: mat_archetype->expected_input){
                if(x.second == '0'){
                    mat->tex_components[x.first].texture = new unsigned int();
                    mat->tex_components[x.first].index = j[x.first];
                    loadTexture( mat->tex_components[x.first].index, mat->tex_components[x.first].texture, ress_man, i++);
                    
                }else{ 
                    mat->float_components[x.first] = j[x.first];
                }


            }
        }

        void MaterialLoader::loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man) {
            json j = json::parse(data.json_component_data);
            loadComponent(reg, entity, j, ress_man);
        }

        void MaterialLoader::loadTexture(int texture_data_index, unsigned int* texture, RESSOURCES::RessourceManager& ress_man, int slot){
            TextureData* txt = dynamic_cast<TextureData*>(ress_man.getData(texture_data_index));
            gpu->createTexture(*texture, txt->width, txt->height, txt->nrchannels, txt->data);
            gpu->bindTexture(*texture, slot);
            ress_man.unload(texture_data_index);
        }

        json& MaterialLoader::exportjson(Registry& reg, int entity){
            json j;
            Material* mat = dynamic_cast<Material*>(reg.getComponent<Material>(entity));
            j["mat_archetype_index"] = mat->archetype_index_ressource;
            for(auto& x: mat->tex_components){
                j[x.first] = x.second.index;
            }
            for(auto& x: mat->float_components){
                j[x.first] = x.second;
            }
            return j;
        }

        int MaterialLoader::exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant){
            json j = exportjson(reg, entity);
            ComponentData* data = new ComponentData;
            data->component_type = "Material";
            data->json_component_data = j.dump(4);
            return ress_man.exportData(data, "component", variant);
        }
}