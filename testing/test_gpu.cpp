#include "engine.h"

int main(){
    Settings* s = Settings::getInstance();
    // Create an instance of your OpenGL wrapper graphics device
    GraphicsDevice* gpu = GraphicsDevice::getInstance();

    // Initialize OpenGL and create the window

    // Vertex data for a rectangle (two triangles)
    float vertices[] = {
         // positions (x, y, z)
         0.5, 0.5, 0.0, 0.0, 0.0, 1.0,  // top right
         0.5, -0.5, 0.0, 0.0, 0.0, 1.0,  // bottom right
         -0.5, 0.5, 0.0, 0.0, 0.0, 1.0,  // bottom left
         -0.5, -0.5, 0.0, 0.0, 0.0, 1.0   // top left 
    };

    unsigned int indices[] = {
        0, 1, 2,  // first triangle
        1, 3, 2   // second triangle
    };

    // Create a Vertex Array Object (VAO)
    unsigned int VAO;
    gpu->createVertexArray(VAO);
    gpu->bindVertexArray(VAO);

    // Create Vertex Buffer Object (VBO) and load vertex data
    unsigned int VBO;
    gpu->createVertexBuffer(VBO, vertices, sizeof(vertices));

    // Create Element Buffer Object (EBO) and load index data
    unsigned int EBO;
    gpu->createIndexBuffer(EBO, indices, sizeof(indices));

    // Specify vertex attribute layout:
    // - location 0, 3 floats per vertex, stride = 3 floats, starting at offset 0
    gpu->structBuffer(0, 3, 6, 0);
    gpu->structBuffer(1, 3, 6, 3);

    const char* vertexShaderSource = "#version 330 core\n"
                                        "layout (location = 0) in vec3 aPos;\n"
                                        "uniform mat4 model;\n"
                                        "void main()\n"
                                        "{\n"
                                        "   gl_Position = model*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor; \n"
        "void main()\n"
        "{\n"
        "	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
        "}\n";

    // Create shader program using the wrapper.
    unsigned int shaderProgram;
    gpu->createShader(&shaderProgram, vertexShaderSource, fragmentShaderSource);

    // Main render loop
    while (gpu->windowCheck()) {
        gpu->setUniform(shaderProgram, "model", mat4::scale(vec3(1.0f,1.0f,1.0f)).list);
        // Process input and events (for example, close window on ESC key)
        gpu->events();

        // Set background color and clear the screen
        gpu->color();

        // Use the shader program
        gpu->useShader(shaderProgram);

        // Bind VAO and draw our rectangle
        gpu->bindVertexArray(VAO);
        gpu->drawIndexed(6);

        // Swap front and back buffers
        gpu->swapBuffers();
    }

    // Clean up resources
    gpu->deleteBuffer(VBO);
    gpu->deleteBuffer(EBO);
    gpu->deleteVertexArray(VAO);
    gpu->deleteShader(shaderProgram);

    return 0;
}