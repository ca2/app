// This file was automatically generated from a command line like:
// application_build_helper --inline-text "equirectangular_cubemap.frag"
#pragma once


const ::i8 g_psz_hdricube_frag[] = R"frag_text(#version 450 core

in vec3 modelCoordinates;
out vec4 outColor;

uniform sampler2D hdri;

const ::f32 PI = 3.14159265359;

void main()
{
    
    vec3 dir = normalize(modelCoordinates);

    ::f32 phi = atan(dir.z, dir.x);
    
    ::f32 theta = acos(dir.y);

    ::f32 u = mod(0.75 + ((phi + PI) / (2.0 * PI)), 1.0);
    
    ::f32 v = theta / PI;
    
    outColor = texture(hdri, vec2(1.0 - u, v));

})frag_text";




