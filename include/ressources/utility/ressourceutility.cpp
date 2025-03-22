#include "ressources/utility/ressourceutility.h"
#include <string>
#include "ressources/ressource.h"
#include <fstream>
#include "utilite/parser.h"
#include "maths/vec.h"


namespace RESSOURCES{


    Ressource* RessourceFactoryTypeA::createMeshData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new MeshLoader(), ressource_index, "a"));
    }

    Ressource* RessourceFactoryTypeA::createTextureData(std::string path, int ressource_index) {
        
        return (new Ressource(path,new TextureLoader(), ressource_index, "a"));
    }












    
    void MeshLoader::load(const std::string& path,  Data*& data,const std::string& type_variant) {
        data = new MeshData();
        
        if (type_variant == "a"){
            
            MeshLoader::_objLoader(path, dynamic_cast<MeshData&> (*data));
            
        }
        
    }

    

    void MeshLoader::_objLoader(const std::string& path, MeshData& data){

        std::ifstream inputFile(path);
        if(!inputFile.is_open()) {
            throw std::runtime_error("Failed to open OBJ file: " + path);
        }

        std::string line;

        
        while(std::getline(inputFile, line)){
            

            if (line.substr(0,2) == "v "){
                List<float> *vect = (UTILITY::NumberParser::parse(line));
                MATH::vec3 v = vect;
                data.vertices->append(v);
                delete vect;
                
            }
            else if(line.substr(0,2) == "vt"){
                List<float> *texture_coordinate = (UTILITY::NumberParser::parse(line));
                MATH::vec2 vt = texture_coordinate;
                data.UV->append(vt);
                delete texture_coordinate;
                
            }
            else if (line.substr(0,2) == "vn"){
                List<float> *normal = (UTILITY::NumberParser::parse(line));
                MATH::vec3 vn = normal;
                data.normals->append(vn);
                delete normal;
                
            }
            else if(line.substr(0,1) == "f"){
                List<float>* face = (UTILITY::NumberParser::parse(line));
                if (face->len() >= 6) { 
                    data.faces->append(paire<float, float>(face->get(0), face->get(1)));
                    data.faces->append(paire<float, float>(face->get(2), face->get(3)));
                    data.faces->append(paire<float, float>(face->get(4), face->get(5)));
                }
                delete face;
                

            }
                
        }

    }

    void TextureLoader::load(const std::string& path,  Data*& data,const std::string& type_variant) {

        if (type_variant == "a"){
            TextureLoader::_jspLoader(path, dynamic_cast<MeshData&> (*data));
        }
        
    }

    void TextureLoader::_jspLoader(const std::string& path,  MeshData& data){
        // a implementer
        return;
    }



}