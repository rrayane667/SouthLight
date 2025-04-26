#include "ressources/utility/ressourceutility.h"
#include <string>
#include <fstream>
#include "stb_image.h"


namespace RESSOURCES{
    void TextureLoader::load(const std::string& path,  Data*& data,const std::string& type_variant) {
        data = new TextureData();
        if (type_variant == "a"){
            TextureLoader::_jspLoader(path, dynamic_cast<TextureData&> (*data));
        }
        
    }
    void TextureLoader::exportRessource(const std::string& path, Data*& data,const std::string& type_variant) {
        if (type_variant == "a"){
            //TextureLoader::_jspExport(path, dynamic_cast<TextureData&> (*data));
        }
        
    }



    void TextureLoader::_jspLoader(const std::string& path,  TextureData& data){

	    data.data = stbi_load(path.c_str(), &(data.width), &(data.height), &(data.nrchannels), 0);

    }
}