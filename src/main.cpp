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
#include "camera.h"

#define FPS_MAX 120
#define WIDTH 500
#define HEIGHT 500

#define LOG(str) std::cout << "[LOG]: " << str << std::endl

#define uint unsigned int

enum Direction {
    NONE,
    UP, 
    DOWN,
    LEFT,
    RIGHT
};

enum ButtonState
{
    PRESS,
    RELEASE
};

struct InputState
{
    Direction dir = Direction::NONE;
    ButtonState state = ButtonState::RELEASE;
};


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

void processInput(GLFWwindow *window, InputState& inputState)
{
    //Press
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // LOG("update");
        inputState.dir = Direction::LEFT;
        inputState.state = ButtonState::PRESS;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        inputState.dir = Direction::UP;
        inputState.state = ButtonState::PRESS;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        inputState.dir = Direction::RIGHT;
        inputState.state = ButtonState::PRESS;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        inputState.dir = Direction::DOWN;
        inputState.state = ButtonState::PRESS;
    }

    //Release
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && inputState.dir == Direction::LEFT)
    {
        inputState.dir = Direction::LEFT;
        inputState.state = ButtonState::RELEASE;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && inputState.dir == Direction::UP)
    {
        inputState.dir = Direction::UP;
        inputState.state = ButtonState::RELEASE;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE && inputState.dir == Direction::RIGHT)
    {
        inputState.dir = Direction::RIGHT;
        inputState.state = ButtonState::RELEASE;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE && inputState.dir == Direction::DOWN)
    {
        inputState.dir = Direction::DOWN;
        inputState.state = ButtonState::RELEASE;
    }
}

