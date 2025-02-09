//
// Created by mavri on 07 Jan 2025.
//

#ifndef SUN_H
#define SUN_H

#include "Entity.h"
#include "LightEmitter.h"

/**
 * @class Sun
 * @brief Represents a sun entity in the scene, inheriting from LightEmitter.
 */
class Sun final : public LightEmitter {
public:
    /**
     * @brief Constructs a Sun object.
     * @param position The initial position of the sun.
     * @param size The size of the sun.
     * @param rotation The rotation of the sun.
     * @param name The name of the sun entity.
     */
    Sun(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
        const std::string &name);

    /**
     * @brief Default destructor.
     */
    ~Sun() override = default;

    /**
     * @brief Updates the sun's state.
     * @param DeltaTime The time elapsed since the last update.
     */
    void Update(float DeltaTime) override;

private:
    static constexpr float m_InitialSpeed = 0.1f; ///< The initial speed of the sun.
    float                  m_RotationSpeed; ///< The rotation speed of the sun.
    float                  m_InitialIntensity; ///< The initial intensity of the sun's light.
};

#endif // SUN_H
