#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Level.h"
#include "FileReader.h"
#include "ConsoleController.h"

#include <iostream>
#include <string>
//#include <dirent.h>

using namespace Levels;
using namespace FileReader;
using namespace ConsoleController_N;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
int main();
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);
unsigned int loadCubemap(vector<std::string> faces);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


Level level("resources/textFiles/Levels/", 35, 35, 15);
float levelHeight = 3.0f;
std::vector<glm::vec3> levelPositions;

//TO DO: FIX TEXTURES LIST WITH DIRENT!!!!!!!
#pragma region Textures
struct Textures {
    unsigned int diffuseMap;
    unsigned int specularMap;
    unsigned int emissionMap;
};
std::vector<char const* > textures; //TO DO - UPDATE TO USE TEXTURES STRUCT 
const char* texFilePos = "resources/textures";
bool texLoaded = false;
#pragma endregion

#pragma region Model
Reader fileReaderTest;
//Model_data model_data;
Model ourModel = Model();
int modelIndices = 0;
bool firstModel = false;
int numModels = 0;
#pragma endregion

#pragma region Console
ConsoleCtrl consoleCtrl;
std::string command;
bool console;
bool read;
int tempCount;
#pragma endregion


// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
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

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

// utility function for a list of texture files
// ---------------------------------------------------
//void StoreTextures(string path) {
//    struct dirent* d;
//    DIR* dr;
//    dr = opendir("resources/textures");
//    if (dr != NULL)
//    {
//        texLoaded = false;
//        while (!texLoaded) {
//            //std::cout << "List of Files & Folders:-\n";
//            for (d = readdir(dr); d != NULL; d = readdir(dr))
//            {
//                if (d->d_namlen > 2) {
//                    std::string test = "resources/textures/" + (string)d->d_name;
//                    const char* temp = test.c_str();
//                    //cout << "HERE!!!!" << d->d_ino << endl;
//                    textures.push_back(temp);
//                    std::cout << textures.back() << endl;
//                }               
//            }
//            closedir(dr);
//            texLoaded = true;
//        }        
//    }
//    else
//        std::cout << "\nError Occurred!";
//    std::cout << endl;
//}

#pragma region Error Handeling
GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void APIENTRY glDebugOutput(GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam)
{
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}
#pragma endregion

void character_callback(GLFWwindow* window, unsigned int codePoint) {
    std::cout << (char)codePoint;
    command += (char)codePoint;
}

int main()
{
    consoleCtrl.triangleCount = 0;
    console = false;
    read = false;   
 
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // enable OpenGL debug context if context allows for debug context
    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_DECR_WRAP, GL_DECR_WRAP, GL_DECR_WRAP);
    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);*/

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("MultipleLights.vert", "MultipleLights.frag");
    Shader lightCubeShader("Light_Cube.vert", "Light_Cube.frag");
    // build and compile shaders
    // -------------------------
    Shader ourShader("Model_Loading.vert", "Model_Loading.frag");
    vector<glm::mat4> modelMatrices;
    // load models
    // -----------    
    
    //cout << ourModel.GetTotalIndices() << std::endl;

    Shader cubeShader("Cubemap.vert","Cubemap.frag");
    Shader skyboxShader("Skybox.vert", "Skybox.frag");


    // set up vertex data (and buffer(s)) and configure vertex attributes    
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,//back
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,//front
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,//left
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,//right
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,//bottom
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,//top
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };   
    float cubeVertices[] = {
        // positions          // normals
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };   

    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // vertices VAO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    //StoreTextures("resources/textures/");
    
    unsigned int diffuseMap = loadTexture("resources/textures/0_TexturesCom_ConcreteFloors0075_1_seamless_S.jpg");
   // unsigned int diffuseMap = loadTexture("resources/textures/bark.jpg");
    unsigned int specularMap = loadTexture("resources/textures/trippyTest.png");
    unsigned int emissionMap = loadTexture("resources/textures/matrix.jpg");
    
   unsigned int diffuseMaps[2];
    unsigned int specularMaps[2];
    unsigned int emissionMaps[2];

    diffuseMaps[0] = diffuseMap;
    specularMaps[0] = specularMap;
    emissionMaps[0] = emissionMap;

    diffuseMap = loadTexture("resources/textures/1_TexturesCom_ConcreteBunker0262_4_seamless_S.png");
    specularMap = loadTexture("resources/textures/trippyTest.png");
    emissionMap = loadTexture("resources/textures/matrix.jpg");
    
    diffuseMaps[1] = diffuseMap;
    specularMaps[1] = specularMap;
    emissionMaps[1] = emissionMap;

     

    vector<std::string> faces
    {
        "resources/textures/Spacebox2/right.png",
        "resources/textures/Spacebox2/left.png",
        "resources/textures/Spacebox2/top.png",
        "resources/textures/Spacebox2/bottom.png",
        "resources/textures/Spacebox2/front.png",
        "resources/textures/Spacebox2/back.png",
    };
    unsigned int cubemapTexture = loadCubemap(faces);

    // shader configuration
    // --------------------   
    lightingShader.use();
    cubeShader.use();
    cubeShader.setInt("skybox", 0);

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    lightingShader.setInt("material.emission", 2);
    ourShader.use();
