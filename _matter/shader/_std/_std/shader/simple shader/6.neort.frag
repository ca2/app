/* FileF1: June 2020 */
precision highp float;

uniform vec2 resolution;
uniform float time;
uniform vec2 mouse;
uniform sampler2D backbuffer;


vec2 coord(in vec2 p) {
    p = p / resolution.xy;
    
    if (resolution.x > resolution.y) {
        p.x *= resolution.x / resolution.y;
        p.x += (resolution.y - resolution.x) / resolution.y / 2.0;
    } else {
        p.y *= resolution.y / resolution.x;
        p.y += (resolution.x - resolution.y) / resolution.x / 2.0;
    }
    
    p -= 0.5;
    p *= vec2(-1.0, 1.0);
    return p;
}
#define rx 1.0 / min(resoltion.x, resoltion.y)
#define uv gl_FragCoord.xy / resoltion.xy
#define st coord(gl_FragCoord.xy)
#define mx coord(u_mouse)

vec3 random3(vec3 c) {
    float j = 4096.0*sin(dot(c,vec3(17.0, 59.4, 15.0)));
    vec3 r;
    r.z = fract(512.0*j);
    j *= .125;
    r.x = fract(512.0*j);
    j *= .125;
    r.y = fract(512.0*j);
    return r-0.5;
}

const float F3 =  0.3333333;
const float G3 =  0.1666667;
float snoise(vec3 p) {

    vec3 s = floor(p + dot(p, vec3(F3)));
    vec3 x = p - s + dot(s, vec3(G3));

    vec3 e = step(vec3(0.0), x - x.yzx);
    vec3 i1 = e*(1.0 - e.zxy);
    vec3 i2 = 1.0 - e.zxy*(1.0 - e);

    vec3 x1 = x - i1 + G3;
    vec3 x2 = x - i2 + 2.0*G3;
    vec3 x3 = x - 1.0 + 3.0*G3;

    vec4 w, d;

    w.x = dot(x, x);
    w.y = dot(x1, x1);
    w.z = dot(x2, x2);
    w.w = dot(x3, x3);

    w = max(0.6 - w, 0.0);

    d.x = dot(random3(s), x);
    d.y = dot(random3(s + i1), x1);
    d.z = dot(random3(s + i2), x2);
    d.w = dot(random3(s + 1.0), x3);

    w *= w;
    w *= w;
    d *= w;

    return dot(d, vec4(52.0));
}

vec4 normalNoise(vec2 _st, float _zoom, float _speed){
    vec2 v1 = _st;
    vec2 v2 = _st;
    vec2 v3 = _st;
    float expon = pow(10.0, _zoom*2.0);
    v1 /= 1.0*expon;
    v2 /= 0.62*expon;
    v3 /= 0.83*expon;
    float n = time*_speed;
    //float nb = (snoise(vec3(v1, n)) + snoise(vec3(v2, n)) + snoise(vec3(v3, n))) / 3.0 + 0.4;
    n = time * _speed + 1000.0;
	float na = (snoise(vec3(v1, n)) + snoise(vec3(v2, n)) + snoise(vec3(v3, n))) / 2.0 + 0.2;
    return vec4(1.0,1.0,1.0,na);
}

#define NUM_OCTAVES 6
vec4 fbm(vec2 x) {
    vec4 v = vec4(0.0);
    float a = 0.5;
    vec2 shift = vec2(100);
    // Rotate to reduce axial bias
    mat2 rot = mat2(cos(0.5), sin(0.5), -sin(0.5), cos(0.50));
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * normalNoise(x * 5. , 0.1, 0.1);
        x = rot * x * 2.0 + shift;
        a *= .5;
    }
    return v;
}

void main() {
    vec4 baseColor = vec4(
        fbm(st + vec2(fbm(st + vec2(fbm(st)))))
    );
    gl_FragColor = vec4(baseColor);
}