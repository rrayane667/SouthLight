#include "gpu/gl/gl_gpu.h"

#include<iostream>
#include "settings/settings.cpp"

namespace GPU{
    void GL_GraphicsDevice::events(){
        
        if (glfwGetKey(reinterpret_cast<GLFWwindow*>(window), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(reinterpret_cast<GLFWwindow*>(window), true);
        glfwPollEvents();
    }
    bool GL_GraphicsDevice::windowCheck(){
        return !glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(window));
    }
    
    void GL_GraphicsDevice::mouseEvents(EVENTS::EventManager& em) {
        static double lastX = 0.0, lastY = 0.0;
        double xPos, yPos;
    
        glfwGetCursorPos(reinterpret_cast<GLFWwindow*>(window), &xPos, &yPos);
    

        if (xPos != lastX || yPos != lastY) {

            EVENTS::MouseMoveEvent* mouseEvent = new EVENTS::MouseMoveEvent(-(xPos - lastX), -(yPos - lastY)); 
            em.publish(mouseEvent);
    
            lastX = xPos;
            lastY = yPos;
        }
    }


    void GL_GraphicsDevice::InputEvents(EVENTS::EventManager& em) {
        GLFWwindow* glfwWindow = reinterpret_cast<GLFWwindow*>(window);
    
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) {  // Loop through keys
            if (glfwGetKey(glfwWindow, key) == GLFW_PRESS) {
                
                EVENTS::KeyPressEvent* keyEvent = new EVENTS::KeyPressEvent(key);
                em.publish(keyEvent);
                
            }
        }
        
        
    }

    void GL_GraphicsDevice::initialisation(){

        std::cout << "setting up to opengl..." << std::endl;
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
        window = glfwCreateWindow(Settings::getWidth(), Settings::getHeight(), "South light", NULL, NULL);
        //au cas ou erreur
        if (window == NULL)
        {
            std::cout << "GROS FAIL" << std::endl;
            glfwTerminate();
            return;
        }
        //dire quelle window utiliser
        glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*> (window));

        //charger GLAD
        gladLoadGL();

        //viewport dimensions
        glViewport(0,0, Settings::getWidth(), Settings::getHeight());
        glEnable(GL_DEPTH_TEST);
        std::cout << "opengl t9ad" << std::endl;
        std::cout << std::endl;
    }

    void GL_GraphicsDevice::createVertexBuffer(unsigned int& vbo, const void* data, size_t size){
        
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

	    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

    }

    void GL_GraphicsDevice::createIndexBuffer(unsigned int& bufferID, const void* data, size_t size) {

        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    }
    void GL_GraphicsDevice::structBuffer(unsigned int channel, int dimension, int stride, int start){
        glVertexAttribPointer(channel, dimension, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)(start * sizeof(float)));
        glEnableVertexAttribArray(channel);
    }

    void GL_GraphicsDevice::instanceDiviseur(int channel, int count){
        glVertexAttribDivisor(channel, count);
    }
    
    void GL_GraphicsDevice::updateBuffer(unsigned int& bufferID, const void* data, size_t size) {
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
    
    void GL_GraphicsDevice::deleteBuffer(unsigned int& bufferID) {
        glDeleteBuffers(1, &bufferID);
    }

    void GL_GraphicsDevice::createVertexArray(unsigned int& vaoID) {

        glGenVertexArrays(1, &vaoID);

    }
    
    void GL_GraphicsDevice::bindVertexArray(unsigned int& vaoID) {
        glBindVertexArray(vaoID);
    }
    
    void GL_GraphicsDevice::deleteVertexArray(unsigned int& vaoID) {
        glDeleteVertexArrays(1, &vaoID);
    }

    void GL_GraphicsDevice::setUniform(unsigned int& shaderID, const std::string& name, const float* matrix) {
        int location = glGetUniformLocation(shaderID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
    }

    void GL_GraphicsDevice::setUniform(unsigned int& shaderID, const std::string& name, const vec3* vector) const{
        int location = glGetUniformLocation(shaderID, name.c_str());
        glUniform3fv(location, 1, (vector->vecToList()) );
    }

    void GL_GraphicsDevice::setUniform(unsigned int& shaderID, const std::string& name, float value){
        int location = glGetUniformLocation(shaderID, name.c_str());
        glUniform1f(location, value);
    }

    void GL_GraphicsDevice::createTexture(unsigned int& textureID, int width, int height, int channels, const void* data) {

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
    
        GLint format = (channels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    

    }
    
    void GL_GraphicsDevice::bindTexture(unsigned int& textureID, unsigned int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    void GL_GraphicsDevice::setUniformTex(unsigned int& shaderID, const std::string& name, float value) {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);}
    
    void GL_GraphicsDevice::deleteTexture(unsigned int& textureID) {
        glDeleteTextures(1, &textureID);
    }
    
    void GL_GraphicsDevice::drawIndexed(unsigned int count) {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
    
    void GL_GraphicsDevice::drawArrays(unsigned int count) {
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void GL_GraphicsDevice::drawInstanced(unsigned int count, unsigned int instance_nbr){
        glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT,nullptr,instance_nbr);
       
    }

    void GL_GraphicsDevice::createShader(unsigned int* shaderProgram, const char* vertexCode, const char* fragmentCode) {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertexCode, nullptr);
        glCompileShader(vertexShader);
        // Error checking omitted for brevity
    
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
        glCompileShader(fragmentShader);
        // Error checking omitted for brevity
    
        *shaderProgram = glCreateProgram();
        glAttachShader(*shaderProgram, vertexShader);
        glAttachShader(*shaderProgram, fragmentShader);
        glLinkProgram(*shaderProgram);
        // Error checking omitted for brevity
    
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    

    }
    
    void GL_GraphicsDevice::useShader(unsigned int& shaderID) {
        glUseProgram(shaderID);
    }
    
    void GL_GraphicsDevice::deleteShader(unsigned int& shaderID) {
        glDeleteProgram(shaderID);
    }

    void GL_GraphicsDevice::color(){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GL_GraphicsDevice::swapBuffers(){
        glfwSwapBuffers(reinterpret_cast<GLFWwindow*> (window));
    }
}