//
// Created by mavri on 07 Jan 2025.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <pch.h>

struct Particle {
    glm::vec3 Position;
    glm::vec3 Velocity;
    glm::vec4 Color;
    float     Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) {}

    bool operator==(const Particle &other) const {
        return Position == other.Position && Velocity == other.Velocity && Color == other.Color &&
               Life == other.Life;
    }
};

#endif // PARTICLE_H
