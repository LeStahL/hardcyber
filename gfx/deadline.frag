#version 130

uniform float iTime;
uniform vec2 iResolution;

float iScale;

void scale(out float s);

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);

void rand(in vec2 x, out float n);
void lfnoise(in vec2 t, out float n);
void hash11(in float p, out float d);
void hash12(in vec2 p, out float d);
void hash22(in vec2 p, out vec2 d);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void stroke(in float d0, in float s, out float d);
void dbox(in vec2 x, in vec2 b, out float d);
void ddeadline(in vec2 x, out float ret);
void zextrude(in float z, in float d2d, in float h, out float d);

vec2 pdec;
void ddecorations(in vec2 x, in float decs, out float d)
{
    float r, v, vz;
    vec2 y, yi;
    
    dvoronoi(x/decs, v, yi, vz);
    y = x-yi*decs;
 
    hash12(yi*decs, r);
    if(r < .5)
    {
        dbox(y, vz*decs/sqrt(2.)*c.xx, d);
    }
    else
    {
        hash11(r, r);
        d = length(y)-vz*decs;
    }
    
    pdec = yi/decs;
}

float m;
void scene(in vec3 x, out vec2 sdf)
{
    if(iTime < 8.)
    {
        ddeadline(x.xy, sdf.x);
        zextrude(x.z, -sdf.x, mix(.0,.2,clamp(iTime-2.,0.,1.)*(1.-clamp(iTime-7.,0.,1.))), sdf.x);
        sdf.x = min(sdf.x, x.z);
        
        sdf.y = 1.;
    }
    else
    {
        sdf.x = x.z;
        sdf.y = 1.;
    }
}

void normal(in vec3 x, out vec3 n, in float dx);

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

const vec3 orange =vec3(0.20,0.60,0.86),
    redorange = vec3(0.27,0.70,0.62);

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
    for(float decs = .05; decs <= 1.; decs += .05)
    {
        modgradient(uv, decs, c1);
        
        ddecorations(uv-1337.-12.*decs*c.yx, decs, d);
        
        float ma;
        lfnoise((1.+5.*decs)*uv-1337.-12.*decs*c.yx-clamp(iTime/3.,0.,1.)*iTime*c.yx, ma);
        col = mix(col, mix(col,c1,mix(.6,.1,.8+.2*ma)* mix(1., 0., clamp(length(uv),0.,1.))), sm(d));
        stroke(d, .001, d);
        col = mix(col, 1.4*col, mix(0.,sm(d-.01),mix(0.,.5+.5*ma,clamp(iTime-10.,0.,1.))));
        col = mix(col, mix(orange,c.xxx,decs), sm(d));
    }
    
    col = mix(col, c.yyy, .2);

    if(iTime < 8.)
    {
        ddeadline(uv, d);
        ddl = d;
        
        c1 = mix(col,mix(col,mix(3.5,5.5,.5+.5*sin(6.*iTime))*vec3(0.27,0.36,0.48),.5), sm(ddl/150.));
        
        c1 = mix(c1, mix(col,1.3*vec3(0.27,0.36,0.48),.8), sm(d+.002));
        stroke(d,.002, d);
        c1 = mix(c1, 2.5*vec3(0.27,0.36,0.48), sm(d));
        
        col = mix(col, c1, clamp((iTime-2.),0.,1.)*(1.-clamp(iTime-7.,0.,1.)));
    }
}

void main()
{
    vec2 uv = (gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,
        s;
    
    scale(iScale);
    
    vec3 col = c.xxx,
        o = mix((vec3(uv,1.)),c.yyx+.4*c.yzy,clamp(iTime-1.,0.,1.)),
        r = c.xyy,
        t = c.yyy, 
        u = cross(normalize(t-o),-r),
        dir,
        n, 
        x;
    int N = 150,
        i;
    float d;
    t = uv.x * r + uv.y * u;
    dir = mix(c.yyz,normalize(t-o),clamp(iTime-1.,0.,1.));

    vec3 c0, c1;
    colorize(uv,c0);
    
    d = -(o.z-mix(0.,.2,step(2.,iTime)))/dir.z;
    
    for(i = 0; i<N; ++i)
    {
     	x = o + d * dir;
        scene(x,s);
        if(s.x < 1.e-5)break;
        if(x.z<0.)
        {
            i = N;
            break;
        }
        d += s.x;
    }
    
    if(i < N)
    {
        vec3 l = x+c.yyx;
        normal(x,n, 2.e-6);
        colorize(x.xy, col);
        col = .1*col 
            + .4*col*dot(l, n)
            + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);
    }
    
    col = 2.*col*col;
    col = mix(c0, col, clamp(iTime,0.,1.));
    
    col = mix(col, vec3(0.18,0.24,0.31), clamp(iTime-19.,0.,1.));
    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}

