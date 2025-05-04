#pragma once

#include <string>
#include "utilite/dataStruct.h"
#include "data.h"


using namespace DATASTRUCT;

namespace RESSOURCES{
    
    struct Loader;
    
    class Ressource{

        bool is_loaded;
        std::string path;
        Loader *loader;
        Data* data;
        std::string type_variant;
        int id;

        public:

            ~Ressource();

            inline std::string getPath() const {return path;}
            inline std::string getTypeVariant() const {return type_variant;}
            
            inline void setPath(const std::string& path_arg) {path = path_arg; }
            inline void setTypeVariant(const std::string& type_variant_arg) {type_variant = type_variant_arg; }
            inline void setId(int id_arg) {id = id_arg; }

            std::string exportRessource(const std::string& path_arg) ;
            
            Ressource(const std::string& path, Loader* loadr_arg, int id, const std::string& type_variant);
                
            inline int getId() const {return id;}

            inline Data* getData(){return data;}

            void load();

            void unload();

            inline bool isLoaded() {return is_loaded;}
        };
}