#pragma region FPS tracking vars Initialization
    consoleCtrl.fps.prevTime = 0.0;
    consoleCtrl.fps.crntTime = 0.0;
    consoleCtrl.fps.timeDiff;
    consoleCtrl.fps.counter = 0;
#pragma endregion
    unsigned int tempIndicesFromModel = 0;
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
       // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

#pragma region FPS_Calc
        consoleCtrl.fps.crntTime = glfwGetTime();
        consoleCtrl.fps.timeDiff = consoleCtrl.fps.crntTime - consoleCtrl.fps.prevTime;
        consoleCtrl.fps.counter++;
        if (consoleCtrl.fps.timeDiff >= 1.0 / 2.0) {
             //Resets times and counter
            consoleCtrl.fps.prevTime = consoleCtrl.fps.crntTime;
            consoleCtrl.fps.counter = 0;
        }
#pragma endregion  

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        
#pragma region Lighting

        glm::vec3 pointLightColors[] = {
     glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.3f, 0.1f, 0.1f)
        };
        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        lightingShader.setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "dirLight.diffuse"), 0.05f, 0.05f, 0.05);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "dirLight.specular"), 0.2f, 0.2f, 0.2f);
        // Point light 1
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[0].position"), level.lvl_Structure.lightPos[0].x, level.lvl_Structure.lightPos[0].y, level.lvl_Structure.lightPos[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1, pointLightColors[0].y * 0.1, pointLightColors[0].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[0].linear"), 0.14);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[0].quadratic"), 0.07);
        // Point light 2
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[1].position"), level.lvl_Structure.lightPos[1].x, level.lvl_Structure.lightPos[1].y, level.lvl_Structure.lightPos[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[1].ambient"), pointLightColors[1].x * 0.1, pointLightColors[1].y * 0.1, pointLightColors[1].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[1].diffuse"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[1].specular"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[1].linear"), 0.14);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[1].quadratic"), 0.07);
        // Point light 3
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[2].position"), level.lvl_Structure.lightPos[2].x, level.lvl_Structure.lightPos[2].y, level.lvl_Structure.lightPos[2].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[2].ambient"), pointLightColors[2].x * 0.1, pointLightColors[2].y * 0.1, pointLightColors[2].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[2].diffuse"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[2].specular"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[2].linear"), 0.14);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[2].quadratic"), 0.07);
        // Point light 4
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[3].position"), level.lvl_Structure.lightPos[3].x, level.lvl_Structure.lightPos[3].y, level.lvl_Structure.lightPos[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[3].ambient"), pointLightColors[3].x * 0.1, pointLightColors[3].y * 0.1, pointLightColors[3].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[3].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[3].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[3].linear"), 0.14);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[3].quadratic"), 0.07);
        // Point light 5
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[4].position"), level.lvl_Structure.lightPos[4].x, level.lvl_Structure.lightPos[4].y, level.lvl_Structure.lightPos[4].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[4].ambient"), pointLightColors[3].x * 0.1, pointLightColors[3].y * 0.1, pointLightColors[3].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[4].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[4].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[4].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[4].linear"), 0.14);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[4].quadratic"), 0.07);
        // Point light 6
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[5].position"), level.lvl_Structure.lightPos[5].x, level.lvl_Structure.lightPos[5].y, level.lvl_Structure.lightPos[5].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[5].ambient"), pointLightColors[3].x * 0.1, pointLightColors[3].y * 0.1, pointLightColors[3].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[5].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[5].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[5].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[5].linear"), 0.14);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[5].quadratic"), 0.07);
        // Point light 7
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[6].position"), level.lvl_Structure.lightPos[6].x, level.lvl_Structure.lightPos[6].y, level.lvl_Structure.lightPos[6].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[6].ambient"), pointLightColors[3].x * 0.1, pointLightColors[3].y * 0.1, pointLightColors[3].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[6].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[6].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[6].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[6].linear"), 0.14);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[6].quadratic"), 0.07);
        //-------------------------------------------------------------------------------------------------------
        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.linear"), 0.09);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.quadratic"), 0.032);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.cutOff"), glm::cos(glm::radians(10.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
