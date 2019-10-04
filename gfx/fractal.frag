#version 130

uniform float iTime;
uniform vec2 iResolution;

uniform float iFader0;
uniform float iFader1;
uniform float iFader2;
uniform float iFader3;
uniform float iFader4;
uniform float iFader5;
uniform float iFader6;
uniform float iFader7;

// Global constants
const float pi = acos(-1.);
const vec3 c = vec3(1.0, 0.0, -1.0);
float a = 1.0;

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

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash22(in vec2 p, out vec2 d)
{
	vec3 p3 = fract(vec3(p.xyx) * vec3(.1031, .1030, .0973));
    p3 += dot(p3, p3.yzx+33.33);
    d = fract((p3.xx+p3.yz)*p3.zy);
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

void add(in vec2 sda, in vec2 sdb, out vec2 sdf)
{
    sdf = (sda.x<sdb.x)?sda:sdb;
}

void sub(in vec2 sda, in vec2 sdb, out vec2 sdf)
{
    sdf = (sda.x>sdb.x)?abs(sda):abs(sdb)*c.zx;
}

void zextrude(in float z, in float d2d, in float h, out float d)
{
    vec2 w = vec2(-d2d, abs(z)-0.5*h);
    d = length(max(w,0.0));
}

void dbox3(in vec3 x, in vec3 b, out float d)
{
  vec3 da = abs(x) - b;
  d = length(max(da,0.0))
         + min(max(da.x,max(da.y,da.z)),0.0);
}

void rot3(in vec3 p, out mat3 rot)
{
    rot = mat3(c.xyyy, cos(p.x), sin(p.x), 0., -sin(p.x), cos(p.x))
        *mat3(cos(p.y), 0., -sin(p.y), c.yxy, sin(p.y), 0., cos(p.y))
        *mat3(cos(p.z), -sin(p.z), 0., sin(p.z), cos(p.z), c.yyyx);
}

void dbox(in vec2 x, in vec2 b, out float d)
{
    vec2 da = abs(x)-b;
    d = length(max(da,c.yy)) + min(max(da.x,da.y),0.0);
}

mat3 gR;
vec2 ind = c.yy;
void scene(in vec3 x, out vec2 sdf)
{
    vec3 y = x;
    x.xy += vec2(cos(iTime), sin(iTime));
    
    sdf.x = x.z;
    sdf.y = 0.;
    
    float res = 8.;
    vec2 sdb = c.xy;
    for(float f = 0.; f < 6.; f += 1.)
    {
        float v, vp;
        vec2 vi;
        dvoronoi(res*x.xy, v, vi, vp);
        vp /= res;
        vi /= res;
        v /= res;
        add(sdb, vec2(length(x-vec3(vi,0.))-.5*vp, 0.), sdb);
        res *= 2.;
        
        ind += vi/res;
    }
    sub(sdf, sdb, sdf);
    
    float db = abs(length(y-.1*c.yyx)-.2), 
        dc;
    dbox3(gR * (y-.1*c.yyx), .2*c.xxx, dc);
    db = mix(db, abs(dc), clamp(iTime-5.,0.,1.));
    add(sdf, vec2(db,1.), sdf);
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

void palette(in float scale, out vec3 col)
{
    const int N = 5;
    const vec3 colors[N] = vec3[N](
vec3(0.20,0.27,0.35),
vec3(0.29,0.37,0.45),
vec3(0.36,0.65,0.64),
vec3(0.66,0.85,0.80),
vec3(0.95,0.92,0.82)
    );
	float index = floor(scale*float(N)), 
        remainder = scale*float(N)-index;
    col = mix(colors[int(index)],colors[int(index)+1], remainder);
}

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void main()
{
    rot3(vec3(1.1,1.3,1.5)*iTime, gR);
    vec2 uv = (gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,
        s;
    vec3 col = c.yyy,
        o = c.yyx+.2*c.yzy,
        r = c.xyy,
        t = c.yyy, 
        u = cross(normalize(t-o),-r),
        dir,
        n, 
        x,
        c1,
        o0 = o,
        x0;
    int N = 150,
        i;
        
    vec3 color1 = vec3(0.52,1.00,0.42);
        
    float d;
    t = uv.x * r + uv.y * u;
    dir = normalize(t-o);
    d = 0.;//-(o.z)/dir.y;
    
    for(i = 0; i<N; ++i)
    {
     	x = o + d * dir;
        scene(x,s);
        if(s.x < 1.e-3)break;
        d += s.x;//min(s.x,2.e-1);
    }
    
    if(i < N)
    {
        x0 = x;
        
        vec3 l = x+c.yxy+.5*c.yyx;
        normal(x,n, 2.e-5);
        if(s.y == 0.)
        {
            float na;
            lfnoise(2.*ind, na);
            palette(.5+.5*na, col);
            
//             col = length(col)/sqrt(3.)*c.xxx;
            
            col = .3*col 
                + .5*col*dot(-l, n)
                + .7*col*pow(abs(dot(reflect(l,n),dir)),2.);
        }
        else if(s.y == 1.)
        {
            vec3 c1;
            
            col = c.xxx;
            col = .3*col 
                + .5*col*dot(-l, n)
                + .7*col*pow(abs(dot(reflect(l,n),dir)),2.); 
            
            for(float k = 0.; k < 3.; k += 1.)
            {
                o = x;
                dir = refract(dir, n, .5);
                d = 1.e-2;
                
                for(i = 0; i<N; ++i)
                {
                    x = o + d * dir;
                    scene(x,s);
                    if(s.x < 1.e-5)break;
                    d += s.x;//min(s.x,2.e-3);
                }
                
                if(i<N)
                {
                    vec3 l = x+c.yxy+.5*c.yyx;
                    normal(x,n, 2.e-5);
                    if(s.y == 0.)
                    {
                        float na;
                        lfnoise(ind, na);
                        palette(.5+.5*na, c1);
                        
                        c1 = .4*c1 
                            + .5*c1*dot(-l, n)
                            + .7*c1*pow(abs(dot(reflect(l,n),dir)),2.);
                    }
                    
                    col = mix(col, c1, .3);
                }
                else col = c.yyy;
            }
        }
        else col = c.yyy;
    }
    else col = c.yyy;
    
    float da = (abs(length(x0.xy)-.2)-.03),
        db;
    dbox(x.xy, .4*c.xx, db);
    db = abs(db)-.03;
    da = mix(da, db, clamp(iTime-5.,0.,1.));
    col = mix(col, 8.*col, sm(da/20.));
    
    col = 1.5*col*col;
    
    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}
