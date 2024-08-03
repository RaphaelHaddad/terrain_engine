#ifndef SETUP_H
#define SETUP_H


#include "variables.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
void updateOcean(GLfloat* oceanVertices, GLfloat delta);
void drawFaces(Shader& shader, GLuint VAO, int num, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
std::vector<float> setupHeightMap(const char* filename, int* heightMapPathHEIGHT, int* heightMapPathWIDTH);






//////////////////////////////////////////         VAO and VBO          ///////////////////////////////////////////////////

void updateVBOocean(GLuint &VBO, GLfloat *vertices, size_t verticesSize) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize, vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void setupVAOandVBOSky(GLuint &VAO, GLuint &VBO, GLfloat *vertices, size_t verticesSize) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);
}

void setupVAOandVBOOcean(GLuint &VAO, GLuint &VBO, GLfloat *vertices, size_t verticesSize) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0); 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    
}


void setupHeightVAO(GLuint &terrainVAO, GLuint &terrainVBO, GLuint &terrainEBO, std::vector<float>& vertices, std::vector<unsigned int>& indices){
    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);

    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER,
                vertices.size() * sizeof(float),       // size of vertices buffer
                &vertices[0],                          // pointer to first element
                GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture details coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glGenBuffers(1, &terrainEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                indices.size() * sizeof(unsigned int), // size of indices buffer
                &indices[0],                           // pointer to first element
                GL_STATIC_DRAW);
}







////////////////////////////////////////////      Texture        /////////////////////////////////////////////////////////////


void setupTexture(const char* filename, GLuint &texture, int mode = 1, int flipping = 1) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set our texture parameters
    if (mode == 0){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // Set texture wrapping to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // Set texture wrapping to GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    }
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Load, create texture and generate mipmaps
    
    int width, height, nrChannels;
    if (flipping) {stbi_set_flip_vertically_on_load(1);} ;
    unsigned char* image = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);
}


void addTexture(std::vector<GLuint> &skyTextures, std::string texturePath[]){
    for (std::string path : skyTexturePath) {
        GLuint texture;
        setupTexture(path.c_str(), texture);
        skyTextures.push_back(texture);
    }
}

void bindSkyTexture(std::vector<GLuint> skyTextures){
    for (int i = 0; i < skyTextures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, skyTextures[i]);
        }
}



////////////////////////////////////////////      Height Map Processing        /////////////////////////////////////////////////



std::vector<float> setupHeightMap(const char* filename, int* heightMapPathHEIGHT, int* heightMapPathWIDTH, float Scale, float Shift, float repeat) {
    int nrChannels;
    unsigned char* image = stbi_load(filename, heightMapPathWIDTH, heightMapPathHEIGHT, &nrChannels, 0);
    std::cout << "Width: " << *heightMapPathWIDTH << std::endl;
    std::cout << "Height: " << *heightMapPathHEIGHT << std::endl;
    std::cout << "Number of Channels: " << nrChannels << std::endl;
    std::vector<float> verticesHeight;
    int width = *heightMapPathWIDTH, height = *heightMapPathHEIGHT;
    if (image) {
        for(unsigned int i = 0; i < height; i++){
            for(unsigned int j = 0; j < width; j++){
                unsigned char* texel = image + (j + width * i) * nrChannels;
                unsigned char y = texel[0];
                // vertex
                verticesHeight.push_back( -height/2.0f + i );        // v.x
                verticesHeight.push_back( (int)y * Scale - Shift); // v.y
                verticesHeight.push_back( -width/2.0f + j );        // v.z

                // texture coordinates global
                verticesHeight.push_back(1.0f - (float)j / (width - 1));  // u
                verticesHeight.push_back((float)i / (height - 1)); // v

                // texture coordinates detail
                verticesHeight.push_back((float)j / (width - 1) * repeat);  // u
                verticesHeight.push_back((float)i / (height - 1) * repeat); // v
            }
        }
        }
    else {
        std::cout << "Failed to load height map" << std::endl;
    }
    std::cout << "Loaded " << verticesHeight.size() / 7 << " vertices" << std::endl;
    stbi_image_free(image);
    return verticesHeight;
}


