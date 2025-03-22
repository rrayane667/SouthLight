#pragma once
#include <string>
#include "maths/vec.h"
#include "settings/settings.cpp"

using namespace MATH; 

namespace GPU{



    class GraphicsDevice{
        protected :
        GraphicsDevice(){initialisation();}
        virtual void initialisation() = 0;

        static GraphicsDevice* ptr;
        public:

        static GraphicsDevice* getInstance(){
            RENDERER_TYPE t = Settings::getRendererType();
            if (t = GL_TYPE){
                if (ptr != nullptr) delete ptr;
                ptr = GL_GraphicsDevice::getInstanceGL();
            }
        }

        // ---- Buffers (VBO, IBO, UBO) ----
        virtual unsigned int createVertexBuffer(const void* data, size_t size, unsigned int usage) = 0;
        virtual unsigned int createIndexBuffer(const void* data, size_t size, unsigned int usage) = 0;
        virtual void updateBuffer(unsigned int bufferID, const void* data, size_t size) = 0;
        virtual void deleteBuffer(unsigned int bufferID) = 0;

        // ---- Vertex Array / Pipeline State ----
        virtual unsigned int createVertexArray() = 0;
        virtual void bindVertexArray(unsigned int vaoID) = 0;
        virtual void deleteVertexArray(unsigned int vaoID) = 0;

        // ---- Shaders ----
        virtual unsigned int createShader(const std::string& vertexCode, const std::string& fragmentCode) = 0;
        virtual void useShader(unsigned int shaderID) = 0;
        virtual void deleteShader(unsigned int shaderID) = 0;
        virtual void setUniform(unsigned int shaderID, const std::string& name, const float* matrix) = 0;
        virtual void setUniform(unsigned int shaderID, const std::string& name, const vec3* vector)const= 0;
        virtual void setUniform(unsigned int shaderID, const std::string& name, float value) = 0;

        // ---- Textures ----
        virtual unsigned int createTexture(int width, int height, int channels, const void* data) = 0;
        virtual void bindTexture(unsigned int textureID, unsigned int slot) = 0;
        virtual void deleteTexture(unsigned int textureID) = 0;

        // ---- Draw Calls ----
        virtual void drawIndexed(unsigned int count) = 0;
        virtual void drawArrays(unsigned int count) = 0;

        // ---- Synchronisation ----
        //virtual void waitForGPU() = 0;
    };
}