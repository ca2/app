#version 330 core

uniform sampler2D uTexture;

in vec2 uv;

out vec4 outColor;

void main()
{

   outColor = texture(uTexture, uv);

}
