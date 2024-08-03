#include <iostream>
#include <cmath>

// GLFW
#include <glad/glad.h>  // Glad should be included first
#include <GLFW/glfw3.h> // Then GLFW

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "shader.h"
#include "variables.h"
#include "setup.h"


// Problems to fix 
// - find good scale of moutains
// - Remove the second texture beneath the moutain


// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    GLFWwindow* window = setupGLFW();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    // Build and compile our shader program
    Shader skyboxShader("shaders/skybox.vert.glsl", "shaders/skybox.frag.glsl");
    Shader oceanShader("shaders/ocean.vert.glsl", "shaders/ocean.frag.glsl");
    Shader heightMapShader("shaders/height.vert.glsl","shaders/height.frag.glsl");
    Shader heightReverseShader("shaders/height.vert.glsl","shaders/height_reverse.frag.glsl");


    // Set up the image texture
    std::vector<GLuint> skyTextures;
    addTexture(skyTextures, skyTexturePath);

    GLuint oceanTexture;
    setupTexture(oceanTextPath.c_str(), oceanTexture, 0); // mode 0 = GL_REPEAT

    GLuint MapTexture, detailTexture;
    setupTexture(textMapPath, MapTexture, 1, 1);  // flipping 0 = no horizontal flipping
    setupTexture(detailMapPath, detailTexture, 0, 1);  // flipping 0 = no horizontal flipping



    // Computing the height map
    GLuint terrainVAO, terrainVBO, terrainEBO;
    std::vector<float> verticesHeight = setupHeightMap(heightMapPath, &heightMapPathHEIGHT, &heightMapPathWIDTH, heightScale, heightShift, repeatDetail);
    std::vector<unsigned int> indicesHeight = setupIndicesHeight(heightMapPathHEIGHT, heightMapPathWIDTH);
    const unsigned int NUM_STRIPS = heightMapPathHEIGHT-1, NUM_VERTS_PER_STRIP = heightMapPathWIDTH*2;
    setupHeightVAO(terrainVAO, terrainVBO, terrainEBO, verticesHeight, indicesHeight);



    // set the container's VAO (and VBO)
    GLuint skyboxVAO, skyboxVBO, oceanVAO, oceanVBO;
    glm::mat4 oceanModel = skyModel;
    setupVAOandVBOSky(skyboxVAO, skyboxVBO, skyboxVertices, sizeof(skyboxVertices));
    setupVAOandVBOOcean(oceanVAO, oceanVBO, oceanVertices, sizeof(oceanVertices));
     

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        setupGameLoop();
        updateOceanMovement(currentTime, oceanSpeed, accumulator, oceanVertices, timestep);
        updateVBOocean(oceanVBO, oceanVertices, sizeof(oceanVertices));

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 10000.0f);

        // Draw the skybox and reverse
        bindSkyTexture(skyTextures);
        drawSkybox(skyboxShader, skyboxVAO, skyModel, view, projection);
        drawSkybox(skyboxShader, skyboxVAO, reverseSkyModel, view, projection);

        // // Draw the moutain and reverse
        bindDrawHeightMap(heightMapShader, view, projection, modelHeight, terrainVAO, NUM_STRIPS, NUM_VERTS_PER_STRIP, MapTexture, detailTexture);
        bindDrawHeightMap(heightReverseShader, view, projection, modelHeightReverse, terrainVAO, NUM_STRIPS, NUM_VERTS_PER_STRIP, MapTexture, detailTexture);

        // Draw the ocean
        glDepthMask(GL_FALSE);
        bindDrawOcean(oceanTexture, oceanModel, view, projection, oceanShader, oceanVAO);
        glDepthMask(GL_TRUE);


        // Swap the screen buffers
        glfwSwapBuffers(window);
        lastFrame = currentTime;
    }
    
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}



