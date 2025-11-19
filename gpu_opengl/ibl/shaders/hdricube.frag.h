// This file was automatically generated from a command line like:
// application_build_helper --inline-text "hdricube.frag"
#pragma once


const char g_psz_hdricube_frag[] = R"frag_text(#version 330 core

out vec4 FragColor;
in vec3 modelCoordinates;

// equirectangular projection HDRI
uniform sampler2D hdri;

vec2 sphericalToCartesian(vec3 v)
{
    float phi = atan(v.z, -v.x);       // horizontal angle
    float theta = asin(v.y);          // vertical angle

    // normalize to 0..1
    vec2 uv;
    uv.x = 0.5 + phi * (0.15915494309189535);   // 1 / (2π)
    uv.y = 0.5 - theta * (0.3183098861837907);  // 1 / π (note the minus!)

    return uv;
}

void main() {
	vec3 sampleDirection = normalize(modelCoordinates);
	vec2 uv = sphericalToCartesian(sampleDirection);
	vec3 color = texture(hdri, uv).rgb;

	FragColor = vec4(color, 1.0);
})frag_text";




