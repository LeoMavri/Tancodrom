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
    Rocket(const Rocket &other);
    Rocket &operator=(const Rocket &other);
    ~Rocket() override = default;

    void Update(float DeltaTime) override;
    void Render(Shader &shader) override;

    bool           m_Exploded{false};
    ParticleSystem m_ParticleSystem{10000};

private:
    glm::vec3 m_Target;
    float     m_Speed = 25.0f;
};

#endif // ROCKET_H
