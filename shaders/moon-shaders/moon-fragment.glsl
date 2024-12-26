#version 450 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in mat3 TBN;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D displacementMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // Obtain normal from normal map in range [0,1]
    vec3 normal = texture(normalMap, TexCoords).rgb;
    // Transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(TBN * normal);

    // Obtain displacement from displacement map
    float displacement = texture(displacementMap, TexCoords).r;

    // Ambient
    vec3 ambient = 0.2 * texture(diffuseMap, TexCoords).rgb;

    // Diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    diff = smoothstep(0.0, 1.0, diff); // Smooth transition
    vec3 diffuse = diff * texture(diffuseMap, TexCoords).rgb;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    spec = smoothstep(0.0, 1.0, spec); // Smooth transition
    vec3 specular = vec3(0.2) * spec;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}