//
// Created by mavri on 07 Jan 2025.
//

#include "ParticleSystem.h"

#include <random>

unsigned int quadVAO = 0;
unsigned int quadVBO;

ParticleSystem::ParticleSystem(const unsigned int maxParticles) :
    maxParticles(maxParticles), lastUsedParticle(0) {
    m_Particles.resize(maxParticles);

    float particleQuad[] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, 1.0f, 0.0f,
                            0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 1.0f};

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleQuad), particleQuad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glBindVertexArray(0);
}

void ParticleSystem::Update(const float deltaTime) {
    for (auto &particle : m_Particles) {
        if (particle.Life > 0.0f) {
            particle.Life -= deltaTime;
            if (particle.Life > 0.0f) {
                particle.Position += particle.Velocity * deltaTime;
                particle.Color.a -= deltaTime * 0.5f;

                if (particle.Color.a <= 0.4f) {
                    particle.Life = 0.0f;
                }
            }
        }
    }
}

void ParticleSystem::Render(const glm::mat4 &view, const glm::mat4 &projection) {
    m_Shader.Use();
    m_Shader.SetMat4("view", view);
    m_Shader.SetMat4("projection", projection);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glBindVertexArray(quadVAO);
    for (const auto &particle : m_Particles) {
        if (particle.Life > 0.0f) {
            m_Shader.SetVec3("offset", particle.Position);
            m_Shader.SetVec4("color", particle.Color);
            glDrawArrays(GL_POINTS, 0, 1);
        }
    }
    glBindVertexArray(0);

    glDisable(GL_BLEND);
    glDisable(GL_PROGRAM_POINT_SIZE);
}

void ParticleSystem::Explode(const glm::vec3 &position) {
    for (unsigned int i = 0; i < maxParticles; ++i) {
        RespawnParticle(m_Particles[i], position);
    }
}

unsigned int ParticleSystem::FindUnusedParticle() {
    for (unsigned int i = lastUsedParticle; i < maxParticles; ++i) {
        if (m_Particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    for (unsigned int i = 0; i < lastUsedParticle; ++i) {
        if (m_Particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    lastUsedParticle = 0;
    return 0;
}

void ParticleSystem::RespawnParticle(Particle &particle, const glm::vec3 &position) {
    static std::random_device rd;
    static std::mt19937       gen(rd());

    static std::uniform_real_distribution<> disColor(0.5, 1.0);
    static std::uniform_real_distribution<> disVelocity(-1.0, 1.0);
    static std::uniform_real_distribution<> disRadius(0.0, 5.0);
    static std::uniform_real_distribution<> disTheta(0.0, 2.0 * M_PI);
    static std::uniform_real_distribution<> disPhi(M_PI,
                                                   M_PI); // Limit to upper hemisphere

    const float rColor = disColor(gen);
    const float radius = disRadius(gen);
    const float theta  = disTheta(gen);
    const float phi    = disPhi(gen);

    particle.Position.x = position.x + radius * sin(phi) * cos(theta);
    particle.Position.y = position.y + radius * sin(phi) * sin(theta);
    particle.Position.z = position.z + radius * cos(phi);
    particle.Color      = glm::vec4(1.0f, rColor, 0.0f, 1.0f); // Yellow-orange gradient
    particle.Life       = 1.5f;
    particle.Velocity   = glm::vec3(disVelocity(gen), disVelocity(gen), disVelocity(gen));
}
