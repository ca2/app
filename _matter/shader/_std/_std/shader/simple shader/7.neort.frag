precision highp float;

uniform vec2 resolution;
uniform float time;
uniform vec2 mouse;
uniform sampler2D backbuffer;

vec3 mod289(vec3 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec2 mod289(vec2 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec3 permute(vec3 x) {
  return mod289(((x*34.0)+1.0)*x);
}

float snoise(vec2 v) {
  const vec4 C = vec4(0.211324865405187,  // (3.0-sqrt(3.0))/6.0
                      0.366025403784439,  // 0.5*(sqrt(3.0)-1.0)
                     -0.577350269189626,  // -1.0 + 2.0 * C.x
                      0.024390243902439); // 1.0 / 41.0
  // First corner
  vec2 i  = floor(v + dot(v, C.yy) );
  vec2 x0 = v -   i + dot(i, C.xx);

  // Other corners
  vec2 i1;
  i1.x = step( x0.y, x0.x ); // x0.x > x0.y ? 1.0 : 0.0
  i1.y = 1.0 - i1.x;
  i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
  // x0 = x0 - 0.0 + 0.0 * C.xx ;
  // x1 = x0 - i1 + 1.0 * C.xx ;
  // x2 = x0 - 1.0 + 2.0 * C.xx ;
  vec4 x12 = x0.xyxy + C.xxzz;
  x12.xy -= i1;

  // Permutations
  i = mod289(i); // Avoid truncation effects in permutation
  vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
		+ i.x + vec3(0.0, i1.x, 1.0 ));

  vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
  m = m*m ;
  m = m*m ;

  // Gradients: 41 points uniformly over a line, mapped onto a diamond.
  // The ring size 17*17 = 289 is close to a multiple of 41 (41*7 = 287)
  vec3 x = 2.0 * fract(p * C.www) - 1.0;
  vec3 h = abs(x) - 0.5;
  vec3 ox = floor(x + 0.5);
  vec3 a0 = x - ox;

  // Normalise gradients implicitly by scaling m
  // Approximation of: m *= inversesqrt( a0*a0 + h*h );
  m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );


  // Compute final noise value at P
  vec3 g;
  g.x  = a0.x  * x0.x  + h.x  * x0.y;
  g.yz = a0.yz * x12.xz + h.yz * x12.yw;
  return 130.0 * dot(m, g);

}

float fbm(in vec2 st) {
    float v = 0.0;
    float a = 0.5;
    vec2 shift = vec2(100.0);
    // Rotate to reduce axial bias
    mat2 rot = mat2(cos(0.5), sin(0.5), -sin(0.5), cos(0.5));
    for (int i = 0; i < 5; ++i) {
        v += a * snoise(st);
        st = rot * st * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}

void main() {
    vec2 st = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
    vec3 color = vec3(1.0);
    vec2 st2 = st;

    float lng = length(st);
    float at = atan(st.y, st.x) + lng * 5.0;
    st = vec2(cos(at) * lng, sin(at) * lng);
    st *= 1.5 + dot(lng, lng);

    st = abs(st / dot(st, st));
    color += fbm(st * 1.5 + time * 0.5);
    color = mix(color, vec3(0.8,0.5,0.5), 0.5);
    color = mix(color, vec3(0.5,0.3,0.8), fbm(st * 5.0 + time * 0.2));
    color.r += fbm(st * 2.0 + time * 0.2);

    color -= length(st2) - 0.65;
    
    float a = (color.r + color.g + color.b) / 3.0;
   

    gl_FragColor = vec4(color, a);
}