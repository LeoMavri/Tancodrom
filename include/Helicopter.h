//
// Created by mavri on 06 Jan 2025.
//

#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "Camera.h"
#include "Entity.h"
#include "Rocket.h"

/**
 * @enum MovementType
 * @brief Enum representing different types of movement for the Helicopter.
 */
enum MovementType { None, Forward, Backward, Left, Right, Up, Down, SpinLeft, SpinRight };

/**
 * @class Helicopter
 * @brief A class representing a helicopter entity in the game.
 */
class Helicopter final : public Entity {
public:
    /**
     * @brief Constructor for the Helicopter class.
     * @param position The initial position of the helicopter.
     * @param size The size of the helicopter.
     * @param rotation The initial rotation of the helicopter.
     * @param window Pointer to the GLFW window.
     * @param pCamera Pointer to the camera.
     */
    Helicopter(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
               GLFWwindow *window, Camera *pCamera);

    /**
     * @brief Destructor for the Helicopter class.
     */
    ~Helicopter() override = default;

    /**
     * @brief Updates the state of the helicopter.
     * @param DeltaTime The time elapsed since the last update.
     */
    void Update(float DeltaTime) override;

    /**
     * @brief Renders the helicopter.
     * @param shader The shader used for rendering.
     */
    void Render(Shader &shader) override;

    /**
     * @brief Updates the position of the camera relative to the helicopter.
     */
    void UpdateCameraPosition() const;

    /**
     * @brief Launches a rocket from the helicopter.
     * @param position The initial position of the rocket.
     */
    void LaunchRocket(const glm::vec3 &position);

    /**
     * @brief Moves the helicopter in a specified direction.
     * @param direction The direction to move the helicopter.
     * @param DeltaTime The time elapsed since the last update.
     */
    void MoveAt(const MovementType &direction, float DeltaTime);

    /**
     * @brief Sets the entities that the helicopter interacts with.
     * @param entities A vector of pointers to the entities.
     */
    void SetEntities(const std::vector<Entity *> &entities) { m_Entities = entities; }

private:
    float m_Pitch = 0; ///< The pitch of the helicopter.
    float m_Yaw   = 0; ///< The yaw of the helicopter.

    std::vector<Rocket>   m_Rockets; ///< The rockets launched by the helicopter.
    std::vector<Entity *> m_Entities; ///< The entities that the helicopter interacts with.

    static constexpr float m_RotationSpeed = 30.0f; ///< The rotation speed of the helicopter.
    static constexpr float m_MoveSpeed     = 6.0f; ///< The movement speed of the helicopter.
    static constexpr float m_MaxTilt       = 30.0f; ///< The maximum tilt angle of the helicopter.
    static constexpr float m_TiltSpeed     = 15.0f; ///< The tilt speed of the helicopter.
};

#endif // HELICOPTER_H
