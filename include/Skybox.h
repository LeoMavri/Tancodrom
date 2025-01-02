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

private:
    void loadCubemap(const std::vector<std::string> &faces);
    void setupSkybox();

    GLuint skyboxVAO{}, skyboxVBO{}, cubemapTexture{};
    Shader skyboxShader;
};

#endif // SKYBOX_H
