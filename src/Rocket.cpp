//
// Created by mavri on 07 Jan 2025.
//

#include "Rocket.h"
#include <pch.h>

Rocket::Rocket(const glm::vec3 &position, const glm::vec3 &target, GLFWwindow *window,
               Camera *pCamera) :
    Entity(position, glm::vec3(1.0f), glm::vec3(0.0f), "rocket", window, pCamera),
    m_Target(target) {

    static Model *cachedModel = nullptr;
    if (!cachedModel) {
        cachedModel = new Model("../models/Rocket/rocket.obj", false);
    }

    m_Model = std::make_unique<Model>(*cachedModel);
}

Rocket::Rocket(const Rocket &other) = default;

Rocket &Rocket::operator=(const Rocket &other) {
    if (this != &other) {
        Entity::operator=(other);
        m_Target         = other.m_Target;
        m_Exploded       = other.m_Exploded;
        m_Speed          = other.m_Speed;
        m_ParticleSystem = other.m_ParticleSystem;
    }
    return *this;
}

void Rocket::Update(const float DeltaTime) {
    if (m_Exploded) {
        m_ParticleSystem.Update(DeltaTime);
        return;
    }

    const auto direction = glm::normalize(m_Target - m_Position);
    m_Position += direction * m_Speed * DeltaTime;

    if (glm::distance(m_Position, m_Target) < 1.0f) {
        m_Exploded = true;
        m_ParticleSystem.Explode(m_Position);
    }
}

void Rocket::Render(Shader &shader) {
    if (m_Exploded) {
        m_ParticleSystem.Render(m_pCamera->GetViewMatrix(), m_pCamera->GetProjectionMatrix());
        return;
    }

    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::translate(modelTransform, m_Position);

    const auto direction = glm::normalize(m_Target - m_Position);
    glm::vec3  up(0.0f, 1.0f, 0.0f);
    const auto right    = glm::normalize(glm::cross(up, direction));
    up                  = glm::cross(direction, right);
    const auto rotation = glm::mat4(glm::vec4(right, 0.0f), glm::vec4(up, 0.0f),
                                    glm::vec4(direction, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    modelTransform *= rotation;
    modelTransform = glm::scale(modelTransform, {0.1f, 0.1f, 0.1f});

    shader.Use();
    shader.SetMat4("model", modelTransform);

    m_Model->Draw(shader, modelTransform);
}
