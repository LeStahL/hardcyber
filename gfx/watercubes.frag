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

vec3 color1, color2;

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

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash33(in vec3 p3, out vec3 d)
{
	p3 = fract(p3 * vec3(.1031, .1030, .0973));
    p3 += dot(p3, p3.yxz+33.33);
    d = fract((p3.xxy + p3.yxx)*p3.zyx);
}

void dist3(in vec3 a, in vec3 b, out float d)
{
    d = length(b-a);
}

void nearest_controlpoint3(in vec3 x, out vec3 p)
{
    float dmin = 1.e5, 
        d;
    vec3 dp,
        y = floor(x);
    
    for(float i = -1.; i <= 1.; i += 1.)
        for(float j = -1.; j <= 1.; j += 1.)
        {
            for(float k = -1.; k <= 1.; k += 1.)
            {
                hash33(y+vec3(i,j,k), dp);
                dp += y+vec3(i,j,k);
                dist3(x, dp, d);
                if(d<dmin)
                {
                    dmin = d;
                    p = dp;
                }
            }
        }
}

void dvoronoi3(in vec3 x, out float d, out vec3 p, out float control_distance)
{
    d = 1.e4;
    vec3 y,
        dp;
    
    nearest_controlpoint3(x, p);
    y = floor(p);
    
    control_distance = 1.e4;
    
    for(float i = -2.; i <= 2.; i += 1.)
        for(float j = -2.; j <= 2.; j += 1.)
        {
            for(float k = -1.; k <= 1.; k += 1.)
            {
                if(i==0. && j==0. && k == 0.) continue;
                hash33(y+vec3(i,j,k), dp);
                dp += y+vec3(i,j,k);
                vec3 o = p - dp;
                float l = length(o);
                d = min(d,abs(.5*l-dot(x-dp,o)/l));
                control_distance = min(control_distance,.5*l);
            }
        }
}

// iq's smooth minimum
void smoothmin(in float a, in float b, in float k, out float dst)
{
    float h = max( k-abs(a-b), 0.0 )/k;
    dst = min( a, b ) - h*h*h*k*(1.0/6.0);
}

void dsmoothvoronoi3(in vec3 x, out float d, out vec3 p, out float control_distance)
{
    d = 1.e4;
    vec3 y,
        dp;
    
    nearest_controlpoint3(x, p);
    y = floor(p);
    
    control_distance = 1.e4;
    
    for(float i = -2.; i <= 2.; i += 1.)
        for(float j = -2.; j <= 2.; j += 1.)
        {
            for(float k = -1.; k <= 1.; k += 1.)
            {
                if(i==0. && j==0. && k == 0.) continue;
                hash33(y+vec3(i,j,k), dp);
                dp += y+vec3(i,j,k);
                vec3 o = p - dp;
                float l = length(o);
//                 d = min(d,abs(.5*l-dot(x-dp,o)/l));
                smoothmin(d,abs(.5*l-dot(x-dp,o)/l), .15, d);
//                 control_distance = min(control_distance,.5*l);
                smoothmin(control_distance, .5*l, .15, control_distance);
            }
        }
}

mat3 gR;
void rot3(in vec3 p, out mat3 rot)
{
    rot = mat3(c.xyyy, cos(p.x), sin(p.x), 0., -sin(p.x), cos(p.x))
        *mat3(cos(p.y), 0., -sin(p.y), c.yxy, sin(p.y), 0., cos(p.y))
        *mat3(cos(p.z), -sin(p.z), 0., sin(p.z), cos(p.z), c.yyyx);
}

void add(in vec2 sda, in vec2 sdb, out vec2 sdf)
{
    sdf = (sda.x<sdb.x)?sda:sdb;
}

void dbox3(in vec3 x, in vec3 b, out float d)
{
  vec3 da = abs(x) - b;
  d = length(max(da,0.0))
         + min(max(da.x,max(da.y,da.z)),0.0);
}

void dstar(in vec2 x, in float N, in vec2 R, out float dst)
{
    float d = pi/N,
        p0 = acos(x.x/length(x)),
        p = mod(p0, d),
        i = mod(round((p-p0)/d),2.);
    x = length(x)*vec2(cos(p),sin(p));
    vec2 a = mix(R,R.yx,i),
    	p1 = a.x*c.xy,
        ff = a.y*vec2(cos(d),sin(d))-p1;
   	ff = ff.yx*c.zx;
    dst = dot(x-p1,ff)/length(ff);
}

void smoothmax(in float a, in float b, in float k, out float res)
{
    smoothmin(a,b,k,res);
    res = a + b - res;
}

void dstar3(in vec3 x, in float N, in vec2 R, out float dst)
{
    float d;
    
    dstar(x.xy, N, R, dst);
    dstar(x.yz, N, R, d);
    smoothmax(-d,-dst,.15,dst);
    dstar(x.zx, N, R, d);
    smoothmax(-d,dst,.15,dst);
}

