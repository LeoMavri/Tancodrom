//
// Created by mavri on 02 Jan 2025.
//

#include <Skybox.h>
#include <pch.h>
#include <stb_image.h>

Skybox::Skybox(const std::vector<std::string> &faces) :
    skyboxShader("../shaders/skybox/skybox_vertex.glsl", "../shaders/skybox/skybox_fragment.glsl") {
    setupSkybox();
    loadCubemap(faces);

    skyboxShader.Use();
}

void Skybox::setupSkybox() {
    constexpr float scale            = 50.0f;
    constexpr float skyboxVertices[] = {
            -1.0f * scale, 1.0f * scale,  -1.0f * scale, -1.0f * scale, -1.0f * scale,
            -1.0f * scale, 1.0f * scale,  -1.0f * scale, -1.0f * scale, 1.0f * scale,
            -1.0f * scale, -1.0f * scale, 1.0f * scale,  1.0f * scale,  -1.0f * scale,
            -1.0f * scale, 1.0f * scale,  -1.0f * scale,

            -1.0f * scale, -1.0f * scale, 1.0f * scale,  -1.0f * scale, -1.0f * scale,
            -1.0f * scale, -1.0f * scale, 1.0f * scale,  -1.0f * scale, -1.0f * scale,
            1.0f * scale,  -1.0f * scale, -1.0f * scale, 1.0f * scale,  1.0f * scale,
            -1.0f * scale, -1.0f * scale, 1.0f * scale,

            1.0f * scale,  -1.0f * scale, -1.0f * scale, 1.0f * scale,  -1.0f * scale,
            1.0f * scale,  1.0f * scale,  1.0f * scale,  1.0f * scale,  1.0f * scale,
            1.0f * scale,  1.0f * scale,  1.0f * scale,  1.0f * scale,  -1.0f * scale,
            1.0f * scale,  -1.0f * scale, -1.0f * scale,

            -1.0f * scale, -1.0f * scale, 1.0f * scale,  -1.0f * scale, 1.0f * scale,
            1.0f * scale,  1.0f * scale,  1.0f * scale,  1.0f * scale,  1.0f * scale,
            1.0f * scale,  1.0f * scale,  1.0f * scale,  -1.0f * scale, 1.0f * scale,
            -1.0f * scale, -1.0f * scale, 1.0f * scale,

            -1.0f * scale, 1.0f * scale,  -1.0f * scale, 1.0f * scale,  1.0f * scale,
            -1.0f * scale, 1.0f * scale,  1.0f * scale,  1.0f * scale,  1.0f * scale,
            1.0f * scale,  1.0f * scale,  -1.0f * scale, 1.0f * scale,  1.0f * scale,
            -1.0f * scale, 1.0f * scale,  -1.0f * scale,

            -1.0f * scale, -1.0f * scale, -1.0f * scale, -1.0f * scale, -1.0f * scale,
            1.0f * scale,  1.0f * scale,  -1.0f * scale, -1.0f * scale, 1.0f * scale,
            -1.0f * scale, -1.0f * scale, -1.0f * scale, -1.0f * scale, 1.0f * scale,
            1.0f * scale,  -1.0f * scale, 1.0f * scale};

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          static_cast<void *>(nullptr));
    glBindVertexArray(0);
}

void Skybox::loadCubemap(const std::vector<std::string> &faces) {
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::Draw(const glm::mat4 &view, const glm::mat4 &projection) const {
    glDepthFunc(GL_LEQUAL);

    const auto viewMatrix = glm::mat4(glm::mat3(view));

    skyboxShader.Use();
    skyboxShader.SetMat4("view", viewMatrix);
    skyboxShader.SetMat4("projection", projection);

    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
}
