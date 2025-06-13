#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 color;
uniform float color_alpha;
uniform float roughness; // Range: [0.0, 1.0],      0.0 = smooth,        1.0 = rough
uniform float metallic;  // Range: [0.0, 1.0],      0.0 = dielectric,    1.0 = metallic

void main()
{
    FragColor = texture(texture1, TexCoord) * vec4(color, 1.0);

    // Sample base color from texture and apply uniform color
    vec4 baseColor = texture(texture1, TexCoord) * vec4(color, color_alpha);

    // Simple PBR-like modulation
    // Roughness affects diffuse contribution (simplified)
    float diffuseFactor = 1.0 - roughness;
    vec3 diffuse = baseColor.rgb * diffuseFactor;

    // Metallic affects how much the material takes on the environment's color vs. its own
    vec3 finalColor = mix(diffuse, color * metallic, metallic);

    // Apply alpha from color_alpha uniform
    FragColor = vec4(finalColor, baseColor.a);
}
