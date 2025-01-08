//
// Created by mavri on 07 Jan 2025.
//

#include "LightEmitter.h"

#include <utility>

LightEmitter::LightEmitter(const glm::vec3 &position, const glm::vec3 &size,
                           const glm::vec3 &rotation, const std::string &name) :
    Entity(position, size, rotation, name, nullptr, nullptr), m_Intensity(0.0f) {}

glm::mat4 LightEmitter::GetLightSpaceMatrix() const {
    return GetLightProjection() * GetLightView();
}

glm::mat4 LightEmitter::GetLightProjection() {
    constexpr float nearPlane = 0.1f;
    constexpr float farPlane  = 200.f;
    return glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, nearPlane, farPlane);
}

glm::mat4 LightEmitter::GetLightView() const {
    return glm::lookAt(m_Position, GetForward(), {0, 1.0f, 0});
}

void LightEmitter::Update(float DeltaTime) {}
