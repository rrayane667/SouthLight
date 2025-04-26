#include "registry/ressourceToComponentLoader/componentloader.h"


using namespace RESSOURCES;
using json = nlohmann::json;

namespace REG{


        
        void TransformLoader::loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man) {
            Data& data = *ress_man.getData(index);
            try {
                ComponentData& i_data = dynamic_cast<ComponentData&>(data);
                loadComponent(reg, entity, i_data, ress_man);

            } catch (const std::bad_cast& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return;
            }
            
                
        }

        void TransformLoader::loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man) {
            json j = json::parse(data.json_component_data);

            loadComponent(reg, entity, j, ress_man);
        }
        void TransformLoader::loadComponent(Registry& reg, int entity,  json j, RESSOURCES::RessourceManager& ress_man){
            Transform* t = dynamic_cast<Transform*>(reg.getComponent<Transform>(entity));
            MATH::from_json( j["position"], t->position);
            MATH::from_json(j["rotation"], t->rotation);
            MATH::from_json(j["scale"], t->scale );
        }
}