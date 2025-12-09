#version 450 core

in vec3 modelCoordinates;
out vec4 outColor;

uniform sampler2D hdri;

const float PI = 3.14159265359;

void main()
{
    
    vec3 dir = normalize(modelCoordinates);

    float phi = atan(dir.z, dir.x);
    
    float theta = acos(dir.y);

    float u = mod(0.75 + ((phi + PI) / (2.0 * PI)), 1.0);
    
    float v = theta / PI;
    
    outColor = texture(hdri, vec2(1.0 - u, v));

}