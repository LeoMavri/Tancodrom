#include <Camera.h>
#include <Entity.h>
#include <Shader.h>
#include <Skybox.h>
#include <pch.h>

constexpr int WIDTH  = 1920;
constexpr int HEIGHT = 1080;

std::unique_ptr<Camera> pCamera;

double DeltaTime = 0.0f;
double LastFrame = 0.0f;

void FrameBufferCallback(GLFWwindow * /*window*/, const int width, const int height) {
    glViewport(0, 0, width, height);
    pCamera->Reshape(width, height);
}

void MouseCallback(GLFWwindow * /*window*/, const double xpos, const double ypos) {
    pCamera->MouseControl(static_cast<float>(xpos), static_cast<float>(ypos));
}

void ScrollCallback(GLFWwindow * /*window*/, const double /*xoffset*/, const double yOffset) {
    pCamera->ProcessMouseScroll(static_cast<float>(yOffset));
}

void KeyboardCallback(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // std::cout << "DeltaTime: " << DeltaTime << std::endl;

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
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW context version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
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

    // Generate and bind a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind a Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable face culling
    glEnable(GL_CULL_FACE);

    Entity entity("../models/Moon/Moon.obj", "../shaders/moon-shaders/moon-vertex.glsl",
                  "../shaders/moon-shaders/moon-fragment.glsl");

    constexpr glm::vec3 modelPosition(0.0f, 0.0f, 0.0f);
    constexpr glm::vec3 lightPosition(0.0f, 20.0f, 0.0f);

    const Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    const std::vector<std::string> faces{
            "../textures/skybox/right.jpg", "../textures/skybox/left.jpg",
            "../textures/skybox/top.jpg",   "../textures/skybox/bottom.jpg",
            "../textures/skybox/front.jpg", "../textures/skybox/back.jpg"};

    // shader.Use();

    const Skybox skybox(faces);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        const double currentFrame = glfwGetTime();
        DeltaTime                 = currentFrame - LastFrame;
        LastFrame                 = currentFrame;

        // This is a lot smoother than using the cb
        KeyboardCallback(window);

        // Set the clear color (background color)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Create model matrix with translation
        glm::mat4 model = glm::translate(glm::mat4(1.0f), modelPosition);

        shader.SetMat4("model", model);

        glm::mat4 view       = pCamera->GetViewMatrix();
        glm::mat4 projection = pCamera->GetProjectionMatrix();
        shader.SetMat4("view", view);
        shader.SetMat4("projection", projection);

        shader.SetVec3("lightPos", lightPosition);

        entity.SetPosition(modelPosition);
        entity.SetMatrixes(model, view, projection);
        entity.Draw();

        skybox.Draw(view, projection);
        shader.Use();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
