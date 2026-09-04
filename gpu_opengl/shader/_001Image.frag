#version 330 core

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

}