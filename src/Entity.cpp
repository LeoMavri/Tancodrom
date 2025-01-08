//
// Created by mavri on 24.12.2024.
//

#include "Entity.h"

#include <utility>

Entity::Entity(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
               std::string name, GLFWwindow *window, Camera *pCamera) :
    m_Name{std::move(name)}, m_Model{nullptr}, m_Position{position}, m_Rotation{rotation},
    m_Size{size}, m_pCamera{pCamera}, m_pWindow{window} {}

void Entity::SetModel(std::string const &path, const bool bSmoothNormals, const int modelId) {
    m_Model = std::make_unique<Model>(path, bSmoothNormals, modelId);
}

Entity::Entity(const Entity &other) :
    m_Name(other.m_Name), m_Model(std::make_unique<Model>(*other.m_Model)),
    m_Position(other.m_Position), m_Rotation(other.m_Rotation), m_Size(other.m_Size),
    m_pCamera(other.m_pCamera), m_pWindow(other.m_pWindow) {}

Entity &Entity::operator=(const Entity &other) {
    if (this != &other) {
        m_Name     = other.m_Name;
        m_Model    = std::make_unique<Model>(*other.m_Model);
        m_Position = other.m_Position;
        m_Rotation = other.m_Rotation;
        m_Size     = other.m_Size;
        m_pWindow  = other.m_pWindow;
        m_pCamera  = other.m_pCamera;
    }
    return *this;
}

void Entity::SetModel(Model *model) { m_Model = std::make_unique<Model>(*model); }

Model *Entity::GetModel() const { return m_Model.get(); }

std::string Entity::GetName() { return m_Name; }

glm::vec3 Entity::GetPosition() const { return m_Position; }

void Entity::SetPosition(const glm::vec3 &position) { m_Position = position; }

void Entity::Move(const glm::vec3 &direction) { m_Position += direction; }

void Entity::MoveTowards(const glm::vec3 &point, const float speed) {
    const auto direction        = glm::normalize(point - m_Position);
    const auto displacement     = direction * speed;
    const auto distanceToTarget = glm::distance(point, m_Position);

    if (glm::length(displacement) > distanceToTarget)
        m_Position = point;
    else
        m_Position += displacement;
}

glm::vec3 Entity::GetRotation() const { return m_Rotation; }

glm::vec3 Entity::GetForward() const {
    const auto rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(m_Rotation)));

    const auto forward = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

    return glm::normalize(forward);
}

glm::vec3 Entity::GetRight() const {
    const auto rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(m_Rotation)));

    const auto right = glm::vec3(rotationMatrix * glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));

    return glm::normalize(right);
}

glm::vec3 Entity::GetUp() const {
    const auto rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(m_Rotation)));

    const auto up = glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

    return glm::normalize(up);
}
void Entity::SetSelected(const bool isSelected) { m_IsSelected = isSelected; }

bool Entity::IsSelected() const { return m_IsSelected; }

void Entity::SetRotation(const glm::vec3 &rotation) {
    m_Rotation = rotation;

    NormalizeRotation();
}

void Entity::Rotate(const glm::vec3 &direction) {
    m_Rotation += direction;

    NormalizeRotation();
}

float AngleBetweenVectors(glm::vec3 vec1, glm::vec3 vec2) {
    vec1 = glm::normalize(vec1);
    vec2 = glm::normalize(vec2);

    const auto dotProduct = glm::dot(vec1, vec2);

    const auto angle = glm::acos(dotProduct);

    return glm::degrees(angle);
}

void Entity::RotateTowards(const glm::vec3 &targetPoint, const float rotationSpeed) {
    const auto targetDirection = glm::normalize(targetPoint - m_Position);

    const auto angleToTarget = AngleBetweenVectors(GetForward(), targetDirection);

    const auto maxRotation = rotationSpeed;

    if (std::abs(angleToTarget) > maxRotation) {
        const auto rotationAxis      = glm::cross(GetForward(), targetDirection);
        const auto sign              = glm::sign(angleToTarget);
        const auto rotationDirection = rotationAxis * sign;

        Rotate(rotationDirection * maxRotation);
    } else {
        Rotate(targetDirection * angleToTarget);
    }
}

void Entity::RotateAround(const glm::vec3 &point, const float distance, const glm::vec3 &axis,
                          const float speed) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(speed), axis);
    glm::vec4 newPosition    = rotationMatrix * glm::vec4(m_Position - point, 1.0f);
    newPosition              = glm::normalize(newPosition) * distance;

    m_Position = glm::vec3(newPosition) + point;
}

void Entity::LookAt(const glm::vec3 &targetPoint, const glm::vec3 &up) {
    const auto direction = glm::normalize(targetPoint - m_Position);

    // Calculate rotation around Y axis (yaw)
    const auto yaw = glm::degrees(atan2(direction.z, direction.x)) - 90.0f;

    // Calculate rotation around X axis (pitch)
    const auto pitch = glm::degrees(asin(direction.y));

    // Set the new rotation
    const glm::vec3 newRotation(-pitch, -yaw, 0);
    SetRotation(newRotation);
}

glm::vec3 Entity::GetSize() const { return m_Size; }

void Entity::SetSize(const glm::vec3 &size) { m_Size = size; }

void Entity::NormalizeRotation() {
    m_Rotation.x = std::fmod(m_Rotation.x, 360.0f);
    m_Rotation.y = std::fmod(m_Rotation.y, 360.0f);
    m_Rotation.z = std::fmod(m_Rotation.z, 360.0f);
}

void Entity::Render(Shader &shader) {
    if (!m_Model) {
        std::cout << "Entity::Render: Model is not set" << std::endl;
        return;
    }

    if (!m_ShouldRender)
        return;

    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::translate(modelTransform, m_Position);
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelTransform = glm::scale(modelTransform, m_Size);

    m_Model->Draw(shader, modelTransform);
}

glm::mat4 Entity::GetModelMatrix() const {
    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::translate(modelTransform, m_Position);
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelTransform =
            glm::rotate(modelTransform, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelTransform = glm::scale(modelTransform, m_Size);
    return modelTransform;
}
