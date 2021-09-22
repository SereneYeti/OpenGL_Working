#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Level.h"
#include "Tools.h"

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <dirent.h>
using namespace Levels;
using namespace Tool;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

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

#pragma region MixValue
// stores how much we're seeing of either texture
float mixValue = 0.2f;
float mixValue2 = 0.2f;
void IncreaseMixValue()
{
    mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
    if (mixValue >= 1.0f)
        mixValue = 1.0f;
}
void DecreaseMixValue()
{
    mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
    if (mixValue <= 0.0f)
        mixValue = 0.0f;
}
void IncreaseMixValue2()
{
    mixValue2 += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
    if (mixValue2 >= 1.0f)
        mixValue2 = 1.0f;
}
void DecreaseMixValue2()
{
    mixValue2 -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
    if (mixValue2 <= 0.0f)
        mixValue2 = 0.0f;
}
#pragma endregion

Level level("resources/textFiles/map.txt", 5, 5, 2);
Tools tool;

#pragma region Textures
struct Textures {
    unsigned int diffuseMap;
    unsigned int specularMap;
    unsigned int emissionMap;
};
std::list<string> textures; //TO DO - UPDATE TO USE TEXTURES STRUCT 
#pragma endregion


#pragma region Materials
//Material List
struct Materials {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

Materials test;
std::map<std::string, Materials> MatList;

void PopulateMaterialList() {
    Materials mat;
    std::string key = "";
#pragma region Old
    /*string line = "";
    string words [264];
    fstream matInfo;

    matInfo.open("MaterialInfo.txt");
    if (matInfo.is_open() == true) {
        while (getline(matInfo, line)) {
            int counter = 0;

            for (int i = 0; i < line.length(); i++) {
                if (isspace(line[i])||iswspace(line[i]))
                {
                    counter++;
                }
                else
                {
                    words[counter]= line[i];
                }
            }
            key = words[0].c_str();
            words[0] = {};
            float w1 = strtof(words[1].c_str(), NULL);
            float w2 = strtof(words[2].c_str(), NULL);
            float w3 = strtof(words[3].c_str(), NULL);
            mat.ambient = glm::vec3(w1, w2, w3);
            words[1] = {};
            words[2] = {};
            words[3] = {};
            float w4 = strtof(words[4].c_str(), NULL);
            float w5 = strtof(words[5].c_str(), NULL);
            float w6 = strtof(words[6].c_str(), NULL);
            mat.diffuse = glm::vec3(w4, w5, w6);
            words[4] = {};
            words[5] = {};
            words[6] = {};
            float w7 = strtof(words[7].c_str(), NULL);
            float w8 = strtof(words[8].c_str(), NULL);
            float w9 = strtof(words[9].c_str(), NULL);
            mat.specular = glm::vec3(w7, w8,w9);
            words[7] = {};
            words[8] = {};
            words[9] = {};
            float w10 = strtof(words[10].c_str(), NULL);
            mat.shininess = w10;
            words[10] = {};
            MatList.insert((pair<string,Materials>(key,mat)));
            for (int i = 0; i < 10; i++) {
                shiftright(words, 264);
            }
            cout << counter<<endl;
        }
        cout << "Im Out!" << endl;
        matInfo.close();
    }
    else
    {
        cout << "Error opening file";
    }*/
#pragma endregion

#pragma region Materials
    //1
    key = "emerald";

    mat.ambient = glm::vec3(0.0215, 0.1745, 0.0215);

    mat.diffuse = glm::vec3(0.07568, 0.07568, 0.61424);

    mat.specular = glm::vec3(0.633, 0.727811, 0.633);

    mat.shininess = 0.6;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //2
    key = "jade";

    mat.ambient = glm::vec3(0.135, 0.2225, 0.1575);

    mat.diffuse = glm::vec3(0.54, 0.89, 0.63);

    mat.specular = glm::vec3(0.316228, 0.316228, 0.316228);

    mat.shininess = 0.1;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //3
    key = "obsidian";

    mat.ambient = glm::vec3(0.05375, 0.05, 0.06625);

    mat.diffuse = glm::vec3(0.18275, 0.17, 0.22525);

    mat.specular = glm::vec3(0.332741, 0.328634, 0.346435);

    mat.shininess = 0.3;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //4
    key = "pearl";

    mat.ambient = glm::vec3(0.25, 0.20725, 0.20725);

    mat.diffuse = glm::vec3(1, 0.829, 0.829);

    mat.specular = glm::vec3(0.296648, 0.296648, 0.296648);

    mat.shininess = 0.088;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //5
    key = "ruby";

    mat.ambient = glm::vec3(0.1745, 0.01175, 0.01175);

    mat.diffuse = glm::vec3(0.61424, 0.04136, 0.04136);

    mat.specular = glm::vec3(0.727811, 0.626959, 0.626959);

    mat.shininess = 0.6;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //6
    key = "turquoise";

    mat.ambient = glm::vec3(0.1, 0.18725, 0.1745);

    mat.diffuse = glm::vec3(0.396, 0.74151, 0.69102);

    mat.specular = glm::vec3(0.297254, 0.30829, 0.306678);

    mat.shininess = 0.1;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //7
    key = "brass";

    mat.ambient = glm::vec3(0.329412, 0.223529, 0.027451);

    mat.diffuse = glm::vec3(0.780392, 0.568627, 0.113725);

    mat.specular = glm::vec3(0.992157, 0.941176, 0.807843);

    mat.shininess = 0.21794872;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //8
    key = "bronze";

    mat.ambient = glm::vec3(0.2125, 0.1275, 0.054);

    mat.diffuse = glm::vec3(0.714, 0.4284, 0.18144);

    mat.specular = glm::vec3(0.393548, 0.271906, 0.166721);

    mat.shininess = 0.2;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //9
    key = "chrome";

    mat.ambient = glm::vec3(0.25, 0.25, 0.25);

    mat.diffuse = glm::vec3(0.4, 0.4, 0.4);

    mat.specular = glm::vec3(0.774597, 0.774597, 0.774597);

    mat.shininess = 0.6;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //10
    key = "copper";

    mat.ambient = glm::vec3(0.19125, 0.0735, 0.0225);

    mat.diffuse = glm::vec3(0.7038, 0.27048, 0.0828);

    mat.specular = glm::vec3(0.256777, 0.137622, 0.086014);

    mat.shininess = 0.1;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //11
    key = "gold";

    mat.ambient = glm::vec3(0.24725, 0.1995, 0.0745);

    mat.diffuse = glm::vec3(0.75164, 0.60648, 0.22648);

    mat.specular = glm::vec3(0.628281, 0.555802, 0.366065);

    mat.shininess = 0.4;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //12
    key = "silver";

    mat.ambient = glm::vec3(0.19225, 0.19225, 0.19225);

    mat.diffuse = glm::vec3(0.50754, 0.50754, 0.50754);

    mat.specular = glm::vec3(0.508273, 0.508273, 0.508273);

    mat.shininess = 0.4;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //13
    key = "black plastic";

    mat.ambient = glm::vec3(0.0, 0.0, 0.0);

    mat.diffuse = glm::vec3(0.01, 0.01, 0.01);

    mat.specular = glm::vec3(0.50, 0.50, 0.50);

    mat.shininess = .25;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //14
    key = "cyan plastic";

    mat.ambient = glm::vec3(0.0, 0.1, 0.06);

    mat.diffuse = glm::vec3(0.0, 0.50980392, 0.50980392);

    mat.specular = glm::vec3(0.50196078, 0.50196078, 0.50196078);

    mat.shininess = .25;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //15
    key = "green plastic";

    mat.ambient = glm::vec3(0.0, 0.0, 0.0);

    mat.diffuse = glm::vec3(0.1, 0.35, 0.1);

    mat.specular = glm::vec3(0.45, 0.55, 0.45);

    mat.shininess = .25;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //16
    key = "red plastic";

    mat.ambient = glm::vec3(0.0, 0.0, 0.0);

    mat.diffuse = glm::vec3(0.5, 0.0, 0.0);

    mat.specular = glm::vec3(0.7, 0.6, 0.6);

    mat.shininess = .25;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //17
    key = "white plastic";

    mat.ambient = glm::vec3(0.0, 0.0, 0.0);

    mat.diffuse = glm::vec3(0.55, 0.55, 0.55);

    mat.specular = glm::vec3(0.70, 0.70, 0.70);

    mat.shininess = .25;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //18
    key = "yellow plastic";

    mat.ambient = glm::vec3(0.0, 0.0, 0.0);

    mat.diffuse = glm::vec3(0.5, 0.5, 0.0);

    mat.specular = glm::vec3(0.60, 0.60, 0.50);

    mat.shininess = .25;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //19
    key = "black rubber";

    mat.ambient = glm::vec3(0.02, 0.02, 0.02);

    mat.diffuse = glm::vec3(0.01, 0.01, 0.01);

    mat.specular = glm::vec3(0.4, 0.4, 0.4);

    mat.shininess = .078125;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //20
    key = "cyan rubber";

    mat.ambient = glm::vec3(0.0, 0.05, 0.05);

    mat.diffuse = glm::vec3(0.4, 0.5, 0.5);

    mat.specular = glm::vec3(0.04, 0.7, 0.7);

    mat.shininess = .078125;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //21
    key = "green rubber";

    mat.ambient = glm::vec3(0.0, 0.05, 0.0);

    mat.diffuse = glm::vec3(0.4, 0.5, 0.4);

    mat.specular = glm::vec3(0.04, 0.7, 0.04);

    mat.shininess = .078125;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //22
    key = "red rubber";

    mat.ambient = glm::vec3(0.05, 0.0, 0.0);

    mat.diffuse = glm::vec3(0.5, 0.4, 0.4);

    mat.specular = glm::vec3(0.7, 0.04, 0.04);

    mat.shininess = .078125;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //23
    key = "white rubber";

    mat.ambient = glm::vec3(0.05, 0.05, 0.05);

    mat.diffuse = glm::vec3(0.5, 0.5, 0.5);

    mat.specular = glm::vec3(0.7, 0.7, 0.7);

    mat.shininess = .078125;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
    //24
    key = "yellow rubber";

    mat.ambient = glm::vec3(0.05, 0.05, 0.0);

    mat.diffuse = glm::vec3(0.5, 0.5, 0.4);

    mat.specular = glm::vec3(0.7, 0.7, 0.04);

    mat.shininess = .078125;

    MatList.insert((std::pair<std::string, Materials>(key, mat)));
#pragma endregion    
}
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
// utility function for a list of texture files
// ---------------------------------------------------
void StoreTextures(string path) {
    struct dirent* d;
    DIR* dr;
    dr = opendir("resources/textures");
    if (dr != NULL)
    {
        cout << "List of Files & Folders:-\n";
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            //cout << d->d_name << endl;
            textures.push_back(d->d_name);
            cout << textures.back()<< endl;

        }
        closedir(dr);
    }
    else
        cout << "\nError Occurred!";
    cout << endl;
}

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

    PopulateMaterialList();
    //Tools tools = Tools();

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("MultipleLights.vert", "MultipleLights.frag");
    Shader lightCubeShader("Light_Cube.vert", "Light_Cube.frag");
    // build and compile shaders
    // -------------------------
    Shader ourShader("Model_Loading.vert", "Model_Loading.frag");
    // load models
    // -----------
    Model ourModel("resources/objects/backpack/backpack.obj");


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
    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //test
    //------------------------------------------------------

    level.ReadFile();    
    
    std::vector<glm::vec3> planePositions;    
    for (int i = 0; i < level.lvl_Structure.sizeX; i++) {
        for (int j = 0; j < level.lvl_Structure.sizeZ; j++)
        {
            planePositions.push_back(level.ReturnPosition(i, j));
        }       
    }
    
    
    //-------------------------------------------------------
    //test
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
    StoreTextures("resources/textures/");
    unsigned int diffuseMap = loadTexture("resources/textures/spirals.jpg");
    unsigned int specularMap = loadTexture("resources/textures/trippyTest.png");
    unsigned int emissionMap = loadTexture("resources/textures/matrix.jpg");

    // shader configuration
    // --------------------
    // shader configuration
    // --------------------
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    lightingShader.setInt("material.emission", 2);
    

    //lightingShader.setFloat("mixValue", mixValue);
    //lightingShader.setFloat("mixValue2", mixValue2);
    
   
    std::string test = "";
    if (std::cin >> test)
        std::cout << "HEY!";
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
       // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
