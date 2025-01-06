//
// Created by mavri on 24.12.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <Model.h>
#include <Texture.h>

class Entity {
public:
    Entity(const std::string &modelPath, const std::string &vertexShaderPath,
           const std::string &fragmentShaderPath);

    ~Entity() = default;

    void Draw();

    void SetMatrixes(const glm::mat4 &model, const glm::mat4 &view,
                     const glm::mat4 &projection) const;

    void SetPosition(const glm::vec3 &position);

    [[nodiscard]] glm::vec3 GetPosition() const;
    [[nodiscard]] Shader   &GetShader();

private:
    Model     m_Model;
    Shader    m_Shader;
    glm::vec3 m_Position{0, 0, 0};
};

#endif // ENTITY_H
