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

    json& TransformLoader::exportjson(Registry& reg, int entity) {
        Transform* t = dynamic_cast<Transform*>(reg.getComponent<Transform>(entity));
        json j;
        
        MATH::to_json(j["position"], t->position);
        MATH::to_json(j["rotation"], t->rotation);
        MATH::to_json(j["scale"], t->scale);
        return j;
    }
    int TransformLoader::exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant) {

        ComponentData* data = new ComponentData;
        data->component_type = "Transform";
        data->json_component_data = exportjson(reg, entity).dump(4);
        return ress_man.exportData(data, "component", variant);
    }
}