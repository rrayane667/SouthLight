#include "ressources/utility/ressourceutility.h"
#include <fstream>
#include <string>
#include "utilite/fileUtil.h"


namespace RESSOURCES{
    void TexteLoader::load(const std::string& path,  Data*& data,const std::string& type_variant) {
        data = new ShaderData();
        if (type_variant == "a"){

            TexteLoader::_jspLoader(path, dynamic_cast<ShaderData&> (*data));
        }
        
    }
    std::string TexteLoader::exportRessource(const std::string& path, Data*& data,const std::string& type_variant) {
        if (type_variant == "a"){
            return TexteLoader::_jspExport(path, dynamic_cast<ShaderData&> (*data));
        }
        std::cerr << "Unknown type variant for ShaderData export: " << type_variant << '\n';
        return "";
        
    }

    std::string TexteLoader::_jspExport(const std::string& path, ShaderData& data){
        int i = 0;
        std::string filename;
        do {
            filename = path + "/" + data.name + std::to_string(i++) + ".json";
        } while (std::filesystem::exists(filename));
        std::ofstream outFile(filename);
        if (!outFile.good()){
            std::cerr << "Cannot open file: " << filename << '\n';
            return "";
        }
        outFile << data.shaderString; 
        outFile.close();
        return path + "/" + data.name + std::to_string(i) + ".json";

    }

    void TexteLoader::_jspLoader(const std::string& path,  ShaderData& data){

        data.shaderString = readFiles(path);

    }
}