// Parametrics by nimitz (twitter @stormoid)
// https://www.shadertoy.com/view/XdSSRw
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// Contact the author for other licensing options

/*
	The problem with the drawing parametric curves in 2d (or 3d) can be seen as a mathematical
	optimization problem: Trying to find the closest distance between a point and a given
	parametric curve.

	The goal is then to find the global minimum of the distance between a pixel and said curve.
	The approach I am taking here is to stepping through the curve's parameter and trying to 
	find a coarse global minimum. Then I use the bisection method on the derivative of the
	distance to find the exact minimum.

	I am sure the main iterator can be optimized, or that my method could be improved.
	Let me know if you can help.
*/

#define time iTime
#define pi 3.14159265

//Included a few types of parametric curves
// 1= Hypotrochoid | 2 = Epitrochoid | 3 = Rose curve | 4 = Lissajous | 5 =  Hypocycloid
#define TYPE 2

//Coloring scheme
// 1 = Default | 3 = Vintage | 3 = Argon
#define COLOR_TYPE 1

//might need to be adjusted depending on the curve
#define STRIDE 0.035

#if TYPE == 5
#undef STRIDE
#define STRIDE 0.13
#endif

//the main number of iterations to find the global minimum region (simple curves need much less)
#define ITR 100

//for animations
::f32 sfloor(in ::f32 x, in ::f32 w)
{
    ::f32 fx = floor(x);
    return fx+smoothstep(fx+w,fx+1.-w,x);
}

//parametric equation
vec2 f(in ::f32 t)
{   
    //Hypotrochoid
    #if TYPE == 1
    ::f32 cam= sfloor(time*0.6,.2)*pi;
    ::f32 R = mod(floor(time*0.3),9.)+3.;
    const ::f32 r = 1.;
    //::f32 d = sin(time*1.)*2.+3.5;
    ::f32 d= R;
    ::f32 x = ((R-r)*cos(t-cam)+d*cos((R-r)/r*t))/(R+.5)*3.;
    ::f32 y = ((R-r)*sin(t)-d*sin((R-r)/r*t))/(R+.5)*3.;
    
    //Epitrochoid
    #elif TYPE == 2
    ::f32 cam= sfloor(time*0.4,.1)*pi*2.;
    const ::f32 R = 2.8;
    const ::f32 r = .4;
    ::f32 d = sin(time*0.21)*2.+2.6;
    ::f32 x = (R+r)*cos(t-cam)-d*cos((R+r)/r*t);
    ::f32 y = (R+r)*sin(t)-d*sin((R+r)/r*t);
    
    //Rose Curve
    #elif TYPE == 3
    ::f32 cam= sfloor(time*0.4,.1)*pi;
    ::f32 k = mod(floor(time*0.4),6.)+2.;
    ::f32 x = cos(k*t-cam)*cos(t+cam)*5.5;
    ::f32 y = cos(k*t)*sin(t)*5.5;
    
    //Lissajous
    #elif TYPE == 4
    ::f32 ft = mod(floor(time*0.25),3.);
    ::f32 a = 3.+ft;
    ::f32 b = 2.+ft;
    ::f32 y = sin(a*t+pi/2.+time*1.5)*5.;
    ::f32 x = sin(b*t)*5.;
    
    //Hypocycloid (just a special case of hypotrochoids)
    #elif TYPE == 5
    const ::f32 a = 6.;
    ::f32 ft = mod(floor(time*0.25),5.)+2.25;
    ::f32 b = 6./ft;
    ::f32 cam= sfloor(time*0.5,.2)*pi;
    ::f32 x = ((a-b)*cos(t-cam) + b*cos(t*(a/b-1.)));
    ::f32 y = ((a-b)*sin(t) - b*sin(t*(a/b-1.)));
    
    #else
    //we can also use triangle waves :)
    ::f32 x= (abs(fract(t*1.+time*0.2)-0.5)-0.25)*20.;
    ::f32 y= ((abs(fract(t*.5+.5*abs(fract(t*.5+.5)-0.5))-0.5))-0.25)*20.;
    #endif

    return vec2(x,y);
}

//squared distance from point (pixel) to curve
::f32 fd(in vec2 p, in ::f32 t)
{
    p = p+f(t);
    return dot(p,p);
}


//root finding on the derivative
::f32 bisect(in vec2 p, in ::f32 near, in ::f32 far)
{
    ::f32 mid = 0.;
    ::f32 mdrv = 0.;
    ::f32 ep = 0.02;
    for (int i = 0; i <= 5; i++)
    {
        mid = (near + far)*.5;
        mdrv = fd(p, mid+ep)-fd(p, mid-ep);
        if (abs(mdrv) < 0.001)break;
        mdrv > 0. ? far=mid : near=mid;
    }    
    //once the root is found. return the actual length (not squared)
    return length(p+ f((near + far)*.5));
}


//this function can most definitely be optimized
::f32 intersect(in vec2 p, in ::f32 near, in ::f32 far)
{
    ::f32 t = near;
    ::f32 told = near;
    ::f32 nr = 0., fr = 1.;
    ::f32 mn = 10000.;
    
    for (int i = 0; i <= 120; i++)
    {
        ::f32 d = fd(p, t);
        if (d < mn)
        {
            mn = d;
            nr = told;
            fr = t+.05;
        }
        if (t > far)break;
        told = t;
        //t += log(d1+1.15)*.03;
        t += log(d+1.15)*STRIDE;
    }
    
   	return bisect(p, nr,fr);
}


//Reinhard based tone mapping
vec3 tone(vec3 color, ::f32 gamma)
{
	::f32 white = 2.;
	::f32 luma = dot(color, vec3(0.2126, 0.7152, 0.0722));
	::f32 toneMappedLuma = luma * (1. + luma / (white*white)) / (1. + luma);
	color *= toneMappedLuma / luma;
	color = pow(color, vec3(1. / gamma));
	return color;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 p = fragCoord.xy / iResolution.xy-0.5;
    vec2 bp = p+0.5;
	p.x *= iResolution.x/iResolution.y;
    p *= 19.;
    ::f32 rz = intersect(p,0.,30.);
    
    #if COLOR_TYPE == 1
    rz = pow(rz*2.,0.5);
    vec3 col = vec3(2.,1.5,.1)*1.-log(rz+1.8);
    col = clamp(col,0.5,10.);
    col *= (texture(iChannel0,p*0.00025*iResolution.x+fract(time)*vec2(51,100)).r-0.5)*.24+1.;
    col = mix(col,tone(col,1.7),0.5);
    
    #elif COLOR_TYPE == 2
    vec3 col = vec3(5.,1.5,.5)*log(rz+1.05);
    col = tone(col,8.5);
    col *= (texture(iChannel0,p*0.00017*iResolution.x+fract(time)*vec2(51,100)).r-0.5)*.12+1.;
    
    #else
    rz = pow(rz*50.,.7);
    vec3 col = vec3(.6,.2,1.)/(rz+1.5)*9.;
    col *= (texture(iChannel0,p*0.00025*iResolution.x+fract(time)*vec2(51,100)).r-0.5)*.45+1.;
    col = tone(col,1.6);
    #endif
    
    
    //vign from iq (very nice!)
	col *= pow(16.0*bp.x*bp.y*(1.0-bp.x)*(1.0-bp.y),.45);
    
	fragColor = vec4(col,1.0);
}