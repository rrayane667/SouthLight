#pragma once
#include <string>
#include "ressources/data.h"


namespace RESSOURCES{

    
    class Ressource;
    
    struct Loader{

        Loader() = default;
        virtual void load(const std::string& path,  Data& data,const int& type_variant) =0;
    };

    struct MeshLoader : public Loader {

        MeshLoader() = default;
        //depending on type_variant it chooses a different loader
        void load(const std::string& path,  Data& data,const int& type_variant)  override;

        static void _objLoader(const std::string& path,  MeshData& data);
    };


    class AbstractFactory{
        virtual Ressource* createMeshData(std::string path, int ressource_index);
        virtual Ressource* createTextureData(std::string path, int ressource_index);
    };




    class RessourceFactory1 : public AbstractFactory{

        public :
            Ressource* createMeshData(std::string path, int ressource_index) override;
            //Ressource* createTextureData(std::string path, int ressource_index) override;
    };

    
}