#include "registry/ressourceToComponentLoader/sceneloader.h"
#include "utilite/parser.h"


namespace REG{
    
    void SceneLoader::createScene(Registry& reg, RESSOURCES::RessourceManager& ress_man, int scene_index){
        List<int>* gameobjects = new DynamicList( (dynamic_cast<SceneData*> (ress_man.getData(scene_index)))->gameobjects);
        for (int i = 0; i < gameobjects->len(); ++i) {
            int entity = reg.createEntity();
            reg.setEntityRessourceId(entity, gameobjects->get(i));
            reg.setEntityName(entity, "Entity" + std::to_string(i));
            ObjectLoader::load(reg, entity, gameobjects->get(i), ress_man);
        }
    }

    void SceneLoader::exportScene(Registry& reg, int scene_index, RESSOURCES::RessourceManager& ress_man){
        SceneData* scene = new SceneData;
        scene->gameobjects = new DynamicList<int>();
        json j;
        for (int i = 0; i < reg.entitiesCount(); ++i) {
            if (reg.getEntityRessourceId(i) == -1) {
                scene->gameobjects->append(ObjectLoader::exportComponent(reg, i, ress_man,"GameObject", "a"));

            }else{
                scene->gameobjects->append(reg.getEntityRessourceId(i));
            }
        }

        ress_man.exportData(scene, "Scene", "a");

    }
}