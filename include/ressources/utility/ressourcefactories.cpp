#include "ressources/utility/ressourceutility.h"
#include <string>
#include "ressources/ressource.h"
#include <fstream>
#include "utilite/parser.h"
#include "maths/vec.h"
#include "utilite/fileUtil.h"
#include "json/json.hpp"
#include "stb_image.h"

using json = nlohmann::json;

namespace RESSOURCES{


    Ressource* RessourceFactoryTypeA::createMeshData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new MeshLoader(), ressource_index, "a"));
    }

    Ressource* RessourceFactoryTypeA::createTextureData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new TextureLoader(), ressource_index, "a"));
    }

    Ressource* RessourceFactoryTypeA::createShaderData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new TexteLoader(), ressource_index, "a"));
    }
    Ressource* RessourceFactoryTypeA::createMaterialArchetypeData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new MaterialArchetypeLoader(), ressource_index, "a"));
    }
    Ressource* RessourceFactoryTypeA::createSceneData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new SceneLoader(), ressource_index, "a"));
    }
    Ressource* RessourceFactoryTypeA::createGameObjectData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new GameObjectLoader(), ressource_index, "a"));
    }
    Ressource* RessourceFactoryTypeA::createComponentData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new ComponentLoader(), ressource_index, "a"));
    }

}