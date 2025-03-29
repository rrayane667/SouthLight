#pragma once
#include "system/system.h"

namespace SYSTEMS{

    System* SystemFactory::createSystem(SYSTEM type){

        if (type == RENDERER){
            return new Renderer();
        }
    }
}