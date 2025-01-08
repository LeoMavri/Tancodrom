//
// Created by mavri on 06 Jan 2025.
//

#ifndef TANK_H
#define TANK_H
#include "Camera.h"
#include "Entity.h"

class Rocket;
class Tank final : public Entity {
public:
    Tank(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
         GLFWwindow *window, Camera *pCamera);
    ~Tank() override = default;

    void Update(float DeltaTime) override;
    void UpdateCameraPosition() const;

    void ControlTank(GLFWwindow *window, float DeltaTime);
    void MouseControl() const;

    void SetEntities(const std::vector<Entity *> &entities);

    void Render(Shader &shader) override;

    void Fire();

private:
    Camera               *m_pCamera;
    std::vector<Entity *> m_Entities;

    std::vector<Rocket> m_Rockets;
    Entity             *m_pNearestEntity = nullptr;

    static constexpr float m_TurretRotationSpeed = 1.0f;
    static constexpr float m_Speed               = 5.0f;
    static constexpr float m_MouseSensitivity    = 0.1f;
    float                  m_TurretRotation      = 0.0f;
};

#endif // TANK_H
