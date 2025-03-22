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
            
            Ressource(const std::string& path, Loader* loadr_arg, int id, const std::string& type_variant);
                
            inline int getId() const {return id;}

            void load();

            void unload();

            inline bool isLoaded() {return is_loaded;}
        };
}