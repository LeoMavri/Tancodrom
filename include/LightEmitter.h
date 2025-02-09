//
// Created by mavri on 07 Jan 2025.
//

#ifndef LIGHTEMITTER_H
#define LIGHTEMITTER_H

#include "Entity.h"

/**
 * @class LightEmitter
 * @brief A class representing a light-emitting entity in a 3D environment.
 *
 * The LightEmitter class inherits from the Entity class and represents a light source in the game
 * world. It provides methods to get the light space matrix, light projection, and light view.
 */
class LightEmitter : public Entity {
public:
    /**
     * @brief Constructor for the LightEmitter class.
     * @param position Initial position of the light emitter.
     * @param size Size of the light emitter.
     * @param rotation Initial rotation of the light emitter.
     * @param name Name of the light emitter.
     */
    LightEmitter(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
                 const std::string &name);

    /**
     * @brief Get the light space matrix of the light emitter.
     * @return The light space matrix.
     */
    [[nodiscard]] glm::mat4 GetLightSpaceMatrix() const;

    /**
     * @brief Get the light projection matrix.
     * @return The light projection matrix.
     */
    [[nodiscard]] static glm::mat4 GetLightProjection();

    /**
     * @brief Get the light view matrix of the light emitter.
     * @return The light view matrix.
     */
    [[nodiscard]] glm::mat4 GetLightView() const;

    /**
     * @brief Update the light emitter.
     * @param DeltaTime Time elapsed since the last frame.
     */
    void Update(float DeltaTime) override;

    glm::vec3 m_Color; ///< Color of the light emitted.
    float     m_Intensity; ///< Intensity of the light emitted.
};

#endif // LIGHTEMITTER_H
