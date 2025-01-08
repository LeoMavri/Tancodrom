//
// Created by mavri on 02 Jan 2025.
//

#ifndef SKYBOX_H
#define SKYBOX_H

#include <Shader.h>
#include <pch.h>

class Skybox {
public:
    explicit Skybox(const std::vector<std::string> &faces);

    void Draw(const glm::mat4 &view, const glm::mat4 &projection) const;

    void SetSkyboxHue(float hue) const;

private:
    void LoadCubemap(const std::vector<std::string> &faces);
    void SetupSkybox();

    Shader m_Shader;
    GLuint m_SkyboxVAO{}, m_SkyboxVBO{}, m_CubemapTexture{};
};

#endif // SKYBOX_H
