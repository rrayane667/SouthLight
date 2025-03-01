#include "ressources/ressource.h"
#include "ressources/utility/ressourceutility.h"

namespace RESSOURCES{
    Ressource::Ressource(const std::string& path, Loader* loadr_arg, int id, int type_variant) : id(id), path(path), is_loaded(false)
    {
        loader = loadr_arg;
    }

    Ressource::~Ressource(){
        delete loader;
        delete data;
    }

    void Ressource::load(){
        if(!is_loaded){loader->load(path, *data, type_variant); is_loaded = true;}
    }

    void Ressource::unload(){

        if(is_loaded){

            delete data;
            is_loaded=false;
        }
            
    }
}

