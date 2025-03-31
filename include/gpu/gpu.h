#pragma once
#include <string>
#include "maths/vec.h"



using namespace MATH; 

namespace GPU{
    struct ProcessedMesh {
        float* vertices;
        unsigned int* indices;
        size_t vertexCount;
        size_t indexCount;
    };


    class GraphicsDevice{
        protected :
        GraphicsDevice() = default;
        virtual void initialisation() = 0;

        static inline GraphicsDevice* ptr = nullptr;
        static inline void* window= nullptr;

        public:

        static GraphicsDevice* getInstance();

        // ---- Buffers (VBO, EBO) ----
        virtual void createVertexBuffer(unsigned int& vboID, const void* data, size_t size) = 0;
        virtual void createIndexBuffer(unsigned int& eboID, const void* data, size_t size) = 0;
        virtual void updateBuffer(unsigned int& bufferID, const void* data, size_t size) = 0;
        virtual void deleteBuffer(unsigned int& bufferID) = 0;

        virtual void structBuffer(unsigned int channel, int dimension, int stride, int start) = 0;

        // ---- Vertex Array / Pipeline State ----
        virtual void createVertexArray(unsigned int& vaoID) = 0;
        virtual void bindVertexArray(unsigned int& vaoID) = 0;
        virtual void deleteVertexArray(unsigned int& vaoID) = 0;

        // ---- Shaders ----
        virtual void createShader(unsigned int* shaderID, const char* vertexCode, const char* fragmentCode) = 0;
        virtual void useShader(unsigned int& shaderID) = 0;
        virtual void deleteShader(unsigned int& shaderID) = 0;
        virtual void setUniform(unsigned int& shaderID, const std::string& name, const float* matrix) = 0;
        virtual void setUniform(unsigned int& shaderID, const std::string& name, const vec3* vector)const= 0;
        virtual void setUniform(unsigned int& shaderID, const std::string& name, float value) = 0;

        // ---- Textures ----
        virtual void createTexture(unsigned int& textureID, int width, int height, int channels, const void* data) = 0;
        virtual void bindTexture(unsigned int& textureID, unsigned int slot) = 0;
        virtual void deleteTexture(unsigned int& textureID) = 0;

        // ---- Draw Calls ----
        virtual void drawIndexed(unsigned int count) = 0;
        virtual void drawArrays(unsigned int count) = 0;
        virtual void swapBuffers() = 0;
        virtual void drawInstanced(unsigned int& count, unsigned int& instance_nbr) = 0;

        // ---- arriere plan ----
        virtual void color() = 0;

        virtual void events() = 0;
        virtual bool windowCheck() = 0;

        // ---- Synchronisation ----
        //virtual void waitForGPU() = 0;
    };
}