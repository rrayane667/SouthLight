#include "ressources/utility/ressourceutility.h"
#include <fstream>
#include <string>
#include "utilite/parser.h"
#include "maths/vec.h"

namespace RESSOURCES{
    void MeshLoader::load(const std::string& path,  Data*& data,const std::string& type_variant) {
        data = new MeshData();
        
        if (type_variant == "a"){
            
            MeshLoader::_objLoader(path, dynamic_cast<MeshData&> (*data));
            
        }
        
    }

    std::string MeshLoader::exportRessource(const std::string& path, Data*& data,const std::string& type_variant) {
        if (type_variant == "a"){
            return MeshLoader::_objExport(path, dynamic_cast<MeshData&> (*data));
        }
        std::cerr << "Unknown type variant for export: " << type_variant << std::endl;
        return "";
        
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
                data.is_uv = true;
                
            }
            else if (line.substr(0,2) == "vn"){
                List<float> *normal = (UTILITY::NumberParser::parse(line));
                MATH::vec3 vn = normal;
                data.normals->append(vn);
                delete normal;
                data.is_normal = true;
            }
            else if(line.substr(0,1) == "f"){
                List<float>* face = (UTILITY::NumberParser::parse(line));
                if (!data.is_normal && !data.is_uv) {
                    data.faces->append(face->get(0)-1);
                    data.faces->append(face->get(1)-1);
                    data.faces->append(face->get(2)-1);
                
                }else if(data.is_normal && data.is_uv){
                    data.faces->append(face->get(0)-1);
                    data.faces->append(face->get(1)-1);
                    data.faces->append(face->get(2)-1);
                    data.faces->append(face->get(3)-1);
                    data.faces->append(face->get(4)-1);
                    data.faces->append(face->get(5)-1);
                    data.faces->append(face->get(6)-1);
                    data.faces->append(face->get(7)-1);
                    data.faces->append(face->get(8)-1);

                }
                
                else {
                    data.faces->append(face->get(0)-1);
                    data.faces->append(face->get(1)-1);
                    data.faces->append(face->get(2)-1);
                    data.faces->append(face->get(3)-1);
                    data.faces->append(face->get(4)-1);
                    data.faces->append(face->get(5)-1);
                    
                
                }
                delete face;
                

            }
                
        }

    }

    std::string MeshLoader::_objExport(const std::string& path, MeshData& data){

        int i = 1;
        //check if file with that name already exists
        std::string filename;
        do {
            filename = path + "/" + data.name + std::to_string(i++) + ".json";
        } while (std::filesystem::exists(filename));

  
        

        
        std::ofstream outFile(filename);
        if (!outFile.good()){
            std::cerr << "Cannot open file: " << path << '\n';
            return "";
        }

        for(auto& x : *data.vertices){
            outFile << "v " << x.x << " " << x.y << " " << x.z << "\n";
        }
        for(auto& x : *data.UV){
            outFile << "vt " << x.x << " " << x.y << "\n";
        }
        for(auto& x : *data.normals){
            outFile << "vn " << x.x << " " << x.y << " " << x.z << "\n";
        }

        int n = (!data.is_normal && !data.is_uv)?1:((data.is_normal && data.is_uv)?3:2);
        if (!data.is_normal && !data.is_uv) {
            for(int i = 0; i < data.faces->len(); i+=n){
                outFile << "f " << data.faces->get(i)+1 << " " << data.faces->get(i+1)+1 << " " << data.faces->get(i+2)+1 << "\n";
            }
        
        }else if(data.is_normal && data.is_uv){
            for(int i = 0; i < data.faces->len(); i+=n){
                outFile << "f " << data.faces->get(i)+1 << "/" << data.faces->get(i+1)+1 << "/" << data.faces->get(i+2)+1 << " " 
                << data.faces->get(i+3)+1 << "/" << data.faces->get(i+4)+1 << "/" << data.faces->get(i+5)+1 << " "
                << data.faces->get(i+6)+1 << "/" << data.faces->get(i+7)+1 << "/" << data.faces->get(i+8)+1 << "\n";
            }

        }
            
        else {
            for(int i = 0; i < data.faces->len(); i+=n){
                outFile << "f " << data.faces->get(i)+1 << "/" << data.faces->get(i+1)+1 << " " 
                << data.faces->get(i+2)+1 << "/" << data.faces->get(i+3)+1 << " "
                << data.faces->get(i+4)+1 << "/" << data.faces->get(i+5)+1 << "\n";
            }
            
        
        }
        outFile.close();
        return path+"/"+data.name +std::to_string(i) +".obj";
    }
}