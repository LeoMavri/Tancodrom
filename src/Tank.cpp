//
// Created by mavri on 06 Jan 2025.
//

#include <Tank.h>

#include "Camera.h"
#include "Rocket.h"

Tank::Tank(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
           GLFWwindow *window, Camera *pCamera) :
    Entity(position, size, rotation, "tank", window, pCamera), m_pCamera(pCamera) {

    static Model *cachedModel = nullptr;
    if (!cachedModel) {
        cachedModel = new Model("../models/Tank/IS.obj", false);
    }
    m_Model = std::make_unique<Model>(*cachedModel);
}

void Tank::Update(const float DeltaTime) {
    if (!m_IsSelected)
        return;

    for (auto &rocket : m_Rockets) {
        if (rocket.m_Exploded) {
            if (!rocket.m_ParticleSystem.m_Particles.empty()) {
                rocket.Update(DeltaTime);
            } else {
                m_Rockets.clear();
            }
        } else {
            rocket.Update(DeltaTime);
        }
    }

    UpdateCameraPosition();
    ControlTank(m_pWindow, DeltaTime);
    MouseControl();
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

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        Fire();
    }

    m_Model->SetMeshTransform(1, glm::rotate(m_Model->GetMeshTransform(1),
                                             glm::radians(turretRotation), glm::vec3(0, 1, 0)));
    m_Model->SetMeshTransform(0, glm::rotate(m_Model->GetMeshTransform(0),
                                             glm::radians(turretRotation), glm::vec3(0, 1, 0)));
}

void Tank::MouseControl() const {
    constexpr float distance = 20.0f;
    const auto      offset   = glm::vec3(
            distance * cos(glm::radians(m_pCamera->m_Yaw)) * cos(glm::radians(m_pCamera->m_Pitch)),
            -distance * sin(glm::radians(m_pCamera->m_Pitch)),
            distance * sin(glm::radians(m_pCamera->m_Yaw)) * cos(glm::radians(m_pCamera->m_Pitch)));

    m_pCamera->SetPosition(GetPosition() + offset);
    m_pCamera->LookAt(GetPosition(), GetUp());
}

void Tank::Render(Shader &shader) {
    if (m_ShouldRender) {
        glm::mat4 modelTransform(1.0f);
        modelTransform = glm::translate(modelTransform, m_Position);
        modelTransform = glm::rotate(modelTransform, glm::radians(m_Rotation.x),
                                     glm::vec3(1.0f, 0.0f, 0.0f));
        modelTransform = glm::rotate(modelTransform, glm::radians(m_Rotation.y),
                                     glm::vec3(0.0f, 1.0f, 0.0f));
        modelTransform = glm::rotate(modelTransform, glm::radians(m_Rotation.z),
                                     glm::vec3(0.0f, 0.0f, 1.0f));
        modelTransform = glm::scale(modelTransform, m_Size);

        m_Model->Draw(shader, modelTransform);
    }

    for (auto &rocket : m_Rockets) {
        if (rocket.m_Exploded) {
            if (!rocket.m_ParticleSystem.m_Particles.empty()) {
                rocket.Render(shader);
            } else {
                m_Rockets.clear();
                m_pNearestEntity->m_ShouldRender = false;
                m_pNearestEntity                 = nullptr;
            }
        } else {
            rocket.Render(shader);
        }
    }
}

void Tank::SetEntities(const std::vector<Entity *> &entities) { m_Entities = entities; }

void Tank::Fire() {
    if (!m_Rockets.empty())
        return;

    glm::mat4 barrelTransform = m_Model->GetMeshTransform(1);
    auto      barrelPosition  = glm::vec3(barrelTransform[3]);
    glm::vec3 barrelDirection = glm::normalize(glm::vec3(barrelTransform[2]));

    Entity *closestEntity   = nullptr;
    float   closestDistance = std::numeric_limits<float>::max();

    for (Entity *entity : m_Entities) {
        glm::vec3 toEntity = entity->GetPosition() - barrelPosition;
        float     distance = glm::length(toEntity);
        float angle = glm::degrees(glm::acos(glm::dot(glm::normalize(toEntity), barrelDirection)));

        if (angle < 10.0f && distance < closestDistance && entity->m_ShouldRender) {
            std::cout << "Angle: " << angle << " Distance: " << distance << std::endl;
            closestDistance = distance;
            closestEntity   = entity;
        }
    }

    if (closestEntity) {
        m_pNearestEntity         = closestEntity;
        glm::vec3 targetPosition = closestEntity->GetPosition();
        glm::vec3 toTarget       = glm::normalize(targetPosition - barrelPosition);

        // Calculate the rotation needed to point the barrel towards the target
        float     angle        = glm::degrees(glm::acos(glm::dot(barrelDirection, toTarget)));
        glm::vec3 rotationAxis = glm::cross(barrelDirection, toTarget);

        if (glm::length(rotationAxis) > 0.0f) {
            rotationAxis    = glm::normalize(rotationAxis);
            barrelTransform = glm::rotate(barrelTransform, glm::radians(angle), rotationAxis);
            m_Model->SetMeshTransform(1, barrelTransform);
            m_Model->SetMeshTransform(0, barrelTransform);
        }

        auto pos       = m_Position;
        pos.y          = -1.0f;
        auto targetPos = closestEntity->GetPosition();
        targetPos.y    = -1.0f;
        m_Rockets.emplace_back(pos, targetPos, m_pWindow, m_pCamera);
    }
}
