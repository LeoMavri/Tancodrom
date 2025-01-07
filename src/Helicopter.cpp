//
// Created by mavri on 06 Jan 2025.
//

#include "Helicopter.h"

Helicopter::Helicopter(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
                       GLFWwindow *window, Camera *pCamera) :
    Entity(position, size, rotation, "helicopter", window, pCamera) {
    m_Model = std::make_unique<Model>("../models/Helicopter/uh60.dae", false);

    for (int i = 0; i < m_Model->meshes.size(); ++i) {
        m_Model->SetMeshTransform(i, glm::rotate(m_Model->GetMeshTransform(i), glm::radians(90.0f),
                                                 glm::vec3(1, 0, 0)));
        m_Model->SetMeshTransform(i, glm::rotate(m_Model->GetMeshTransform(i),
                                                 glm::radians(-180.0f), glm::vec3(0, 1, 0)));
    }
}

void Helicopter::Update() {
    // nothing
}

void Helicopter::Update(const float DeltaTime) {
    m_Model->SetMeshTransform(10, glm::rotate(m_Model->GetMeshTransform(10),
                                              glm::radians(120 * DeltaTime), glm::vec3(0, 0, 1)));
    m_Model->RotateMesh(19, 120 * DeltaTime, glm::vec3(1, 0, 0));

    if (!m_IsSelected)
        return;

    bool isMoving = false;

    if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS) {
        MoveAt(Forward, DeltaTime);
        isMoving = true;
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS) {
        MoveAt(Left, DeltaTime);
        isMoving = true;
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS) {
        MoveAt(Backward, DeltaTime);
        isMoving = true;
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS) {
        MoveAt(Right, DeltaTime);
        isMoving = true;
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_Q) == GLFW_PRESS) {
        MoveAt(Up, DeltaTime);
        isMoving = true;
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_E) == GLFW_PRESS) {
        MoveAt(Down, DeltaTime);
        isMoving = true;
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_Z) == GLFW_PRESS) {
        MoveAt(SpinLeft, DeltaTime);
        isMoving = true;
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_C) == GLFW_PRESS) {
        MoveAt(SpinRight, DeltaTime);
        isMoving = true;
    }

    if (!isMoving) {
        MoveAt(None, DeltaTime);
    }
}

void Helicopter::MoveAt(const MovementType &direction, const float DeltaTime) {
    constexpr int constTiltSpeed = 60;
    const float   tiltSpeed      = constTiltSpeed * DeltaTime;

    float moveSpeed     = m_MoveSpeed * DeltaTime;
    float rotationSpeed = m_RotationSpeed * DeltaTime;

    if (direction == None) {
        if (m_Pitch != 0) {
            if (m_Pitch > 0)
                m_Pitch = (m_Pitch - tiltSpeed < 0) ? 0 : m_Pitch - tiltSpeed;
            else
                m_Pitch = (m_Pitch + tiltSpeed > 0) ? 0 : m_Pitch + tiltSpeed;
        }
        if (m_Yaw != 0) {
            if (m_Yaw > 0)
                m_Yaw = (m_Yaw - tiltSpeed < 0) ? 0 : m_Yaw - tiltSpeed;
            else
                m_Yaw = (m_Yaw + tiltSpeed > 0) ? 0 : m_Yaw + tiltSpeed;
        }
        return;
    }

    switch (direction) {
        case Forward:
            m_Pitch = (m_Pitch + tiltSpeed * 2 > m_MaxTilt) ? m_MaxTilt : m_Pitch + tiltSpeed * 2;
            Move(GetForward() * moveSpeed);
            break;
        case Backward:
            m_Pitch = (m_Pitch - tiltSpeed * 2 < -m_MaxTilt) ? -m_MaxTilt : m_Pitch - tiltSpeed * 2;
            Move(-GetForward() * moveSpeed);
            break;
        case Left:
            m_Yaw = (m_Yaw - tiltSpeed * 2 < -m_MaxTilt) ? -m_MaxTilt : m_Yaw - tiltSpeed * 2;
            Move(-GetRight() * moveSpeed);
            break;
        case Right:
            m_Yaw = (m_Yaw + tiltSpeed * 2 > m_MaxTilt) ? m_MaxTilt : m_Yaw + tiltSpeed * 2;
            Move(GetRight() * moveSpeed);
            break;
        case Up:
            Move(glm::vec3(0.0f, 1.0f, 0.0f) * moveSpeed);
            break;
        case Down:
            Move(glm::vec3(0.0f, -1.0f, 0.0f) * moveSpeed);
            break;
        case SpinLeft:
            Rotate({0, rotationSpeed, 0});
            m_Model->RotateMesh(19, 120 * DeltaTime, glm::vec3(-1, 0, 0));
            break;
        case SpinRight:
            Rotate({0, -rotationSpeed, 0});
            m_Model->RotateMesh(19, 120 * DeltaTime, glm::vec3(2, 0, 0));
            break;
    }
}

void Helicopter::Render(Shader &shader) {
    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::translate(modelTransform, m_Position);
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    modelTransform = glm::rotate(modelTransform, glm::radians(m_Yaw), glm::vec3(0.0f, 0.0f, 1.0f));
    modelTransform = glm::scale(modelTransform, m_Size);
    m_Model->Draw(shader, modelTransform);
}
