//
// Created by mavri on 07 Jan 2025.
//

#ifndef ROCKET_H
#define ROCKET_H

#include "Entity.h"
#include "ParticleSystem.h"

class Rocket final : public Entity {
public:
    Rocket(const glm::vec3 &position, const glm::vec3 &target, GLFWwindow *window, Camera *pCamera);

    void Update() override;
    void Update(float DeltaTime);
    void Render(Shader &shader) override;

private:
    glm::vec3      m_Target;
    float          m_Speed = 25.0f;
    bool           m_Exploded{false};
    ParticleSystem m_ParticleSystem{10000}; // Initialize with 100 m_Particles
};

#endif // ROCKET_H
