precision highp float;
uniform vec2 resolution;
uniform vec2 mouse;
uniform float time;
uniform sampler2D backbuffer;

mat2 rot(float r){
  return mat2(cos(r),sin(r),-sin(r),cos(r));
}


float PI = acos(-1.);

vec2 pmod(vec2 p,float n){
  float np = PI*2./n;
  float r = atan(p.x,p.y)-0.5*np;
  r =  mod(r,np)-0.5*np;
  return length(p)*vec2(cos(r),sin(r));
}

float cube(vec3 p,vec3 s){
  vec3 q =abs(p);
  vec3 m = max(s-q,0.);
  return length(max(q-s,0.))-min(min(m.x,m.y),m.z);
}

float tube(vec3 p){
  float st = max(abs(p.z)-0.2,0.);
  return length(vec2(length(p.xy)-0.02,st));
}

vec4 cllo(vec3 p,float s){
  vec3 col = vec3(0.5,1.,2.);
  float ex = 999.;
  float s1 = cube(p,vec3(ex,s,s));
  float s2 = cube(p,vec3(s,ex,s));
  float s3 = cube(p,vec3(s,s,ex));
  if(s1<s2&&s1<s3){
    col = vec3(2.,0.4,0.7);
  }
  return vec4(col,min(min(s1,s2),s3));
}

vec4 dist(vec3 p){
  
  vec3 sp = p;
  
  p.z -= -3.*time;
  

  p.xy = pmod(p.xy,9.);
  
    for(int i =0;i<4;i++){
    p = abs(p)-0.3;
    p.xy *= rot(floor(2.*time));
  }
  
  
  float k = 2.;
  p = mod(p,k)-0.5*k;
  vec4 rsd =cllo(p,0.15); 
  vec3 col = rsd.xyz*exp(-2.0*rsd.w)*4.;
  
  p = sp;
  float kz = 0.6;
  p.z += -time;
  p.x += cos(time+p.z*0.8);
  p.z = mod(p.z,kz)-0.5*kz;
  p.xy = pmod(p.xy,6.);
  p.x -= 0.9;
  float ds = tube(p);
  float d = min(ds,rsd.w);
  if(d<rsd.w) col = 0.8/ds*vec3(0.05,1.3,0.05);
  return vec4(col,d);
}

vec3 gn(vec3 p){
  vec2 e = vec2(0.0001,0.);
  return normalize(vec3(
    dist(p+e.xyy).w-dist(p-e.xyy).w,
    dist(p+e.yxy).w-dist(p-e.yxy).w,
    dist(p+e.yyx).w-dist(p-e.yyx).w
    ));
}

void main(){vec2 r=resolution,p=(gl_FragCoord.xy*2.-r)/min(r.x,r.y);
vec2 uv = gl_FragCoord.xy/r;
p.xy *= rot(time*0.2);
float rs = 1.2;
float kt = time*0.3;
vec3 ro  = vec3(rs*cos(kt),rs*sin(kt),0.);
vec3 ta = vec3(0.,0.,3.);
vec3 cdir = normalize(ta-ro);
vec3 side = cross(cdir,vec3(0,1,0));
vec3 up = cross(side,cdir);
vec3 rd = normalize(p.x*side+p.y*up+cdir*0.3);
float d,t=1.;
float esp = 0.0001;
vec3 ac = vec3(0.);
for(int i = 0;i<66;i++){
  vec4 rsd = dist(ro+rd*t);
  d = rsd.w;
  t += d*0.7;
  ac += rsd.xyz;
  if(d<esp)break;
}

vec3 sp = ro+rd*t;

vec3 col = ac*0.006;
if(d<esp){
  vec3 no = gn(sp);
  rd = reflect(rd,no);
  ro = sp;
  t = 0.01;
  ac *= 0.;
  for(int i = 0;i<66;i++){
    vec4 rsd = dist(ro+rd*t);
    d = rsd.w;
    t += d*0.7;
    ac += rsd.xyz;
    if(d<esp)break;
  }
  col += ac*0.003;
}

col *= 0.8;

col = clamp(col,vec3(0.),vec3(1.));
col = pow(col,vec3(1.8));
gl_FragColor=vec4(col,1);}