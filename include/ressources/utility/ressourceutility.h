#pragma once
#include <string>
#include "ressources/data.h"


namespace RESSOURCES{

    
    class Ressource;
    
    struct Loader{

        Loader() = default;
        virtual void load(const std::string& path,  Data*& data,const std::string& type_variant) = 0;
        virtual void exportRessource(const std::string& path, Data*& data,const std::string& type_variant) = 0;
    };

    struct MeshLoader : public Loader {


        MeshLoader() = default;
        //depending on type_variant it chooses a different loader
        void load(const std::string& path,  Data*& data,const std::string& type_variant)  override;
        void exportRessource(const std::string& path, Data*& data,const std::string& type_variant)  override;

        static void _objLoader(const std::string& path,  MeshData& data);
        static void _objExport(const std::string& path, MeshData& data);
    };

    struct TextureLoader : public Loader {
        
        void load(const std::string& path,  Data*& data,const std::string& type_variant)  override;
        void exportRessource(const std::string& path, Data*& data,const std::string& type_variant)  override;

        static void _jspLoader(const std::string& path,  TextureData& data);
        //static void _jspExport(const std::string& path, TextureData& data);
    };

    struct TexteLoader : public Loader {
        
        void load(const std::string& path,  Data*& data,const std::string& type_variant)  override;
        void exportRessource(const std::string& path, Data*& data,const std::string& type_variant)  override;

        static void _jspLoader(const std::string& path,  ShaderData& data);
        static void _jspExport(const std::string& path, ShaderData& data);
    };

    struct MaterialArchetypeLoader : public Loader {
        
        void load(const std::string& path,  Data*& data,const std::string& type_variant)  override;
        void exportRessource(const std::string& path, Data*& data,const std::string& type_variant)  override;

        static void jsonLoader(const std::string& path,  MaterialArchetypeData& data);
        static void jsonExport(const std::string& path, MaterialArchetypeData& data);
    };

    struct SceneLoader : public Loader {
        
        void load(const std::string& path,  Data*& data,const std::string& type_variant)  override;
        void exportRessource(const std::string& path, Data*& data,const std::string& type_variant)  override;

        static void sceneLoader(const std::string& path,  SceneData& data);
        static void sceneExport(const std::string& path, SceneData& data);
    };

    struct ComponentLoader : public Loader {
        
        void load(const std::string& path,  Data*& data,const std::string& type_variant)  override;
        void exportRessource(const std::string& path, Data*& data,const std::string& type_variant)  override;

        static void componentLoader(const std::string& path,  ComponentData& data);
        static void componentExport(const std::string& path, ComponentData& data);
    };

    struct GameObjectLoader : public Loader {
        
        void load(const std::string& path,  Data*& data,const std::string& type_variant)  override;
        void exportRessource(const std::string& path, Data*& data,const std::string& type_variant)  override;

        static void gameObjectLoader(const std::string& path,  GameObjectData& data);
        static void gameObjectExport(const std::string& path, GameObjectData& data);
    };







    


    struct AbstractFactory{
        virtual Ressource* createMeshData(std::string path, int ressource_index) = 0;
        virtual Ressource* createTextureData(std::string path, int ressource_index) = 0;
        virtual Ressource* createShaderData(std::string path, int ressource_index) = 0;
        virtual Ressource* createMaterialArchetypeData(std::string path, int ressource_index) = 0;
        virtual Ressource* createGameObjectData(std::string path, int ressource_index) = 0;
        virtual Ressource* createSceneData(std::string path, int ressource_index) = 0;
        virtual Ressource* createComponentData(std::string path, int ressource_index) = 0;
        virtual ~AbstractFactory() = default;
    };




    struct RessourceFactoryTypeA : public AbstractFactory{

        public :
            Ressource* createMeshData(std::string path, int ressource_index) override;
            Ressource* createTextureData(std::string path, int ressource_index) override;
            Ressource* createShaderData(std::string path, int ressource_index) override;
            Ressource* createMaterialArchetypeData(std::string path, int ressource_index) override;
            Ressource* createGameObjectData(std::string path, int ressource_index) override;
            Ressource* createSceneData(std::string path, int ressource_index) override;
            Ressource* createComponentData(std::string path, int ressource_index) override;
            ~RessourceFactoryTypeA() override = default;
    };

    
}