#include "ressources/utility/ressourceutility.h"
#include "utilite/parser.h"
#include <fstream>
#include <string>
#include "utilite/dataStruct.h"

using namespace UTILITY;
using namespace DATASTRUCT;

namespace RESSOURCES{
    void SceneLoader::load(const std::string& path,  Data*& data,const std::string& type_variant) {
        data = new SceneData();
        if (type_variant == "a"){
            SceneLoader::sceneLoader(path, dynamic_cast<SceneData&> (*data));
        }
        
    }
    void SceneLoader::sceneLoader(const std::string& path,  SceneData& data){
        std::ifstream inputFile(path);
        if (!inputFile.good()){
            std::cerr << "Cannot open file : " << path << '\n';
            return;
        }
        std::string line;
        List<float>* go;
        if(std::getline(inputFile, line)){
            go = UTILITY::NumberParser::parse(line);
        }
        else{
            std::cerr << "Cannot read scene: " << path << '\n';
            return;
        }
        
        for(auto& x:*go){
            data.gameobjects->append((int) x);
        }
        delete go;
    }
}