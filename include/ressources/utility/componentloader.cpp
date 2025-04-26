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
}