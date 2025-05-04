#include "registry/ressourceToComponentLoader/componentloader.h"


using namespace RESSOURCES;
using json = nlohmann::json;

namespace REG{


        
        void VisibiliteLoader::loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man) {
            Data& data = *ress_man.getData(index);
            try {
                ComponentData& i_data = dynamic_cast<ComponentData&>(data);
                loadComponent(reg, entity, i_data, ress_man);

            } catch (const std::bad_cast& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return;
            }
            
                
        }

        void VisibiliteLoader::loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man) {
            Visibilite* v = dynamic_cast<Visibilite*>(reg.getComponent<Visibilite>(entity));
            v->isActive = j["isActive"];
        }

        void VisibiliteLoader::loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man) {
            json j = json::parse(data.json_component_data);

            loadComponent(reg, entity, j, ress_man);
        }

        json& VisibiliteLoader::exportjson(Registry& reg, int entity) {
            Visibilite* v = dynamic_cast<Visibilite*>(reg.getComponent<Visibilite>(entity));
            json j;
            
            j["isActive"] = v->isActive;
            return j;
        }
        int VisibiliteLoader::exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant) {

            ComponentData* data = new ComponentData;
            data->component_type = "Visibilite";
            data->json_component_data = exportjson(reg, entity).dump(4);
            return ress_man.exportData(data, "component", variant);
        }

            
}