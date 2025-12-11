// This file was automatically generated from a command line like:
// application_build_helper --inline-text "hdricube1.frag"
#pragma once


const char g_psz_hdricube1_frag[] = R"frag_text(#version 330 core

out vec4 FragColor;
in vec3 modelCoordinates;

// equirectangular projection HDRI
uniform sampler2D hdri;

const vec2 inverseAtan = vec2(0.1591, 0.3183);
vec2 sphericalToCartesian(vec3 v)
{
	vec2 xy = vec2(atan(v.x, -v.z), asin(v.y));
	xy *= inverseAtan;
	xy += 0.5;

	xy.y = 1.0 - xy.y;                 // invert Y
	return xy;
}

void main() {
	vec3 sampleDirection = normalize(modelCoordinates);
	vec2 uv = sphericalToCartesian(sampleDirection);
	vec3 color = texture(hdri, uv).rgb;
})frag_text";




