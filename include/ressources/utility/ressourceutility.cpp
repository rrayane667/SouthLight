#include "ressources/utility/ressourceutility.h"
#include <string>
#include "ressources/ressource.h"
#include <fstream>
#include "utilite/parser.h"
#include "maths/vec.h"


namespace RESSOURCES{

    typedef enum types{
        Mesh,
        Texture
    } RessourceType;

    typedef enum RessourceTypes{
        OBJ
    } MeshTypes;


    Ressource* RessourceFactory1::createMeshData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new MeshLoader(), ressource_index, OBJ));
    }



    void MeshLoader::load(const std::string& path,  Data& data,const int& type_variant) {
        switch (type_variant){
            case 0 :
                MeshLoader::_objLoader(path, dynamic_cast<MeshData&> (data));
                break;
        }
        
    }

    void MeshLoader::_objLoader(const std::string& path, MeshData& data){
        std::ifstream inputFile(path);

        std::string line;

        while(std::getline(inputFile, line)){

            if (line.substr(0,2) == "v "){

                MATH::vec3 v = *(UTILITY::NumberParser::parse(line));
                data.vertices->append(v);
            }
            else if(line.substr(0,2) == "vt"){
                MATH::vec2 vt = *(UTILITY::NumberParser::parse(line));
                data.UV->append(vt);
            }
            else if (line.substr(0,2) == "vn"){

                MATH::vec3 vn = *(UTILITY::NumberParser::parse(line));
                data.normals->append(vn);
            }
                
        }

    }



}