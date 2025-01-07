#include <Camera.h>
#include <Entity.h>
#include <Shader.h>
#include <Skybox.h>
#include <pch.h>

#include "Helicopter.h"
#include "Rocket.h"
#include "Tank.h"
#include "Terrain.h"

constexpr int WIDTH  = 1920;
constexpr int HEIGHT = 1080;

std::unique_ptr<Camera>              pCamera;
std::vector<std::unique_ptr<Entity>> entities;

double DeltaTime = 0.0f;
double LastFrame = 0.0f;

void FrameBufferCallback(GLFWwindow * /*window*/, const int width, const int height) {
    glViewport(0, 0, width, height);
    pCamera->Reshape(width, height);
}

void MouseCallback(GLFWwindow * /*window*/, const double xpos, const double ypos) {
    for (const auto &entity : entities) {
        if (!entity->IsSelected())
            continue;
        if (entity->GetName() == "tank") {
            const auto tank = dynamic_cast<Tank *>(entity.get());
            if (tank) {
                std::cout << "MouseCallback: " << xpos << " " << ypos << std::endl;
                tank->MouseControl(static_cast<float>(xpos), static_cast<float>(ypos));
            }
            return;
        }
    }

    pCamera->MouseControl(static_cast<float>(xpos), static_cast<float>(ypos));
}

void ScrollCallback(GLFWwindow * /*window*/, const double /*xoffset*/, const double yOffset) {
    pCamera->ProcessMouseScroll(static_cast<float>(yOffset));
}

void KeyboardCallback(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // for (const auto &entity : entities) {
    //     if (!entity->IsSelected())
    //         continue;
    //     if (entity->GetName() == "tank") {
    //         const auto tank = dynamic_cast<Tank *>(entity.get());
    //         if (tank) {
    //             tank->ControlTank(window, static_cast<float>(DeltaTime));
    //         }
    //         return;
    //     }
    // }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        pCamera->ProcessKeyboard(FORWARD, static_cast<float>(DeltaTime));
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        pCamera->ProcessKeyboard(BACKWARD, static_cast<float>(DeltaTime));
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        pCamera->ProcessKeyboard(LEFT, static_cast<float>(DeltaTime));
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        pCamera->ProcessKeyboard(RIGHT, static_cast<float>(DeltaTime));
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Tancodrom", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    pCamera = std::make_unique<Camera>(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f));

    glfwSetFramebufferSizeCallback(window, FrameBufferCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable face culling
    // glEnable(GL_CULL_FACE);

    constexpr glm::vec3 modelPosition(0.0f, 10.0f, 0.0f);
    constexpr glm::vec3 lightPosition(0.0f, 20.0f, 0.0f);

    Shader phongLightingShader("../shaders/PhongVertex.glsl", "../shaders/PhongFragment.glsl");
    Shader shadowMappingShader("../shaders/ShadowMapVertex.glsl",
                               "../shaders/ShadowMapFragment.glsl");
    Shader shadowMappingDepthShader("../shaders/ShadowMapDepthVertex.glsl",
                                    "../shaders/ShadowMapDepthFragment.glsl");

    const std::vector<std::string> faces{
            "../textures/skybox/right.jpg", "../textures/skybox/left.jpg",
            "../textures/skybox/top.jpg",   "../textures/skybox/bottom.jpg",
            "../textures/skybox/front.jpg", "../textures/skybox/back.jpg"};

    const Skybox skybox(faces);

    entities.push_back(std::make_unique<Tank>(modelPosition, glm::vec3(1.0f), glm::vec3(0.0f),
                                              window, pCamera.get()));
    entities.push_back(std::make_unique<Helicopter>(modelPosition, glm::vec3(1.0f), glm::vec3(0.0f),
                                                    window, pCamera.get()));

    // auto tank = dynamic_cast<Tank *>(entities[0].get());
    // auto heli = dynamic_cast<Helicopter *>(entities[1].get());

    Terrain terrain(glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), "terrain",
                    window, pCamera.get());

    auto rocket = std::make_unique<Rocket>(glm::vec3(40.0f, 30.0f, 0.0f),
                                           glm::vec3(0.0f, -5.0f, 0.0f), window, pCamera.get());

    while (!glfwWindowShouldClose(window)) {
        const double currentFrame = glfwGetTime();
        DeltaTime                 = currentFrame - LastFrame;
        LastFrame                 = currentFrame;

        KeyboardCallback(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4      view       = pCamera->GetViewMatrix();
        glm::mat4      projection = pCamera->GetProjectionMatrix();
        constexpr auto model      = glm::mat4(1.0f);

        // Use Phong lighting shader
        phongLightingShader.Use();
        phongLightingShader.SetMat4("view", view);
        phongLightingShader.SetMat4("projection", projection);
        phongLightingShader.SetMat4("model", model);
        phongLightingShader.SetVec3("lightPos", lightPosition);
        phongLightingShader.SetVec3("viewPos", pCamera->GetPosition());
        phongLightingShader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        phongLightingShader.SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

        terrain.Render(phongLightingShader);

        rocket->Update(static_cast<float>(DeltaTime));
        rocket->Render(phongLightingShader);

        // Render the skybox
        skybox.Draw(view, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
