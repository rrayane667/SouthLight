#include "gpu/gl/gl_gpu.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "settings/settings.cpp"

namespace GPU{
    void GL_GraphicsDevice::initialisation(){
        //initialisation glfw
        glfwInit();

        //specifier a glfw version openGL
        //openGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        //utilisation de CORE profile
        //pas de compatibilité avec anciennes fonctions
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //creation objet GLFWwindow 800x800px
        GLFWwindow* window = glfwCreateWindow(800, 800, "South light", NULL, NULL);
        //au cas ou erreur
        if (window == NULL)
        {
            std::cout << "GROS FAIL" << std::endl;
            glfwTerminate();
            return;
        }
        //dire quelle window utiliser
        glfwMakeContextCurrent(window);

        //charger GLAD
        gladLoadGL();

        //viewport dimensions
        glViewport(0,0, Settings::getWidth(), Settings::getHeight());
    }

    unsigned int GL_GraphicsDevice::createVertexBuffer(const void* data, size_t size){
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

	    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        return vbo;
    }

    unsigned int GL_GraphicsDevice::createIndexBuffer(const void* data, size_t size) {
        unsigned int bufferID;
        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        return bufferID;
    }
    void GL_GraphicsDevice::structBuffer(unsigned int channel, int dimension, int stride, int start){
        glVertexAttribPointer(channel, dimension, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)(start * sizeof(float)));
        glEnableVertexAttribArray(channel);
    }
    
    void GL_GraphicsDevice::updateBuffer(unsigned int bufferID, const void* data, size_t size) {
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
    
    void GL_GraphicsDevice::deleteBuffer(unsigned int bufferID) {
        glDeleteBuffers(1, &bufferID);
    }

    unsigned int GL_GraphicsDevice::createVertexArray() {
        unsigned int vaoID;
        glGenVertexArrays(1, &vaoID);
        return vaoID;
    }
    
    void GL_GraphicsDevice::bindVertexArray(unsigned int vaoID) {
        glBindVertexArray(vaoID);
    }
    
    void GL_GraphicsDevice::deleteVertexArray(unsigned int vaoID) {
        glDeleteVertexArrays(1, &vaoID);
    }

    void GL_GraphicsDevice::setUniform(unsigned int shaderID, const std::string& name, const float* matrix) {
        int location = glGetUniformLocation(shaderID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
    }

    void GL_GraphicsDevice::setUniform(unsigned int shaderID, const std::string& name, const vec3* vector) const{
        int location = glGetUniformLocation(shaderID, name.c_str());
        glUniform3fv(location, 1, (vector->vecToList()) );
    }

    void setUniform(unsigned int shaderID, const std::string& name, float value){
        int location = glGetUniformLocation(shaderID, name.c_str());
        glUniform1f(location, value);
    }

    unsigned int GL_GraphicsDevice::createTexture(int width, int height, int channels, const void* data) {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
    
        GLint format = (channels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    
        return textureID;
    }
    
    void GL_GraphicsDevice::bindTexture(unsigned int textureID, unsigned int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    
    void GL_GraphicsDevice::deleteTexture(unsigned int textureID) {
        glDeleteTextures(1, &textureID);
    }
    
    void GL_GraphicsDevice::drawIndexed(unsigned int count) {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
    
    void GL_GraphicsDevice::drawArrays(unsigned int count) {
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    unsigned int GL_GraphicsDevice::createShader(const std::string& vertexCode, const std::string& fragmentCode) {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vSrc = vertexCode.c_str();
        glShaderSource(vertexShader, 1, &vSrc, nullptr);
        glCompileShader(vertexShader);
        // Error checking omitted for brevity
    
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fSrc = fragmentCode.c_str();
        glShaderSource(fragmentShader, 1, &fSrc, nullptr);
        glCompileShader(fragmentShader);
        // Error checking omitted for brevity
    
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // Error checking omitted for brevity
    
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    
        return shaderProgram;
    }
    
    void GL_GraphicsDevice::useShader(unsigned int shaderID) {
        glUseProgram(shaderID);
    }
    
    void GL_GraphicsDevice::deleteShader(unsigned int shaderID) {
        glDeleteProgram(shaderID);
    }
}