void scene(in vec3 x, out vec2 sdf)
{
    if(length(x) > .5) sdf = vec2(length(x)-.5,-1.);
    x = gR * x;
    vec3 yi;
    float vi, 
        vip, 
        rel = 8.,
        db = length(x)-.4,
        dc;
    dbox3(x,.2,dc);
    db = mix(db, dc, clamp(iTime-5., 0., 1.));
    dstar3(x, 6., vec2(.2,.5), dc);
    db = mix(db, dc, clamp(iTime-10., 0.,1.));
//     db = mix(db, dc, .6+.6*sin(iTime));
    dsmoothvoronoi3(rel*x, vi, yi, vip);
    sdf = vec2(abs(vi/rel)-.0001, 0.);
    sdf.x = max(sdf.x, db);
    add(sdf, vec2(abs(db+.0002)-.0001, 1.), sdf);
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

void dbox(in vec2 x, in vec2 b, out float d)
{
    vec2 da = abs(x)-b;
    d = length(max(da,c.yy)) + min(max(da.x,da.y),0.0);
}

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void colorize(in vec2 uv, out vec3 col)
{
    col = mix(color2, c.yyy, length(uv));
    
    vec2 s;
    scene(vec3(uv,0.), s);
    
    float v, vip, res = mix(12.,100., s.x);
    vec2 vi;
    dvoronoi(res*uv, v, vi, vip);
    float d = abs(v/res)-mix(.002,.0001, s.x);
    col = mix(col, 4.*col,sm(-v/res+.01));
    col = mix(col, mix(4.*color2, c.yyy, 2.*s.x), sm(d));
}

void main()
{
    vec2 uv = (gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,
        s;
    
    rot3(vec3(1.1,1.3,1.5)*iTime, gR);
    color1 = mix(vec3(0.47,0.21,0.22), vec3(0.17,0.24,0.30), clamp(iTime-5.,0.,1.));
    color1 = mix(color1, vec3(0.52,0.85,0.31), clamp(iTime-10., 0., 1.));
    color2 = mix(vec3(0.22,0.21,0.47), .3*vec3(1.00,0.59,0.22), clamp(iTime-5.,0.,1.));
    color2 = mix(color2, .15
    *c.xxx, clamp(iTime-10., 0., 1.));
    
    vec3 col = c.xxx,
        o = c.yyx,
        r = c.xyy,
        t = c.yyy, 
        u = cross(normalize(t-o),-r),
        dir,
        n, 
        x,
        c1,
        o0 = o;
    int N = 150,
        i;
        
    float d = .5;
    t = uv.x * r + uv.y * u;
    dir = normalize(t-o);
    
    for(i = 0; i<N; ++i)
    {
     	x = o + d * dir;
        scene(x,s);
        if(s.x < 1.e-5)break;
        if(d > length(.6+.2*c.xx))
        {
            i = N;
            break;
        }
        d += s.x;

    }
    
    if(i < N)
    {
        vec3 l = 2.*normalize(x+2.*c.xxx);//x+c.yyx;
//         vec3 l = x + .3*(o-x);
        normal(x,n, 2.e-3);
        
        if(s.y == 0.)
        {
            col = color1;
            
            col = .3*col 
                + .5*col*dot(-l, n)
                + .7*col*pow(abs(dot(reflect(l,n),dir)),2.);
        }
        else if(s.y == 1.)
        {
            col = color2;
            
            col = .1*col 
                + .1*col*dot(l, n)
                + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);
        }
        
        for(float k = .5; k < .9; k += .2)
        {
            o = x;
            d = 1.e-3;
            dir = refract(dir, n, .99);
            
            for(i = 0; i<N; ++i)
            {
                x = o + d * dir;
                scene(x,s);
                if(s.x < 1.e-5)break;
                if(d > length(o0)+.4001)
                {
                    i = N;
                    break;
                }
                d += s.x;

            }
            
            if(i < N)
            {
                vec3 l = 2.*normalize(x+2.*c.xxx);//x+c.yyx;
//                 vec3 l = x + .3*(o-x);
                normal(x,n, 2.e-3);
                
                if(s.y == 0.)
                {
                    c1 = color1;
                    
                    c1 = .3*c1 
                        + .5*c1*dot(-l, n)
                        + .7*c1*pow(abs(dot(reflect(l,n),dir)),2.);
                        
                    c1 = mix(c1, c.xxx, smoothstep(0.458, .602, 1.-abs(dot(n, c.yyz))));
                }
                else if(s.y == 1.)
                {
                    c1 = color2;
                    
                    c1 = .1*c1 
                        + .1*c1*dot(l, n)
                        + .6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);
                }
                else c1 = c.yyx;
                
                col = mix(c1, col, k);
            }
            else colorize(uv,col);
        }
    }
    else colorize(uv,col);
    
    col = 2.*col*col;
    
    
//     col = mix(col, c0, clamp(iTime/2.,0.,1.));
//     col = mix(col, c.yyy, clamp(iTime-9.,0.,1.));

//     dhydrantradius(abs(uv.y), uv.x+.2, 0., d);
//     col = mix(col, c.yyy, sm(abs(d)-.001));

    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}
