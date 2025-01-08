//
// Created by mavri on 07 Jan 2025.
//

#ifndef LIGHTEMITTER_H
#define LIGHTEMITTER_H

#include "Entity.h"

class LightEmitter : public Entity {
public:
    LightEmitter(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &rotation,
                 const std::string &name);

    glm::mat4 GetLightSpaceMatrix();
    glm::mat4 GetLightProjection();
    glm::mat4 GetLightView();

    void Update() override;

    glm::vec3 m_Color;
    float     m_Intensity;
};

#endif // LIGHTEMITTER_H