#pragma region Lighting

        glm::vec3 pointLightColors[] = {
    glm::vec3(0.4f, 0.7f, 0.1f),
    glm::vec3(0.4f, 0.7f, 0.1f),
    glm::vec3(0.4f, 0.7f, 0.1f),
    glm::vec3(0.4f, 0.7f, 0.1f)
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
        glUniform3f(glGetUniformLocation(lightingShader.ID, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "dirLight.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "dirLight.specular"), 1.0f, 1.0f, 1.0f);
        // Point light 1
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1, pointLightColors[0].y * 0.1, pointLightColors[0].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[0].linear"), 0.07);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[0].quadratic"), 0.017);
        // Point light 2
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[1].ambient"), pointLightColors[1].x * 0.1, pointLightColors[1].y * 0.1, pointLightColors[1].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[1].diffuse"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[1].specular"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[1].linear"), 0.07);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[1].quadratic"), 0.017);
        // Point light 3
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[2].ambient"), pointLightColors[2].x * 0.1, pointLightColors[2].y * 0.1, pointLightColors[2].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[2].diffuse"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[2].specular"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[2].linear"), 0.07);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[2].quadratic"), 0.017);
        // Point light 4
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[3].ambient"), pointLightColors[3].x * 0.1, pointLightColors[3].y * 0.1, pointLightColors[3].z * 0.1);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[3].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "pointLights[3].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[3].linear"), 0.07);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "pointLights[3].quadratic"), 0.017);
        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.diffuse"), 0.0f, 1.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.ID, "spotLight.specular"), 0.0f, 1.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.linear"), 0.07);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.quadratic"), 0.017);
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.cutOff"), glm::cos(glm::radians(7.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(10.0f)));
#pragma endregion
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);
       

        // render the loaded model
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        //glBindVertexArray(cubeVAO);
        //if (level.cnrCounter < 4)
        //{
        //    for (unsigned int i = 0; i <= 4; i++)
        //    {
        //        for (unsigned int j = 0; j <= 4; i++)
        //        {
        //            //    // calculate the model matrix for each object and pass it to shader before drawing
        //            model = glm::mat4(1.0f);
        //            if (level.ReturnMapCharacter(i, j) == 'C')
        //                level.cnrCounter++;
        //            model = glm::translate(model, DetermineIndices(level.ReturnMapCharacter(i, j), i, j));
        //            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        //            lightCubeShader.setMat4("model", model);
        //            glDrawArrays(GL_TRIANGLES, 0, 36);
        //        }                
        //    }
        //}
        

        // render containers
        //glBindVertexArray(cubeVAO);
        //for (unsigned int i = 0; i < 10; i++)
        //{
        //    // calculate the model matrix for each object and pass it to shader before drawing
        //    glm::mat4 model = glm::mat4(1.0f);
        //    model = glm::translate(model, cubePositions[i]);
        //    float angle = 20.0f * i;
        //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //    lightingShader.setMat4("model", model);

        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}
        
        // my render
        //--------------------------------------------------------------------------------------
         // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < planePositions.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);           
            model = glm::translate(model, planePositions[i]);
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == 'T')
            {
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f,0.0f,0.0f));               
                //std::cout << "Here!";
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(planePositions[i].x,planePositions[i].y-1.0f, planePositions[i].z));  
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(planePositions[i].x, planePositions[i].y + 1.0f, planePositions[i].z));
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
            }
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == 'B')
            {
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                //std::cout << "Here!";
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(planePositions[i].x, planePositions[i].y - 1.0f, planePositions[i].z));
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(planePositions[i].x, planePositions[i].y + 1.0f, planePositions[i].z));
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                //glDrawArrays(GL_TRIANGLES, 0, 6);                
            }
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == 'L')
            {
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                //std::cout << "Here!";
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(planePositions[i].x, planePositions[i].y - 1.0f, planePositions[i].z));
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                lightingShader.setMat4("model", model);
                
                          }
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == 'R')
            {
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                //std::cout << "Here!";
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(planePositions[i].x, planePositions[i].y - 1.0f, planePositions[i].z));
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                lightingShader.setMat4("model", model);
               
               
            }   
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == '[') //Top Left Corner
            {
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 1.0f));
                //std::cout << "Here!";
                lightingShader.setMat4("model", model);
                
            }
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == ']') //Top Right Corner
            {
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                model = glm::translate(model, glm::vec3(1.0f, 0.0f, 1.0f));
                //std::cout << "Here!";
                lightingShader.setMat4("model", model);               
            }
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == '{') //Bottom Left Corner
            {
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
                //std::cout << "Here!";
                lightingShader.setMat4("model", model);                
            }
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == '}') //Bottom Right Corner
            {
                model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                model = glm::translate(model, glm::vec3(1.0f, 0.0f, -1.0f));
                //std::cout << "Here!";
                lightingShader.setMat4("model", model);
            }     
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == '*' || level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == '+') //Floor & Therefore Roof
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, planePositions[i]);
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(planePositions[i].x, planePositions[i].y + 4.0f, planePositions[i].z));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                lightingShader.setMat4("model", model);               
            }
            if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z) == 'D') //Floor & Therefore Roof
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, planePositions[i]);
                lightingShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                model = glm::mat4(1.0f);               
                model = glm::translate(model, glm::vec3(planePositions[i].x, planePositions[i].y + 3.0f, planePositions[i].z));
                if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z+1) == 'L')
                    model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));
                else if (level.ReturnMapCharacter(planePositions[i].x, planePositions[i].z + 1) == 'R')
                    model = glm::rotate(model, glm::radians(90.0f), level.DetermineRotation(planePositions[i].x, planePositions[i].z));                
                lightingShader.setMat4("model", model);
            }

            
            lightingShader.setMat4("model", model);
            //std::cout << "Here!";
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(cubeVAO);
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(i, -1.0, j));
                lightingShader.setMat4("model", model);
                //std::cout << "Here!";
                glDrawArrays(GL_TRIANGLES, 30, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(-(i), -1.0, -(j)));
                lightingShader.setMat4("model", model);
                //std::cout << "Here!";
                glDrawArrays(GL_TRIANGLES, 30, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3((i), -1.0, -(j)));
                lightingShader.setMat4("model", model);
                //std::cout << "Here!";
                glDrawArrays(GL_TRIANGLES, 30, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(-(i), -1.0, (j)));
                lightingShader.setMat4("model", model);
                //std::cout << "Here!";
                glDrawArrays(GL_TRIANGLES, 30, 36);
            }            
        }      
        // calculate the model matrix for each object and pass it to shader before drawing
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, planePositions[0]);
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f)); //right
        //lightingShader.setMat4("model", model);
        ////std::cout << "Here!";
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glBindVertexArray(mapVAO);
        //// calculate the model matrix for each object and pass it to shader before drawing
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, planePositions[1]);
        ////model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //top
        //lightingShader.setMat4("model", model);
        //std::cout << "Here!";
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // calculate the model matrix for each object and pass it to shader before drawing
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, planePositions[2]);
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //left
        //lightingShader.setMat4("model", model);
        ////std::cout << "Here!";
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glBindVertexArray(mapVAO);
        // calculate the model matrix for each object and pass it to shader before drawing
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, planePositions[3]);
        //model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); //bottom
        //lightingShader.setMat4("model", model);
        //std::cout << "Here!";
        //glDrawArrays(GL_TRIANGLES, 0, 36);
                    
        //            
        //---------------------------------------------------------------------
        //my render

        // also draw the lamp object(s)
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        //glBindVertexArray(lightCubeVAO);
        //for (unsigned int i = 0; i < 4; i++)
        //{
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, pointLightPositions[i]);
        //    model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        //    lightCubeShader.setMat4("model", model);
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}
        //glBindVertexArray(lightCubeVAO);
       
       
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 2; i++)
        {
            model = glm::mat4(1.0f);
            //std::cout << level.lvl_Structure.lightPos[i].x << "-";
            //std::cout << level.lvl_Structure.lightPos[i].z << "-";
            model = glm::translate(model, level.lvl_Structure.lightPos[i]);            
            model = glm::scale(model, glm::vec3(0.6f)); // Make it a smaller cube
            lightCubeShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);  
   
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

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        IncreaseMixValue();
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        DecreaseMixValue();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        IncreaseMixValue2();
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        DecreaseMixValue2();
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
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