#include "registry/ressourceToComponentLoader/sceneloader.h"
#include "utilite/parser.h"


namespace REG{
    
    void SceneLoader::createScene(Registry& reg, RESSOURCES::RessourceManager& ress_man, int scene_index){
        List<int>* gameobjects = new DynamicList( (dynamic_cast<SceneData*> (ress_man.getData(scene_index)))->gameobjects);
        for (int i = 0; i < gameobjects->len(); ++i) {
            int entity = reg.createEntity();
            ObjectLoader::load(reg, entity, gameobjects->get(i), ress_man);
        }
    }

    void SceneLoader::exportScene(Registry& reg, int scene_index, RESSOURCES::RessourceManager& ress_man){
        SceneData* scene = dynamic_cast<SceneData*>(ress_man.getData(scene_index));
        json j;
}