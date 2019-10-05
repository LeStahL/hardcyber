#version 130

uniform float iTime;
uniform vec2 iResolution;

float iScale;

void scale(out float s);

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);

void rand(in vec2 x, out float n);
void hash11(in float p, out float d);
void hash12(in vec2 p, out float d);
void hash21(in float p, out vec2 d);
void hash22(in vec2 p, out vec2 d);
void hash31(in float p, out vec3 d);
void stroke(in float d0, in float s, out float d);
void lfnoise(in vec2 t, out float n);
void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void dbox(in vec2 x, in vec2 b, out float d);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void smoothmin(in float a, in float b, in float k, out float dst);

void gerst(in vec2 x, out float z)
{
    float df, 
        A = 1.,
        da;
    vec2 dk,
        k;
    
    z = 0.;
    
    for(float f = 1.; f < 6.; f *= 1.1)
    {
        hash11(f,df);
        f *= (.95+.2*df);
        hash21(f+2337.,k);
        k *= 64./f+.5;
        hash11(f+1337., da);
        A *= (1.+.3*da);
        
        z += A*pow(.5*(1.+sin(dot(k,x)+f*iTime)),2.);
    }
    
}

void add(in vec2 sda, in vec2 sdb, out vec2 sdf);

void scene(in vec3 x, out vec2 sdf)
{
    float g;
    gerst(x.xy, g);
    sdf = vec2(x.z-.002*g, 1.);
    sdf.x = abs(sdf.x) - .002;
    
    add(sdf, vec2(x.z+.2, 2.), sdf);
}

void normal(in vec3 x, out vec3 n, in float dx);

void palette(in float scale, out vec3 col)
{
    const int N = 5;
    const vec3 colors[N] = vec3[N](
//             vec3(0.27,0.13,0.26),
//             vec3(0.43,0.21,0.33),
//             vec3(0.69,0.36,0.42),
//             vec3(0.87,0.52,0.45),
//             vec3(0.99,0.68,0.53)
vec3(0.04,0.04,0.15),
vec3(0.18,0.32,0.46),
vec3(0.66,0.43,0.62),
vec3(0.96,0.78,0.88),
vec3(0.40,0.00,0.18)
    );
	float index = floor(scale*float(N)), 
        remainder = scale*float(N)-index;
    col = mix(colors[int(index)],colors[int(index)+1], remainder);
}

float dspiral(vec2 x, float a, float d);

void colorize(in vec2 x, inout vec3 col)
{
    float v, n = 64., r;
    vec2 ind;
    dvoronoi(n*x, v, ind, r);
    rand(ind, r);
    vec2 y = x-ind/n;
    vec3 c1;
    rand(ind+1337., c1.x);
    rand(ind+2337., c1.y);
    rand(ind+3337., c1.z);
    c1 *= vec3(1.,.7,.3);
    c1 = .5+.5*c1;
    c1 *= vec3(.4,.6,1.);
    float d = length(y)-.0002*r;
    if(r > .75)
        col = mix(col, c1, sm(d));
//     r *= cos(pi*x.y);
    if(r>.5)
    {
        col = mix(col, mix(col, 2.*c1, .8), sm(d-.004*r*r));
        col = mix(col, mix(col, 3.*c1, .4), sm(d-.01*r*r));
    }
    
    float cpa;
    dvoronoi(2.*n*x, v, ind, cpa);
    y = x-ind/n/2.;
    rand(ind, r);
    d = length(y)-.002*r;
    col = mix(col, c.xxx, sm(d));
    
    lfnoise(x.xy-v*v*v, d);
    col = mix(col, c.yyy, .5+.5*d);
    
    col = .6*col+.3*step(.8,col);
    col *= 2.;
    
    v = dspiral(x, .1,.01);
    col = mix(col, c.yyy, 1.-sm(v*6.e-3));
    col = mix(col, 2.5*col, sm(v*2.e-3));
}

void main()
{
    scale(iScale);
    vec2 uv = (gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,
        s;
    
    vec3 col = c.yyy,
        o = .5*c.yyx+c.yzy,
        r = c.xyy,
        t = c.yyy, 
        u = cross(normalize(t-o),-r),
        dir,
        n, 
        x;
    int N = 150,
        i;
    t = uv.x * r + uv.y * u;
    dir = normalize(t-o);

    vec3 c1;
    float d = -(o.z-.15)/dir.z;
    
    vec3 o0, dir0;
    float d0;
    
    for(i = 0; i<N; ++i)
    {
     	x = o + d * dir;
        scene(x,s);
        if(s.x < 1.e-4) break;
        d += s.x;
//         d += min(s.x,1.e-2);
        //d += s.x;
    }
    
    if(i < N)
    {
        vec3 l = c.yyx;
        normal(x,n, 1.e-4);
        
        if(s.y == 1.)
        {
            palette(x.z/.22, col);

            col = .1*col 
                + .1*col*dot(l, n)
                + 1.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);
        }
        
        o = x;
        d = 1.e-2;
        dir = refract(dir,n,.5);
        vec3 c1;
        
        for(i = 0; i<N; ++i)
        {
            x = o + d * dir;
            scene(x,s);
            if(s.x < 1.e-3)break;
            d += s.x;
    //         d += min(s.x,1.e-1);
            //d += s.x;
        }
        
        if(i < N)
        {
            vec3 l = c.yyx;
            normal(x,n, 2.e-3);
            
            
            if(s.y == 1.)
            {
                palette(x.z/.22, c1);

                c1 = .1*c1 
                    + .1*c1*dot(l, n)
                    + 1.6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);
            }
            else if(s.y == 2.)
            {
                c1 = vec3(0.26,0.16,0.32);
//                 float v, cv;
//                 vec2 ind;
//                 dvoronoi(12.*x.xy, v, ind, cv);
//                 c1 = mix(c1, c.xxx, sm(abs(v)-.02));
                float v = .5+.5*sin(100.*x.y);
                c1 = mix(c1,2.*c1, v);
                
                c1 = .1*c1 
                    + .1*c1*dot(l, n)
                    + 1.6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);
            }
        }
        col = mix(col, c1, .1);
    }

    col = 3.*col*col;
    
    //col = mix(col, c.yyy, tanh(2.e-1*d));
   
    
    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}

