//
// Created by mavri on 07 Jan 2025.
//

#include "Rocket.h"
#include <pch.h>

Rocket::Rocket(const glm::vec3 &position, const glm::vec3 &target, GLFWwindow *window,
               Camera *pCamera) :
    Entity(position, glm::vec3(1.0f), glm::vec3(0.0f), "rocket", window, pCamera),
    m_Target(target) {
    generateSphere(1.0f, 20, 20); // Generate a sphere with radius 1.0 and 20 rings and sectors
}
void Rocket::Update() {
    // nothing
}

void Rocket::generateSphere(float radius, unsigned int rings, unsigned int sectors) {
    std::vector<float>        vertices;
    std::vector<unsigned int> indices;

    for (unsigned int r = 0; r <= rings; ++r) {
        for (unsigned int s = 0; s <= sectors; ++s) {
            float y = sin(-M_PI_2 + M_PI * r / rings);
            float x = cos(2 * M_PI * s / sectors) * sin(M_PI * r / rings);
            float z = sin(2 * M_PI * s / sectors) * sin(M_PI * r / rings);

            vertices.push_back(x * radius);
            vertices.push_back(y * radius);
            vertices.push_back(z * radius);
            vertices.push_back((float) s / sectors);
            vertices.push_back((float) r / rings);
        }
    }

    for (unsigned int r = 0; r < rings; ++r) {
        for (unsigned int s = 0; s < sectors; ++s) {
            indices.push_back(r * (sectors + 1) + s);
            indices.push_back(r * (sectors + 1) + (s + 1));
            indices.push_back((r + 1) * (sectors + 1) + (s + 1));
            indices.push_back(r * (sectors + 1) + s);
            indices.push_back((r + 1) * (sectors + 1) + (s + 1));
            indices.push_back((r + 1) * (sectors + 1) + s);
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0],
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Rocket::Update(const float DeltaTime) {
    const auto direction = glm::normalize(m_Target - m_Position);
    m_Position += direction * m_Speed * DeltaTime;

    // Add a new particle to the trail
    m_TrailParticles.push_back(m_Position);

    // Remove old particles to limit the trail length
    if (m_TrailParticles.size() > 100) {
        m_TrailParticles.erase(m_TrailParticles.begin());
    }

    if (glm::distance(m_Position, m_Target) < 1.0f) {
        // Rocket reached the target, handle explosion or removal
    }
}

void Rocket::Render(Shader &shader) {
    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::translate(modelTransform, m_Position);
    modelTransform = glm::scale(modelTransform, m_Size);

    shader.Use();
    shader.SetMat4("model", modelTransform);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6 * 20 * 20, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Render the trail
    for (const auto &particle : m_TrailParticles) {
        glm::mat4 particleTransform(1.0f);
        particleTransform = glm::translate(particleTransform, particle);
        particleTransform =
                glm::scale(particleTransform, glm::vec3(0.1f)); // Smaller size for particles
        shader.SetMat4("model", particleTransform);
        glDrawElements(GL_TRIANGLES, 6 * 20 * 20, GL_UNSIGNED_INT, 0);
    }
}
