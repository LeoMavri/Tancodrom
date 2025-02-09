#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform vec4 color;

void main() {
    float distance = length(gl_PointCoord - vec2(0.5));
    if (distance > 0.5) {
        discard;
    }
    float alpha = 1.0 - distance * 2.0; // Adjust alpha based on distance for glow effect
    FragColor = vec4(color.rgb, alpha) * color.a;
}