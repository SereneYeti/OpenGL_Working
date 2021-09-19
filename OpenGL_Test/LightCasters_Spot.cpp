//#include <glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//
//#include "Shader.h"
//#include "Camera.h"
//#include "Tools.h"
//#include "stb_image.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <map>
//
//
//using namespace Tool;
//using namespace std;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//#pragma region MixValue
////mix value
//float mixValue = 0.2f;
//float mixValue2 = 0.2f;
//void IncreaseMixValue();
//void DecreaseMixValue();
//void IncreaseMixValue2();
//void DecreaseMixValue2();
//#pragma endregion
//
//#pragma region Materials
////Material List
//struct Materials {
//    glm::vec3 ambient;
//    glm::vec3 diffuse;
//    glm::vec3 specular;
//    float shininess;
//};
//
//Materials test;
//map<string, Materials> MatList;
//
//void PopulateMaterialList() {
//    Materials mat;
//    string key = "";
//#pragma region Old
//    /*string line = "";
//    string words [264];
//    fstream matInfo;
//
//    matInfo.open("MaterialInfo.txt");
//    if (matInfo.is_open() == true) {
//        while (getline(matInfo, line)) {
//            int counter = 0;
//
//            for (int i = 0; i < line.length(); i++) {
//                if (isspace(line[i])||iswspace(line[i]))
//                {
//                    counter++;
//                }
//                else
//                {
//                    words[counter]= line[i];
//                }
//            }
//            key = words[0].c_str();
//            words[0] = {};
//            float w1 = strtof(words[1].c_str(), NULL);
//            float w2 = strtof(words[2].c_str(), NULL);
//            float w3 = strtof(words[3].c_str(), NULL);
//            mat.ambient = glm::vec3(w1, w2, w3);
//            words[1] = {};
//            words[2] = {};
//            words[3] = {};
//            float w4 = strtof(words[4].c_str(), NULL);
//            float w5 = strtof(words[5].c_str(), NULL);
//            float w6 = strtof(words[6].c_str(), NULL);
//            mat.diffuse = glm::vec3(w4, w5, w6);
//            words[4] = {};
//            words[5] = {};
//            words[6] = {};
//            float w7 = strtof(words[7].c_str(), NULL);
//            float w8 = strtof(words[8].c_str(), NULL);
//            float w9 = strtof(words[9].c_str(), NULL);
//            mat.specular = glm::vec3(w7, w8,w9);
//            words[7] = {};
//            words[8] = {};
//            words[9] = {};
//            float w10 = strtof(words[10].c_str(), NULL);
//            mat.shininess = w10;
//            words[10] = {};
//            MatList.insert((pair<string,Materials>(key,mat)));
//            for (int i = 0; i < 10; i++) {
//                shiftright(words, 264);
//            }
//            cout << counter<<endl;
//        }
//        cout << "Im Out!" << endl;
//        matInfo.close();
//    }
//    else
//    {
//        cout << "Error opening file";
//    }*/
//#pragma endregion
//
//#pragma region Materials
//    //1
//    key = "emerald";
//
//    mat.ambient = glm::vec3(0.0215, 0.1745, 0.0215);
//
//    mat.diffuse = glm::vec3(0.07568, 0.07568, 0.61424);
//
//    mat.specular = glm::vec3(0.633, 0.727811, 0.633);
//
//    mat.shininess = 0.6;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //2
//    key = "jade";
//
//    mat.ambient = glm::vec3(0.135, 0.2225, 0.1575);
//
//    mat.diffuse = glm::vec3(0.54, 0.89, 0.63);
//
//    mat.specular = glm::vec3(0.316228, 0.316228, 0.316228);
//
//    mat.shininess = 0.1;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //3
//    key = "obsidian";
//
//    mat.ambient = glm::vec3(0.05375, 0.05, 0.06625);
//
//    mat.diffuse = glm::vec3(0.18275, 0.17, 0.22525);
//
//    mat.specular = glm::vec3(0.332741, 0.328634, 0.346435);
//
//    mat.shininess = 0.3;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //4
//    key = "pearl";
//
//    mat.ambient = glm::vec3(0.25, 0.20725, 0.20725);
//
//    mat.diffuse = glm::vec3(1, 0.829, 0.829);
//
//    mat.specular = glm::vec3(0.296648, 0.296648, 0.296648);
//
//    mat.shininess = 0.088;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //5
//    key = "ruby";
//
//    mat.ambient = glm::vec3(0.1745, 0.01175, 0.01175);
//
//    mat.diffuse = glm::vec3(0.61424, 0.04136, 0.04136);
//
//    mat.specular = glm::vec3(0.727811, 0.626959, 0.626959);
//
//    mat.shininess = 0.6;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //6
//    key = "turquoise";
//
//    mat.ambient = glm::vec3(0.1, 0.18725, 0.1745);
//
//    mat.diffuse = glm::vec3(0.396, 0.74151, 0.69102);
//
//    mat.specular = glm::vec3(0.297254, 0.30829, 0.306678);
//
//    mat.shininess = 0.1;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //7
//    key = "brass";
//
//    mat.ambient = glm::vec3(0.329412, 0.223529, 0.027451);
//
//    mat.diffuse = glm::vec3(0.780392, 0.568627, 0.113725);
//
//    mat.specular = glm::vec3(0.992157, 0.941176, 0.807843);
//
//    mat.shininess = 0.21794872;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //8
//    key = "bronze";
//
//    mat.ambient = glm::vec3(0.2125, 0.1275, 0.054);
//
//    mat.diffuse = glm::vec3(0.714, 0.4284, 0.18144);
//
//    mat.specular = glm::vec3(0.393548, 0.271906, 0.166721);
//
//    mat.shininess = 0.2;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //9
//    key = "chrome";
//
//    mat.ambient = glm::vec3(0.25, 0.25, 0.25);
//
//    mat.diffuse = glm::vec3(0.4, 0.4, 0.4);
//
//    mat.specular = glm::vec3(0.774597, 0.774597, 0.774597);
//
//    mat.shininess = 0.6;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //10
//    key = "copper";
//
//    mat.ambient = glm::vec3(0.19125, 0.0735, 0.0225);
//
//    mat.diffuse = glm::vec3(0.7038, 0.27048, 0.0828);
//
//    mat.specular = glm::vec3(0.256777, 0.137622, 0.086014);
//
//    mat.shininess = 0.1;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //11
//    key = "gold";
//
//    mat.ambient = glm::vec3(0.24725, 0.1995, 0.0745);
//
//    mat.diffuse = glm::vec3(0.75164, 0.60648, 0.22648);
//
//    mat.specular = glm::vec3(0.628281, 0.555802, 0.366065);
//
//    mat.shininess = 0.4;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //12
//    key = "silver";
//
//    mat.ambient = glm::vec3(0.19225, 0.19225, 0.19225);
//
//    mat.diffuse = glm::vec3(0.50754, 0.50754, 0.50754);
//
//    mat.specular = glm::vec3(0.508273, 0.508273, 0.508273);
//
//    mat.shininess = 0.4;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //13
//    key = "black plastic";
//
//    mat.ambient = glm::vec3(0.0, 0.0, 0.0);
//
//    mat.diffuse = glm::vec3(0.01, 0.01, 0.01);
//
//    mat.specular = glm::vec3(0.50, 0.50, 0.50);
//
//    mat.shininess = .25;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //14
//    key = "cyan plastic";
//
//    mat.ambient = glm::vec3(0.0, 0.1, 0.06);
//
//    mat.diffuse = glm::vec3(0.0, 0.50980392, 0.50980392);
//
//    mat.specular = glm::vec3(0.50196078, 0.50196078, 0.50196078);
//
//    mat.shininess = .25;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //15
//    key = "green plastic";
//
//    mat.ambient = glm::vec3(0.0, 0.0, 0.0);
//
//    mat.diffuse = glm::vec3(0.1, 0.35, 0.1);
//
//    mat.specular = glm::vec3(0.45, 0.55, 0.45);
//
//    mat.shininess = .25;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //16
//    key = "red plastic";
//
//    mat.ambient = glm::vec3(0.0, 0.0, 0.0);
//
//    mat.diffuse = glm::vec3(0.5, 0.0, 0.0);
//
//    mat.specular = glm::vec3(0.7, 0.6, 0.6);
//
//    mat.shininess = .25;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //17
//    key = "white plastic";
//
//    mat.ambient = glm::vec3(0.0, 0.0, 0.0);
//
//    mat.diffuse = glm::vec3(0.55, 0.55, 0.55);
//
//    mat.specular = glm::vec3(0.70, 0.70, 0.70);
//
//    mat.shininess = .25;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //18
//    key = "yellow plastic";
//
//    mat.ambient = glm::vec3(0.0, 0.0, 0.0);
//
//    mat.diffuse = glm::vec3(0.5, 0.5, 0.0);
//
//    mat.specular = glm::vec3(0.60, 0.60, 0.50);
//
//    mat.shininess = .25;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //19
//    key = "black rubber";
//
//    mat.ambient = glm::vec3(0.02, 0.02, 0.02);
//
//    mat.diffuse = glm::vec3(0.01, 0.01, 0.01);
//
//    mat.specular = glm::vec3(0.4, 0.4, 0.4);
//
//    mat.shininess = .078125;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //20
//    key = "cyan rubber";
//
//    mat.ambient = glm::vec3(0.0, 0.05, 0.05);
//
//    mat.diffuse = glm::vec3(0.4, 0.5, 0.5);
//
//    mat.specular = glm::vec3(0.04, 0.7, 0.7);
//
//    mat.shininess = .078125;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //21
//    key = "green rubber";
//
//    mat.ambient = glm::vec3(0.0, 0.05, 0.0);
//
//    mat.diffuse = glm::vec3(0.4, 0.5, 0.4);
//
//    mat.specular = glm::vec3(0.04, 0.7, 0.04);
//
//    mat.shininess = .078125;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //22
//    key = "red rubber";
//
//    mat.ambient = glm::vec3(0.05, 0.0, 0.0);
//
//    mat.diffuse = glm::vec3(0.5, 0.4, 0.4);
//
//    mat.specular = glm::vec3(0.7, 0.04, 0.04);
//
//    mat.shininess = .078125;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //23
//    key = "white rubber";
//
//    mat.ambient = glm::vec3(0.05, 0.05, 0.05);
//
//    mat.diffuse = glm::vec3(0.5, 0.5, 0.5);
//
//    mat.specular = glm::vec3(0.7, 0.7, 0.7);
//
//    mat.shininess = .078125;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//    //24
//    key = "yellow rubber";
//
//    mat.ambient = glm::vec3(0.05, 0.05, 0.0);
//
//    mat.diffuse = glm::vec3(0.5, 0.5, 0.4);
//
//    mat.specular = glm::vec3(0.7, 0.7, 0.04);
//
//    mat.shininess = .078125;
//
//    MatList.insert((pair<string, Materials>(key, mat)));
//#pragma endregion    
//}
//#pragma endregion
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const* path)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    PopulateMaterialList();
//    Tools tools = Tools();
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//
//    // build and compile our shader zprogram
//    // ------------------------------------
//    Shader lightingShader("LightCasters_Spot.vert", "LightCasters_Spot.frag");
//    Shader lightCubeShader("Light_Cube.vert", "Light_Cube.frag");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//        // positions          // normals           // texture coords
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
//    };
//    // positions all containers
//    glm::vec3 cubePositions[] = {
//        glm::vec3(0.0f,  0.0f,  0.0f),
//        glm::vec3(2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3(2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3(1.3f, -2.0f, -2.5f),
//        glm::vec3(1.5f,  2.0f, -2.5f),
//        glm::vec3(1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//    // first, configure the cube's VAO (and VBO)
//    unsigned int VBO, cubeVAO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &VBO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindVertexArray(cubeVAO);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
//    unsigned int lightCubeVAO;
//    glGenVertexArrays(1, &lightCubeVAO);
//    glBindVertexArray(lightCubeVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    // load textures (we now use a utility function to keep the code more organized)
//    // -----------------------------------------------------------------------------
//    unsigned int diffuseMap = loadTexture("container2.png");
//    unsigned int specularMap = loadTexture("lighting_maps_specular_color.png");
//    unsigned int emissionMap = loadTexture("matrix.jpg");
//
//    // shader configuration
//    // --------------------
//    // shader configuration
//    // --------------------
//    lightingShader.use();
//    lightingShader.setInt("material.diffuse", 0);
//    lightingShader.setInt("material.specular", 1);
//    lightingShader.setInt("material.emission", 2);
//
//    //lightingShader.setFloat("mixValue", mixValue);
//    //lightingShader.setFloat("mixValue2", mixValue2);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//       // --------------------
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // be sure to activate shader when setting uniforms/drawing objects
//        lightingShader.use();
//        lightingShader.setVec3("light.position", camera.Position);
//        lightingShader.setVec3("light.direction", camera.Front);
//        lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
//        lightingShader.setVec3("viewPos", camera.Position);
//
//        // light properties
//        lightingShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
//        // we configure the diffuse intensity slightly higher; the right lighting conditions differ with each lighting method and environment.
//        // each environment and lighting type requires some tweaking to get the best out of your environment.
//        lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
//        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("light.constant", 1.0f);
//        lightingShader.setFloat("light.linear", 0.09f);
//        lightingShader.setFloat("light.quadratic", 0.032f);
//
//        // material properties
//        lightingShader.setFloat("material.shininess", 32.0f);
//
//        // view/projection transformations
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        lightingShader.setMat4("projection", projection);
//        lightingShader.setMat4("view", view);
//
//        // world transformation
//        glm::mat4 model = glm::mat4(1.0f);
//        lightingShader.setMat4("model", model);
//
//        // bind diffuse map
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//        // bind specular map
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, specularMap);
//
//        // render containers
//        glBindVertexArray(cubeVAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            // calculate the model matrix for each object and pass it to shader before drawing
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            lightingShader.setMat4("model", model);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//
//        // also draw the lamp object
//        //lightCubeShader.use();
//        //lightCubeShader.setMat4("projection", projection);
//        //lightCubeShader.setMat4("view", view);
//        //model = glm::mat4(1.0f);
//        //model = glm::translate(model, lightPos);
//        //model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
//        //lightCubeShader.setMat4("model", model);
//
//        //glBindVertexArray(lightCubeVAO);
//        //glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &lightCubeVAO);
//    glDeleteBuffers(1, &VBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//    {
//        IncreaseMixValue();
//    }
//    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//    {
//        DecreaseMixValue();
//    }
//    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
//    {
//        IncreaseMixValue2();
//    }
//    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//    {
//        DecreaseMixValue2();
//    }
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//void IncreaseMixValue()
//{
//    mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
//    if (mixValue >= 1.0f)
//        mixValue = 1.0f;
//}
//void DecreaseMixValue()
//{
//    mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
//    if (mixValue <= 0.0f)
//        mixValue = 0.0f;
//}
//
//void IncreaseMixValue2()
//{
//    mixValue2 += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
//    if (mixValue2 >= 1.0f)
//        mixValue2 = 1.0f;
//}
//
//void DecreaseMixValue2()
//{
//    mixValue2 -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
//    if (mixValue2 <= 0.0f)
//        mixValue2 = 0.0f;
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//}
