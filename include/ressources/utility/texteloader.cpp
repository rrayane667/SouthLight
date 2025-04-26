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
    void TexteLoader::exportRessource(const std::string& path, Data*& data,const std::string& type_variant) {
        if (type_variant == "a"){
            TexteLoader::_jspExport(path, dynamic_cast<ShaderData&> (*data));
        }
        
    }

    void TexteLoader::_jspExport(const std::string& path, ShaderData& data){
        std::ofstream outFile(path+"/"+data.test);
        outFile << data.shaderString; 
        outFile.close();

    }

    void TexteLoader::_jspLoader(const std::string& path,  ShaderData& data){

        data.shaderString = readFiles(path);

    }
}