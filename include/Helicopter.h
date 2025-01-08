//
// Created by mavri on 06 Jan 2025.
//

#ifndef HELICOPTER_H
#define HELICOPTER_H
#include "Camera.h"
#include "Entity.h"
#include "Rocket.h"

enum MovementType { None, Forward, Backward, Left, Right, Up, Down, SpinLeft, SpinRight };

class Helicopter final : public Entity {
public:
    Helicopter(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
               GLFWwindow *window, Camera *pCamera);
    ~Helicopter() override = default;

    void Update(const float DeltaTime) override;

    void Render(Shader &shader) override;
    void UpdateCameraPosition() const;
    void LaunchRocket();
    void MoveAt(const MovementType &direction, float DeltaTime);

private:
    float m_Pitch = 0;
    float m_Yaw   = 0;

    std::vector<Rocket> m_Rockets;

    static constexpr float m_RotationSpeed = 30.0f;
    static constexpr float m_MoveSpeed     = 6.0f;
    static constexpr float m_MaxTilt       = 30.0f;
    static constexpr float m_TiltSpeed     = 15.0f;
};

#endif // HELICOPTER_H
