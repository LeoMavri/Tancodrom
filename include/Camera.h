//
// Created by mavri on 17.12.2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <pch.h>

/**
 * @enum CameraMovementType
 * @brief Enum representing the different types of camera movement.
 */
enum CameraMovementType { UNKNOWN, FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

/**
 * @class Camera
 * @brief A class representing a camera in a 3D environment.
 */
class Camera {
    static constexpr float zNEAR = 0.1f; ///< Near clipping plane
    static constexpr float zFAR  = 10000.f; ///< Far clipping plane
    static constexpr float YAW   = -90.0f; ///< Default m_Yaw angle
    static constexpr float PITCH = 0.0f; ///< Default m_Pitch angle
    static constexpr float FOV   = 45.0f; ///< Default field of view
    glm::vec3              m_StartPosition; ///< Initial position of the camera

public:
    /**
     * @brief Constructor for the Camera class.
     * @param width Width of the viewport.
     * @param height Height of the viewport.
     * @param position Initial position of the camera.
     */
    Camera(int width, int height, const glm::vec3 &position);

    /**
     * @brief Get the view matrix of the camera.
     * @return The view matrix.
     */
    [[nodiscard]] glm::mat4 GetViewMatrix() const;

    /**
     * @brief Get the position of the camera.
     * @return The position of the camera.
     */
    [[nodiscard]] const glm::vec3 &GetPosition() const;

    /**
     * @brief Get the projection matrix of the camera.
     * @return The projection matrix.
     */
    [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

    /**
     * @brief Set the camera parameters.
     * @param width Width of the viewport.
     * @param height Height of the viewport.
     * @param position Position of the camera.
     */
    void Set(int width, int height, const glm::vec3 &position);

    /**
     * @brief Reset the camera to its initial parameters.
     * @param width Width of the viewport.
     * @param height Height of the viewport.
     */
    void Reset(int width, int height);

    /**
     * @brief Reshape the camera viewport.
     * @param windowWidth New width of the viewport.
     * @param windowHeight New height of the viewport.
     */
    void Reshape(int windowWidth, int windowHeight);

    /**
     * @brief Process keyboard input for camera movement.
     * @param direction Direction of the movement.
     * @param deltaTime Time elapsed since the last frame.
     */
    void ProcessKeyboard(const CameraMovementType &direction, float deltaTime);

    /**
     * @brief Process mouse movement input.
     * @param xPos X position of the mouse.
     * @param yPos Y position of the mouse.
     */
    void MouseControl(float xPos, float yPos);

    /**
     * @brief Process mouse scroll input.
     * @param yOffset Offset of the scroll input.
     */
    void ProcessMouseScroll(float yOffset);

    void SetPosition(const glm::vec3 &position);

    void LookAt(const glm::vec3 &targetPoint, const glm::vec3 &up);

    /**
     * @brief Process mouse movement.
     * @param xOffset Offset in the X direction.
     * @param yOffset Offset in the Y direction.
     */
    void ProcessMouseMovement(float xOffset, float yOffset);

private:
    /**
     * @brief Update the camera vectors based on the current yaw and pitch.
     */
    void UpdateCameraVectors();

public:
    static constexpr float m_CameraSpeed      = 10.0f; ///< Camera movement speed
    static constexpr float m_MouseSensitivity = 0.1f; ///< Mouse sensitivity

    float m_ZNear; ///< Near clipping plane
    float m_ZFar; ///< Far clipping plane
    float m_FoVy; ///< Field of view
    int   m_Width; ///< Width of the viewport
    int   m_Height; ///< Height of the viewport
    bool  m_IsPerspective; ///< Perspective projection flag

    glm::vec3 m_Position; ///< Position of the camera
    glm::vec3 m_Forward; ///< Forward vector of the camera
    glm::vec3 m_Right; ///< Right vector of the camera
    glm::vec3 m_Up; ///< Up vector of the camera
    glm::vec3 m_WorldUp; ///< World up vector

    float m_Yaw; ///< Yaw angle
    float m_Pitch; ///< Pitch angle

    bool  m_FirstMouseMove = true; ///< Flag for the first mouse movement
    float m_LastX = 0.f, m_LastY = 0.f; ///< Last mouse positions
};

#endif // CAMERA_H
