//
// Created by mavri on 08 Jan 2025.
//

#ifndef MOON_H
#define MOON_H

#include "Entity.h"
#include "LightEmitter.h"

class Moon final : public LightEmitter {
public:
    Moon(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
         const std::string &name);
    ~Moon() override = default;

    void Update(float DeltaTime) override;

private:
    static constexpr float m_InitialSpeed = 0.1f;
    float                  m_RotationSpeed;
    float                  m_InitialIntensity;
};

#endif // MOON_H
