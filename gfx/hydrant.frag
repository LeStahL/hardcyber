#version 130

uniform float iTime;
uniform vec2 iResolution;

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);

void rand(in vec2 x, out float n)
{
    x += 400.;
    n = fract(sin(dot(sign(x)*abs(x) ,vec2(12.9898,78.233)))*43758.5453);
}


void lfnoise(in vec2 t, out float n)
{
    vec2 i = floor(t);
    t = fract(t);
    t = smoothstep(c.yy, c.xx, t);
    vec2 v1, v2;
    rand(i, v1.x);
    rand(i+c.xy, v1.y);
    rand(i+c.yx, v2.x);
    rand(i+c.xx, v2.y);
    v1 = c.zz+2.*mix(v1, v2, t.y);
    n = mix(v1.x, v1.y, t.x);
}

void mfnoise(in vec2 x, in float d, in float b, in float e, out float n)
{
    n = 0.;
    float a = 1., nf = 0., buf;
    for(float f = d; f<b; f *= 2.)
    {
        lfnoise(f*x, buf);
        n += a*buf;
        a *= e;
        nf += 1.;
    }
    n *= (1.-e)/(1.-pow(e, nf));
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash11(in float p, out float d)
{
    p = fract(p * .1031);
    p *= p + 33.33;
    p *= p + p;
    d = fract(p);
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash12(in vec2 p, out float d)
{
	vec3 p3  = fract(vec3(p.xyx) * .1031);
    p3 += dot(p3, p3.yzx + 33.33);
    d = fract((p3.x + p3.y) * p3.z);
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash21(in float p, out vec2 d)
{
	vec3 p3 = fract(vec3(p) * vec3(.1031, .1030, .0973));
	p3 += dot(p3, p3.yzx + 33.33);
    d = fract((p3.xx+p3.yz)*p3.zy);
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash22(in vec2 p, out vec2 d)
{
	vec3 p3 = fract(vec3(p.xyx) * vec3(.1031, .1030, .0973));
    p3 += dot(p3, p3.yzx+33.33);
    d = fract((p3.xx+p3.yz)*p3.zy);
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash31(in float p, out vec3 d)
{
   vec3 p3 = fract(vec3(p) * vec3(.1031, .1030, .0973));
   p3 += dot(p3, p3.yzx+33.33);
   d = fract((p3.xxy+p3.yzz)*p3.zyx); 
}

void dist(in vec2 a, in vec2 b, out float d)
{
    d = length(b-a);
}

void nearest_controlpoint(in vec2 x, out vec2 p)
{
    float dmin = 1.e5, 
        d;
    vec2 dp,
        y = floor(x);
    
    float i = 0.;
    for(float i = -1.; i <= 1.; i += 1.)
        for(float j = -1.; j <= 1.; j += 1.)
        {
            hash22(y+vec2(i,j), dp);
            dp += y+vec2(i,j);
            dist(x, dp, d);
            if(d<dmin)
            {
                dmin = d;
                p = dp;
            }
        }
}

void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance)
{
    d = 1.e4;
    vec2 y,
        dp;
    
    nearest_controlpoint(x, p);
    y = floor(p);
    
    control_distance = 1.e4;
    
    for(float i = -2.; i <= 2.; i += 1.)
        for(float j = -2.; j <= 2.; j += 1.)
        {
            if(i==0. && j==0.) continue;
            hash22(y+vec2(i,j), dp);
            dp += y+vec2(i,j);
            vec2 o = p - dp;
            float l = length(o);
            d = min(d,abs(.5*l-dot(x-dp,o)/l));
            control_distance = min(control_distance,.5*l);
        }
}

// void worley(in vec2 x, out float n)
// {
//     vec2 p, dp, y;
//     nearest_controlpoint(x, p);
//     y = floor(p);
//     
//     float control_distance = 1.e4;
//     
//     for(float i = -2.; i <= 2.; i += 1.)
//         for(float j = -2.; j <= 2.; j += 1.)
//         {
//             if(i==0. && j==0.) continue;
//             hash22(y+vec2(i,j), dp);
//             dp += y+vec2(i,j);
//             vec2 o = p - dp;
//             float l = length(o);
//             control_distance = min(control_distance,.5*l);
//         }
//     n = 1.-length(x-p)*1.5;
// }
// 
// void mfworley(in vec2 x, in float d, in float b, in float e, out float n)
// {
//     n = 0.;
//     float a = 1., nf = 0., buf;
//     for(float f = d; f<b; f *= 2.)
//     {
//         worley(f*x-f, buf);
//         n += a*buf;
//         a *= e;
//         nf += 1.;
//     }
//     n *= (1.-e)/(1.-pow(e, nf));
// }

// Stroke
void stroke(in float d0, in float s, out float d)
{
    d = abs(d0)-s;
}


void dbox(in vec2 x, in vec2 b, out float d)
{
    vec2 da = abs(x)-b;
    d = length(max(da,c.yy)) + min(max(da.x,da.y),0.0);
}


void drhomboid(in vec2 x, in vec2 b, in float tilt, out float dst)
{
    x.x -= tilt/2./b.y*x.y;
    dbox(x,b,dst);
}

void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d)
{
    vec2 da = p2-p1;
    d = length(x-mix(p1, p2, clamp(dot(x-p1, da)/dot(da,da),0.,1.)));
}

void ddeadline(in vec2 x, out float ret)
{
    ret = 1.;
    float da;
    const int npts = 368;
const float path[npts] = float[npts](0.114,-0.123,0.102,-0.137,0.102,-0.137,0.040,-0.137,0.040,-0.137,-0.013,-0.078,-0.013,-0.078,-0.064,-0.137,-0.064,-0.137,-0.153,-0.137,-0.153,-0.137,-0.165,-0.123,-0.165,-0.123,-0.176,-0.137,-0.176,-0.137,-0.380,-0.137,-0.380,-0.137,-0.500,0.002,-0.500,0.002,-0.412,0.104,-0.412,0.104,-0.393,0.104,-0.393,0.104,-0.480,0.002,-0.480,0.002,-0.467,0.002,-0.467,0.002,-0.380,0.104,-0.380,0.104,-0.297,0.104,-0.297,0.104,-0.253,0.054,-0.253,0.054,-0.238,0.073,-0.238,0.073,-0.259,0.073,-0.259,0.073,-0.288,0.104,-0.288,0.104,0.030,0.104,0.030,0.104,-0.039,0.023,-0.039,0.023,-0.196,0.023,-0.196,0.023,-0.205,0.033,-0.205,0.033,-0.228,0.002,-0.228,0.002,-0.044,0.002,-0.044,0.002,0.042,0.104,0.042,0.104,0.067,0.104,0.067,0.104,-0.020,0.002,-0.020,0.002,-0.011,0.002,-0.011,0.002,0.077,0.104,0.077,0.104,0.090,0.104,0.090,0.104,0.057,0.145,0.057,0.145,0.123,0.145,0.123,0.145,0.156,0.104,0.156,0.104,0.357,0.105,0.357,0.105,0.332,0.072,0.332,0.072,0.260,0.072,0.260,0.072,0.301,0.023,0.301,0.023,0.404,0.145,0.404,0.145,0.470,0.145,0.470,0.145,0.349,0.001,0.349,0.001,0.255,0.001,0.255,0.001,0.195,0.072,0.195,0.072,0.185,0.072,0.185,0.072,0.251,-0.009,0.251,-0.009,0.352,-0.009,0.352,-0.009,0.481,0.145,0.481,0.145,0.500,0.145,0.500,0.145,0.376,-0.009,0.376,-0.009,0.442,-0.086,0.442,-0.086,0.143,-0.086,0.143,-0.086,0.127,-0.107,0.127,-0.107,0.396,-0.107,0.396,-0.107,0.428,-0.145,0.428,-0.145,0.133,-0.145,0.133,-0.145,0.114,-0.123,-0.155,-0.050,-0.131,-0.050,-0.131,-0.050,-0.094,-0.093,-0.094,-0.093,-0.047,-0.039,-0.047,-0.039,-0.144,-0.038,-0.144,-0.038,-0.240,-0.037,-0.240,-0.037,-0.252,-0.025,-0.252,-0.025,-0.263,-0.037,-0.263,-0.037,-0.398,-0.039,-0.398,-0.039,-0.340,-0.107,-0.340,-0.107,-0.180,-0.107,-0.180,-0.107,-0.231,-0.050,-0.231,-0.050,-0.164,-0.050,-0.164,-0.050,-0.112,-0.116,-0.112,-0.116,-0.107,-0.109,-0.107,-0.109,-0.155,-0.050,0.125,-0.038,0.032,-0.036,0.032,-0.036,0.065,0.003,0.065,0.003,0.175,0.003,0.175,0.003,0.115,0.072,0.115,0.072,0.022,-0.037,0.022,-0.037,0.073,-0.098,0.073,-0.098,0.125,-0.038,0.350,-0.056,0.336,-0.037,0.336,-0.037,0.210,-0.037,0.210,-0.037,0.200,-0.024,0.200,-0.024,0.172,-0.056,0.172,-0.056,0.350,-0.056,-0.281,0.023,-0.299,0.023,-0.299,0.023,-0.341,0.071,-0.341,0.071,-0.401,0.002,-0.401,0.002,-0.297,0.002,-0.297,0.002,-0.281,0.023,-0.063,0.073,-0.172,0.073,-0.172,0.073,-0.186,0.055,-0.186,0.055,-0.076,0.055,-0.076,0.055,-0.063,0.073);

    float n = 0.;
    for(int i=0; i<npts/4; ++i)
    {
        vec2 ptsi = vec2(path[4*i], path[4*i+1]),
            ptsip1 = vec2(path[4*i+2], path[4*i+3]),
            k = x-ptsi, 
            d = ptsip1-ptsi;
        
        float beta = k.x/d.x,
            alpha = d.y*k.x/d.x-k.y;
        
        n += step(.0, beta)*step(beta, 1.)*step(0., alpha);
        dlinesegment(x, ptsi, ptsip1, da);
        ret = min(ret, da);
    }
    
    ret = mix(ret, -ret, mod(n, 2.));
}

// Extrusion
void zextrude(in float z, in float d2d, in float h, out float d)
{
    vec2 w = vec2(-d2d, abs(z)-0.5*h);
    d = length(max(w,0.0));
}

void dhydrantradius(in float lxy, in float z, in float phi, out float r)
{
    const float dx = 2.e-2,
        rfoot = .3,
        rpipe = .5,
        rtop = .01;
    
    float y = abs(z)-.4;
    
    // sides
    r = rfoot*step(y,6.*dx)*step(0.,y);
    r += .1*rfoot*smoothstep(.3*dx, .7*dx, y)*(1.-smoothstep(5.3*dx,5.7*dx, y));
    r += .1*rfoot*smoothstep(1.3*dx, 1.7*dx, y)*(1.-smoothstep(4.3*dx,4.7*dx, y));
    r += .6*rfoot*step(y,0.);
    
    // center
    y = z+.2;
    r += .1*rfoot*smoothstep(.3*dx, .7*dx, y)*(1.-smoothstep(5.3*dx,5.7*dx, y));
    r += .1*rfoot*smoothstep(1.3*dx, 1.7*dx, y)*(1.-smoothstep(4.3*dx,4.7*dx, y));
    
    // cap
    float phidep = clamp(-.5+2.*abs(cos(2.*pi*phi)),0.,1.);
    r += step(.52,z)*mix(.8*rfoot*(1.+.05*phidep), rtop*(1.+.05*phidep), smoothstep(0.,24.*dx, z - .55));
    r *= step(z,.9);
    
    // cap decoration
    r += .2*rfoot*step(.9,z)*step(z,.9+2.*dx);
    r += .3*rfoot*smoothstep(9.,10., z)*(1.-smoothstep(10., 11., z));
    r += .1*rfoot*smoothstep(.3*dx, .7*dx, z-9.)*(1.-smoothstep(1.3*dx, 1.7*dx, z-9.));
    r = lxy - r;
}

void add(in vec2 sda, in vec2 sdb, out vec2 sdf)
{
    sdf = (sda.x<sdb.x)?sda:sdb;
}

void scene(in vec3 x, out vec2 sdf)
{    
    vec3 y = 2.*x;
    dhydrantradius(length(y.xy), y.z, atan(y.y, y.x), sdf.x);
    
    sdf.x /= 10.;
    
    float rarm = .05;
    rarm -= .01*smoothstep(.05, .07, abs(x.x)-.05);
    rarm -= .01*smoothstep(.05, .07, abs(x.x)-.1);
    rarm -= .02*step(.08, abs(x.x)-.05)*step(abs(x.x)-.05, .09);
    rarm -= .02*step(.08, abs(x.x)-.1)*step(abs(x.x)-.1, .09);
    rarm += .03*step(.17, abs(x.x))*step(abs(x.x),.19);
    sdf.x = min(sdf.x, length(x.yz-.05*c.yx)-rarm*(step(abs(x.x),.2)));
    
    rarm = .05;
    rarm -= .01*smoothstep(.05, .07, abs(x.y)-.05);
    rarm -= .01*smoothstep(.05, .07, abs(x.y)-.1);
    rarm -= .02*step(.08, abs(x.y)-.05)*step(abs(x.y)-.05, .09);
    rarm -= .02*step(.08, abs(x.y)-.1)*step(abs(x.y)-.1, .09);
    rarm += .03*step(.17, abs(x.y))*step(abs(x.y),.2);
    sdf.x = min(sdf.x, .1*(length(x.xz-.05*c.yx)-rarm*step(abs(x.y),.2)));
    
    sdf.y = 0.;
    
    add(sdf, vec2(x.z+.4,1.), sdf);
//     stroke(sdf.x, mix(0.,.01,clamp((iTime-3.5)/.5,0.,1.)), sdf.x);
//     sdf.x = abs(sdf.x);
//     sdf.x /= 4.;
}

void normal(in vec3 x, out vec3 n, in float dx)
{
    vec2 s, na;
    
    scene(x,s);
    scene(x+dx*c.xyy, na);
    n.x = na.x;
    scene(x+dx*c.yxy, na);
    n.y = na.x;
    scene(x+dx*c.yyx, na);
    n.z = na.x;
    n = normalize(n-s.x);
}

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void dcircle(in vec2 x, out float d)
{
    d = length(x)-1.;
}

void dear(in vec2 x, out float d)
{
    d = abs(2.*x.y)
        -.95+smoothstep(0.,.5,clamp(abs(x.x),0.,1.))
        -.5*min(-abs(x.x),.01);
}

void dpolygon(in vec2 x, in float N, out float d)
{
    d = 2.0*pi/N;
    float t = mod(acos(x.x/length(x)), d)-0.5*d;
    d = -0.5+length(x)*cos(t)/cos(0.5*d);
}

void dspacepigs(in vec2 x, out float d)
{
    dpolygon(.5*x,6.0,d);
//     d = 1.;
    float da, d0;
    
    // Head
    dcircle(2.5*x,d0);
    d0 /= 2.5;
    
    // Ears
    dear(vec2(2.,5.)*x-vec2(.8,1.3), da);
    d0 = min(d0,da/10.);
    dear(vec2(2.,5.)*x+vec2(.8,-1.3), da);
    d0 = min(d0,da/10.);
    
    // Nose
    dcircle(6.*x-vec2(0.,-.5),da);
    d0 = max(d0,-da/6.);
    dcircle(24.*x-vec2(-1.5,-2.),da);
    d0 = min(d0,da/24.);
    dcircle(24.*x-vec2(1.5,-2.),da);
    d0 = min(d0,da/24.);
    
    // Eyes
    dcircle(16.*x-vec2(-3.5,2.5),da);
    d0 = max(d0,-da/16.);
    dcircle(16.*x-vec2(3.5,2.5),da);
    d0 = max(d0,-da/16.);
    dcircle(24.*x-vec2(-5.,3.5),da);
    d0 = min(d0,da/24.);
    dcircle(24.*x-vec2(5.,3.5),da);
    d0 = min(d0,da/24.);
    
    d = max(d, -d0);
}

const vec3 orange = 2.*vec3(0.99,0.34,0.39),
    redorange = vec3(0.97,0.60,0.33);
void ddecorations(in vec2 x, in float decs, out float d)
{
    float r, v, vz;
    vec2 y, yi;
    
    dvoronoi(x/decs, v, yi, vz);
    y = x-yi*decs;
 
//     hash12(yi*decs, r);
//     if(r < .5)
//     {
//         dbox(y, vz*decs/sqrt(2.)*c.xx, d);
//     }
//     else
//     {
//         hash11(r, r);
//         d = length(y)-vz*decs;
//     }
    dspacepigs(y/decs*2.5, d);
    d *= -decs/2.5;
}

void modgradient(in vec2 x, in float decs, inout vec3 col)
{
    float y = mod(x.y, decs)-.5*decs;
    
    col = mix(orange, redorange, 2.*abs(y)/decs);
}

float ddl;
void colorize(in vec2 uv, out vec3 col)
{
    vec3 c1 = col;
    float d;
    
    // Background geraffel
    for(float decs = .4; decs <= 1.5; decs += .3)
    {
        modgradient(uv, decs, c1);
        
        ddecorations(uv-1337.-12.*decs*c.yx, decs, d);
        
        float m;
        lfnoise((1.+5.*decs)*uv-1337.-12.*decs*c.yx, m);
        
        col = mix(col, mix(col,c1,mix(.6,.1,.8+.0*m)),.8*decs*sm(d));// mix(1., 0., clamp(.5*length(uv),0.,1.))), sm(d));
        stroke(d, .001, d);
        col = mix(col, mix(orange,c.xxx,decs), sm(d));
    }
    
    col = mix(col, c.yyy, .2);
}

void analytical_box(in vec3 o, in vec3 dir, in vec3 size, out float d)
{
    vec3 tlo = min((size-o)/dir,(-size-o)/dir); // Select 3 visible planes
    vec2 abxlo = abs(o.yz + tlo.x*dir.yz),
        abylo = abs(o.xz + tlo.y*dir.xz),
        abzlo = abs(o.xy + tlo.z*dir.xy);
    vec4 dn = 100.*c.xyyy;
    
    dn = mix(dn, vec4(tlo.x,c.xyy), float(all(lessThan(abxlo,size.yz)))*step(tlo.x,dn.x));
    dn = mix(dn, vec4(tlo.y,c.yxy), float(all(lessThan(abylo,size.xz)))*step(tlo.y,dn.x));
    dn = mix(dn, vec4(tlo.z,c.yyx), float(all(lessThan(abzlo,size.xy)))*step(tlo.z,dn.x));

    d = dn.r;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,
        s;
    
    vec3 col = c.xxx,
        o = c.yyx+1.4*c.yzy+.3*vec3(cos(iTime), sin(iTime), 0.),
        r = vec3(sin(iTime), cos(iTime), 0.),
        t = c.yyy, 
        u = cross(normalize(t-o),-r),
        dir,
        n, 
        x;
    int N = 250,
        i;
    float d;
    t = uv.x * r + uv.y * u;
    dir = normalize(t-o);

    vec3 c0, c1;
    colorize(uv,c0);
    
//     d = 0.;//-(o.z-mix(0.,.2,step(.2,iTime)))/dir.z;
    analytical_box(o-.25*c.yyx, dir, vec3(.2,.2,.5),d);
    if(d > 4.)
    d = -o.z/dir.z;
    
    for(i = 0; i<N; ++i)
    {
     	x = o + d * dir;
        scene(x,s);
        if(s.x < 1.e-5)break;
//         if(x.z<0.)
//         {
//             i = N;
//             break;
//         }
        d += s.x;
//         d += min(s.x,1.e-1);
        //d += s.x;
    }
    
    if(i < N)
    {
        vec3 l = 2.*normalize(x+2.*c.xxx);//x+c.yyx;
        normal(x,n, 2.e-3);
        
        if(s.y == 0.)
        {
            col = vec3(0.47,0.21,0.22);
            
            float na;
            mfnoise(vec2(12.*length(x),x.z)+vec2(x.z,atan(x.y,x.x)),5.,500., .45, na);
            col = mix(col,.1*c.xxx, sm(na+.3));
            col = mix(col, .5*col, .5+.5*na);
            
            col = .3*col 
                + .5*col*dot(-l, n)
                + .7*col*pow(abs(dot(reflect(l,n),dir)),2.);
        }
        else if(s.y == 1.)
        {
            colorize(x.xy, col);
            col = .1*col 
                + .1*col*dot(l, n)
                + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);
        }
    }

    col = 2.*col*col;
//     col = mix(col, c0, clamp(iTime/2.,0.,1.));
//     col = mix(col, c.yyy, clamp(iTime-9.,0.,1.));

//     dhydrantradius(abs(uv.y), uv.x+.2, 0., d);
//     col = mix(col, c.yyy, sm(abs(d)-.001));

    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}

