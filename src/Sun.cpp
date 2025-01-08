//
// Created by mavri on 07 Jan 2025.
//

#include "Sun.h"

Sun::Sun(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
         const std::string &name) : LightEmitter(position, size, rotation, name) {
    m_Model = std::make_unique<Model>("../models/Sun/sun.obj", false);

    m_RotationSpeed    = 5.729f;
    m_Color            = glm::vec3(0.6f);
    m_Intensity        = 25.f;
    m_InitialIntensity = m_Intensity;
}

void Sun::Update() {
    // nothing
}

Sun *Sun::Update(const float DeltaTime) {
    // RotateAround(glm::vec3(0), 300, glm::vec3(0, 0, 1), m_RotationSpeed * DeltaTime * 5);

    // if (m_Position.y <= -2)
    // m_Intensity = 0;
    // else
    if (m_Position.y <= 2)
        m_Intensity = ((m_Position.y + 2) / 4) * m_InitialIntensity;
    else
        m_Intensity = m_InitialIntensity;

    if (m_Position.y >= 1) {
        return this;
    }

    return nullptr;
}
