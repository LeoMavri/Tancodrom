//
// Created by mavri on 06 Jan 2025.
//

#include <Tank.h>

#include "Camera.h"

Tank::Tank(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
           GLFWwindow *window, Camera *pCamera) :
    Entity(position, size, rotation, "tank", window, pCamera), m_pCamera(pCamera) {

    static Model *cachedModel = nullptr;
    if (!cachedModel) {
        cachedModel = new Model("../models/Tank/IS.obj", false);
    }
    m_Model = std::make_unique<Model>(*cachedModel);
}

void Tank::Update(float DeltaTime) {
    if (!m_IsSelected)
        return;

    UpdateCameraPosition();
}

void Tank::UpdateCameraPosition() const {
    constexpr float distance = 20.0f; // Fixed distance from the tank
    const auto      offset   = glm::vec3(
            distance * cos(glm::radians(m_pCamera->m_Yaw)) * cos(glm::radians(m_pCamera->m_Pitch)),
            distance * sin(glm::radians(m_pCamera->m_Pitch)),
            distance * sin(glm::radians(m_pCamera->m_Yaw)) * cos(glm::radians(m_pCamera->m_Pitch)));

    m_pCamera->SetPosition(GetPosition() + offset);
    m_pCamera->LookAt(GetPosition(), GetUp());
}

void Tank::ControlTank(GLFWwindow *window, const float DeltaTime) {
    static float    turretRotation = 0.0f;
    constexpr float RotationSpeed  = 10.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Move(GetForward() * m_Speed * DeltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Move(-GetForward() * m_Speed * DeltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        SetRotation(GetRotation() +
                    glm::vec3(0.0f, m_TurretRotationSpeed * DeltaTime * RotationSpeed, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        SetRotation(GetRotation() -
                    glm::vec3(0.0f, m_TurretRotationSpeed * DeltaTime * RotationSpeed, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        turretRotation += m_TurretRotationSpeed * static_cast<float>(DeltaTime);
    } else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        turretRotation -= m_TurretRotationSpeed * static_cast<float>(DeltaTime);
    } else {
        turretRotation = 0.0f; // Reset rotation when no key is pressed
    }

    m_Model->SetMeshTransform(1, glm::rotate(m_Model->GetMeshTransform(1),
                                             glm::radians(turretRotation), glm::vec3(0, 1, 0)));
    m_Model->SetMeshTransform(0, glm::rotate(m_Model->GetMeshTransform(0),
                                             glm::radians(turretRotation), glm::vec3(0, 1, 0)));
}

void Tank::MouseControl(const float xOffset, const float yOffset) const {
    static float lastX      = 0.0f;
    static float lastY      = 0.0f;
    static bool  firstMouse = true;

    if (firstMouse) {
        lastX      = xOffset;
        lastY      = yOffset;
        firstMouse = false;
    }

    float xChange = xOffset - lastX;
    float yChange = yOffset - lastY;

    lastX = xOffset;
    lastY = yOffset;

    xChange *= m_MouseSensitivity;
    yChange *= m_MouseSensitivity;

    // Update the camera's yaw and pitch based on mouse movement
    m_pCamera->ProcessMouseMovement(xChange, yChange);

    // Calculate the new camera position to keep it at a fixed distance from the tank's center
    constexpr float distance = 20.0f; // Fixed distance from the tank
    const auto      offset   = glm::vec3(
            distance * cos(glm::radians(m_pCamera->m_Yaw)) * cos(glm::radians(m_pCamera->m_Pitch)),
            distance * sin(glm::radians(m_pCamera->m_Pitch)),
            distance * sin(glm::radians(m_pCamera->m_Yaw)) * cos(glm::radians(m_pCamera->m_Pitch)));

    m_pCamera->SetPosition(GetPosition() + offset);
    m_pCamera->LookAt(GetPosition(), GetUp());
}
