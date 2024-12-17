#include "../include/Camera.h"
#include "../include/Shader.h"
#include "../lib/pch.h"

constexpr int WIDTH  = 2560;
constexpr int HEIGHT = 1440;

constexpr float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

std::unique_ptr<Camera> pCamera;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    pCamera->Reshape(width, height);
}

void mouse_callback(GLFWwindow *window, const double xpos, const double ypos) {
    std::cout << std::format("Mouse position: ({}, {})\n", xpos, ypos);
    pCamera->MouseControl(static_cast<float>(xpos), static_cast<float>(ypos));
}

void scroll_callback(GLFWwindow *window, const double xoffset, const double yOffset) {
    std::cout << std::format("Scroll offset: ({}, {})\n", xoffset, yOffset);
    pCamera->ProcessMouseScroll(static_cast<float>(yOffset));
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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetScrollCallback(window, scroll_callback);

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    // Generate and bind a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind a Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // TODO: Implement camera movement + other stuff
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();

        glm::mat4 view       = pCamera->GetViewMatrix();
        glm::mat4 projection = pCamera->GetProjectionMatrix();
        shader.SetMat4("view", view);
        shader.SetMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
