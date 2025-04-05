#pragma once
#include "gpu/gpu.h"
#include "gpu/gl/gl_gpu.h"
#include "settings/settings.cpp"

namespace GPU{
    GraphicsDevice* GraphicsDevice::getInstance(){
        RENDERER_TYPE t = Settings::getRendererType();

        if (t == GL_TYPE){
            

            //if (ptr != nullptr) delete ptr; //a ameliorer si y a pas qu opengl
            return GL_GraphicsDevice::getInstanceGL();
            
        }
        return ptr;
    }
}