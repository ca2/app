#version 330 core

out vec4 outColor;
in vec3 modelCoordinates;

// equirectangular projection HDRI
uniform sampler2D hdri;

const float PI = 3.14159265359;

void main()
{
    vec3 N = normalize(modelCoordinates);

    float phi = atan(N.z, N.x);     // range: -pi..pi
    float theta = asin(N.y);        // range: -pi/2..pi/2

    float u = (phi / (2.0 * PI)) + 0.5;
    float v = (theta / PI) + 0.5;

    outColor = texture(hdri, vec2(u, v));
}
