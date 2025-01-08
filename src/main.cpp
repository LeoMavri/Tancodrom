#include <Camera.h>
#include <Entity.h>
#include <Shader.h>
#include <Skybox.h>
#include <pch.h>

#include "Helicopter.h"
#include "Rocket.h"
#include "Sun.h"
#include "Tank.h"
#include "Terrain.h"

constexpr int WIDTH  = 1920;
constexpr int HEIGHT = 1080;

std::unique_ptr<Camera> pCamera;
// std::vector<std::unique_ptr<Entity>> entities;

double DeltaTime = 0.0f;
double LastFrame = 0.0f;

void FrameBufferCallback(GLFWwindow * /*window*/, const int width, const int height) {
    glViewport(0, 0, width, height);
    pCamera->Reshape(width, height);
}

void MouseCallback(GLFWwindow * /*window*/, const double xpos, const double ypos) {
    // for (const auto &entity : entities) {
    //     if (!entity->IsSelected())
    //         continue;
    //     if (entity->GetName() == "tank") {
    //         const auto tank = dynamic_cast<Tank *>(entity.get());
    //         if (tank) {
    //             tank->MouseControl(static_cast<float>(xpos), static_cast<float>(ypos));
    //         }
    //         return;
    //     }
    // }

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
    //
    //     if (entity->GetName() == "tank") {
    //         const auto tank = dynamic_cast<Tank *>(entity.get());
    //         if (tank) {
    //             tank->ControlTank(window, static_cast<float>(DeltaTime));
    //         }
    //         return;
    //     }
    //
    //     // if (entity->GetName() == "helicopter") {
    //     //     const auto heli = dynamic_cast<Helicopter *>(entity.get());
    //     //
    //     //     if (heli) {
    //     //         heli->
    //     //     }
    //     // }
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

    // Shader phongLightingShader("../shaders/PhongVertex.glsl", "../shaders/PhongFragment.glsl");
    Shader shadowShader("../shaders/ShadowMapVertex.glsl", "../shaders/ShadowMapFragment.glsl");
    Shader shadowDepthShader("../shaders/ShadowMapDepthVertex.glsl",
                             "../shaders/ShadowMapDepthFragment.glsl");

    const std::vector<std::string> faces{
            "../textures/skybox/right.jpg", "../textures/skybox/left.jpg",
            "../textures/skybox/top.jpg",   "../textures/skybox/bottom.jpg",
            "../textures/skybox/front.jpg", "../textures/skybox/back.jpg"};

    const Skybox skybox(faces);

    // entities.push_back(std::make_unique<Tank>(glm::vec3(0.0f, -4.5f, 0.0f), glm::vec3(1.0f),
    //                                           glm::vec3(0.0f), window, pCamera.get()));
    // entities.push_back(std::make_unique<Helicopter>(modelPosition, glm::vec3(1.0f),
    // glm::vec3(0.0f),
    //                                                 window, pCamera.get()));

    Tank       tank{glm::vec3(0.0f, -4.4f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), window,
              pCamera.get()};
    Helicopter heli{modelPosition, glm::vec3(1.0f), glm::vec3(0.0f), window, pCamera.get()};

    Terrain terrain{glm::vec3(0.0f, -5.0f, 0.0f),
                    glm::vec3(15.0f, 1.0f, 15.0f),
                    glm::vec3(0.0f),
                    "terrain",
                    window,
                    pCamera.get()};

    // auto rocket = std::make_unique<Rocket>(glm::vec3(40.0f, 30.0f, 0.0f),
    //                                        glm::vec3(0.0f, -5.0f, 0.0f), window, pCamera.get());

    Sun sun(glm::vec3(5, 160, 0), glm::vec3(0.005), glm::vec3(0, 0, 0), "sun");

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Shadow map setup
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    const unsigned int SHADOW_WIDTH = 8192, SHADOW_HEIGHT = 8192;
    unsigned int       depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,
                 GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    shadowShader.Use();
    shadowShader.SetInt("diffuseTexture", 0);
    shadowShader.SetInt("shadowMap", 1);

    heli.SetSelected(true);

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const double currentFrame = glfwGetTime();
        DeltaTime                 = currentFrame - LastFrame;
        LastFrame                 = currentFrame;

        KeyboardCallback(window);

        // tank.Update();
        heli.Update(static_cast<float>(DeltaTime));
        sun.Update(static_cast<float>(DeltaTime));

        shadowDepthShader.Use();
        shadowDepthShader.SetMat4("lightSpaceMatrix", sun.GetLightSpaceMatrix());

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        terrain.Render(shadowDepthShader);
        sun.Render(shadowDepthShader);
        tank.Render(shadowDepthShader);
        heli.Render(shadowDepthShader);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glActiveTexture(GL_TEXTURE0);

        // Render pass
        glViewport(0, 0, WIDTH, HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shadowShader.Use();
        shadowShader.SetMat4("projection", pCamera->GetProjectionMatrix());
        shadowShader.SetMat4("view", pCamera->GetViewMatrix());
        shadowShader.SetVec3("viewPos", pCamera->GetPosition());
        shadowShader.SetVec3("lightPos", sun.GetPosition());
        shadowShader.SetMat4("lightSpaceMatrix", sun.GetLightSpaceMatrix());

        shadowShader.SetInt("numLights", 1);
        shadowShader.SetLightsVec3("position", {sun.GetPosition()});
        shadowShader.SetLightsVec3("color", {sun.m_Color});
        shadowShader.SetLightsFloat("intensity", {sun.m_Intensity});

        glActiveTexture(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        terrain.Render(shadowShader);
        sun.Render(shadowShader);
        tank.Render(shadowShader);
        heli.Render(shadowShader);
        // rocket.Render(shadowShader);

        float timeOfDay = fmod(glfwGetTime(), 0.01f); // Simulate a 24-hour cycle
        float hueShift  = (timeOfDay < 12.0f) ? timeOfDay / 12.0f : (24.0f - timeOfDay) / 12.0f;

        skybox.SetSkyboxHue(hueShift);
        skybox.Draw(pCamera->GetViewMatrix(), pCamera->GetProjectionMatrix());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
