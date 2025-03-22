#include "ressources/ressource.h"
#include "ressources/utility/ressourceutility.h"

namespace RESSOURCES{
    Ressource::Ressource(const std::string& path, Loader* loadr_arg, int id, const std::string& variant) : type_variant(variant), id(id), path(path), is_loaded(false)
    {
        data = nullptr;
        loader = loadr_arg;
    }

    Ressource::~Ressource() {
        unload(); // Appelle unload() pour libérer data de manière sécurisée
        delete loader; // Libère le loader
    }

    void Ressource::load(){
        if(!is_loaded){loader->load(path, data, type_variant); is_loaded = true;}
    }

    void Ressource::unload() {
        if (is_loaded && data) { 
            delete data;         
            data = nullptr;      
            is_loaded = false;   
        }
    }
}

