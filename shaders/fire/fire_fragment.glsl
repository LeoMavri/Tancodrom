#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform float time;

void main() {
    vec2 uv = TexCoords;
    uv.y += time * 0.5; // Animate the texture coordinates
    vec4 texColor = texture(texture1, uv);
    vec3 fireColor = vec3(1.0, 0.5, 0.0); // Orange-ish color
    FragColor = vec4(fireColor * texColor.rgb, texColor.a);
}