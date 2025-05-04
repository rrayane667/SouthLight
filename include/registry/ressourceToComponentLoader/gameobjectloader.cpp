#include "registry/ressourceToComponentLoader/componentloader.h"
#include <fstream>

using namespace RESSOURCES;
using json = nlohmann::json;

namespace REG{
    
    void GameobjectLoader::loadComponent(Registry& reg, int entity, int index, RESSOURCES::RessourceManager& ress_man) {
        Data& data = *ress_man.getData(index);
        try {
            ComponentData& g_data = dynamic_cast<ComponentData&>(data);
            int ent = reg.createEntity();
            loadComponent(reg, ent, g_data, ress_man);

        } catch (const std::bad_cast& e) {
            std::cerr << "Error: " << e.what() << "ressource index : " << index<< std::endl;
            return;
        }
    }

    void GameobjectLoader::loadComponent(Registry& reg, int entity, RESSOURCES::ComponentData& data, RESSOURCES::RessourceManager& ress_man){
        json j = json::parse(data.json_component_data);
        const json& components = j["Components"];
        for (std::size_t i = 0; i < components.size(); ++i) {
            

            ObjectLoader::load(reg, entity, components[i], ress_man);

        }

    }

    json& GameobjectLoader::exportjson(Registry& reg, int entity) {
        json j;
        j["type"] = "GameObject";
        j["Components"] = json::array();
        for (auto& component : *reg.getComponents()) {
            if (component.second.getIndex(entity) != -1) {
                json component_json ;
                component_json["data"] = ObjectLoader::exportjson(reg, entity, component.first);
                component_json["type"] = component.first;
                j["data"]["Components"].push_back(component_json);
            }
        
        }
        return j;
    }

    int GameobjectLoader::exportComponent(Registry& reg, int entity, RESSOURCES::RessourceManager& ress_man, std::string variant){
        json j = exportjson(reg, entity);
        GameObjectData* data = new GameObjectData;
        data->json_game_object_data = j.dump(4);
        return ress_man.exportData(data, "gameobject", variant);
    }
}