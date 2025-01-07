//
// Created by mavri on 07 Jan 2025.
//

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <Particle.h>
#include <Shader.h>

class ParticleSystem {
public:
    explicit ParticleSystem(unsigned int maxParticles);

    void Update(float deltaTime);
    void Render(const glm::mat4 &view, const glm::mat4 &projection);

    void Explode(const glm::vec3 &position);

private:
    std::vector<Particle> m_Particles;
    Shader                m_Shader{"../shaders/particles/particle_vertex.glsl",
                    "../shaders/particles/particle_fragment.glsl"};
    unsigned int          maxParticles;
    unsigned int          lastUsedParticle;

    unsigned int FindUnusedParticle();
    static void  RespawnParticle(Particle &particle, const glm::vec3 &position);
};

#endif // PARTICLESYSTEM_H
