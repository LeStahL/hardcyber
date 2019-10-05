#version 130

out vec4 gl_FragColor;

uniform float iTime;
uniform vec2 iResolution;

float iScale;

void scale(out float s);

const float pi = acos(-1.);
const vec3 c = vec3(1.0, 0.0, -1.0);
float a = 1.0;

vec3 color1 =vec3(0.02,0.08,0.18),
    color2 = 2.*vec3(0.08,0.08,0.24);

void hash22(in vec2 p, out vec2 d);
void hash12(in vec2 p, out float d);
void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void add(in vec2 sda, in vec2 sdb, out vec2 sdf);
void dbox3(in vec3 x, in vec3 b, out float d);

float h;
void scene(in vec3 x, out vec2 sdf)
{
    x.x += .1*iTime;
    
    vec2 vi;
    float v, vip, res = 15., d;
    dvoronoi(res*x.xz, v, vi, vip);
    vip /= res;
    vi /= res;
    v /= res;
    
    sdf = vec2(x.y,0.);
    
    if(vi.y < .5)
    {
        hash12(vi, h);
        vec2 cs = vec2(cos(2.*pi*h), sin(2.*pi*h));
        mat2 R = mat2(cs.x, cs.y, -cs.y, cs.x);
        vec3 y = vec3(x.x-vi.x, x.y, x.z-vi.y);
        y.xz = R * y.xz;
        dbox3(y, vip/sqrt(2.)*c.xyx+(.1+.05*h)*c.yxy, d);
        add(sdf, vec2(d, 1.), sdf);
    }
    sdf.x -= .003;
}

void normal(in vec3 x, out vec3 n, in float dx);

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void colorize(in vec2 uv, out vec3 col)
{
    col = c.yyy;
}

void housetexture(in vec2 uv, out vec3 col)
{
    uv.x += .1*iTime;
    float dsta = .002;
    col = mix(.05*color1, 4.*color2, sm(4.*(abs(mod(uv.y, dsta)-.5*dsta)-.25*dsta)));
    
    vec2 x = mod(uv, dsta)-.5*dsta,
        xi = (uv-x)/dsta;
    float f;
    hash12(xi,f);
    if(f < .3)    
    {
        col = mix(col, mix(4.*col,c.xxx,.5), sm(min(abs(x.x), abs(x.y))-.25*dsta));
    }
}

void palette2(in float scale, out vec3 col)
{
    const int N = 5;
    const vec3 colors[N] = vec3[N](
            vec3(0.98,0.80,1.00),
            vec3(0.52,1.00,0.42),
            vec3(0.45,0.99,0.96),
            vec3(1.00,0.09,0.31),
            vec3(1.00,1.00,0.43)
    );
	float index = floor(scale*float(N)), 
        remainder = scale*float(N)-index;
    col = mix(colors[int(index)],colors[int(index)+1], remainder);
}

void main()
{
    vec2 uv = (gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,
        s;
        
    scale(iScale);
    
    if(uv.y>.16)
    {
        gl_FragColor = vec4(mix(vec3(0.10,0.17,0.33),c.yyy,clamp((uv.y-.16)/(.5-.16),0.,1.)),1.);
        return;
    }
    
    vec3 col = c.xxx,
        o = c.yyx+.2*c.yxy,
        r = c.xyy,
        t = c.yyy, 
        u = cross(normalize(t-o),-r),
        dir,
        n, 
        x,
        c1,
        o0 = o;
    int N = 350,
        i;
        
    float d;
    t = uv.x * r + uv.y * u;
    dir = normalize(t-o);
    d = -(o.y-.15)/dir.y;
    
    for(i = 0; i<N; ++i)
    {
     	x = o + d * dir;
        scene(x,s);
        if(s.x < 1.e-5)break;
        if(x.y > .15)
        {
            gl_FragColor = c.yyyx;
            return;
        }
        d += min(s.x,2.e-3);
    }
    
    float d0 = d;
    
    if(i < N)
    {
        vec3 l = x+c.yxy+.5*c.yyx;
        normal(x,n, 2.e-5);
        if(s.y == 0.)
        {
            col = color1;
            
            col = .3*col 
                + .5*col*dot(-l, n)
                + .7*col*pow(abs(dot(reflect(l,n),dir)),2.);
            
            {
                o = x;
                d = 1.e-3;
                dir = reflect(dir, n);
                
                for(i = 0; i<N; ++i)
                {
                    x = o + d * dir;
                    scene(x,s);
                    if(s.x < 1.e-5)break;
                    if(x.y > .15)
                    {
                        gl_FragColor = c.yyyx;
                        return;
                    }
                    d += min(s.x,5.e-3);
                }
                
                if(i < N)
                {
                    vec3 l = x+c.yxy;
                    normal(x,n, 2.e-4);
                    
                    if(s.y == 0.)
                    {
                        c1 = color1;
                        
                        c1 = .3*c1 
                            + .5*c1*dot(-l, n)
                            + .7*c1*pow(abs(dot(reflect(l,n),dir)),2.);
                    }
                    else if(s.y == 1.)
                    {
                        housetexture(x.xy, c1);
                        
                        c1 = .1*c1 
                            + .1*c1*dot(l, n)
                            + .6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);
                    }
                    else c1 = c.yyx;
                    
                    col = mix(c1, col, .5);
                }
                else colorize(uv,col);
            }
        }
        else if(s.y == 1.)
        {
            housetexture(x.xy, col);
            
            col = .1*col 
                + .1*col*dot(l, n)
                + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);
                
            col = mix(col, c.xxx, smoothstep(.63, 1.2, 1.-abs(dot(n, 3.*c.xyx))));
            col = mix(col, c.xxx, smoothstep(.63, 1.2, 1.-abs(dot(n, 3.*c.zyx))));
            
        }
    }
    else colorize(uv,col);
    
    d = d0;
    float ha = mod(abs(x.y)-mix(-1.,1.,h)*iTime+12.*h,.15);
    palette2(fract(h), c1);
    col = mix(col,1.15*c1, smoothstep(-.2,1.,smoothstep(.1,1.3,(1.-8.*ha)))); 
    palette2(fract(h+13.37e-3), c1);
    col = mix(col,1.65*c1*c1, smoothstep(-.2,1.,smoothstep(.1,1.3,(1.-26.*ha)))); 
    
    col = 2.*col*col;
    col = mix(col,c.yyy, smoothstep(0.,2.,d));
    
    col = clamp(col, 0.,1.);
    col = mix(col, c.yyy, .3);
    col = mix(col, vec3(0.10,0.17,0.33), smoothstep(.1,1.3,d));
    
    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}
