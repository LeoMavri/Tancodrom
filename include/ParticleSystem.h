//
// Created by mavri on 07 Jan 2025.
//

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <Particle.h>
#include <Shader.h>

/**
 * @class ParticleSystem
 * @brief A class representing a particle system.
 *
 * The ParticleSystem class manages a collection of particles, updating their states and rendering
 * them.
 */
class ParticleSystem {
public:
    /**
     * @brief Constructs a new ParticleSystem object.
     *
     * @param maxParticles The maximum number of particles in the system.
     */
    explicit ParticleSystem(unsigned int maxParticles);

    /**
     * @brief Updates the state of the particle system.
     *
     * This function updates the position, color, and life of each particle based on the elapsed
     * time.
     *
     * @param deltaTime The time elapsed since the last update.
     */
    void Update(float deltaTime);

    /**
     * @brief Renders the particles in the system.
     *
     * This function renders all active particles using the provided view and projection matrices.
     *
     * @param view The view matrix.
     * @param projection The projection matrix.
     */
    void Render(const glm::mat4 &view, const glm::mat4 &projection);

    /**
     * @brief Triggers an explosion of particles at a given position.
     *
     * This function respawns all particles at the specified position, simulating an explosion.
     *
     * @param position The position of the explosion.
     */
    void Explode(const glm::vec3 &position);

    std::vector<Particle> m_Particles; ///< The collection of particles in the system.

private:
    Shader       m_Shader; ///< The shader used for rendering particles.
    unsigned int maxParticles; ///< The maximum number of particles in the system.
    unsigned int lastUsedParticle; ///< The index of the last used particle.

    /**
     * @brief Finds an unused particle in the system.
     *
     * This function searches for a particle with no remaining life and returns its index.
     *
     * @return The index of an unused particle.
     */
    unsigned int FindUnusedParticle();

    /**
     * @brief Respawns a particle at a given position.
     *
     * This function initializes a particle's properties, such as position, color, life, and
     * velocity.
     *
     * @param particle The particle to respawn.
     * @param position The position to respawn the particle at.
     */
    static void RespawnParticle(Particle &particle, const glm::vec3 &position);
};

#endif // PARTICLESYSTEM_H
