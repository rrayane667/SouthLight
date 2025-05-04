#include <sstream>
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
        std::stringstream buffer;

	    buffer << inputFile.rdbuf();
        data.json_game_object_data = buffer.str();
    }

    std::string GameObjectLoader::exportRessource(const std::string& path, Data*& data,const std::string& type_variant) {
        if (type_variant == "a"){
            return GameObjectLoader::gameObjectExport(path, dynamic_cast<GameObjectData&> (*data));
        }
        std::cerr << "type variant doesnt exist : " << type_variant << '\n';
        return"";
    }
    std::string GameObjectLoader::gameObjectExport(const std::string& path,  GameObjectData& data){
        
        
        
        int i = 0;
        std::string filename;
        do {
            filename = path + "/" + data.name + std::to_string(i++) + ".json";
        } while (std::filesystem::exists(filename));
        std::ofstream outputFile(filename);
        if (!outputFile.good()){
            std::cerr << "Cannot open file: " << path << '\n';
            return;
        }
        std::ofstream outputFile(filename);
        outputFile << data.json_game_object_data;
        outputFile.close();
        return path+"/"+data.name +std::to_string(i) +".json";
    }
} 