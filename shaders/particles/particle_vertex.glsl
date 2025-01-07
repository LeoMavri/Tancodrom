#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 offset;

void main() {
    TexCoords = aTexCoords;
    gl_Position = projection * view * vec4(aPos + offset.xy, offset.z, 1.0);
    gl_PointSize = 5.0;
}