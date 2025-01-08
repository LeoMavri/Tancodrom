//
// Created by mavri on 07 Jan 2025.
//

#ifndef SUN_H
#define SUN_H
#include "Entity.h"
#include "LightEmitter.h"

class Sun final : public LightEmitter {
public:
    Sun(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
        const std::string &name);
    ~Sun() override = default;

    void Update() override;

    Sun *Update(float DeltaTime);

private:
    static constexpr float m_InitialSpeed = 0.1f;
    float                  m_RotationSpeed;
    float                  m_InitialIntensity;
};

#endif // SUN_H
