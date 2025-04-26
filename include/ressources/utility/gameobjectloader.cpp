#include "json/json.hpp"
#include "ressources/utility/ressourceutility.h"
#include <fstream>

namespace RESSOURCES{
    void GameObjectLoader::load(const std::string& path,  Data*& data,const std::string& type_variant) {
        data = new GameObjectData();
        if (type_variant == "a"){
            GameObjectLoader::gameObjectLoader(path, dynamic_cast<GameObjectData&> (*data));
        }
    }

    void GameObjectLoader::gameObjectLoader(const std::string& path,  GameObjectData& data){
        std::ifstream inputFile(path);
        if (!inputFile.good()){
            std::cerr << "Cannot open file: " << path << '\n';
            return;
        }
        data.json_game_object_data = json::parse(inputFile)["data"];
    }

    void GameObjectLoader::exportRessource(const std::string& path, Data*& data,const std::string& type_variant) {
        if (type_variant == "a"){
            GameObjectLoader::gameObjectExport(path, dynamic_cast<GameObjectData&> (*data));
        }
    }
    void GameObjectLoader::gameObjectExport(const std::string& path,  GameObjectData& data){
        std::ofstream outputFile(path);
        if (!outputFile.good()){
            std::cerr << "Cannot open file: " << path << '\n';
            return;
        }
        json j;
        j["data"] = data.json_game_object_data;
        outputFile << j.dump(4);
    }
} 