void updateCamera(Geometry::Vec3f& eye, InputState& inputState, float deltaTime)
{
    if (inputState.state == ButtonState::PRESS)
    {
        // LOG(inputState.dir << " " << inputState.state);
        std::cout << eye << std::endl;
        switch (inputState.dir)
        {
            case Direction::DOWN:
            {
                eye.y -= deltaTime;
                break;
            }
            case Direction::UP:
            {
                eye.y += deltaTime;
                break;
            }
            case Direction::LEFT:
            {
                eye.x -= deltaTime;
                break;
            }
            case Direction::RIGHT:
            {
                eye.x += deltaTime;
                break;
            }
        }
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

    window = glfwCreateWindow(WIDTH, HEIGHT, "My Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "failed glad" << "\n";
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    glfwSwapInterval(0);

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
    int location3 = glGetUniformLocation(program, "u_view");
    int location4 = glGetUniformLocation(program, "u_proj");

    uint texture = createTexture("../resources/textures/brick.jpg");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // auto lastTime = std::chrono::high_resolution_clock::now();
    // double timePerFrameTarget = 1000.0 / FPS_MAX; //miliseconds
    // // std::chrono::duration<double> deltaTime;
    // LARGE_INTEGER frequency;
    // LARGE_INTEGER startCount, endCount, lastCount;
    // QueryPerformanceFrequency(&frequency);
    // double deltaTime = 0.0, timeSleep = 0.0;
    // // LOG(timePerFrameTarget);

    // double start, end;
    // float realFps = (float)FPS_MAX;

    //test
    double lastTime = glfwGetTime(), lastFrameTime = glfwGetTime(), currentTime;
    int numFrames = 0;
    float frameTime = 0.0;

    float x = 0;

    float uModel[] = {
        1, 0, 0,  0.5,
        0, 1, 0, -0.5,
        0, 0, 1,    0,
        0, 0, 0,    1
    };

    float fov = rad(45);
    float ratio = (WIDTH * 1.0/ HEIGHT);
    float nearPlane = 0.1;
    float farPlane = 1000.0;

    Geometry::Vec3f eye(0, 0, -3);
    // std::cout << eye << std::endl;
    Geometry::Vec3f center(0, 0, 0);
    // std::cout << center << std::endl;
    Geometry::Vec3f up(0, 1, 0);
    // std::cout << up << std::endl;

    Geometry::Mat4f cameraMatrix, projectMatrix;

    float angle = 0;
    // Geometry::Mat4f translateMatrix = Geometry::translate(0.5, -0.5, 0); 
    Geometry::Mat4f translateMatrix = Geometry::translate(0, 0, 0); 
    // Geometry::Mat4f rotateXMatrix;
    // Geometry::Mat4f uModel1 = translateMatrix * rotateXMatrix; 
    Geometry::Mat4f uModel1;// = Geometry::translate(0.5, -0.5, 0) * Geometry::rotateZ(rad(angle)); 
    // Geometry::Mat4f uModel1 = Geometry::rotateZ(rad(angle));// * Geometry::rotateZ(rad(angle)); 
    // uModel1.print();

    // cameraMatrix = Camera::lookAt(eye, center, up);

    InputState inputState;

    while(!glfwWindowShouldClose(window))
    {
        // QueryPerformanceCounter(&lastCount);
        // LOG("Real fps: " << 1 / (static_cast<double>(lastCount.QuadPart - startCount.QuadPart) / frequency.QuadPart));
        // glfwSetWindowTitle(window, std::to_string(1 / (static_cast<double>(lastCount.QuadPart - startCount.QuadPart) / frequency.QuadPart)).c_str());
        // // start = glfwGetTime();

        // if (timeSleep > 0)
        // {
        //     std::this_thread::sleep_for(std::chrono::duration<float>(timeSleep));
        // }

        // QueryPerformanceCounter(&startCount);
        // // LOG("FPS = " << realFps);
        // // timeSleep = timePerFrameTarget - deltaTime;
        // // if (miliTimeSleep > 0)
        // // {
        // //     // LOG("time sleep: " << miliTimeSleep);
        // //     // std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(miliTimeSleep));
        // //     std::this_thread::sleep_for(std::chrono::duration<double, std::nano>(miliTimeSleep));
        // //     // std::this_thread::sleep_for(std::chrono::milliseconds(miliTimeSleep));
        // // }

        // event
        glfwPollEvents();
        processInput(window, inputState);

        // update
        // updateCamera(eye, inputState, deltaTime);
        updateCamera(eye, inputState, frameTime);
        projectMatrix = Camera::perspective(fov, ratio, nearPlane, farPlane);
        cameraMatrix = Camera::lookAt(eye, center, up);
        uModel1 = translateMatrix * Geometry::rotateZ(rad(angle)); 
        // x += 0.00001 * deltaTime;
        x += 0.00001 * frameTime;
        angle += 0.1;

        //render
        glClearColor(1, 1, 0.5, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glUniform1i(location, 0);
        // glUniform1f(location1, x);
        glUniformMatrix4fv(location2, 1, GL_FALSE, uModel1.valuePtr());
        glUniformMatrix4fv(location3, 1, GL_FALSE, cameraMatrix.valuePtr());
        glUniformMatrix4fv(location4, 1, GL_FALSE, projectMatrix.valuePtr());
        glBindVertexArray(vao);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // swap frame buffer
        glfwSwapBuffers(window);

        // if (timeSleep > 0)
        // {
        //     std::this_thread::sleep_for(std::chrono::nanoseconds((uint64_t)(timeSleep * 1000000000)));
        // }

        // QueryPerformanceCounter(&endCount);
        // deltaTime = (static_cast<double>(endCount.QuadPart - startCount.QuadPart) / frequency.QuadPart) * 1000.0;
        // // timeSleep = (timePerFrameTarget - deltaTime);
        // // if (deltaTime > timePerFrameTarget)
        //     // LOG("Time process: " << deltaTime);

        // if (timePerFrameTarget > deltaTime)
        // {
        //     // LOG("time sleep: " << miliTimeSleep);
        //     std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(timePerFrameTarget - deltaTime));
        // }

        // realFps = 1 / static_cast<float>(glfwGetTime() - start);
        // LOG("real fps: " << realFps);

        currentTime = glfwGetTime();
        double delta = currentTime - lastTime;
        double frameDelta = currentTime - lastFrameTime;
        frameTime = float(1000.0f * frameDelta);
        lastFrameTime = currentTime;

        if (delta >= 1) {
            int framerate{ std::max(1, int(numFrames / delta)) };
            std::stringstream title;
            title << "Running at " << framerate << " fps.";
            glfwSetWindowTitle(window, title.str().c_str());
            lastTime = currentTime;
            numFrames = -1;
        }

        ++numFrames;
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}