std::vector<unsigned int> setupIndicesHeight(int height, int width){
    // index generation
    std::vector<unsigned int> indices;
    for(unsigned int i = 0; i < height-1; i++)       // for each row a.k.a. each strip
    {
        for(unsigned int j = 0; j < width; j++)      // for each column
        {
            for(unsigned int k = 0; k < 2; k++)      // for each side of the strip
            {
                indices.push_back(j + width * (i + k));
            }
        }
    }
    std::cout << "Loaded " << indices.size() << " indices" << std::endl;
    return indices;
}



////////////////////////////////////////////      Drawing functions        /////////////////////////////////////////////////



void drawSkybox(Shader& skyboxShader, GLuint skyboxVAO, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {

        // Draw the skybox
        skyboxShader.Use();
        skyboxShader.setUniform4fv("model", glm::value_ptr(model));
        skyboxShader.setUniform4fv("view", glm::value_ptr(view));
        skyboxShader.setUniform4fv("projection", glm::value_ptr(projection));

        for (int i = 0; i < 5; i++) {
            skyboxShader.setInt(("ourTextures[" + std::to_string(i) + "]").c_str(), i);
        }

        glBindVertexArray(skyboxVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
}


void bindDrawOcean(GLuint oceanTexture, glm::mat4 model, glm::mat4 view, glm::mat4 projection, Shader& oceanShader, GLuint oceanVAO) {
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, oceanTexture);
    // Draw the skybox
    oceanShader.Use();
    oceanShader.setUniform4fv("model", glm::value_ptr(model));
    oceanShader.setUniform4fv("view", glm::value_ptr(view));
    oceanShader.setUniform4fv("projection", glm::value_ptr(projection));
    oceanShader.setInt("ourTexture", 5);
    glBindVertexArray(oceanVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


void bindDrawHeightMap(Shader& heightMapShader, glm::mat4 view, glm::mat4 projection, glm::mat4 modelHeight, GLuint terrainVAO, unsigned int NUM_STRIPS, unsigned int NUM_VERTS_PER_STRIP, GLuint Texture1, GLuint detailTexture){
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, Texture1);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, detailTexture);
        heightMapShader.Use();
        heightMapShader.setUniform4fv("view", glm::value_ptr(view));
        heightMapShader.setUniform4fv("projection", glm::value_ptr(projection));
        heightMapShader.setUniform4fv("model", glm::value_ptr(modelHeight));
        heightMapShader.setInt("ourTexture", 6);
        heightMapShader.setInt("detailTexture", 7);
        glBindVertexArray(terrainVAO);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for(unsigned strip = 0; strip < NUM_STRIPS; strip++)
            {
                glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                            NUM_VERTS_PER_STRIP+2,   // number of indices to render
                            GL_UNSIGNED_INT,     // index data type
                            (void*)(sizeof(unsigned) * (NUM_VERTS_PER_STRIP+2) * strip)); // offset to starting index
            }


}

void updateOceanMovement(float &currentTime, float oceanSpeed, float &accumulator, GLfloat* oceanVertices, float timestep){
    float newTime = glfwGetTime();
    float frameTime = newTime - currentTime;
    currentTime = newTime;
    accumulator += frameTime;
    while (accumulator >= timestep) {
        updateOcean(oceanVertices, oceanSpeed * timestep);
        accumulator -= timestep;
    }
}

void updateOcean(GLfloat* oceanVertices, GLfloat delta) {
    for (int i = 0; i < 5 * 6; i += 5) {
        oceanVertices[i + 3] += delta;
    }
}





////////////////////////////////////////////      Other utils        /////////////////////////////////////////////////


GLFWwindow* setupGLFW() {
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Assignement 5", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the required callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    // Initialize GLAD to setup the OpenGL Function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
    glEnable(GL_DEPTH_TEST);
    return window;
};


void setupGameLoop(){
// Calculate deltatime of current frame
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents();
    do_movement();
    
    // Clear the colorbuffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}







void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    WIDTH = width;
    HEIGHT = height;
    glViewport(0, 0, width, height);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void do_movement()
{
    // Camera controls
    if (keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_R])
		camera.ProcessKeyboard(UP, deltaTime);
	if (keys[GLFW_KEY_F])
		camera.ProcessKeyboard(DOWN, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
#endif // SETUP_H