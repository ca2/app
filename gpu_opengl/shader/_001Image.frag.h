// This file was automatically generated from a command line like:
// application_build_helper --inline-text "_001Image.frag"
#pragma once


const char g_psz__001Image_frag[] = R"frag_text(#version 330 core

uniform sampler2D uTexture;

//uniform mat4 colorMatrix;
//uniform vec4 colorOffset;

in vec2 uv;

out vec4 outColor;

void main()
{

   vec4 color =
      texture(uTexture, uv);

   //color =
     // colorMatrix * color + colorOffset;

   outColor = color;

})frag_text";




