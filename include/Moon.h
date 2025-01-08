//
// Created by mavri on 08 Jan 2025.
//

#ifndef MOON_H
#define MOON_H

#include "Entity.h"
#include "LightEmitter.h"

/**
 * @class Moon
 * @brief A class representing a Moon entity that emits light and rotates around a point.
 *
 * The Moon class inherits from the LightEmitter class and represents a moon object in the scene.
 * It handles the moon's position, size, rotation, and light emission properties.
 */
class Moon final : public LightEmitter {
public:
    /**
     * @brief Constructs a new Moon object.
     *
     * @param position The initial position of the moon.
     * @param size The size of the moon.
     * @param rotation The initial rotation of the moon.
     * @param name The name of the moon.
     */
    Moon(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
         const std::string &name);

    /**
     * @brief Default destructor.
     */
    ~Moon() override = default;

    /**
     * @brief Updates the moon's state.
     *
     * This function updates the moon's rotation and light intensity based on its position.
     *
     * @param DeltaTime The time elapsed since the last update.
     */
    void Update(float DeltaTime) override;

private:
    static constexpr float m_InitialSpeed = 0.1f; ///< The initial speed of the moon.
    float                  m_RotationSpeed; ///< The rotation speed of the moon.
    float                  m_InitialIntensity; ///< The initial light intensity of the moon.
};

#endif // MOON_H
