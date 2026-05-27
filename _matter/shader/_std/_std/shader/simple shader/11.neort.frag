#version 330 core
precision highp ::f32;

uniform vec2 resolution;
uniform ::f32 time;
uniform vec2 mouse;
uniform sampler2D backbuffer;


vec3 wave(vec2 uv,::f32 speed, ::f32 thickness, ::f32 amplitude, ::f32 delay, vec3 color){
   //bure shake
   ::f32 shake = mix(0.0, 1.0, amplitude);
   //wave
   ::f32 wave = sin(delay + mod(uv.x+uv.y/2.0,0.25) * 1.0 - time * speed ) / 5.0 * shake;
   //colwave
   ::f32 colwave = thickness /  abs((1.0-length(uv))+wave); //線の太さ
   //color
   return color * colwave;
}
   
::f32 random (in vec2 st) {
      return fract(cos(dot(st.xy,
                           vec2(12.9898,78.233)))
                  * 43758.5453123);
}



void main(void) {
   vec2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / min(resolution.x, resolution.y);
      
   vec3 col0 = wave(uv,0.1,0.08,8.0,5., vec3(0.6, 0.6, 0.6));
   vec3 col1 = wave(uv,0.2,0.08,9.0,6., vec3(0.4, 0.9, 0.9));
   vec3 col2 = wave(uv,0.2,0.08,10.0,7., vec3(0.6, 0.9, 0.9));
   vec3 col3 = wave(uv,0.1,0.08,11.0,8., vec3(0.6, 0.6, 0.6));

   vec3 col = col0+col1+col2+col3;

   gl_FragColor = vec4(vec3(col), 1.0);
}


