precision highp float;

uniform vec2 resolution;
uniform float time;

#define t time
#define r resolution
#define o gl_FragColor

void main(void) {
    vec3 u=vec3(2.*gl_FragCoord.xy-r.xy,r.y)/3e2;
    u=normalize(vec3(u.xy,sqrt(max(u.z*u.z-dot(u.xy,u.xy)*2.,0.))));
    for(int i=0;i<2;i++){    //i<6
        float l=length(u);
        u.xz+=sin(u.z+t*.2+l);
        u.y+=cos(u.x+t*.6);
    o += vec4(cos(l + vec3(.3,.1,0)), 1.);
}}

//void main(){vec3 u=vec3(2.*gl_FragCoord.xy-r.xy,r.y)/3e2;u=normalize(vec3(u.xy,sqrt(max(u.z*u.z-dot(u.xy,u.xy)*2.,0.))));for(int i=0;i<2;i++){float l=length(u);u.xz+=sin(u.z+t*.2+l);u.y+=cos(u.x+t*.6);o+=cos(l+vec4(.3,.1,0,0));}}