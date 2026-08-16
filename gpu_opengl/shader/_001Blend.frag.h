// This file was automatically generated from a command line like:
// application_build_helper --inline-text "_001Blend.frag"
#pragma once


const char g_psz__001Blend_frag[] = R"frag_text(#version 330 core

uniform sampler2D uTexture;

in vec2 uv;

out vec4 outColor;

void main()
{

   outColor = texture(uTexture, uv);

}
)frag_text";




