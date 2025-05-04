#include "json/json.hpp"
#include "ressources/utility/ressourceutility.h"
#include <fstream>

namespace RESSOURCES{
    void ComponentLoader::load(const std::string& path,  Data*& data,const std::string& type_variant) {
        data = new ComponentData();
        if (type_variant == "a"){
            ComponentLoader::componentLoader(path, dynamic_cast<ComponentData&> (*data));
        }
        
    }
    void ComponentLoader::componentLoader(const std::string& path,  ComponentData& data){
        std::ifstream inputFile(path);
        if (!inputFile.good()){
            std::cerr << "Cannot open file: " << path << '\n';
            return;
        }
        data.json_component_data = json::parse(inputFile)["data"];
        data.component_type = json::parse(inputFile)["type"];
    }

    std::string ComponentLoader::exportRessource(const std::string& path, Data*& data,const std::string& type_variant) {
        if (type_variant == "a"){
           return ComponentLoader::componentExport(path, dynamic_cast<ComponentData&> (*data));
        }
    }
    std::string ComponentLoader::componentExport(const std::string& path, ComponentData& data){

        int i = 0;
        std::string filename;
        do {
            filename = path + "/" + data.name + std::to_string(i++) + ".json";
        } while (std::filesystem::exists(filename));
        
        std::ofstream outputFile(filename);
        if (!outputFile.good()){
            std::cerr << "Cannot open file: " << path << '\n';
            return "";
        }
        outputFile << "{\n";
        outputFile << "  \"type\": \"" << data.component_type << "\",\n";
        outputFile << "  \"data\": " << data.json_component_data << "\n";
        outputFile << "}\n";
        outputFile.close();
        return path+"/"+data.name +std::to_string(i) +".json";
    }
        
}