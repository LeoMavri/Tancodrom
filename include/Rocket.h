//
// Created by mavri on 07 Jan 2025.
//

#ifndef ROCKET_H
#define ROCKET_H

#include "Entity.h"

class Rocket final : public Entity {
public:
    Rocket(const glm::vec3 &position, const glm::vec3 &target, GLFWwindow *window, Camera *pCamera);
    void Update() override;
    void Update(const float DeltaTime);
    void Render(Shader &shader) override;

private:
    glm::vec3              m_Target;
    float                  m_Speed = 5.0f; // Reduced speed for slower movement
    unsigned int           VAO, VBO, EBO;
    void                   generateSphere(float radius, unsigned int rings, unsigned int sectors);
    void                   generateTrail();
    std::vector<glm::vec3> m_TrailParticles;
};

#endif // ROCKET_H
