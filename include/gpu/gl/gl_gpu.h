#include "gpu/gpu.h"


namespace GPU{

    class GL_GraphicsDevice : public GraphicsDevice{
        void initialisation() override;


        public:

        static GL_GraphicsDevice* getInstanceGL(){
            if (ptr == nullptr){
                ptr = new GL_GraphicsDevice;
            }
            return dynamic_cast<GL_GraphicsDevice*> (ptr);
        }

        // ---- Buffers (VBO, EBO) ----
        unsigned int createVertexBuffer(const void* data, size_t size, unsigned int usage) override;
        unsigned int createIndexBuffer(const void* data, size_t size, unsigned int usage) override;
        void updateBuffer(unsigned int bufferID, const void* data, size_t size) override;
        void deleteBuffer(unsigned int bufferID) override;

        // ---- Vertex Array / Pipeline State ----
        unsigned int createVertexArray() override;
        void bindVertexArray(unsigned int vaoID) override;
        void deleteVertexArray(unsigned int vaoID) override;

        // ---- Shaders ----
        unsigned int createShader(const std::string& vertexCode, const std::string& fragmentCode) override;
        void useShader(unsigned int shaderID) override;
        void deleteShader(unsigned int shaderID) override;
        void setUniform(unsigned int shaderID, const std::string& name, const float* matrix) override;
        void setUniform(unsigned int shaderID, const std::string& name, const vec3* vector) const override;
        void setUniform(unsigned int shaderID, const std::string& name, float value) override;

        // ---- Textures ----
        unsigned int createTexture(int width, int height, int channels, const void* data) override;
        void bindTexture(unsigned int textureID, unsigned int slot) override;
        void deleteTexture(unsigned int textureID) override;

        // ---- Draw Calls ----
        void drawIndexed(unsigned int count) override;
        void drawArrays(unsigned int count) override;

        // ---- Synchronisation ----
        //void waitForGPU() override;
    };

}