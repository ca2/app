#version 450
layout(location = 0) in vec3 outColor;
layout(location = 0) out vec4 outFragColor;

void main() {
    outFragColor = vec4(outColor, 1.0);
}
