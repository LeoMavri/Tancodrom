//
// Created by mavri on 06 Jan 2025.
//

#ifndef TANK_H
#define TANK_H

#include "Camera.h"
#include "Entity.h"
#include "Rocket.h"

/**
 * @class Tank
 * @brief Represents a tank entity in the scene, inheriting from Entity.
 */
class Tank final : public Entity {
public:
    /**
     * @brief Constructs a Tank object.
     * @param position The initial position of the tank.
     * @param size The size of the tank.
     * @param rotation The rotation of the tank.
     * @param window The GLFW window associated with the tank.
     * @param pCamera Pointer to the camera associated with the tank.
     */
    Tank(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
         GLFWwindow *window, Camera *pCamera);

    /**
     * @brief Default destructor.
     */
    ~Tank() override = default;

    /**
     * @brief Updates the tank's state.
     * @param DeltaTime The time elapsed since the last update.
     */
    void Update(float DeltaTime) override;

    /**
     * @brief Updates the camera position based on the tank's position.
     */
    void UpdateCameraPosition() const;

    /**
     * @brief Controls the tank's movement and actions based on user input.
     * @param window The GLFW window associated with the tank.
     * @param DeltaTime The time elapsed since the last update.
     */
    void ControlTank(GLFWwindow *window, float DeltaTime);

    /**
     * @brief Controls the tank's camera based on mouse input.
     */
    void MouseControl() const;

    /**
     * @brief Sets the entities that the tank can interact with.
     * @param entities A vector of pointers to entities.
     */
    void SetEntities(const std::vector<Entity *> &entities);

    /**
     * @brief Renders the tank using the specified shader.
     * @param shader The shader to use for rendering.
     */
    void Render(Shader &shader) override;

    /**
     * @brief Fires a rocket from the tank.
     */
    void Fire();

private:
    Camera               *m_pCamera; ///< Pointer to the camera associated with the tank.
    std::vector<Entity *> m_Entities; ///< Entities that the tank can interact with.
    std::vector<Rocket>   m_Rockets; ///< Rockets fired by the tank.
    Entity               *m_pNearestEntity = nullptr; ///< Pointer to the nearest entity.

    static constexpr float m_TurretRotationSpeed = 1.0f; ///< The rotation speed of the turret.
    static constexpr float m_Speed               = 5.0f; ///< The movement speed of the tank.
    static constexpr float m_MouseSensitivity =
            0.1f; ///< The mouse sensitivity for controlling the tank.
    float m_TurretRotation = 0.0f; ///< The current rotation of the turret.
};

#endif // TANK_H
