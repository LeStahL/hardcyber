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

void rand(in vec2 x, out float n);
void lfnoise(in vec2 t, out float n);
void dhexagonpattern(in vec2 p, out float d, out vec2 ind);

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void dbox(in vec2 x, in vec2 b, out float d);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void stroke(in float d0, in float s, out float d);
void addwindow(in vec2 uv, inout vec3 col, in vec2 dimensions);
void dpolygon(in vec2 x, in float N, out float d);
void dmercury(in vec2 x, out float d);
void dcircle(in vec2 x, out float d);
void dtriangle(in vec2 p, in vec2 p0, in vec2 p1, in vec2 p2, out float dst);
void rot(in float phi, out mat2 m);
void dschnappsgirls(in vec2 x, out float d);
void dhaujobb(in vec2 x, out float d);
void dkewlers(in vec2 x, out float d);
void dfarbrausch(in vec2 x, out float d);
void d5711(in vec2 x, out float ret);

void main()
{
    vec2 uv = (gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,
        hind;
    vec3 col = c.yyy,
        col1 = vec3(0.00,0.42,0.84); // blu
    float h,
        h0,
        res = 34.;
    
    col1 = mix(col1, vec3(0.91,0.30,0.24), clamp(iTime-4., 0., 1.)); // red
    col1 = mix(col1, vec3(0.44,0.65,0.35), clamp(iTime-9.,0.,1.)); // green
    col1 = mix(col1, vec3(0.82,0.14,0.34), clamp(iTime-14.,0.,1.)); // pink
    col1 = mix(col1, vec3(0.92,0.76,0.20), clamp(iTime-19.,0.,1.)); // orange
    col1 = mix(col1, .5*c.xxx, clamp(iTime-24.,0.,1.)); // grayscale
    
    dhexagonpattern(res*uv, h, hind);
    h /= res;
    h0 = h;
    hind /= res;
    h = -abs(h)+.005;
    col = mix(col, col1, sm(h));
    h = abs(h+.005)-.0015;
    col = mix(col, 2.*col, sm(h));
    
    float n;
    lfnoise(res*hind-iTime, n);
    col = mix(c.yyy, col, (.5+.5*n)*(1.-2.*abs(uv.y)));
    
    col = mix(col, 2.*col1, sm(abs(h0)-.001*(.5+.5*n)));
    
    col = 1.4*col;
    
    addwindow(uv, col, vec2(.6,.4));
    
    float d, da;
    if(iTime < 4.) dmercury(5.*uv, d);
    else if(iTime < 9.)
    {
        dmercury(5.*uv, d);
        dschnappsgirls(5.*uv, da);
        d = mix(d, da, clamp(iTime-4., 0., 1.));
    }
    else if(iTime < 14.)
    {
        dschnappsgirls(5.*uv, d);
        dhaujobb(5.*uv, da);
        d = mix(d, da, clamp(iTime-9., 0., 1.));
    }
    else if(iTime < 19.)
    {
        dhaujobb(5.*uv, d);
        dkewlers(5.*uv, da);
        d = mix(d, da, clamp(iTime-14., 0., 1.));
    }
    else if(iTime < 24.)
    {
        dkewlers(5.*uv, d);
        dfarbrausch(5.*uv, da);
        d = mix(d, da, clamp(iTime-19., 0., 1.));
    }
    else if(iTime < 29.)
    {
        dfarbrausch(5.*uv, d);
        d5711(5.*uv, da);
        d = mix(d, da, clamp(iTime-24., 0., 1.));
    }
    d /= 5.;
    col = mix(col, 1.9*col1, sm(d));
    col = mix(col, mix(col, 3.*col1, .5+.5*sin(iTime)), sm((abs(d-.01)-.001)/22.));
    
    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}
