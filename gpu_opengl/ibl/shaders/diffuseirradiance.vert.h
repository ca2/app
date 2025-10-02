// This file was automatically generated from a command line like:
// application_build_helper --inline-text "diffuseirradiance.vert"
#pragma once


const char g_psz_diffuseirradiance_vert[] = R"vert_text(#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 modelCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	modelCoordinates = aPos;
})vert_text";




