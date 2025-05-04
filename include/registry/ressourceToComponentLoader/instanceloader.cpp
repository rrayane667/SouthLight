#include "registry/ressourceToComponentLoader/componentloader.h"


using namespace RESSOURCES;
using json = nlohmann::json;

namespace REG{


        
        void InstancesLoader::loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man) {
            Data& data = *ress_man.getData(index);
            try {
                ComponentData& i_data = dynamic_cast<ComponentData&>(data);
                loadComponent(reg, entity, i_data, ress_man);

            } catch (const std::bad_cast& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return;
            }
            
                
        }

        void InstancesLoader::loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man) {
            
            json j = json::parse(data.json_component_data);
            loadComponent(reg, entity, j, ress_man);
        }

        void InstancesLoader::loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man){
            reg.addComponent<Instances>(entity);
            Instances* instances = dynamic_cast<Instances*>(reg.getComponent<Instances>(entity));
            DATASTRUCT::from_json(j["instances"], *instances->instances);
        }

        json& InstancesLoader::exportjson(Registry& reg, int entity){
            json j;

            Instances* instances = dynamic_cast<Instances*>(reg.getComponent<Instances>(entity));
            DATASTRUCT::to_json(j["instances"], *instances->instances);
            return j;
        }
        int InstancesLoader::exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant){

            ComponentData* data = new ComponentData;
            data->component_type = "Instances";
            data->json_component_data = exportjson(reg, entity).dump(4);
            return ress_man.exportData(data, "component", variant);
        }
}