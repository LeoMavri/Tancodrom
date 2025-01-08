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

    [[nodiscard]] glm::mat4        GetLightSpaceMatrix() const;
    [[nodiscard]] static glm::mat4 GetLightProjection();
    [[nodiscard]] glm::mat4        GetLightView() const;

    void Update(float DeltaTime) override;

    glm::vec3 m_Color;
    float     m_Intensity;
};

#endif // LIGHTEMITTER_H
