//
// Created by mavri on 07 Jan 2025.
//

#ifndef ROCKET_H
#define ROCKET_H

#include "Entity.h"
#include "ParticleSystem.h"

/**
 * @class Rocket
 * @brief Represents a rocket entity in the simulation.
 *
 * The Rocket class inherits from the Entity class and represents a rocket that can move towards a
 * target and explode upon reaching it, triggering a particle system.
 */
class Rocket final : public Entity {
public:
    /**
     * @brief Constructs a Rocket object.
     *
     * @param position The initial position of the rocket.
     * @param target The target position the rocket is aiming for.
     * @param window A pointer to the GLFW window.
     * @param pCamera A pointer to the camera object.
     */
    Rocket(const glm::vec3 &position, const glm::vec3 &target, GLFWwindow *window, Camera *pCamera);

    /**
     * @brief Copy constructor for the Rocket class.
     *
     * @param other The Rocket object to copy from.
     */
    Rocket(const Rocket &other);

    /**
     * @brief Copy assignment operator for the Rocket class.
     *
     * @param other The Rocket object to copy from.
     * @return A reference to the assigned Rocket object.
     */
    Rocket &operator=(const Rocket &other);

    /**
     * @brief Destructor for the Rocket class.
     */
    ~Rocket() override = default;

    /**
     * @brief Updates the state of the rocket.
     *
     * This function updates the rocket's position and checks if it has reached its target.
     * If the rocket has exploded, it updates the particle system.
     *
     * @param DeltaTime The time elapsed since the last update.
     */
    void Update(float DeltaTime) override;

    /**
     * @brief Renders the rocket or its particle system.
     *
     * This function renders the rocket if it has not exploded. If the rocket has exploded,
     * it renders the particle system.
     *
     * @param shader The shader used for rendering.
     */
    void Render(Shader &shader) override;

    bool           m_Exploded{false}; ///< Indicates whether the rocket has exploded.
    ParticleSystem m_ParticleSystem{10000}; ///< The particle system used when the rocket explodes.

private:
    glm::vec3 m_Target; ///< The target position the rocket is aiming for.
    float     m_Speed = 100.0f; ///< The speed of the rocket.
};

#endif // ROCKET_H
