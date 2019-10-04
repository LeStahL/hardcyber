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

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);

void rand(in vec2 x, out float n);
void lfnoise(in vec2 t, out float n);
void mfnoise(in vec2 x, in float d, in float b, in float e, out float n);
void hash11(in float p, out float d);
void hash12(in vec2 p, out float d);
void hash21(in float p, out vec2 d);
void hash22(in vec2 p, out vec2 d);
void hash31(in float p, out vec3 d);
void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void stroke(in float d0, in float s, out float d);
void dbox(in vec2 x, in vec2 b, out float d);
void drhomboid(in vec2 x, in vec2 b, in float tilt, out float dst);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void zextrude(in float z, in float d2d, in float h, out float d);

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

void add(in vec2 sda, in vec2 sdb, out vec2 sdf);

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
}

void normal(in vec3 x, out vec3 n, in float dx);

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void dcircle(in vec2 x, out float d)
{
    d = length(x)-1.;
}

void dpolygon(in vec2 x, in float N, out float d);
void dspacepigs(in vec2 x, out float d);

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

void analytical_box(in vec3 o, in vec3 dir, in vec3 size, out float d);
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
    
    analytical_box(o-.25*c.yyx, dir, vec3(.2,.2,.5),d);
    if(d > 4.)
    d = -o.z/dir.z;
    
    for(i = 0; i<N; ++i)
    {
     	x = o + d * dir;
        scene(x,s);
        if(s.x < 1.e-5)break;
        if(x.y>.5)
        {
            d = -(o.z+.4)/dir.z;
            x = o + d * dir;
            scene(x,s);
            break;
        }
        d += s.x;

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

