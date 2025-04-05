#include "gpu/gpu.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>

namespace GPU{



    class GL_GraphicsDevice : public GraphicsDevice{
        void initialisation() override;



        public:

        static GL_GraphicsDevice* getInstanceGL(){
            if (ptr == nullptr){
                std::cout<< "creating opengl instance" << std::endl;
                ptr = new GL_GraphicsDevice;
                (dynamic_cast<GL_GraphicsDevice*>(ptr))->initialisation();
    
            }
            return dynamic_cast<GL_GraphicsDevice*> (ptr);
        }

        // ---- Buffers (VBO, EBO) ----
        void createVertexBuffer(unsigned int& vbo, const void* data, size_t size) override;
        void createIndexBuffer(unsigned int& bufferID, const void* data, size_t size) override;
        void updateBuffer(unsigned int& bufferID, const void* data, size_t size) override;
        void deleteBuffer(unsigned int& bufferID) override;

        void structBuffer(unsigned int channel, int dimension, int stride, int start);

        // ---- Vertex Array / Pipeline State ----
        void createVertexArray(unsigned int& vaoID) override;
        void bindVertexArray(unsigned int& vaoID) override;
        void deleteVertexArray(unsigned int& vaoID) override;

        // ---- Shaders ----
        void createShader(unsigned int* shaderID, const char* vertexCode, const char* fragmentCode) override;
        void useShader(unsigned int& shaderID) override;
        void deleteShader(unsigned int& shaderID) override;
        void setUniform(unsigned int& shaderID, const std::string& name, const float* matrix) override;
        void setUniform(unsigned int& shaderID, const std::string& name, const vec3* vector) const override;
        void setUniform(unsigned int& shaderID, const std::string& name, float value) override;
        void setUniformTex(unsigned int& shaderID, const std::string& name, float value);

        // ---- Textures ----
        void createTexture(unsigned int& textureID, int width, int height, int channels, const void* data) override;
        void bindTexture(unsigned int& textureID, unsigned int slot) override;
        void deleteTexture(unsigned int& textureID) override;

        // ---- Draw Calls ----
        void drawIndexed(unsigned int count) override;
        void drawArrays(unsigned int count) override;
        void drawInstanced(unsigned int count, unsigned int instance_nbr) override;
        void instanceDiviseur(int channel, int count);


        void color() override;
        void swapBuffers() override;



        void events() override;
        void InputEvents(EVENTS::EventManager& em) override;
        void mouseEvents(EVENTS::EventManager& em) override;
        bool windowCheck() override;

        // ---- Synchronisation ----
        //void waitForGPU() override;
    };

}