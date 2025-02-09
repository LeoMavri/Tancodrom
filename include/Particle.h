//
// Created by mavri on 07 Jan 2025.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <pch.h>

/**
 * @struct Particle
 * @brief A structure representing a single particle in a particle system.
 *
 * The Particle struct contains properties for position, velocity, color, and life span.
 */
struct Particle {
    glm::vec3 Position; ///< The position of the particle.
    glm::vec3 Velocity; ///< The velocity of the particle.
    glm::vec4 Color; ///< The color of the particle.
    float     Life; ///< The remaining life of the particle.

    /**
     * @brief Default constructor for the Particle struct.
     *
     * Initializes the particle with default values.
     */
    Particle() = default;

    /**
     * @brief Equality operator for comparing two particles.
     *
     * @param other The other particle to compare with.
     * @return True if the particles are equal, false otherwise.
     */
    bool operator==(const Particle &other) const;
};

#endif // PARTICLE_H
