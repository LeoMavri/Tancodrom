//
// Created by mavri on 24.12.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <Model.h>
#include <Texture.h>

#include "Camera.h"

using ModelUPtr = std::unique_ptr<Model>;

class Entity {
public:
    Entity(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
           std::string name, GLFWwindow *window, Camera *pCamera);

    Entity(const Entity &other); // Copy constructor
    Entity &operator=(const Entity &other); // Copy assignment operator
    virtual ~Entity() = default;

    std::string GetName();

    virtual void Update(float DeltaTime) = 0;

    void                 SetModel(const std::string &path, bool bSmoothNormals, int modelId);
    void                 SetModel(Model *model);
    [[nodiscard]] Model *GetModel() const;

    [[nodiscard]] glm::vec3 GetPosition() const;
    void                    SetPosition(const glm::vec3 &position);
    void                    Move(const glm::vec3 &direction);
    void                    MoveTowards(const glm::vec3 &point, float speed);

    [[nodiscard]] glm::vec3 GetRotation() const;
    void                    SetRotation(const glm::vec3 &rotation);
    void                    LookAt(const glm::vec3 &targetPoint, const glm::vec3 &up);
    void RotateAround(const glm::vec3 &point, float distance, const glm::vec3 &axis, float speed);
    void Rotate(const glm::vec3 &direction);
    void RotateTowards(const glm::vec3 &targetPoint, float rotationSpeed);

    [[nodiscard]] glm::vec3 GetSize() const;
    void                    SetSize(const glm::vec3 &size);

    [[nodiscard]] glm::vec3 GetForward() const;
    [[nodiscard]] glm::vec3 GetRight() const;
    [[nodiscard]] glm::vec3 GetUp() const;

    void               SetSelected(const bool isSelected) { m_IsSelected = isSelected; }
    [[nodiscard]] bool IsSelected() const { return m_IsSelected; }

    [[nodiscard]] glm::mat4 GetModelMatrix() const;

    void NormalizeRotation();

    virtual void Render(Shader &shader);

    bool m_ShouldRender{true};

protected:
    std::string            m_Name;
    std::unique_ptr<Model> m_Model;
    glm::vec3              m_Position{0, 0, 0}, m_Rotation{0, 0, 0}, m_Size{1, 1, 1};
    Camera                *m_pCamera;
    GLFWwindow            *m_pWindow;
    bool                   m_IsSelected{false};
};

#endif // ENTITY_H
