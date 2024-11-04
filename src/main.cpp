#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include <immintrin.h> //toi uu hoa cac phep toan bang cach tinh cung mot luc
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "geometry.h"

#define FPS_MAX 120

#define LOG(str) std::cout << "[LOG]: " << str << std::endl

#define uint unsigned int

unsigned int createShaderProgram(std::string vertexPath, std::string fragmentPath)
{
    uint vertexId = glCreateShader(GL_VERTEX_SHADER);
    std::ifstream vertexShaderFile(vertexPath);
    std::stringstream vertexShaderStream;
    std::string vertexShaderString;
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    // vertexShaderFile.open(vertexPath);
    if (!vertexShaderFile.is_open())
    {
        std::cerr << "Open file " << vertexPath << " failed" << std::endl;
    }
    // while (std::getline(in, temp))
    // {
    //     std::cout << "[LINE]: " << temp << std::endl;
    //     ss << temp;
    // }
    vertexShaderStream << vertexShaderFile.rdbuf();
    vertexShaderFile.close();
    vertexShaderString = vertexShaderStream.str();
    const char *string1 = vertexShaderString.c_str();
    glShaderSource(vertexId, 1, &string1, nullptr); 
    glCompileShader(vertexId);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexId, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Error[Vertex shader]: " << infoLog << std::endl;
    }

    uint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    std::ifstream fragmentShaderFile;
    std::stringstream fragmentShaderStream;
    std::string fragmentShaderString;
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit); 
    fragmentShaderFile.open(fragmentPath);
    if (!fragmentShaderFile.is_open())
    {
        std::cerr << "Open file " << vertexPath << " failed" << std::endl;
    }
    fragmentShaderStream << fragmentShaderFile.rdbuf();
    fragmentShaderString = fragmentShaderStream.str();
    const char *string2 = fragmentShaderString.c_str();
    glShaderSource(fragmentId, 1, &string2, nullptr);
    glCompileShader(fragmentId);

    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentId, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Error[Fragment shader]: " << infoLog << std::endl;
    }

    uint programId = glCreateProgram();
    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Error[Shader program]: " << infoLog << std::endl;
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    return programId;
}

uint createTexture(std::string texturePath)
{
    int width, height, chanels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &chanels, 0);
    LOG("Chanels = " << chanels);
    
    stbi__vertical_flip(data, width, height, chanels);

    uint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    GLenum format;
    if (chanels = 3)
    {
        format = GL_RGB;
    }
    else
    {
        format = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    return textureId;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
    }
}

int main()
{
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    if(!glfwInit())
    {
        std::cout << "failed window" << "\n";
        return -1;
    }

    window = glfwCreateWindow(500, 500, "My Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "failed glad" << "\n";
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    float verties[] = {
        -0.5, -0.5, 0, 0,
         0.5, -0.5, 1, 0,
         0.5,  0.5, 1, 1,
        -0.5, -0.5, 0, 0,
         0.5,  0.5, 1, 1,
        -0.5,  0.5, 0, 1
    };

    unsigned int faces[] = {
        0, 1, 2,
        0, 2, 3
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verties), verties, GL_STATIC_DRAW);

    // glGenBuffers(1, &ebo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)(2 * sizeof(GL_FLOAT)));

    uint program = createShaderProgram(
        "../resources/shaders/quad.vert", 
        "../resources/shaders/quad.frag"
    );

    glUseProgram(program);
    int location = glGetUniformLocation(program, "texture0");
    int location1 = glGetUniformLocation(program, "x");
    int location2 = glGetUniformLocation(program, "u_model");

    uint texture = createTexture("../resources/textures/brick.jpg");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // auto lastTime = std::chrono::high_resolution_clock::now();
    double timePerFrameTarget = 1.0 / FPS_MAX; //seconds
    // std::chrono::duration<double> deltaTime;
    LARGE_INTEGER frequency;
    LARGE_INTEGER lastCount, currentCount;
    QueryPerformanceFrequency(&frequency);
    double deltaTime = 0, timeSleep = 0;
    // LOG(timePerFrameTarget);

    double start, end;
    float realFps = (float)FPS_MAX;

    float x = 0;

    float uModel[] = {
        1, 0, 0,  0.5,
        0, 1, 0, -0.5,
        0, 0, 1,    0,
        0, 0, 0,    1
    };

    float angle = 0;
    Geometry::Mat4f translateMatrix = Geometry::translate(0.5, -0.5, 0); 
    // Geometry::Mat4f rotateXMatrix;
    // Geometry::Mat4f uModel1 = translateMatrix * rotateXMatrix; 
    Geometry::Mat4f uModel1;// = Geometry::translate(0.5, -0.5, 0) * Geometry::rotateZ(rad(angle)); 
    // Geometry::Mat4f uModel1 = Geometry::rotateZ(rad(angle));// * Geometry::rotateZ(rad(angle)); 
    uModel1.print();

    while(!glfwWindowShouldClose(window))
    {
        glfwSetWindowTitle(window, std::to_string(realFps).c_str());
        start = glfwGetTime();
        // auto nowTimePoint = std::chrono::high_resolution_clock::now();
        // auto secondsTimePoint = std::chrono::time_point_cast<std::chrono::seconds>(nowTimePoint);
        // std::int64_t seconds = secondsTimePoint.time_since_epoch().count();
        // std::int64_t seconds = nowTimePoint.time_since_epoch().count();
        // LOG("glfw" << glfwGetTime() << ", chrono: " << seconds);

        // auto currentTime = std::chrono::high_resolution_clock::now();

        // lastTime = currentTime;
        // LOG(timeSleep);
        // if (timeSleep > 0)
        // {
        //     std::this_thread::sleep_for(std::chrono::duration<float>(timeSleep));
        // }

        QueryPerformanceCounter(&currentCount);
        deltaTime = static_cast<double>(currentCount.QuadPart - lastCount.QuadPart) / frequency.QuadPart;
        lastCount = currentCount;
        // LOG("FPS = " << realFps);
        timeSleep = timePerFrameTarget - deltaTime;

        // event
        glfwPollEvents();
        processInput(window);

        // update
        uModel1 = translateMatrix * Geometry::rotateZ(rad(angle)); 
        // uModel1 = Geometry::rotateZ(rad(angle)); 
        // uModel1 = Geometry::rotateZ(rad(angle)) * Geometry::translate(0.5, -0.5, 0); 
        x += 0.00001 * deltaTime;
        angle += 0.1;

        //render
        glClearColor(1, 1, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glUniform1i(location, 0);
        glUniform1f(location1, x);
        glUniformMatrix4fv(location2, 1, GL_FALSE, uModel1.valuePtr());
        glBindVertexArray(vao);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // swap frame buffer
        glfwSwapBuffers(window);

        // auto lastTime = std::chrono::high_resolution_clock::now();
        // deltaTime = currentTime - lastTime; //seconds
        // LOG(1 / deltaTime.count());
        // timeSleep = timePerFrameTarget - deltaTime.count();
        // if (timeSleep > 0)
        // {
        //     std::this_thread::sleep_for(std::chrono::duration<double>(timeSleep));
        // }

        // // LOG("timeSleep = " << timeSleep);

        // if (timeSleep > 0)
        // {
        //     std::this_thread::sleep_for(std::chrono::nanoseconds((uint64_t)(timeSleep * 1000000000)));
        // }

        realFps = 1 / static_cast<float>(glfwGetTime() - start);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}