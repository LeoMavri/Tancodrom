//
// Created by mavri on 24.12.2024.
//

#include "Entity.h"

Entity::Entity(const std::string &modelPath, const std::string &vertexShaderPath,
               const std::string &fragmentShaderPath) :
    m_Model(modelPath, true), m_Shader(vertexShaderPath, fragmentShaderPath) {}

void Entity::Draw() {
    m_Shader.Use();
    m_Shader.SetInt("diffuseMap", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Model.GetTextureID());

    if (m_Model.GetTextureID() == 0) {
        std::cerr << "Error: Texture ID is 0. Texture might not be loaded correctly." << std::endl;
    }

    m_Model.Draw(m_Shader);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Entity::SetMatrixes(const glm::mat4 &model, const glm::mat4 &view,
                         const glm::mat4 &projection) const {
    m_Shader.SetMat4("model", model);
    m_Shader.SetMat4("view", view);
    m_Shader.SetMat4("projection", projection);
}

void Entity::SetPosition(const glm::vec3 &position) {
    m_Position = position;
    m_Shader.SetVec3("position", m_Position);
}

glm::vec3 Entity::GetPosition() const { return m_Position; }

Shader &Entity::GetShader() { return m_Shader; }
