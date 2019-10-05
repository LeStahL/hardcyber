#version 130

uniform float iTime;
uniform vec2 iResolution;

float iScale;

void scale(out float s);

// Global constants
const float pi = acos(-1.);
const vec3 c = vec3(1.0, 0.0, -1.0);
float a = 1.0;

void rand(in vec2 x, out float n);
void lfnoise(in vec2 t, out float n);
void hash22(in vec2 p, out vec2 d);
void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void add(in vec2 sda, in vec2 sdb, out vec2 sdf);
void sub(in vec2 sda, in vec2 sdb, out vec2 sdf);
void zextrude(in float z, in float d2d, in float h, out float d);
void dbox3(in vec3 x, in vec3 b, out float d);
void rot3(in vec3 p, out mat3 rot);
void dbox(in vec2 x, in vec2 b, out float d);
void dstar(in vec2 x, in float N, in vec2 R, out float dst);
void doctahedron(in vec3 x, in float h, in float w, out float d);

mat3 gR;
vec2 ind = c.yy;
void scene(in vec3 x, out vec2 sdf)
{
    vec3 y = x;
    x.xy += vec2(cos(.3*iTime), sin(.3*iTime));
    
    sdf.x = x.z;
    sdf.y = 0.;
    
    float db = abs(length(y-.1*c.yyx)-.2), 
        dc;
    dbox3(gR * (y-.1*c.yyx), .2*c.xxx, dc);
    db = mix(db, abs(dc)-.001, clamp(iTime-5.,0.,1.));
    doctahedron(gR * (y-.1*c.yyx),.4,.4, dc);
    db = mix(db, abs(dc)-.001, clamp(iTime-10.,0.,1.));
    add(sdf, vec2(db,1.), sdf);
}

void texture_scene(in vec3 x, out vec2 sdf)
{
    vec3 y = x;
    x.xy += vec2(cos(.3*iTime), sin(.3*iTime));
    
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
    db = mix(db, abs(dc)-.001, clamp(iTime-5.,0.,1.));
    doctahedron(gR * (y-.1*c.yyx),.4,.4, dc);
    db = mix(db, abs(dc)-.001, clamp(iTime-10.,0.,1.));
    add(sdf, vec2(db,1.), sdf);
}

void normal(in vec3 x, out vec3 n, in float dx);

void texture_normal(in vec3 x, out vec3 n, in float dx)
{
    vec2 s, na;
    
    texture_scene(x,s);
    texture_scene(x+dx*c.xyy, na);
    n.x = na.x;
    texture_scene(x+dx*c.yxy, na);
    n.y = na.x;
    texture_scene(x+dx*c.yyx, na);
    n.z = na.x;
    n = normalize(n-s.x);
}

void palette(in float scale, out vec3 col)
{
    scale = clamp(scale, 1.e-2,.99);
    const int N = 5;
    vec3 colors[N] = vec3[N](
mix(vec3(0.20,0.27,0.35),vec3(1.00,0.00,0.47), clamp(iTime-5.,0.,1.)),
mix(vec3(0.29,0.37,0.45),vec3(0.80,0.00,0.47), clamp(iTime-5.,0.,1.)),
mix(vec3(0.36,0.65,0.64),vec3(0.60,0.00,0.47), clamp(iTime-5.,0.,1.)),
mix(vec3(0.66,0.85,0.80),vec3(0.40,0.00,0.47), clamp(iTime-5.,0.,1.)),
mix(vec3(0.95,0.92,0.82),c.yyy,clamp(iTime-5.,0.,1.))
    );
    colors[0] = mix(colors[0], vec3(0.68,1.00,0.00), clamp(iTime-10.,0.,1.));
    colors[1] = mix(colors[1], vec3(0.45,0.84,0.00), clamp(iTime-10.,0.,1.));
    colors[2] = mix(colors[2], vec3(0.01,0.54,0.00), clamp(iTime-10.,0.,1.));
    colors[3] = mix(colors[3], vec3(0.00,0.82,0.50), clamp(iTime-10.,0.,1.));
    colors[4] = mix(colors[4], vec3(0.00,1.00,0.51), clamp(iTime-10.,0.,1.));
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
    scale(iScale);
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
        c1 = c.yyy,
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
        if(s.y == 1.)
        {
            vec3 l = .5*c.yyz;
            normal(x,n, 2.e-5);
            
            col = c.xxx;
            col = .3*col 
                + .5*col*dot(-l, n)
                + 1.7*col*pow(abs(dot(reflect(l,n),dir)),2.); 
        }
        else col = c.yyy;
    }
    else col = c.yyy;
    
    for(i = 0; i<N; ++i)
    {
     	x = o + d * dir;
        texture_scene(x,s);
        if(s.x < 1.e-3)break;
        d += s.x;//min(s.x,2.e-1);
    }
    
    if(i < N)
    {
        x0 = x;
        
        vec3 l = x+c.yxy+.5*c.yyx;
        texture_normal(x,n, 2.e-5);
        if(s.y == 0.)
        {
            float na;
            lfnoise(2.*ind-iTime, na);
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
                
                if(i < N)
                {
                    if(s.y == 1.)
                    {
                        vec3 l = .5*c.yyz;
                        normal(x,n, 2.e-5);
                        
                        c1 = c.xxx;
                        c1 = .3*c1 
                            + .5*c1*dot(-l, n)
                            + 1.7*c1*pow(abs(dot(reflect(l,n),dir)),2.); 
                    }
                    else c1 = c.yyy;
                }
                else c1 = c.yyy;
                col = mix(col, c1, .54);
                
                for(i = 0; i<N; ++i)
                {
                    x = o + d * dir;
                    texture_scene(x,s);
                    if(s.x < 1.e-3)break;
                    d += s.x;//min(s.x,2.e-1);
                }
                
                if(i<N)
                {
                    vec3 l = x+c.yxy+.5*c.yyx;
                    texture_normal(x,n, 2.e-5);
                    if(s.y == 0.)
                    {
                        float na;
                        lfnoise(ind, na);
                        palette(.5+.5*na, c1);
                        
                        c1 = .4*c1 
                            + .5*c1*dot(-l, n)
                            + .7*c1*pow(abs(dot(reflect(l,n),dir)),2.);
                    }
//                     else c1 = c.yyy;
                    
                    col = mix(col, c1, .3);
                }
//                 else col = c.yyy;
            }
        }
//         else col *= -1.;
    }
//     else col = c.yyx;
        
    float da = 1.;
//     (abs(length(x0.xy)-.2)-.03),
//         db;
    scene(vec3(uv,.2), s);
    da = abs(s.x-.1)-.003;
//     dbox(x.xy, .4*c.xx, db);
//     db = abs(db)-.03;
//     da = mix(da, db, clamp(iTime-5.,0.,1.));
    col = mix(col, 8.*col, sm(da/20.));
    col = 1.5*col*col;
    
    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}
