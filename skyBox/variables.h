#ifndef VARIABLES_H
#define VARIABLES_H

#include "camera.h"
#include <glad/glad.h>
std::string concatPath(std::string rootPath, std::string filename);


///////////////////////////////////////////    General parameters   /////////////////////////////////////////////////////////////


// Window dimensions
GLuint WIDTH = 1800, HEIGHT = 900;
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;

// Deltatime
GLfloat deltaTime = 0.0f;    // Time between current frame and last frame
GLfloat lastFrame = 0.0f;      // Time of last frame

bool    keys[1024];
bool firstMouse = true;

//////////////////////////////////////////////////    Ocean parameters   //////////////////////////////////////////////////////

float oceanSpeed = 0.1;
const float timestep = 1.0f / 60.0f; // Update 60 times per second
float accumulator = 0.0f;
float currentTime = 0.0f;
float oceanRepeat = 100.0f;

//////////////////////////////////////////////////    Sky parameters   //////////////////////////////////////////////////////

float scale = 500.0f;
glm::mat4 skyModel = glm::translate(glm::mat4(1), glm::vec3(0.0f, scale, 0.0f)) * glm::scale(glm::mat4(1), glm::vec3(scale));
glm::mat4 reverseSkyModel = glm::translate(glm::mat4(1), glm::vec3(0.0f, -scale, 0.0f)) * glm::scale(glm::mat4(1), glm::vec3(1.0f, -1.0f, 1.0f)) * glm::scale(glm::mat4(1), glm::vec3(scale));


//////////////////////////////////////////////////    Island Parameters   //////////////////////////////////////////////////////

int heightMapPathHEIGHT, heightMapPathWIDTH;
float heightScale = 60 / 256.0f, heightShift = 10.0f, DEPTH = -2.0f, size = 0.3f;
float repeatDetail = 5.0f; // number of repetitions
glm::mat4 modelHeight = glm::translate(glm::mat4(1), glm::vec3(0.0f, DEPTH, 0.0f)) * glm::scale(glm::mat4(1), glm::vec3(size));
glm::mat4 modelHeightReverse = glm::translate(glm::mat4(1), glm::vec3(0.0f, -DEPTH, 0.0f)) * glm::scale(glm::mat4(1), glm::vec3(size)) * glm::scale(glm::mat4(1), glm::vec3(1.0f, -1.0f, 1.0f));


//////////////////////////////////////////////////    Camera parameters   //////////////////////////////////////////////////////


glm::vec3 positionInitial = glm::vec3(-100.0f, 10.0f, 1.2f);
GLfloat Acceleration = 0.1f, MaxSpeed = 20.0f, InitialSpeed = 2.0f;
Camera  camera(positionInitial, glm::vec3(0.0f, 1.0f, 0.0f), -57.0f, -22.0f, Acceleration, MaxSpeed, InitialSpeed);




//////////////////////////////////////////////////    Hardcoded Paths   //////////////////////////////////////////////////////



std::string rootPath = "/Users/raphaelhaddad/Documents/Tsinghua/Semester_2/Computer_Graphics/OpenGL/project/TerrainEngine/data/SkyBox/";
std::string skyTexturePath[] = {
    concatPath(rootPath, "SkyBox3.bmp"), //
    concatPath(rootPath, "SkyBox2.bmp"),
    concatPath(rootPath, "SkyBox0.bmp"),
    concatPath(rootPath, "SkyBox1.bmp"),
    concatPath(rootPath, "SkyBox4.bmp"), //
};
std::string oceanTextPath = concatPath(rootPath, "SkyBox5.bmp");
const char* heightMapPath = "/Users/raphaelhaddad/Documents/Tsinghua/Semester_2/Computer_Graphics/OpenGL/project/TerrainEngine/data/heightmap.bmp";
const char* textMapPath = "/Users/raphaelhaddad/Documents/Tsinghua/Semester_2/Computer_Graphics/OpenGL/project/TerrainEngine/data/terrain-texture3.bmp";
const char* detailMapPath = "/Users/raphaelhaddad/Documents/Tsinghua/Semester_2/Computer_Graphics/OpenGL/project/TerrainEngine/data/detail.bmp";


////////////////////////////////////////////     Hardcoded coordinates     /////////////////////////////////////////////////////


// Skybox vertices
GLfloat skyboxVertices[] = {
    // Positions        // Texture Coords   // Texture index
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0,
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0, 
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0,

    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1,
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 1,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1,
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1,

     1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 2,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 2,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 2,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 2,
     1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 2,
     1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 2,

    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 3,
    -1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 3,
     1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 3,
     1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 3,
     1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 3,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 3,

    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 4,
     1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 4,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 4,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 4,
    -1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 4,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 4,

};

GLfloat oceanVertices[] = {
    // Positions        // Texture Coords  
    -1.0f, -1.0f, -1.0f,  0.0f, oceanRepeat,
     1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  oceanRepeat, 0.0f, 
     1.0f, -1.0f,  1.0f,  oceanRepeat, 0.0f, 
    -1.0f, -1.0f,  1.0f,  oceanRepeat, oceanRepeat,
    -1.0f, -1.0f, -1.0f,  0.0f, oceanRepeat,
};


////////////////////////////////////////////     Utils     /////////////////////////////////////////////////////




std::string concatPath(std::string rootPath, std::string filename) {
    std::string path = rootPath + filename;
    return path.c_str();
}

#endif // VARIABLES_H