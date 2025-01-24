//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"

#include "cube.h"
#include "cylinder.h"
#include "cylinder_tex.h"
#include "hemisphere.h"
#include "sphere.h"
#include "stb_image.h"

#include <iostream>


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void wall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
//unsigned int loadTexture2(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
unsigned int loadTexture2(const char* path, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter);


// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 1500;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(2.0f,0.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 1.0, eyeY = 0.0, eyeZ = 15.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(11.8f, 1.6f, -7.2f),
    glm::vec3(10.7f, 1.4f, -1.0f),
    glm::vec3(-3.0f, 1.4f, -3.5f),
    glm::vec3(-4.0f,  2.1f,  2.7f),
    glm::vec3(5.5f, 1.4f, -3.5f),
    glm::vec3(3.7f,  2.1f,  2.7f)
};


//glm::vec3(-0.5, 1, -0.5)


PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);

PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);

PointLight pointlight5(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number
);

PointLight pointlight6(

    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6       // light number
);


// light settings
bool onOffToggle = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool isBasicView = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);




    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   
   
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    
    //wood flooring
    string diffusefloor = "floor1.jpg";
    string specularfloor = "floor1.jpg";
    unsigned int diffMapf = loadTexture(diffusefloor.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapf = loadTexture(specularfloor.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube floor = Cube(diffMapf, specMapf, 32.0f);

    //chad
    string diffusechad = "chad.jpg";
    string specularchad = "chad.jpg";
    unsigned int diffMapc = loadTexture(diffusechad.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapc = loadTexture(specularchad.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube chad_cake = Cube(diffMapc, specMapc, 32.0f);

    string diffusechad1 = "chad.jpg";
    string specularchad1 = "chad.jpg";
    unsigned int diffMapc1 = loadTexture(diffusechad1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapc1 = loadTexture(specularchad1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube chad_coffee = Cube(diffMapc1, specMapc1, 32.0f);

    //chad
    //grass floor
    string diffusegrass = "grass.jpg";
    string speculargrass = "grass.jpg";
    unsigned int diffMapg = loadTexture(diffusegrass.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapg = loadTexture(speculargrass.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube floor_grass = Cube(diffMapg, specMapg, 32.0f);

    
    // Create the hemisphere object (without textures)
    Hemisphere hemisphere(
        1.0f,                        // Radius
        36,                          // Sector count (number of slices)
        18,                          // Stack count (number of layers)
        glm::vec3(0.1f, 0.1f, 0.1f), // Ambient color
        glm::vec3(0.5f, 0.5f, 0.5f), // Diffuse color
        glm::vec3(0.1f, 0.1f, 0.1f), // Specular color
        glm::vec3(0.0f, 0.0f, 0.0f), // Emissive color
        32.0f                        // Shininess
    );

   
    //demo
    string diffuseMapPath = "container2.png";
    string specularMapPath = "container2_specular.png";
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f);

    
    string frontTexturePath = "menu_cake.jpg";  // Front face texture (e.g., with a lock)
    string otherFacesTexturePath = "menu_cake.jpg";  // Other faces texture (e.g., plain wood)
    unsigned int frontTexture = loadTexture(frontTexturePath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int otherTexture = loadTexture(otherFacesTexturePath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube tv = Cube(frontTexture, otherTexture, 32.0f);  // shininess = 32.0f
    
    string front = "cake.jpeg";  // Front face texture (e.g., with a lock)
    string other= "cake.jpeg";  // Other faces texture (e.g., plain wood)
    unsigned int front1 = loadTexture(front.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int other1 = loadTexture(other.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube desk = Cube(front1, other1, 32.0f);  // shininess = 32.0f

    //cake wall
    string frontw = "background.jpg";  // Front face texture (e.g., with a lock)
    string otherw = "background.jpg";  // Other faces texture (e.g., plain wood)
    unsigned int front1w = loadTexture(frontw.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int other1w = loadTexture(otherw.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wallw = Cube(front1w, other1w, 32.0f);  // shininess = 32.0f
    

    string front11 = "coffee_wall.jpg";  // Front face texture (e.g., with a lock)
    string other11 = "coffee_wall.jpg";  // Other faces texture (e.g., plain wood)
    unsigned int front12 = loadTexture(front11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int other12 = loadTexture(other11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube desk2 = Cube(front12, other12, 32.0f);  // shininess = 32.0f

    string wallcf = "coffee_1.jpg";  // Front face texture (e.g., with a lock)
    string othercf = "coffee_1.jpg";  // Other faces texture (e.g., plain wood)
    unsigned int frontcf = loadTexture(wallcf.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int otherf = loadTexture(othercf.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wall_coffee = Cube(frontcf, otherf, 32.0f);  // shininess = 32.0f

    string coffee_menu1 = "menu_cofee.jpg";  // Front face texture (e.g., with a lock)
    string coffee_menu12 = "menu_cofee.jpg";  // Other faces texture (e.g., plain wood)
    unsigned int menu1 = loadTexture(coffee_menu1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int menu12 = loadTexture(coffee_menu12.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube menu = Cube(menu1, menu12, 32.0f);  // shininess = 32.0f

    /*
    //wallmate
    string diffuseMapPath1 = "wallmate.jpg";
    string specularMapPath1 = "container2_specular.png";
    unsigned int diffMap1 = loadTexture(diffuseMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap1 = loadTexture(specularMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube1 = Cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    */
    Cylinder cylinder = Cylinder();
    //cylinder
    string cake1 = "floor1.jpg";  // Front face texture (e.g., with a lock)
    string cake2 = "floor1.jpg";
    unsigned int a1 = loadTexture2(cake1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int a2 = loadTexture2(cake2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);


    CylinderWithTexture cake(
        1.0f,         // Base radius
        1.0f,         // Top radius
        2.0f,         // Height
        36,           // Sector count
        10,           // Stack count
        glm::vec3(0.2f, 0.2f, 0.2f), // Ambient color
        glm::vec3(0.8f, 0.8f, 0.8f), // Diffuse color
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color
        32.0f,        // Shininess
        a1, // Diffuse texture ID
        a2 // Specular texture ID
    );

    string cake11 = "red_v.jpg";  // Front face texture (e.g., with a lock)
    string cake22 = "red_v.jpg";
    unsigned int b1 = loadTexture2(cake11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int b2 = loadTexture2(cake22.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    CylinderWithTexture acake(
        1.0f,         // Base radius
        1.0f,         // Top radius
        2.0f,         // Height
        36,           // Sector count
        10,           // Stack count
        glm::vec3(0.2f, 0.2f, 0.2f), // Ambient color
        glm::vec3(0.8f, 0.8f, 0.8f), // Diffuse color
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color
        32.0f,        // Shininess
        b1, // Diffuse texture ID
        b2 // Specular texture ID
    );

    string cake111 = "vtex.jpg";  // Front face texture (e.g., with a lock)
    string cake222 = "vtex.jpg";
    unsigned int c1 = loadTexture2(cake111.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int c2 = loadTexture2(cake222.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    CylinderWithTexture bcake(
        1.0f,         // Base radius
        1.0f,         // Top radius
        2.0f,         // Height
        36,           // Sector count
        10,           // Stack count
        glm::vec3(0.2f, 0.2f, 0.2f), // Ambient color
        glm::vec3(0.8f, 0.8f, 0.8f), // Diffuse color
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color
        32.0f,        // Shininess
        c1, // Diffuse texture ID
        c2 // Specular texture ID
    );

    string cake1111 = "ctex.jpg";  // Front face texture (e.g., with a lock)
    string cake2222 = "ctex.jpg";
    unsigned int d1 = loadTexture2(cake1111.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int d2 = loadTexture2(cake2222.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    CylinderWithTexture ccake(
        1.0f,         // Base radius
        1.0f,         // Top radius
        2.0f,         // Height
        36,           // Sector count
        10,           // Stack count
        glm::vec3(0.2f, 0.2f, 0.2f), // Ambient color
        glm::vec3(0.8f, 0.8f, 0.8f), // Diffuse color
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color
        32.0f,        // Shininess
        d1, // Diffuse texture ID
        d2 // Specular texture ID
    );
    
    string cakes1= "ctex.jpg";  // Front face texture (e.g., with a lock)
    string cakes2 = "ctex.jpg";
    unsigned int e1 = loadTexture2(cakes1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int e2 = loadTexture2(cakes2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cakesq = Cube(e1, e2, 32.0f);  // shininess = 32.0f

    string cakes3 = "red_v.jpg";  // Front face texture (e.g., with a lock)
    string cakes4 = "red_v.jpg";
    unsigned int f1 = loadTexture2(cakes3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int f2 = loadTexture2(cakes4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cakesq1 = Cube(f1, f2 , 32.0f);  // shininess = 32.0f

    string cakes5 = "floor1.jpg";  // Front face texture (e.g., with a lock)
    string cakes6 = "floor1.jpg";
    unsigned int g1 = loadTexture2(cakes5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int g2 = loadTexture2(cakes6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cakesq2 = Cube(g1, g2, 32.0f);  // shininess = 32.0f

    string cakes7 = "vtex.jpg";  // Front face texture (e.g., with a lock)
    string cakes8 = "vtex.jpg";
    unsigned int h1 = loadTexture2(cakes7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int h2 = loadTexture2(cakes8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cakesq3 = Cube(h1, h2, 32.0f);  // shininess = 32.0f

    Sphere spheres[] = {
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(1.0f, 0.6f, 0.2f), glm::vec3(1.0f, 0.7f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)
    };

    Sphere spheres1[] = {
    Sphere(0.5f, 36, 18, glm::vec3(0.7f, 0.1f, 0.2f), glm::vec3(0.8f, 0.2f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(0.7f, 0.1f, 0.2f), glm::vec3(0.8f, 0.2f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(0.7f, 0.1f, 0.2f), glm::vec3(0.8f, 0.2f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(0.7f, 0.1f, 0.2f), glm::vec3(0.8f, 0.2f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(0.7f, 0.1f, 0.2f), glm::vec3(0.8f, 0.2f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(0.7f, 0.1f, 0.2f), glm::vec3(0.8f, 0.2f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f),
    Sphere(0.5f, 36, 18, glm::vec3(0.7f, 0.1f, 0.2f), glm::vec3(0.8f, 0.2f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f)
    };

    //table texture
    string t1 = "wood.jpg";
    string t2 = "wood.jpg";
    unsigned int tt1 = loadTexture(t1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int tt2 = loadTexture(t2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube ttop1 = Cube(tt1, tt2, 32.0f);
    Cube ttop2 = Cube(tt1, tt2, 32.0f);
    Cube ttop3 = Cube(tt1, tt2, 32.0f);
    Cube ttop4 = Cube(tt1, tt2, 32.0f);




    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);
        pointlight5.setUpPointLight(lightingShader);
        pointlight6.setUpPointLight(lightingShader);


        lightingShader.setVec3("diectionalLight.directiaon", 0.0f, 3.0f, 0.0f);
        lightingShader.setVec3("diectionalLight.ambient", .2, .2, .2);
        lightingShader.setVec3("diectionalLight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("diectionalLight.specular", 1.0f, 1.0f, 1.0f);




        lightingShader.setBool("dlighton", true);


        lightingShader.setVec3("spotlight.position", -0.5, 1, -0.5);
        lightingShader.setVec3("spotlight.direction", 0, -1, 0);
        lightingShader.setVec3("spotlight.ambient", .2, .2, .2);
        lightingShader.setVec3("spotlight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotlight.k_c", 1.0f);
        lightingShader.setFloat("spotlight.k_l", 0.09);
        lightingShader.setFloat("spotlight.k_q", 0.032);
        lightingShader.setFloat("cos_theta", glm::cos(glm::radians(5.5f)));
        lightingShader.setBool("spotlighton", true);


        //pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
        //    1.0f, 1.0f, 1.0f,     // ambient
        //    1.0f, 1.0f, 1.0f,      // diffuse
        //    1.0f, 1.0f, 1.0f,        // specular
        //    1.0f,   //k_c
        //    0.09f,  //k_l
        //    0.032f, //k_q
        //    1,       // light number
        //    glm::cos(glm::radians(20.5f)),
        //    glm::cos(glm::radians(25.0f)),
        //    0, -1, 0
        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);
        //bool isBasicView = true;

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();

        glm::mat4 view;
        if (isBasicView)
        {
            view = basic_camera.createViewMatrix();  // Basic camera view
        }
        else
        {
            // Alternative view logic (e.g., bird's-eye view or any other camera view)
            view = camera.GetViewMatrix();
        }

        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        wall(cubeVAO, lightingShader, model);
        table(cubeVAO, lightingShader, model);
        //coffee(cubeVAO, lightingShader, model);

        //cylinder cake
        Cylinder cylinder = Cylinder();
        translateMatrix = glm::translate(model, glm::vec3(-.80f, -0.6f, 1.5f));
        scaleMatrix = glm::scale(translateMatrix, glm::vec3(0.1f, 0.15f, 0.15f));
        cylinder.drawCylinder(lightingShader, scaleMatrix);

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 6; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.4f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);



        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        pointlight6.setUpPointLight(lightingShaderWithTexture);

        //floor
        glm::mat4 floor1 = glm::mat4(1.0f);
        floor1 = glm::translate(floor1, glm::vec3(-3.7f, -2.5f, -7.0f));
        floor1 = glm::scale(floor1, glm::vec3(17.0f, 0.2f, 11.0f)); // Scale example
        floor.drawCubeWithTexture(lightingShaderWithTexture, floor1);
        
        //floor of grass
        glm::mat4 floor2 = glm::mat4(1.0f);
        floor2 = glm::translate(floor2, glm::vec3(-4.7f, -2.7f, -8.0f));
        floor2 = glm::scale(floor2, glm::vec3(19.0f, 0.2f, 13.0f)); // Scale example
        floor_grass.drawCubeWithTexture(lightingShaderWithTexture, floor2);

        
        //chad of cake
        glm::mat4 chad1 = glm::mat4(1.0f);
        chad1 = glm::translate(chad1, glm::vec3(-3.7f, 2.5f, -7.0f));
        chad1 = glm::scale(chad1, glm::vec3(10.5f, 0.25f, 3.20f)); // Scale example
        //chad1 = glm::rotate(chad1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        chad1 = glm::rotate(chad1, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        chad_cake.drawCubeWithTexture(lightingShaderWithTexture, chad1);

        

        //cake wall
        glm::mat4 wallc = glm::mat4(1.0f);
        wallc = glm::translate(wallc, glm::vec3(-3.7f, -2.5f, -7.0f));
        wallc = glm::scale(wallc, glm::vec3(10.5f, 5.0f, .20f)); // Scale example
        //chad1 = glm::rotate(chad1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //wall_c = glm::rotate(wall_c, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        wallw.drawCubeWithTexture(lightingShaderWithTexture, wallc);

        //wall of coffee
        glm::mat4 wall_c = glm::mat4(1.0f);
        wall_c = glm::translate(wall_c, glm::vec3(12.5f, -2.5f, -5.0f));
        wall_c = glm::scale(wall_c, glm::vec3(.25f, 5.0f, 8.0f)); // Scale example
        //chad1 = glm::rotate(chad1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //wall_c = glm::rotate(wall_c, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        wall_coffee.drawCubeWithTexture(lightingShaderWithTexture, wall_c);

        //chad of coffee
        glm::mat4 chad2 = glm::mat4(1.0f);
        chad2 = glm::translate(chad2, glm::vec3(10.7f, 2.5f, -5.0f));
        chad2 = glm::scale(chad2, glm::vec3(3.5f, .25f, 8.20f)); // Scale example
        //chad1 = glm::rotate(chad1, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        chad2 = glm::rotate(chad2, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        chad_coffee.drawCubeWithTexture(lightingShaderWithTexture, chad2);



        //misty
        glm::mat4 mistyBase = glm::mat4(1.0f); // Start with the identity matrix
        float startX = 2.0f;                   // Starting x-coordinate
        float stepX = 0.1f;                    // Distance between spheres along x-axis
        float startZ = -2.8f;                  // Starting z-coordinate
        float stepZ = 0.1f;                    // Distance between rows along z-axis
        int rows = 5;                          // Number of rows along z-axis
        int spheresPerRow = 7;                 // Number of spheres per row along x-axis

        for (int row = 0; row < rows; ++row) { // Outer loop for rows along z-axis
            for (int i = 0; i < spheresPerRow; ++i) { // Inner loop for spheres in a row along x-axis
                glm::mat4 misty = glm::translate(
                    mistyBase,
                    glm::vec3(startX + i * stepX, -0.40f, startZ - row * stepZ) // Adjust x and z
                );
                misty = glm::scale(misty, glm::vec3(0.1f, 0.1f, 0.1f)); // Scale each sphere

                spheres[i].drawSphere(lightingShader, misty); // Draw each sphere
            }
        }

        glm::mat4 mistyBase1 = glm::mat4(1.0f); // Start with the identity matrix
        float startX1 = 2.0f;                   // Starting x-coordinate
        float stepX1 = 0.1f;                    // Distance between spheres along x-axis
        float startZ1 = -3.8f;                  // Starting z-coordinate
        float stepZ1 = 0.1f;                    // Distance between rows along z-axis
        int rows1 = 5;                          // Number of rows along z-axis
        int spheresPerRow1 = 7;                 // Number of spheres per row along x-axis

        for (int row = 0; row < rows1; ++row) { // Outer loop for rows along z-axis
            for (int i = 0; i < spheresPerRow1; ++i) { // Inner loop for spheres in a row along x-axis
                glm::mat4 misty1 = glm::translate(
                    mistyBase1,
                    glm::vec3(startX1 + i * stepX1, -0.40f, startZ1 - row * stepZ1) // Adjust x and z
                );
                misty1 = glm::scale(misty1, glm::vec3(0.1f, 0.1f, 0.1f)); // Scale each sphere

                spheres1[i].drawSphere(lightingShader, misty1); // Draw each sphere
            }
        }

        


        //cakes
        glm::mat4 cy1 = glm::mat4(1.0f);
        //glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        //Cylinder cake1 = Cylinder();
        cy1 = glm::translate(cy1, glm::vec3(-1.3f, -0.2f, -4.0f));
        cy1 = glm::scale(cy1, glm::vec3(.25f, 0.3f, .25f));
        glm::vec3 viewPos = glm::vec3(2.0f, 0.0f, 0.0f);
        //lightingShader.setVec3("viewPos", viewPos);
        cake.drawCylinder(lightingShaderWithTexture, cy1, viewPos);
       
        glm::mat4 cy2 = glm::mat4(1.0f);
        cy2 = glm::translate(cy2, glm::vec3(-1.3f, -0.2f, -3.0f));
        cy2 = glm::scale(cy2, glm::vec3(.25f, 0.3f, .25f));
        glm::vec3 viewPos1 = glm::vec3(2.0f, 0.0f, 0.0f);
        acake.drawCylinder(lightingShaderWithTexture, cy2, viewPos1);

        glm::mat4 cy3 = glm::mat4(1.0f);
        cy3 = glm::translate(cy3, glm::vec3(-0.5f, -0.2f, -4.0f));
        cy3 = glm::scale(cy3, glm::vec3(.25f, 0.3f, .25f));
        glm::vec3 viewPos2 = glm::vec3(2.0f, 0.0f, 0.0f);
        bcake.drawCylinder(lightingShaderWithTexture, cy3, viewPos2);

        glm::mat4 cy4 = glm::mat4(1.0f);
        cy4 = glm::translate(cy4, glm::vec3(-0.5f, -0.2f, -3.0f));
        cy4 = glm::scale(cy4, glm::vec3(.25f, 0.3f, .25f));
        glm::vec3 viewPos3 = glm::vec3(2.0f, 0.0f, 0.0f);
        ccake.drawCylinder(lightingShaderWithTexture, cy4, viewPos3);

        glm::mat4 cy5 = glm::mat4(1.0f);
        cy5 = glm::translate(cy5, glm::vec3(0.25f, -0.5f, -3.1f));
        cy5 = glm::scale(cy5, glm::vec3(0.5f, .5f, 0.3f)); // Scale example
        cakesq.drawCubeWithTexture(lightingShaderWithTexture, cy5);

        glm::mat4 cy6 = glm::mat4(1.0f);
        cy6 = glm::translate(cy6, glm::vec3(0.25f, -0.5f, -4.1f));
        cy6 = glm::scale(cy6, glm::vec3(0.5f, .5f, 0.3f)); // Scale example
        cakesq1.drawCubeWithTexture(lightingShaderWithTexture, cy6);

        glm::mat4 cy7 = glm::mat4(1.0f);
        cy7 = glm::translate(cy7, glm::vec3(1.05f, -0.5f, -4.1f));
        cy7 = glm::scale(cy7, glm::vec3(0.5f, .5f, 0.3f)); // Scale example
        cakesq2.drawCubeWithTexture(lightingShaderWithTexture, cy7);

        glm::mat4 cy8 = glm::mat4(1.0f);
        cy8 = glm::translate(cy8, glm::vec3(1.05f, -0.5f, -3.1f));
        cy8 = glm::scale(cy8, glm::vec3(0.5f, .5f, 0.3f)); // Scale example
        cakesq3.drawCubeWithTexture(lightingShaderWithTexture, cy8);

        /* try will later
        Cylinder c1 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 ck1 = glm::mat4(1.0f);
        ck1 = glm::rotate(ck1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        ck1 = glm::translate(ck1, glm::vec3(1.5f, -0.3f, 1.4f));
        ck1 = glm::scale(ck1, glm::vec3(.15f, 0.2f, 0.2f));
        c1.drawCylinder(lightingShader, ck1);
        */


        //tv
        glm::mat4 tv1 = glm::mat4(1.0f);
        tv1 = glm::rotate(tv1, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        tv1 = glm::translate(tv1, glm::vec3(-1.0f, .05f, -3.5f));
        tv1 = glm::scale(tv1, glm::vec3(5.0f, 1.8f, .25f)); // Scale example
        tv.drawCubeWithTexture(lightingShaderWithTexture, tv1);
       
        //desk for cake
        glm::mat4 d1 = glm::mat4(1.0f);
        d1 = glm::translate(d1, glm::vec3(-2.0f, -2.5f, -4.5f));
        d1 = glm::scale(d1, glm::vec3(6.2f, 2.0f, 2.0f)); // Scale example
        desk.drawCubeWithTexture(lightingShaderWithTexture, d1);

        
        //desk of coffee
        glm::mat4 d2 = glm::mat4(1.0f);
        d2 = glm::translate(d2, glm::vec3(9.0f, -2.5f, -2.5f));
        d2 = glm::scale(d2, glm::vec3(2.2f, 2.0f, 5.0f)); // Scale example
        desk2.drawCubeWithTexture(lightingShaderWithTexture, d2);

        //menu
        glm::mat4 m1 = glm::mat4(1.0f);
        m1 = glm::rotate(m1, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m1 = glm::translate(m1, glm::vec3(9.5f, -2.5f, 2.0f));
        m1 = glm::scale(m1, glm::vec3(0.1f, 3.5f, 2.0f)); // Scale example
        //m1 = glm::rotate(m1, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        menu.drawCubeWithTexture(lightingShaderWithTexture, m1);

        /*
        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(1.5f, -2.5f, -1.5f));
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);*/

        /*
        //walmate
        glm::mat4 walmate = glm::mat4(1.0f);
        walmate = glm::translate(identityMatrix, glm::vec3(-2.5f, .05f, -1.0f));
        walmate = glm::scale(walmate, glm::vec3(0.05f, 2.0f, 1.5f)); // Scale example
        cube1.drawCubeWithTexture(lightingShaderWithTexture, walmate);
        */

        /*
        glm::mat4 floor = glm::mat4(1.0f);
        floor = glm::translate(identityMatrix, glm::vec3(-2.7f, -2.5f, -3.0f));
        floor = glm::scale(floor, glm::vec3(5.5f, 0.2f, 6.0f)); // Scale example
        cube2.drawCubeWithTexture(lightingShaderWithTexture, floor);
        */


        Cylinder cup1 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup11 = glm::mat4(1.0f);
        cup11 = glm::translate(cup11, glm::vec3(9.5f, -0.3f, 0.80f));
        cup11 = glm::scale(cup11, glm::vec3(.15f, 0.2f, 0.12f));
        cup1.drawCylinder(lightingShader, cup11);

        Cylinder cup2 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup22 = glm::mat4(1.0f);
        cup22 = glm::translate(cup22, glm::vec3(9.5f, -0.3f, 1.1f));
        cup22 = glm::scale(cup22, glm::vec3(.15f, 0.2f, 0.12f));
        cup2.drawCylinder(lightingShader, cup22);

        Cylinder cup3 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup33 = glm::mat4(1.0f);
        cup33 = glm::translate(cup33, glm::vec3(9.5f, -0.3f, 1.4f));
        cup33 = glm::scale(cup33, glm::vec3(.15f, 0.2f, 0.12f));
        cup3.drawCylinder(lightingShader, cup33);

        Cylinder cup4 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup44 = glm::mat4(1.0f);
        cup44 = glm::translate(cup44, glm::vec3(9.5f, -0.3f, 1.7f));
        cup44 = glm::scale(cup44, glm::vec3(.15f, 0.2f, 0.12f));
        cup4.drawCylinder(lightingShader, cup44);

        Cylinder cup5 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup55 = glm::mat4(1.0f);
        cup55 = glm::translate(cup55, glm::vec3(9.5f, -0.3f, 2.0f));
        cup55 = glm::scale(cup55, glm::vec3(.15f, 0.2f, 0.12f));
        cup5.drawCylinder(lightingShader, cup55);

        Cylinder cup6 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup66 = glm::mat4(1.0f);
        cup66 = glm::translate(cup66, glm::vec3(9.5f, 0.1f, 0.93f));
        cup66 = glm::scale(cup66, glm::vec3(.15f, 0.2f, 0.12f));
        cup6.drawCylinder(lightingShader, cup66);

        Cylinder cup7 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup77 = glm::mat4(1.0f);
        cup77 = glm::translate(cup77, glm::vec3(9.5f, 0.1f, 1.23f));
        cup77 = glm::scale(cup77, glm::vec3(.15f, 0.2f, 0.12f));
        cup7.drawCylinder(lightingShader, cup77);

        Cylinder cup8 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup88 = glm::mat4(1.0f);
        cup88 = glm::translate(cup88, glm::vec3(9.5f, 0.1f, 1.53f));
        cup88 = glm::scale(cup88, glm::vec3(.15f, 0.2f, 0.12f));
        cup8.drawCylinder(lightingShader, cup88);

        Cylinder cup9 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup99 = glm::mat4(1.0f);
        cup99 = glm::translate(cup99, glm::vec3(9.5f, 0.1f, 1.83f));
        cup99 = glm::scale(cup99, glm::vec3(.15f, 0.2f, 0.12f));
        cup9.drawCylinder(lightingShader, cup99);

        Cylinder cup10 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup100 = glm::mat4(1.0f);
        cup100 = glm::translate(cup100, glm::vec3(9.5f, 0.5f, 1.08f));
        cup100 = glm::scale(cup100, glm::vec3(.15f, 0.2f, 0.12f));
        cup10.drawCylinder(lightingShader, cup100);

        Cylinder cup101 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup1001 = glm::mat4(1.0f);
        cup1001 = glm::translate(cup1001, glm::vec3(9.5f, 0.5f, 1.38f));
        cup1001 = glm::scale(cup1001, glm::vec3(.15f, 0.2f, 0.12f));
        cup101.drawCylinder(lightingShader, cup1001);

        Cylinder cup102 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup1002 = glm::mat4(1.0f);
        cup1002 = glm::translate(cup1002, glm::vec3(9.5f, 0.5f, 1.68f));
        cup1002 = glm::scale(cup1002, glm::vec3(.15f, 0.2f, 0.12f));
        cup102.drawCylinder(lightingShader, cup1002);

        Cylinder cup20 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup1000 = glm::mat4(1.0f);
        cup1000 = glm::translate(cup1000, glm::vec3(9.5f, 0.9f, 1.23f));
        cup1000 = glm::scale(cup1000, glm::vec3(.15f, 0.2f, 0.12f));
        cup20.drawCylinder(lightingShader, cup1000);

        Cylinder cup201 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cup200 = glm::mat4(1.0f);
        cup200 = glm::translate(cup200, glm::vec3(9.5f, 0.9f, 1.55f));
        cup200 = glm::scale(cup200, glm::vec3(.15f, 0.2f, 0.12f));
        cup201.drawCylinder(lightingShader, cup200);

        Cylinder FINAL_CUP = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
        glm::mat4 cupf = glm::mat4(1.0f);
        cupf = glm::translate(cupf, glm::vec3(9.5f, 1.3f, 1.4f));
        cupf = glm::scale(cupf, glm::vec3(.15f, 0.2f, 0.12f));
        FINAL_CUP.drawCylinder(lightingShader, cupf);

        

        //tables
        glm::mat4 tb1 = glm::mat4(1.0f);
        tb1 = glm::translate(tb1, glm::vec3(-1.5f, -1.0f, 1.0f));
        tb1 = glm::scale(tb1, glm::vec3(1.0f, 0.2f, 1.5f)); // Scale example
        ttop1.drawCubeWithTexture(lightingShaderWithTexture, tb1);

        glm::mat4 tb2 = glm::mat4(1.0f);
        tb2 = glm::translate(tb2, glm::vec3(1.0f, -1.0f, 1.0f));
        tb2 = glm::scale(tb2, glm::vec3(1.0f, 0.2f, 1.5f)); // Scale example
        ttop2.drawCubeWithTexture(lightingShaderWithTexture, tb2);

        glm::mat4 tb3 = glm::mat4(1.0f);
        tb3 = glm::translate(tb3, glm::vec3(3.5f, -1.0f, 1.0f));
        tb3 = glm::scale(tb3, glm::vec3(1.0f, 0.2f, 1.5f)); // Scale example
        ttop3.drawCubeWithTexture(lightingShaderWithTexture, tb3);

        glm::mat4 tb4 = glm::mat4(1.0f);
        tb4 = glm::translate(tb4, glm::vec3(6.0f, -1.0f, 1.0f));
        tb4 = glm::scale(tb4, glm::vec3(1.0f, 0.2f, 1.5f)); // Scale example
        ttop4.drawCubeWithTexture(lightingShaderWithTexture, tb4);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r , g, b));
    lightingShader.setVec3("material.specular", glm::vec3(r, g, b));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void wall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
   
    //stck for light
    glm::mat4 l1 = glm::mat4(1.0f);
    glm::mat4 lt1, ls1, lr1, modell1;
    lt1 = glm::translate(l1, glm::vec3(-3.9f, -2.5f, 4.0f));
    ls1 = glm::scale(l1, glm::vec3(.25f, 6.0f, .25f));
    modell1 = lt1 * ls1;
    drawCube(cubeVAO, lightingShader, modell1, 0.0f, 0.0f, 0.0f);

    glm::mat4 st1 = glm::mat4(1.0f);
    glm::mat4 tst1, sst1, modelst;
    tst1 = glm::translate(st1, glm::vec3(-3.9f, 2.8f, 4.0f));
    sst1 = glm::scale(st1, glm::vec3(0.2f, 0.2f, -1.25f));
    modelst = tst1 * sst1;
    drawCube(cubeVAO, lightingShader, modelst, 0.0f, 0.0f, 0.0f);

    glm::mat4 st11 = glm::mat4(1.0f);
    glm::mat4 tst11, sst11, modelst1;
    tst11 = glm::translate(st11, glm::vec3(-3.9f, 2.8f, 3.0f));
    sst11 = glm::scale(st11, glm::vec3(0.2f, -0.5f, -.25f));
    modelst1 = tst11 * sst11;
    drawCube(cubeVAO, lightingShader, modelst1, 0.0f, 0.0f, 0.0f);

    //light 2
    glm::mat4 l2 = glm::mat4(1.0f);
    glm::mat4 lt2, ls2, lr2, modell2;
    lt2 = glm::translate(l2, glm::vec3(12.9f, -2.5f, -7.1f));
    ls2 = glm::scale(l2, glm::vec3(.25f, 6.0f, .25f));
    modell2 = lt2 * ls2;
    drawCube(cubeVAO, lightingShader, modell2, 0.0f, 0.0f, 0.0f);

    glm::mat4 st2 = glm::mat4(1.0f);
    glm::mat4 tst2, sst2, modelst12;
    tst2 = glm::translate(st2, glm::vec3(12.9f, 2.5f, -7.1f));
    sst2 = glm::scale(st2, glm::vec3(-1.25f, 0.2f, .2f));
    modelst12 = tst2 * sst2;
    drawCube(cubeVAO, lightingShader, modelst12, 0.0f, 0.0f, 0.0f);

    glm::mat4 st3 = glm::mat4(1.0f);
    glm::mat4 tst3, sst3, modelst3;
    tst3 = glm::translate(st3, glm::vec3(11.9f, 2.5f, -7.0f));
    sst3 = glm::scale(st3, glm::vec3(0.2f, -0.5f, -.25f));
    modelst3 = tst3 * sst3;
    drawCube(cubeVAO, lightingShader, modelst3, 0.0f, 0.0f, 0.0f);

    //for 3
    glm::mat4 l3 = glm::mat4(1.0f);
    glm::mat4 lt3, ls3, lr3, modell3;
    lt3 = glm::translate(l3, glm::vec3(3.8f, -2.5f, 4.0f));
    ls3 = glm::scale(l3, glm::vec3(.25f, 6.0f, .25f));
    modell3 = lt3 * ls3;
    drawCube(cubeVAO, lightingShader, modell3, 0.0f, 0.0f, 0.0f);

    glm::mat4 st4 = glm::mat4(1.0f);
    glm::mat4 tst4, sst4, modelst4;
    tst4 = glm::translate(st4, glm::vec3(3.8f, 2.8f, 4.0f));
    sst4 = glm::scale(st1, glm::vec3(0.2f, 0.2f, -1.25f));
    modelst4 = tst4 * sst4;
    drawCube(cubeVAO, lightingShader, modelst4, 0.0f, 0.0f, 0.0f);

    glm::mat4 st21 = glm::mat4(1.0f);
    glm::mat4 tst21, sst21, modelst21;
    tst21 = glm::translate(st21, glm::vec3(3.8f, 2.8f, 3.0f));
    sst21 = glm::scale(st21, glm::vec3(0.2f, -0.5f, -.25f));
    modelst21 = tst21 * sst21;
    drawCube(cubeVAO, lightingShader, modelst21, 0.0f, 0.0f, 0.0f);

    //OUTLINE WALL for cake

    //glm::mat4 identityMatrix = glm::mat4(1.0f);
    //glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    /*
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.7f, -2.5f, -7.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.5f, 5.0f, .20f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 0.671f, 0.0f);
   */


    //stick for tv
    glm::mat4 identityMatrix1 = glm::mat4(1.0f);
    glm::mat4 translateMatrix1, scaleMatrix1, rotateMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix1, glm::vec3(-3.7f, 2.0f, -3.5f));
    scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(10.5f, 0.15f, .25f));
    model1 = translateMatrix1  * scaleMatrix1;
    drawCube(cubeVAO, lightingShader, model1, 0.0f, 0.0f, 0.0f);


    glm::mat4 identityMatrix2 = glm::mat4(1.0f);
    glm::mat4 translateMatrix2, scaleMatrix2, modelc2;
    translateMatrix2 = glm::translate(identityMatrix2, glm::vec3(-3.0f, 1.8f, -3.5f));
    scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.35f, 0.8f, .25f));
    modelc2 = translateMatrix2 * scaleMatrix2;
    drawCube(cubeVAO, lightingShader, modelc2, 0.0f, 0.0f, 0.0f);

    glm::mat4 identityMatrix12 = glm::mat4(1.0f);
    glm::mat4 translateMatrix12, scaleMatrix12, rotateMatrix12, modelc12;
    translateMatrix12 = glm::translate(identityMatrix12, glm::vec3(5.5f, 1.8f, -3.5f));
    scaleMatrix12 = glm::scale(identityMatrix12, glm::vec3(0.35f, 0.8f, .25f));
    modelc12 = translateMatrix12 * scaleMatrix12;
    drawCube(cubeVAO, lightingShader, modelc12, 0.0f, 0.0f, 0.0f);
    //set up for tv

    
    
    
    //stick for light of coffee
    glm::mat4 light = glm::mat4(1.0f);
    glm::mat4 tlight, slight, modelight;
    tlight = glm::translate(light, glm::vec3(10.7f, 2.0f, -4.5f));
    slight = glm::scale(light, glm::vec3(0.5f, 0.15f, 8.0f));
    modelight = tlight * slight;
    drawCube(cubeVAO, lightingShader, modelight, 0.0f, 0.0f, 0.0f);

    glm::mat4 light12 = glm::mat4(1.0f);
    glm::mat4 tlight12, slight12, modelight2;
    tlight12 = glm::translate(light12, glm::vec3(10.7f, 1.8f, -3.5f));
    slight12 = glm::scale(light12, glm::vec3(0.35f, 0.8f, .25f));
    modelight2 = tlight12 * slight12;
    drawCube(cubeVAO, lightingShader, modelight2, 0.0f, 0.0f, 0.0f);

    glm::mat4 light112 = glm::mat4(1.0f);
    glm::mat4 tlight112, slight112, modelight12;
    tlight112 = glm::translate(light112, glm::vec3(10.7f, 1.8f, 2.5f));
    slight112 = glm::scale(light112, glm::vec3(0.35f, 0.8f, .25f));
    modelight12 = tlight112 * slight112;
    drawCube(cubeVAO, lightingShader, modelight12, 0.0f, 0.0f, 0.0f);

    glm::mat4 light1112 = glm::mat4(1.0f);
    glm::mat4 tlight1112, slight1112, modelight112;
    tlight1112 = glm::translate(light1112, glm::vec3(10.7f, 2.0f, -0.9f));
    slight1112 = glm::scale(light1112, glm::vec3(0.35f, -0.2f, .25f));
    modelight112 = tlight1112 * slight1112;
    drawCube(cubeVAO, lightingShader, modelight112, 0.0f, 0.0f, 0.0f);


    
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //plates for cake
    glm::mat4 cy1 = glm::mat4(1.0f);
    Cylinder plt1 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    cy1 = glm::translate(cy1, glm::vec3(-1.3f, -0.5f, -4.0f));
    cy1 = glm::scale(cy1, glm::vec3(.35f, -0.04f, .35f));
    plt1.drawCylinder(lightingShader, cy1);
    
    glm::mat4 cy2 = glm::mat4(1.0f);
    Cylinder plt2 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    cy2 = glm::translate(cy2, glm::vec3(-1.3f, -0.5f, -3.0f));
    cy2 = glm::scale(cy2, glm::vec3(.35f, -0.04f, .35f));
    plt2.drawCylinder(lightingShader, cy2);

    glm::mat4 cy3 = glm::mat4(1.0f);
    Cylinder plt3 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    cy3 = glm::translate(cy3, glm::vec3(-0.5f, -0.5f, -4.0f));
    cy3 = glm::scale(cy3, glm::vec3(.35f, -0.04f, .35f));
    plt3.drawCylinder(lightingShader, cy3);

    glm::mat4 cy4 = glm::mat4(1.0f);
    Cylinder plt4 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    cy4 = glm::translate(cy4, glm::vec3(-0.5f, -0.5f, -3.0f));
    cy4 = glm::scale(cy4, glm::vec3(.35f, -0.04f, .35f));
    plt4.drawCylinder(lightingShader, cy4);
    
    glm::mat4 cy5 = glm::mat4(1.0f);
    Cylinder plt5 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    cy5 = glm::translate(cy5, glm::vec3(0.5f, -0.5f, -3.0f));
    cy5 = glm::scale(cy5, glm::vec3(.35f, -0.04f, .35f));
    plt5.drawCylinder(lightingShader, cy5);

    glm::mat4 cy6 = glm::mat4(1.0f);
    Cylinder plt6 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    cy6 = glm::translate(cy6, glm::vec3(0.5f, -0.5f, -4.0f));
    cy6 = glm::scale(cy6, glm::vec3(.35f, -0.04f, .35f));
    plt6.drawCylinder(lightingShader, cy6);

    glm::mat4 cy7 = glm::mat4(1.0f);
    Cylinder plt7 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    cy7 = glm::translate(cy7, glm::vec3(1.3f, -0.5f, -3.0f));
    cy7 = glm::scale(cy7, glm::vec3(.35f, -0.04f, .35f));
    plt7.drawCylinder(lightingShader, cy7);

    glm::mat4 cy8 = glm::mat4(1.0f);
    Cylinder plt8 = Cylinder(1.0f, 0.5f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    cy8 = glm::translate(cy8, glm::vec3(1.3f, -0.5f, -4.0f));
    cy8 = glm::scale(cy8, glm::vec3(.35f, -0.04f, .35f));
    plt8.drawCylinder(lightingShader, cy8);

    glm::mat4 misty = glm::mat4(1.0f);
    Cylinder mistypl = Cylinder(1.2f, 0.3f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    misty = glm::translate(misty, glm::vec3(2.3f, -0.5f, -4.0f));
    misty = glm::scale(misty, glm::vec3(.35f, -0.04f, .35f));
    mistypl.drawCylinder(lightingShader, misty);

    glm::mat4 misty1 = glm::mat4(1.0f);
    Cylinder mistypl1 = Cylinder(1.2f, 0.3f, 2.0f, 20, 1, glm::vec3(0.95f, 0.95f, 0.90f), glm::vec3(0.98f, 0.98f, 0.92f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    misty1 = glm::translate(misty1, glm::vec3(2.3f, -0.5f, -3.0f));
    misty1 = glm::scale(misty1, glm::vec3(.35f, -0.04f, .35f));
    mistypl1.drawCylinder(lightingShader, misty1);

    

    //coffee machine
    glm::mat4 cm_b = glm::mat4(1.0f);
    glm::mat4 cmtb, cmsb, cmrb, modelcmb;
    cmtb = glm::translate(cm_b, glm::vec3(9.5f, -0.5f, -1.6f));
    cmsb = glm::scale(cm_b, glm::vec3(1.0f, 0.1f, 1.5f));
    modelcmb = cmtb * cmsb;
    drawCube(cubeVAO, lightingShader, modelcmb, 0.7f, 0.7f, 0.7f);

    Cylinder cm11 = Cylinder(1.0f, 1.0f, .5f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    glm::mat4 cm1 = glm::mat4(1.0f);
    cm1 = glm::translate(cm1, glm::vec3(9.5f, 0.45f, -1.4f));
    cm1 = glm::scale(cm1, glm::vec3(.12f, 0.12f, 0.10f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    cm11.drawCylinder(lightingShader, cm1);

    Cylinder cm13 = Cylinder(1.0f, 1.0f, .5f, 20, 1, glm::vec3(0.75f, 0.47f, 0.27f), glm::vec3(0.85f, 0.55f, 0.30f), glm::vec3(0.4f, 0.4f, 0.4f),32.0f);
    glm::mat4 cm112 = glm::mat4(1.0f);
    cm112 = glm::translate(cm112, glm::vec3(9.5f, 0.45f, -1.1f));
    cm112 = glm::scale(cm112, glm::vec3(.12f, 0.09f, 0.09f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    cm112 = glm::rotate(cm112, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    cm13.drawCylinder(lightingShader, cm112);

    Cylinder cm14 = Cylinder(1.0f, 1.0f, .5f, 20, 1, glm::vec3(0.75f, 0.47f, 0.27f), glm::vec3(0.85f, 0.55f, 0.30f), glm::vec3(0.4f, 0.4f, 0.4f), 32.0f);
    glm::mat4 cm113 = glm::mat4(1.0f);
    cm113 = glm::translate(cm113, glm::vec3(9.5f, 0.45f, -0.8f));
    cm113 = glm::scale(cm113, glm::vec3(.12f, 0.09f, 0.09f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    cm113 = glm::rotate(cm113, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    cm14.drawCylinder(lightingShader, cm113);

    Cylinder cm15 = Cylinder(1.0f, 1.0f, .5f, 20, 1, glm::vec3(0.75f, 0.47f, 0.27f), glm::vec3(0.85f, 0.55f, 0.30f), glm::vec3(0.4f, 0.4f, 0.4f), 32.0f);
    glm::mat4 cm114 = glm::mat4(1.0f);
    cm114 = glm::translate(cm114, glm::vec3(9.5f, 0.45f, -0.5f));
    cm114 = glm::scale(cm114, glm::vec3(.12f, 0.09f, 0.09f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    cm114 = glm::rotate(cm114, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    cm15.drawCylinder(lightingShader, cm114);

    Cylinder cm12 = Cylinder(1.0f, 1.0f, .5f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    glm::mat4 cm111 = glm::mat4(1.0f);
    cm111 = glm::translate(cm111, glm::vec3(9.5f, 0.45f, -0.25f));
    cm111= glm::scale(cm111, glm::vec3(.12f, 0.12f, 0.10f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    cm111 = glm::rotate(cm111, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    cm12.drawCylinder(lightingShader, cm111);

    glm::mat4 cm = glm::mat4(1.0f);
    glm::mat4 cmt, cms, cmr, modelcm;
    cmt = glm::translate(cm, glm::vec3(10.4f, -0.5f, -1.6f));
    cms = glm::scale(cm, glm::vec3(0.15f, 0.8f, 1.5f));
    modelcm = cmt * cms;
    drawCube(cubeVAO, lightingShader, modelcm, 0.2f, 0.2f, 0.2f);


    glm::mat4 cm_t = glm::mat4(1.0f);
    glm::mat4 cmtt, cmst, cmrt, modelcmt;
    cmtt = glm::translate(cm_t, glm::vec3(9.5f, 0.3f, -1.6f));
    cmst = glm::scale(cm_t, glm::vec3(1.0f, 0.3f, 1.5f));
    modelcmt = cmtt * cmst;
    drawCube(cubeVAO, lightingShader, modelcmt, 0.7f, 0.7f, 0.7f);

    Cylinder coffee_pipe = Cylinder(1.0f, 1.0f, .5f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    glm::mat4 pipe1 = glm::mat4(1.0f);
    pipe1 = glm::translate(pipe1, glm::vec3(9.7f, 0.25f, -1.4f));
    pipe1 = glm::scale(pipe1, glm::vec3(.15f, 0.20f, 0.15f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    coffee_pipe.drawCylinder(lightingShader, pipe1);

    Cylinder coffee_pipe2 = Cylinder(1.0f, 1.0f, .5f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    glm::mat4 pipe1111 = glm::mat4(1.0f);
    pipe1111 = glm::translate(pipe1111, glm::vec3(9.7f, 0.23f, -1.4f));
    pipe1111 = glm::scale(pipe1111, glm::vec3(.12f, 0.45f, 0.12f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    coffee_pipe2.drawCylinder(lightingShader, pipe1111);


    Cylinder coffee_pipe1 = Cylinder(1.0f, 1.0f, .5f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    glm::mat4 pipe11 = glm::mat4(1.0f);
    pipe11 = glm::translate(pipe11, glm::vec3(9.7f, 0.24f, -0.4f));
    pipe11 = glm::scale(pipe11, glm::vec3(.15f, 0.23f, 0.15f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    coffee_pipe1.drawCylinder(lightingShader, pipe11);

    Cylinder coffee_pipe12 = Cylinder(1.0f, 1.0f, .5f, 20, 1, glm::vec3(0.55f, 0.27f, 0.07f), glm::vec3(0.65f, 0.35f, 0.10f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
    glm::mat4 pipe111 = glm::mat4(1.0f);
    pipe111 = glm::translate(pipe111, glm::vec3(9.7f, 0.23f, -0.4f));
    pipe111 = glm::scale(pipe111, glm::vec3(.12f, 0.45f, 0.12f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //cm1 = glm::rotate(cm1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    coffee_pipe12.drawCylinder(lightingShader, pipe111);

    //COFFEE MACHINE DONE

    //cup upon machine

    Hemisphere cup_upon2(
        1.0f,                        // Radius
        36,                          // Sector count (number of slices)
        18,                          // Stack count (number of layers)
        glm::vec3(0.1f, 0.1f, 0.1f), // Ambient color
        glm::vec3(0.5f, 0.5f, 0.5f), // Diffuse color
        glm::vec3(0.1f, 0.1f, 0.1f), // Specular color
        glm::vec3(0.0f, 0.0f, 0.0f), // Emissive color
        32.0f                        // Shininess
    );

    glm::mat4 cupupon2 = glm::mat4(1.0f);
    glm::mat4 cupupon22 = glm::translate(cupupon2, glm::vec3(10.0f, 0.83f, -0.3f)); // Position
    glm::mat4 cupon2 = glm::scale(cupupon22, glm::vec3(.15f, -.25f, .15f)); // Scaling
    cup_upon2.drawHemiSphere(lightingShader, cupon2);

    Hemisphere cup_upon(
        1.0f,                        // Radius
        36,                          // Sector count (number of slices)
        18,                          // Stack count (number of layers)
        glm::vec3(0.1f, 0.1f, 0.1f), // Ambient color
        glm::vec3(0.5f, 0.5f, 0.5f), // Diffuse color
        glm::vec3(0.1f, 0.1f, 0.1f), // Specular color
        glm::vec3(0.0f, 0.0f, 0.0f), // Emissive color
        32.0f                        // Shininess
    );

    glm::mat4 cupupon = glm::mat4(1.0f);
    glm::mat4 cupupon1 = glm::translate(cupupon, glm::vec3(10.0f, 0.83f, -0.8f)); // Position
    glm::mat4 cupon = glm::scale(cupupon1, glm::vec3(.15f, -.25f, .15f)); // Scaling
    cup_upon.drawHemiSphere(lightingShader, cupon);

    Hemisphere cup_upon1(
        1.0f,                        // Radius
        36,                          // Sector count (number of slices)
        18,                          // Stack count (number of layers)
        glm::vec3(0.1f, 0.1f, 0.1f), // Ambient color
        glm::vec3(0.5f, 0.5f, 0.5f), // Diffuse color
        glm::vec3(0.1f, 0.1f, 0.1f), // Specular color
        glm::vec3(0.0f, 0.0f, 0.0f), // Emissive color
        32.0f                        // Shininess
    );

    glm::mat4 cupupon11 = glm::mat4(1.0f);
    glm::mat4 cupupon111 = glm::translate(cupupon11, glm::vec3(10.0f, 0.83f, -1.3f)); // Position
    glm::mat4 cupon1 = glm::scale(cupupon111, glm::vec3(.15f, -.25f, .15f)); // Scaling
    cup_upon1.drawHemiSphere(lightingShader, cupon1);

    Hemisphere coffee_cup(
        1.0f,                        // Radius
        36,                          // Sector count (number of slices)
        18,                          // Stack count (number of layers)
        glm::vec3(0.1f, 0.1f, 0.1f), // Ambient color
        glm::vec3(0.5f, 0.5f, 0.5f), // Diffuse color
        glm::vec3(0.1f, 0.1f, 0.1f), // Specular color
        glm::vec3(0.0f, 0.0f, 0.0f), // Emissive color
        32.0f                        // Shininess
    );

    glm::mat4 cupupon3 = glm::mat4(1.0f);
    glm::mat4 cupupon33 = glm::translate(cupupon3, glm::vec3(9.8f, -0.2f, -1.4f)); // Position
    glm::mat4 cupon3 = glm::scale(cupupon33, glm::vec3(.15f, -.25f, .15f)); // Scaling
    coffee_cup.drawHemiSphere(lightingShader, cupon3);


    // Initialize necessary variables for position and animation control
    glm::vec3 coffeeMachineBasePos = glm::vec3(9.7f, 0.0f, 0.1f); // Example base position of the coffee machine
    float pipeYOffset = 0.5f;  // Adjust the vertical offset of the pipes
    float outletZStart = -1.5f; // Starting Z-position for the outlets
    float outletSpacing = 0.5f; // Space between the outlets

    // Coffee pouring animation (static variables to maintain state)
    static float pourHeight = 0.0f;  // Maintain pour height across frames
    float pourSpeed = 0.02f;          // Speed of the coffee pouring
    float maxPourHeight = 0.5f;       // Maximum pour height before resetting

    // Update pour height (simulate movement)
    pourHeight += pourSpeed;
    if (pourHeight > maxPourHeight) {
        pourHeight = 0.0f; // Reset the pour height when it reaches max
    }

    // Define the coffee pouring cylinder
    Cylinder coffeePour(
        1.0f, 1.0f, 0.2f, 20, 1,
        glm::vec3(0.55f, 0.27f, 0.07f), // Ambient color (brownish coffee)
        glm::vec3(0.65f, 0.35f, 0.10f), // Diffuse color (slightly lighter brown)
        glm::vec3(0.2f, 0.2f, 0.2f),    // Specular color (dark for more matte look)
        32.0f                         // Shininess (relatively low for matte)
    );

    // Loop for multiple outlets
    for (int i = 0; i < 1; i++) // 3 outlets for coffee pouring
    {
        glm::mat4 pourModel = glm::mat4(1.0f); // Start with identity matrix

        // Adjust the translation to include dynamic height (pourHeight)
        pourModel = glm::translate(
            pourModel,
            coffeeMachineBasePos + glm::vec3(0.0f, pipeYOffset - pourHeight, outletZStart + i * outletSpacing)
        );

        // Scale the coffee stream to make it narrow and long
        pourModel = glm::scale(pourModel, glm::vec3(0.05f, pourHeight, 0.05f)); // narrow and elongated

        // Optional: Add a rotation if you want to simulate the pouring direction
        // pourModel = glm::rotate(pourModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // if you need rotation

        // Draw the coffee pouring cylinder using the model matrix
        coffeePour.drawCylinder(lightingShader, pourModel);
    }




    //cup
    Hemisphere hemisphere = Hemisphere();
    glm::mat4 cupid = glm::mat4(1.0f);
    glm::mat4 cup12 = glm::translate(cupid, glm::vec3(1.40f, -0.55f, 1.5f)); // Position
    glm::mat4 cup = glm::scale(cup12, glm::vec3(.15f, -.25f, .15f)); // Scaling
    hemisphere.drawHemiSphere(lightingShader, cup);

    Cylinder cup_plt = Cylinder();
    translateMatrix = glm::translate(model, glm::vec3(0.55f, .85f, 3.0f));
    scaleMatrix = glm::scale(translateMatrix, glm::vec3(.02f, 0.01f, 0.12f));
    cup_plt.drawCylinder(lightingShader, scaleMatrix);


}


void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    

  
    //table left sam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.4f, -2.5f, 1.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model =  translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table right sam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.7f, -2.5f, 1.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table left pich
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.4f, -2.5f, 2.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model =  translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table right pich
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.7f, -2.5f, 2.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model =  translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
 

    //Cylinder chair11 = Cylinder();
    Cylinder chair11 = Cylinder(
        1.0f,  // radius of the cylinder
        1.0f,  // height of the cylinder
        2.0f,  // depth of the cylinder (optional)
        20,    // slices for smoothness
        1,     // stacks for smoothness
        glm::vec3(1.0f, 0.0f, 0.0f), // Ambient color (red)
        glm::vec3(1.0f, 0.0f, 0.0f), // Diffuse color (red)
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color (white for shine)
        32.0f  // Shininess factor
    );
    translateMatrix = glm::translate(model, glm::vec3(4.5f, 0.65f, -5.0f));
    scaleMatrix = glm::scale(translateMatrix, glm::vec3(3.0f, 0.05f, 3.0f));
    chair11.drawCylinder(lightingShader, scaleMatrix);


    //Cylinder chair12 = Cylinder();
    Cylinder chair12 = Cylinder(
        1.0f,  // radius of the cylinder
        1.0f,  // height of the cylinder
        2.0f,  // depth of the cylinder (optional)
        20,    // slices for smoothness
        1,     // stacks for smoothness
        glm::vec3(1.0f, 0.0f, 0.0f), // Ambient color (red)
        glm::vec3(1.0f, 0.0f, 0.0f), // Diffuse color (red)
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color (white for shine)
        32.0f  // Shininess factor
    );
    translateMatrix = glm::translate(model, glm::vec3(-10.5f, 0.65f, -5.0f));
    scaleMatrix = glm::scale(translateMatrix, glm::vec3(3.0f, 0.05f, 3.0f));
    chair12.drawCylinder(lightingShader, scaleMatrix);

    //Cylinder chair21 = Cylinder();
    Cylinder chair21 = Cylinder(
        1.0f,  // radius of the cylinder
        1.0f,  // height of the cylinder
        2.0f,  // depth of the cylinder (optional)
        20,    // slices for smoothness
        1,     // stacks for smoothness
        glm::vec3(1.0f, 0.0f, 0.0f), // Ambient color (red)
        glm::vec3(1.0f, 0.0f, 0.0f), // Diffuse color (red)
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color (white for shine)
        32.0f  // Shininess factor
    );
    translateMatrix = glm::translate(model, glm::vec3(14.5f, 0.65f, -5.0f));
    scaleMatrix = glm::scale(translateMatrix, glm::vec3(3.0f, 0.05f, 3.0f));
    chair21.drawCylinder(lightingShader, scaleMatrix);

    //Cylinder chair22 = Cylinder();
    Cylinder chair22 = Cylinder(
        1.0f,  // radius of the cylinder
        1.0f,  // height of the cylinder
        2.0f,  // depth of the cylinder (optional)
        20,    // slices for smoothness
        1,     // stacks for smoothness
        glm::vec3(1.0f, 0.0f, 0.0f), // Ambient color (red)
        glm::vec3(1.0f, 0.0f, 0.0f), // Diffuse color (red)
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color (white for shine)
        32.0f  // Shininess factor
    );
    translateMatrix = glm::translate(model, glm::vec3(30.5f, 0.65f, -5.0f));
    scaleMatrix = glm::scale(translateMatrix, glm::vec3(3.0f, 0.05f, 3.0f));
    chair22.drawCylinder(lightingShader, scaleMatrix);

    //Cylinder chair31 = Cylinder();
    Cylinder chair31 = Cylinder(
        1.0f,  // radius of the cylinder
        1.0f,  // height of the cylinder
        2.0f,  // depth of the cylinder (optional)
        20,    // slices for smoothness
        1,     // stacks for smoothness
        glm::vec3(1.0f, 0.0f, 0.0f), // Ambient color (red)
        glm::vec3(1.0f, 0.0f, 0.0f), // Diffuse color (red)
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color (white for shine)
        32.0f  // Shininess factor
    );
    translateMatrix = glm::translate(model, glm::vec3(40.5f, 0.65f, -5.0f));
    scaleMatrix = glm::scale(translateMatrix, glm::vec3(3.0f, 0.05f, 3.0f));
    chair31.drawCylinder(lightingShader, scaleMatrix);

    //Cylinder chair32 = Cylinder();
    Cylinder chair32 = Cylinder(
        1.0f,  // radius of the cylinder
        1.0f,  // height of the cylinder
        2.0f,  // depth of the cylinder (optional)
        20,    // slices for smoothness
        1,     // stacks for smoothness
        glm::vec3(1.0f, 0.0f, 0.0f), // Ambient color (red)
        glm::vec3(1.0f, 0.0f, 0.0f), // Diffuse color (red)
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color (white for shine)
        32.0f  // Shininess factor
    );

    translateMatrix = glm::translate(model, glm::vec3(55.5f, 0.65f, -5.0f));
    scaleMatrix = glm::scale(translateMatrix, glm::vec3(3.0f, 0.05f, 3.0f));
    chair32.drawCylinder(lightingShader, scaleMatrix);

    Cylinder chair41 = Cylinder(
        1.0f,  // radius of the cylinder
        1.0f,  // height of the cylinder
        2.0f,  // depth of the cylinder (optional)
        20,    // slices for smoothness
        1,     // stacks for smoothness
        glm::vec3(1.0f, 0.0f, 0.0f), // Ambient color (red)
        glm::vec3(1.0f, 0.0f, 0.0f), // Diffuse color (red)
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color (white for shine)
        32.0f  // Shininess factor
    );

    translateMatrix = glm::translate(model, glm::vec3(63.5f, 0.65f, -5.0f));
    scaleMatrix = glm::scale(translateMatrix, glm::vec3(3.0f, 0.05f, 3.0f));
    chair41.drawCylinder(lightingShader, scaleMatrix);

    

    Cylinder chair42 = Cylinder(
        1.0f,  // radius of the cylinder
        1.0f,  // height of the cylinder
        2.0f,  // depth of the cylinder (optional)
        20,    // slices for smoothness
        1,     // stacks for smoothness
        glm::vec3(1.0f, 0.0f, 0.0f), // Ambient color (red)
        glm::vec3(1.0f, 0.0f, 0.0f), // Diffuse color (red)
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color (white for shine)
        32.0f  // Shininess factor
    );

    translateMatrix = glm::translate(model, glm::vec3(80.5f, 0.65f, -5.0f));
    scaleMatrix = glm::scale(translateMatrix, glm::vec3(3.0f, 0.05f, 3.0f));
    chair42.drawCylinder(lightingShader, scaleMatrix);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f, -2.5f, 1.75f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, 0.9f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(7.1f, -2.5f, 1.75f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, 0.9f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);





    //Seat of Chair
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.45f, -2.5f, 1.75f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, 0.9f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
    
    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.95f, -2.5f, 1.75f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, 0.9f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

  
    

    //table left sam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1f, -2.5f, 1.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table right sam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.8f, -2.5f, 1.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table left pich
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1f, -2.5f, 2.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table right pich
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.8f, -2.5f, 2.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


    //Seat of Chair
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.57f, -2.5f, 1.75f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, 0.9f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
    
    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.15f, -2.5f, 1.75f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, 0.9f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //3rd table
    

    //table left sam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.6f, -2.5f, 1.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table right sam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.3f, -2.5f, 1.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table left pich
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.6f, -2.5f, 2.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table right pich
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.3f, -2.5f, 2.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


    //Seat of Chair
    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15f, -2.5f, 1.75f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, 0.9f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.65f, -2.5f, 1.75f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.4f, 0.9f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //4th table
    //table left sam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.0f, -2.5f, 1.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table right sam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.9f, -2.5f, 1.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table left pich
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.0f, -2.5f, 2.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //table right pich
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.9f, -2.5f, 2.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, 1.5f, .1f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    //if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    /*if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }*/
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        isBasicView = !isBasicView;  // Toggle the view mode
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        pointlight1.turnOff();
        pointlight2.turnOff();
        pointlight3.turnOff();
        pointlight4.turnOff();
        pointlight5.turnOff();
        pointlight6.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        pointlight1.turnOn();
        pointlight2.turnOn();
        pointlight3.turnOn();
        pointlight4.turnOn();
        pointlight5.turnOn();
        pointlight6.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            
            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            pointlight5.turnDiffuseOff();
            pointlight6.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
           
            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            pointlight5.turnDiffuseOn();
            pointlight6.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        if (specularToggle)
        {
            
            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            pointlight5.turnSpecularOff();
            pointlight6.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            
            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            pointlight5.turnSpecularOff();
            pointlight6.turnSpecularOff();
            specularToggle = !specularToggle;
        }


        
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOn();
        pointlight2.turnAmbientOn();
        pointlight3.turnAmbientOn();
        pointlight4.turnAmbientOn();
        pointlight5.turnAmbientOn();
        pointlight6.turnAmbientOn();
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight2.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        pointlight4.turnDiffuseOn();
        pointlight5.turnDiffuseOn();
        pointlight6.turnDiffuseOn();
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight2.turnSpecularOn();
        pointlight3.turnSpecularOn();
        pointlight4.turnSpecularOn();
        pointlight5.turnSpecularOn();
        pointlight6.turnSpecularOn();
    }

    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        pointlight1.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight2.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight3.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight4.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight4.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight4.specular = glm::vec3(0.0, 1.0, 0.0);

        pointlight5.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight5.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight5.specular = glm::vec3(0.0, 1.0, 0.0);

        pointlight6.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight6.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight6.specular = glm::vec3(0.0, 1.0, 0.0);

    }


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

unsigned int loadTexture2(const char* path, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    // Load image using stb_image
    stbi_set_flip_vertically_on_load(true); // Flip the texture vertically if needed
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
    }
    else {
        std::cerr << "Failed to load texture at path: " << path << std::endl;
    }

    stbi_image_free(data); // Free image memory
    return textureID;
}