#pragma endregion        
         //view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        //// world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);        
        
        // render the loaded model 
        // Set the shaders
        
        
        
        if (consoleCtrl.loadLevel) {
           

            
            for (auto c : levelPositions)
            {         
                if (level.ReturnMapCharacter(c.x, c.z) == 'F' || level.ReturnMapCharacter(c.x, c.z) == 'O') {
                    
                    lightingShader.use();
                    lightingShader.setMat4("projection", projection);
                    lightingShader.setMat4("view", view);

                    // bind diffuse map
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, diffuseMaps[0]);
                    // bind specular map
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, specularMaps[0]);
                    //bind emision map
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, emissionMaps[0]);
                    glBindVertexArray(VAO);

                    if (level.ReturnMapCharacter(c.x, c.z) == 'F' || level.ReturnMapCharacter(c.x, c.z) == 'L')
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::mat4(1.0f);
                        model = glm::translate(model, c);
                        lightingShader.setMat4("model", model);
                        tempCount += 12;
                        glDrawArrays(GL_TRIANGLES, 0, 36);

                        lightingShader.use();
                        lightingShader.setMat4("projection", projection);
                        lightingShader.setMat4("view", view);

                        // bind diffuse map
                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D, diffuseMaps[1]);
                        // bind specular map
                        glActiveTexture(GL_TEXTURE1);
                        glBindTexture(GL_TEXTURE_2D, specularMaps[1]);
                        //bind emision map
                        glActiveTexture(GL_TEXTURE1);
                        glBindTexture(GL_TEXTURE_2D, emissionMaps[1]);
                        glBindVertexArray(VAO);

                        // calculate the model matrix for each object and pass it to shader before drawing
                        model = glm::mat4(1.0f);
                        model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(c.x,c.y+levelHeight,c.z));
                        lightingShader.setMat4("model", model);
                        tempCount += 12;
                        glDrawArrays(GL_TRIANGLES, 0, 36);
                    }
                    else {
                        // calculate the model matrix for each object and pass it to shader before drawing
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::mat4(1.0f);
                        model = glm::translate(model, c);
                        lightingShader.setMat4("model", model);
                        tempCount += 12;
                        glDrawArrays(GL_TRIANGLES, 0, 36);
                    }
                    
                }
                else
                {                    
                    lightingShader.use();
                    lightingShader.setMat4("projection", projection);
                    lightingShader.setMat4("view", view);

                    // bind diffuse map
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, diffuseMaps[1]);
                    // bind specular map
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, specularMaps[1]);
                    //bind emision map
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, emissionMaps[1]);
                    glBindVertexArray(VAO);

                    // calculate the model matrix for each object and pass it to shader before drawing
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, c);
                    lightingShader.setMat4("model", model);
                    tempCount += 12;
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
                

            }

            glBindVertexArray(VAO);
            // also draw the lamp object(s)
            lightCubeShader.use();
            lightCubeShader.setMat4("projection", projection);
            lightCubeShader.setMat4("view", view);

            // we now draw as many light bulbs as we have point lights.   
            glBindVertexArray(lightCubeVAO);
            for (auto p : level.lvl_Structure.lightPos)
            {
                model = glm::mat4(1.0f);
                //std::cout << level.lvl_Structure.lightPos[i].x << "-";
                //std::cout << level.lvl_Structure.lightPos[i].z << "-";
                model = glm::translate(model, p);
                model = glm::scale(model, glm::vec3(0.02f)); // Make it a smaller cube
                lightCubeShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                tempCount += 12;
            }
        }

        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);


        // Set the shaders
        if (consoleCtrl.spawnModel) {
            //std::cout << "IM IN!"<<std::endl;
            try
            {
                glm::mat4 tmodel = glm::mat4(1.0f); //declare new model for model shader
                tmodel = glm::translate(tmodel, glm::vec3(consoleCtrl.modelPos.x, consoleCtrl.modelPos.y, consoleCtrl.modelPos.z)); // translate it down so it's at the center of the scene
                tmodel = glm::scale(tmodel, glm::vec3(0.5f));	// it's a bit too big for our scene, so scale it down
                modelMatrices.push_back(tmodel);
                ourShader.setMat4("tmodel", tmodel);
                modelMatrices.push_back(tmodel);
                ourShader.use();

                int modelAmount = modelMatrices.size();
                for (unsigned int i = 0; i < modelAmount; i++)
                {
                    //ourShader.setMat4("tmodel", tmodel);
                    ourShader.setMat4("tmodel", modelMatrices[i]);
                    if (!firstModel) {
                        modelIndices = ourModel.Draw_GetIndices(ourShader);
                        tempIndicesFromModel = modelIndices;
                        firstModel = true;
                    }
                    else {
                        ourModel.Draw(ourShader);
                        tempIndicesFromModel = modelIndices * numModels;
                    }
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "Could not Find Model.\nException Code: " << e.what() << std::endl;
            }

        }
       

        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);        
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
        //end skybox       
         
        tempCount += tempIndicesFromModel;
        consoleCtrl.triangleCount = tempCount;
        tempCount = 0;
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();      
       
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteVertexArrays(1, &cubeVAO);   
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &skyboxVBO);  
    glDeleteBuffers(1, &cubeVBO);;
   
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (!console)
    {   
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.ProcessKeyboard(CROUCH, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.ProcessKeyboard(JUMP, deltaTime);

        //TO DO: IS THERE A WAY TO CHANGE WINDOW FOCUS AND UNDOCK THE MOUSE
        // tell GLFW to capture our mouse
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
        //glfwSetCharCallback(window, NULL);
        //consoleCtrl.spawnModel = false;
        if (!read) {
            std::cout << "Press ~ to access the console" << endl;
            read = true; 
        }
        if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
        {
            console = true;
            std::cout << "CONSOLE ACTIVE!" << endl << ".............................." << std::endl
                << "COMANDS: " << "\nType !help for a list of available commands" << std::endl;
                //- Get a list of the available commands\nfps - Get the programs current fps" 
                //<<"\nspawn modelname.obj pos1 pos2 pos3 - Spawns the specified model at the specified co-ordinates."
               // <<"\nload mapname.txt - loads the specified map.\ntriangles - Gets the total amount of triangles currently active within the scene" << std::endl;
            glfwSetCharCallback(window, character_callback);
        }

    }
    else if (console) {
        
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            std::cout <<std::endl<< "Command: " << command << endl;            
            console = false;
            read = false;
            glfwSetCharCallback(window, NULL);
            //cout << "Command: HEREEEEE" << command;
            if (consoleCtrl.Commands(command) == "load")
            {
                level.lvl_Structure.name = consoleCtrl.mapName;
                level.ReadFile();                
                levelPositions = level.SettupPosArrUpdated();
            }
            else if (consoleCtrl.Commands(command) == "spawn")
            {
                //cout << "HERE: ";
                //cout << ourModel.GetTotalIndices() << std::endl;
                try
                {
                    ourModel.loadModel(consoleCtrl.modelPath + consoleCtrl.modelName);
                    numModels++;
                }
                catch (const std::exception& e)
                {
                    std::cout << "Could not Find Model.\nException Code: " << e.what() << std::endl;
                }
                
            }
            
            command = "";
        }               
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
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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
    camera.ProcessMouseScroll(yoffset);
}