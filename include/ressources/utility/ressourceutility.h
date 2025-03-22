#pragma once
#include <string>
#include "ressources/data.h"


namespace RESSOURCES{

    
    class Ressource;
    
    struct Loader{

        Loader() = default;
        virtual void load(const std::string& path,  Data*& data,const std::string& type_variant) =0;
    };

    struct MeshLoader : public Loader {


        MeshLoader() = default;
        //depending on type_variant it chooses a different loader
        void load(const std::string& path,  Data*& data,const std::string& type_variant)  override;

        static void _objLoader(const std::string& path,  MeshData& data);
    };

    struct TextureLoader : public Loader {
        
        void load(const std::string& path,  Data*& data,const std::string& type_variant)  override;

        static void _jspLoader(const std::string& path,  MeshData& data);
    };







    


    struct AbstractFactory{
        virtual Ressource* createMeshData(std::string path, int ressource_index) = 0;
        virtual Ressource* createTextureData(std::string path, int ressource_index) = 0;
    };




    struct RessourceFactoryTypeA : public AbstractFactory{

        public :
            Ressource* createMeshData(std::string path, int ressource_index) override;
            Ressource* createTextureData(std::string path, int ressource_index) override;
    };

    
}