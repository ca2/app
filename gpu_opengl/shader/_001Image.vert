#version 330 core

uniform vec4 quad;
// source UV: left, bottom, right, top

out vec2 uv;

void main()
{

   const vec2 pos[4] = vec2[](
      vec2(-1.0, -1.0),
      vec2(-1.0,  1.0),
      vec2( 1.0, -1.0),
      vec2( 1.0,  1.0)
   );

   const vec2 tex[4] = vec2[](
      vec2(0.0, 0.0),
      vec2(0.0, 1.0),
      vec2(1.0, 0.0),
      vec2(1.0, 1.0)
   );

   gl_Position =
      vec4(pos[gl_VertexID], 0.0, 1.0);

   vec2 uvFull =
      tex[gl_VertexID];

   uv = vec2(
      mix(quad.x, quad.z, uvFull.x),
      mix(quad.y, quad.w, uvFull.y)
   );

}
