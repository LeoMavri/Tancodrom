//
// Created by mavri on 24.12.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <Model.h>
#include <Texture.h>

#include "Camera.h"

using ModelUPtr = std::unique_ptr<Model>;

/**
 * @class Entity
 * @brief A class representing an entity in a 3D environment.
 */
class Entity {
public:
    /**
     * @brief Constructor for the Entity class.
     * @param position Initial position of the entity.
     * @param size Size of the entity.
     * @param rotation Initial rotation of the entity.
     * @param name Name of the entity.
     * @param window Pointer to the GLFW window.
     * @param pCamera Pointer to the camera.
     */
    Entity(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
           std::string name, GLFWwindow *window, Camera *pCamera);

    /**
     * @brief Copy constructor for the Entity class.
     * @param other The other entity to copy from.
     */
    Entity(const Entity &other);

    /**
     * @brief Copy assignment operator for the Entity class.
     * @param other The other entity to copy from.
     * @return A reference to this entity.
     */
    Entity &operator=(const Entity &other);

    /**
     * @brief Destructor for the Entity class.
     */
    virtual ~Entity() = default;

    /**
     * @brief Get the name of the entity.
     * @return The name of the entity.
     */
    std::string GetName();

    /**
     * @brief Update the entity.
     * @param DeltaTime Time elapsed since the last frame.
     */
    virtual void Update(float DeltaTime) = 0;

    /**
     * @brief Set the model for the entity.
     * @param path Path to the model file.
     * @param bSmoothNormals Whether to smooth normals.
     * @param modelId ID of the model.
     */
    void SetModel(const std::string &path, bool bSmoothNormals, int modelId);

    /**
     * @brief Set the model for the entity.
     * @param model Pointer to the model.
     */
    void SetModel(Model *model);

    /**
     * @brief Get the model of the entity.
     * @return Pointer to the model.
     */
    [[nodiscard]] Model *GetModel() const;

    /**
     * @brief Get the position of the entity.
     * @return The position of the entity.
     */
    [[nodiscard]] glm::vec3 GetPosition() const;

    /**
     * @brief Set the position of the entity.
     * @param position The new position of the entity.
     */
    void SetPosition(const glm::vec3 &position);

    /**
     * @brief Move the entity in a given direction.
     * @param direction The direction to move the entity.
     */
    void Move(const glm::vec3 &direction);

    /**
     * @brief Move the entity towards a point.
     * @param point The target point.
     * @param speed The speed of movement.
     */
    void MoveTowards(const glm::vec3 &point, float speed);

    /**
     * @brief Get the rotation of the entity.
     * @return The rotation of the entity.
     */
    [[nodiscard]] glm::vec3 GetRotation() const;

    /**
     * @brief Set the rotation of the entity.
     * @param rotation The new rotation of the entity.
     */
    void SetRotation(const glm::vec3 &rotation);

    /**
     * @brief Make the entity look at a target point.
     * @param targetPoint The target point.
     * @param up The up vector.
     */
    void LookAt(const glm::vec3 &targetPoint, const glm::vec3 &up);

    /**
     * @brief Rotate the entity around a point.
     * @param point The point to rotate around.
     * @param distance The distance from the point.
     * @param axis The axis of rotation.
     * @param speed The speed of rotation.
     */
    void RotateAround(const glm::vec3 &point, float distance, const glm::vec3 &axis, float speed);

    /**
     * @brief Rotate the entity in a given direction.
     * @param direction The direction to rotate the entity.
     */
    void Rotate(const glm::vec3 &direction);

    /**
     * @brief Rotate the entity towards a target point.
     * @param targetPoint The target point.
     * @param rotationSpeed The speed of rotation.
     */
    void RotateTowards(const glm::vec3 &targetPoint, float rotationSpeed);

    /**
     * @brief Get the size of the entity.
     * @return The size of the entity.
     */
    [[nodiscard]] glm::vec3 GetSize() const;

    /**
     * @brief Set the size of the entity.
     * @param size The new size of the entity.
     */
    void SetSize(const glm::vec3 &size);

    /**
     * @brief Get the forward vector of the entity.
     * @return The forward vector of the entity.
     */
    [[nodiscard]] glm::vec3 GetForward() const;

    /**
     * @brief Get the right vector of the entity.
     * @return The right vector of the entity.
     */
    [[nodiscard]] glm::vec3 GetRight() const;

    /**
     * @brief Get the up vector of the entity.
     * @return The up vector of the entity.
     */
    [[nodiscard]] glm::vec3 GetUp() const;

    /**
     * @brief Set the selected state of the entity.
     * @param isSelected Whether the entity is selected.
     */
    void SetSelected(bool isSelected);

    /**
     * @brief Check if the entity is selected.
     * @return True if the entity is selected, false otherwise.
     */
    [[nodiscard]] bool IsSelected() const;

    /**
     * @brief Get the model matrix of the entity.
     * @return The model matrix of the entity.
     */
    [[nodiscard]] glm::mat4 GetModelMatrix() const;

    /**
     * @brief Normalize the rotation of the entity.
     */
    void NormalizeRotation();

    /**
     * @brief Render the entity.
     * @param shader The shader to use for rendering.
     */
    virtual void Render(Shader &shader);

    bool m_ShouldRender{true};

protected:
    std::string            m_Name; ///< Name of the entity
    std::unique_ptr<Model> m_Model; ///< Model of the entity
    glm::vec3              m_Position{0, 0, 0}; ///< Position of the entity
    glm::vec3              m_Rotation{0, 0, 0}; ///< Rotation of the entity
    glm::vec3              m_Size{1, 1, 1}; ///< Size of the entity
    Camera                *m_pCamera; ///< Pointer to the camera
    GLFWwindow            *m_pWindow; ///< Pointer to the GLFW window
    bool                   m_IsSelected{false}; ///< Whether the entity is selected
};

#endif // ENTITY_H
