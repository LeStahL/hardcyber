uniform float iTime;
uniform vec2 iResolution;

float iScale;

void scale(out float s);

// Global constants
const float pi = acos(-1.);
const vec3 c = vec3(1.0, 0.0, -1.0);
float a = 1.0;

vec3 color1, color2;

void hash22(in vec2 p, out vec2 d);
void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void hash33(in vec3 p3, out vec3 d);
void dvoronoi3(in vec3 x, out float d, out vec3 p, out float control_distance);
void smoothmin(in float a, in float b, in float k, out float dst);
void dsmoothvoronoi3(in vec3 x, out float d, out vec3 p, out float control_distance);

mat3 gR;
void rot3(in vec3 p, out mat3 rot);
void add(in vec2 sda, in vec2 sdb, out vec2 sdf);
void dbox3(in vec3 x, in vec3 b, out float d);
void dstar(in vec2 x, in float N, in vec2 R, out float dst);
void smoothmax(in float a, in float b, in float k, out float res);
void dstar3(in vec3 x, in float N, in vec2 R, out float dst);

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

void normal(in vec3 x, out vec3 n, in float dx);
void dbox(in vec2 x, in vec2 b, out float d);
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
    scale(iScale);
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
