#include "ressources/utility/ressourceutility.h"
#include <string>
#include <fstream>
#include "json/json.hpp"

namespace RESSOURCES{
    void MaterialArchetypeLoader::load(const std::string& path,  Data*& data,const std::string& type_variant) {
        data = new MaterialArchetypeData();
        if (type_variant == "a"){
            MaterialArchetypeLoader::jsonLoader(path, dynamic_cast<MaterialArchetypeData&> (*data));
        }
        
    }
    std::string MaterialArchetypeLoader::exportRessource(const std::string& path, Data*& data,const std::string& type_variant) {
        if (type_variant == "a"){
            return MaterialArchetypeLoader::jsonExport(path, dynamic_cast<MaterialArchetypeData&> (*data));
        }
        std::cerr << "Unknown type_variant: " << type_variant << std::endl;
        return "";
        
    }
    std::string MaterialArchetypeLoader::jsonExport(const std::string& path, MaterialArchetypeData& data){
        json jsonData = nlohmann::json{
            {"shader_name", data.shader_name},
            {"expected_input", data.expected_input},
            {"frag_index", data.frag_index},
            {"vert_index", data.vert_index}
        };

        int i =0;
        std::string filename;
        do {
            filename = path + "/" + data.name + std::to_string(i++) + ".json";
        } while (std::filesystem::exists(filename));

        
        std::ofstream outputFile(filename);
        if (!outputFile.good()){
            std::cerr << "Cannot open file: " << path << '\n';
            return "";
        }
        outputFile << jsonData.dump(4); 
        outputFile.close();
        return path + "/" + data.name + std::to_string(i) + ".json";
    }

    


    inline void from_json(const nlohmann::json& j, MaterialArchetypeData& m)
    {
        j.at("shader_name").get_to(m.shader_name);
        j.at("expected_input").get_to(m.expected_input);
        j.at("frag_index").get_to(m.frag_index);
        j.at("vert_index").get_to(m.vert_index);
    }
    void MaterialArchetypeLoader::jsonLoader(const std::string& path, MaterialArchetypeData&  outMaterial){
        std::ifstream inFile(path);
        if (!inFile.good()){
            std::cerr << "Cannot open file: " << path << '\n';
            return;
        }

        try{
            nlohmann::json j;
            inFile >> j;                 // parse
            outMaterial = j.get<MaterialArchetypeData>();  // convert
            return ;
        }
        catch (const nlohmann::json::exception& e){
            std::cerr << "JSON error in " << path
            << " : " << e.what() << '\n';
            return ;
        }
    }
}