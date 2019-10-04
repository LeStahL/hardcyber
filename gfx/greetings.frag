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

// Distance to hexagon pattern
void dhexagonpattern(in vec2 p, out float d, out vec2 ind) 
{
    vec2 q = vec2( p.x*1.2, p.y + p.x*0.6 );
    
    vec2 pi = floor(q);
    vec2 pf = fract(q);

    float v = mod(pi.x + pi.y, 3.0);

    float ca = step(1.,v);
    float cb = step(2.,v);
    vec2  ma = step(pf.xy,pf.yx);
    
    d = dot( ma, 1.0-pf.yx + ca*(pf.x+pf.y-1.0) + cb*(pf.yx-2.0*pf.xy) );
    ind = pi + ca - cb*ma;
    ind = vec2(ind.x/1.2, ind.y);
    ind = vec2(ind.x, ind.y-ind.x*.6);
}

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void dbox(in vec2 x, in vec2 b, out float d)
{
    vec2 da = abs(x)-b;
    d = length(max(da,c.yy)) + min(max(da.x,da.y),0.0);
}

void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d)
{
    vec2 da = p2-p1;
    d = length(x-mix(p1, p2, clamp(dot(x-p1, da)/dot(da,da),0.,1.)));
}

void stroke(in float d0, in float s, out float d)
{
    d = abs(d0)-s;
}

void addwindow(in vec2 uv, inout vec3 col, in vec2 dimensions)
{
    float d = 1.;
    
    // Background loading bar window
    dbox(uv, dimensions, d);
    vec3 gcol = length(col)/sqrt(3.)*c.xxx;
    const vec3 window_raw = vec3(0.08,0.07,0.16);
    vec3 window_background = mix(mix(col,window_raw,.2), mix(gcol,window_raw,.8), clamp((.5-uv.y/dimensions.y*.5),0.,1.));
    
    // Shadow
    col = mix(col, .1*gcol, sm(d/8.));
    // Window
    col = mix(col, window_background, sm(d));
    
    // White border on loading bar window
    d = abs(d-.002)-.002;
    d = mix(d, 1., step(abs(uv.y),dimensions.y-.01));
    col = mix(col, c.xxx, sm(d));
    
    // X box
    dbox(uv-(dimensions-.04*c.xx), .015*c.xx, d);
    col = mix(col, c.xxx, sm(d+.005));
    stroke(d, .001, d);
    col = mix(col, c.xxx, sm(d));
    
    // Actual x
    dlinesegment(uv,dimensions-.05*c.xx,dimensions-.03*c.xx,d);
    float da;
    dlinesegment(uv,dimensions-vec2(.05,.03),dimensions-vec2(.03,.05),da);
    d = min(d,da);
    stroke(d,.002, d);
    col = mix(col, c.yyy, sm(d));
}

void dpolygon(in vec2 x, in float N, out float d)
{
    d = 2.0*pi/N;
    float t = mod(acos(x.x/length(x)), d)-0.5*d;
    d = -0.5+length(x)*cos(t)/cos(0.5*d);
}

void dmercury(in vec2 x, out float d)
{
    dpolygon(.5*x,6.0,d);
    float da;

    x += .1*c.yx;

    // Upper part
    dbox(x-.35*c.yx,vec2(.4,.35), da);
    d = max(d, -da);
    dbox(x-.7*c.yx, vec2(.2,.2), da);
    d = min(d,da);
    dbox(x-.25*c.yx,vec2(.2,.05),da);
    d = min(d,da);
    
    // Lower part
    dbox(x+.2*c.yx,vec2(.1,.4),da);
    d = max(d, -da);
    dbox(x+.2*c.yx, vec2(.4,.1),da);
    d = max(d, -da);
}

void dcircle(in vec2 x, out float d)
{
    d = length(x)-1.0;
}

// Adapted from iq, https://www.shadertoy.com/view/XsXSz4
void dtriangle(in vec2 p, in vec2 p0, in vec2 p1, in vec2 p2, out float dst)
{
	vec2 e0 = p1 - p0;
	vec2 e1 = p2 - p1;
	vec2 e2 = p0 - p2;

	vec2 v0 = p - p0;
	vec2 v1 = p - p1;
	vec2 v2 = p - p2;

	vec2 pq0 = v0 - e0*clamp( dot(v0,e0)/dot(e0,e0), 0.0, 1.0 );
	vec2 pq1 = v1 - e1*clamp( dot(v1,e1)/dot(e1,e1), 0.0, 1.0 );
	vec2 pq2 = v2 - e2*clamp( dot(v2,e2)/dot(e2,e2), 0.0, 1.0 );
    
    float s = sign( e0.x*e2.y - e0.y*e2.x );
    vec2 d = min( min( vec2( dot( pq0, pq0 ), s*(v0.x*e0.y-v0.y*e0.x) ),
                       vec2( dot( pq1, pq1 ), s*(v1.x*e1.y-v1.y*e1.x) )),
                       vec2( dot( pq2, pq2 ), s*(v2.x*e2.y-v2.y*e2.x) ));

	dst = -sqrt(d.x)*sign(d.y);
}

void rot(in float phi, out mat2 m)
{
    vec2 cs = vec2(cos(phi), sin(phi));
    m = mat2(cs.x, -cs.y, cs.y, cs.x);
}

void dschnappsgirls(in vec2 x, out float d)
{
    dpolygon(.5*x,6.0,d);
    float da, d0;
    
    // Dress
    dtriangle(x, vec2(-.1,-.3), vec2(.5,-.3), vec2(.2, .6), d0);
    dlinesegment(x, vec2(-.1,.325), vec2(.5,.325), da);
    stroke(da,.06,da);
    d0 = max(d0,-da);
    
    // Head
    dcircle(7.*(x-vec2(.2,.5)), da);
    d0 = max(d0, -da+.5);
    d0 = min(d0, da/7.);
    
    // Legs
    dlinesegment(x, vec2(.125,-.3), vec2(.125,-.6), da);
    stroke(da, .06, da);
    d0 = min(d0, da);
    dlinesegment(x, vec2(.275,-.3), vec2(.275,-.6), da);
    stroke(da, .06, da);
    d0 = min(d0, da);
    
    // Shoulders
    dlinesegment(x, vec2(0.05,.25), vec2(.35,.25), da);
    stroke(da, .085, da);
    d0 = min(d0, da);
    
    // Arms
    dlinesegment(x, vec2(.385,.25), vec2(.5, -.1), da);
    stroke(da, .055, da);
    d0 = min(d0, da);
    dlinesegment(x, vec2(.017,.25), vec2(-.1, -.1), da);
    stroke(da, .055, da);
    d0 = min(d0, da);
    
    // Glass
    dtriangle(x, vec2(-.6,.3), vec2(-.4,.1), vec2(-.2,.3), da);
    stroke(da, .0125, da);
    d0 = min(d0, da);
    dlinesegment(x, vec2(-.4,.15), vec2(-.4,-.1), da);
    stroke(da, .0125, da);
    d0 = min(d0, da);
    dtriangle(x, vec2(-.5,-.15), vec2(-.3,-.15), vec2(-.4,-.1), da);
    d0 = min(d0, da);
    
    // Liquid
    dtriangle(x, vec2(-.55,.25), vec2(-.4,.1), vec2(-.25,.25), da);
    d0 = min(d0, da);
    
    // Salad
    dlinesegment(x, vec2(-.4,.1), vec2(-.2,.5), da);
    stroke(da, .01, da);
    d0 = min(d0, da);
    dcircle(24.*(x-vec2(-.3,.3)), da);
    d0 = min(d0, da/24.);
    dcircle(24.*(x-vec2(-.25,.4)), da);
    d0 = min(d0, da/24.);
    
    d = max(d, -d0);
}

void dhaujobb(in vec2 x, out float d)
{
    dpolygon(.5*x,6.0,d);
    float da, d0;
    mat2 m;
	rot(.3,m);
    x = 1.1*x*m;
    x.x *= 1.1;
        
    x += vec2(-.05,.2);
    
    // Left leg
    dbox(x+.35*c.xx,vec2(.1,.05),d0);
    dbox(x+vec2(.3,.25),vec2(.05,.15),da);
    d0 = min(d0,da);
    dbox(x+vec2(.2,.15),vec2(.1,.05),da);
    d0 = min(d0,da);
    dbox(x+vec2(.15,.05),vec2(.05,.15),da);
    d0 = min(d0,da);
    
    // Right leg
    dbox(x-vec2(.65,.35),vec2(.05,.15),da);
    d0 = min(d0,da);

    // Torso
    rot(.2, m);
    dbox(m*(x-vec2(.25,.15)),vec2(.45,.05),da);
    d0 = min(d0,da);
    dbox(m*(x-vec2(-.15,.35)),vec2(.45,.05),da);
    d0 = min(d0,da);
    rot(pi/8.,m);
    dbox(m*(x-vec2(.0,.25)),vec2(.1,.15),da);
    d0 = min(d0,da);
    
    // Penis
    dbox(m*(x-vec2(.1,-.0)),vec2(.025,.1),da);
    d0 = min(d0,da);
    
    // Left hand
    rot(.3,m);
    dbox(m*(x-vec2(.235,.535)),vec2(.035,.15),da);
    d0 = min(d0,da);
    dbox(m*(x-vec2(.225,.7)),vec2(.075,.025),da);
    d0 = min(d0,da);
    
    // Right hand
    rot(-.2,m);
    dbox(m*(x+vec2(.585,-.2)),vec2(.0375,.1),da);
    d0 = min(d0,da);
    
    // Head
    dcircle(6.*(x-vec2(-.15,.58)),da);
    d0 = min(d0,da/6.);
    
    d0 -= .05*(abs(x.x)+abs(x.y)-.2);
    d = max(d,-d0);
}

void dkewlers(in vec2 x, out float d)
{
    dpolygon(.5*x,6.0,d);
    float da, d0;
    
    x *= 1.2;
    
    dbox(x-vec2(0.,-.3),vec2(.6,.1),d0);
    dbox(x-vec2(-.5,-.0),vec2(.1,.25),da);
    d0 = min(d0,da);
    dbox(x-vec2(-.5+1./3.,.25),vec2(.1,.5),da);
    d0 = min(d0,da);
    dbox(x-vec2(-.5+2./3.,-.0),vec2(.1,.25),da);
    d0 = min(d0,da);
    dbox(x-vec2(.5,-.0),vec2(.1,.25),da);
    d0 = min(d0,da);
    
    d = max(d, -d0);
}

void dfarbrausch(in vec2 x, out float d)
{
    dpolygon(.5*x,6.0,d);
    float da, d0;
    
    x += vec2(.1,0.);
    x *= 1.2;
    
    dlinesegment(x,vec2(-.65,.05),vec2(-.5,.05),d0);
    dlinesegment(x,vec2(-.5,.05),vec2(-.2,-.49),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(-.2,-.49),vec2(-.0,-.49),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(-.0,-.49),vec2(-.27,.0),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(-.07,0.),vec2(-.27,.0),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(.2,-.49),vec2(-.07,.0),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(.4,-.49),vec2(.13,.0),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(.4,-.49),vec2(.2,-.49),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(.33,0.),vec2(.13,.0),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(.33,0.),vec2(.51,-.33),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(.6,-.15),vec2(.51,-.33),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(.53,0.),vec2(.6,-.15),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(.7,0.),vec2(.53,.0),da);
    d0 = min(d0, da);
    dlinesegment(x,vec2(.7,0.),vec2(.68,-.04),da);
    d0 = min(d0, da);
    dpolygon(5.*(x+vec2(.3,.65)),6.,da);
    d0 = min(d0, da/5.);
    dpolygon(5.*(x+vec2(-.5,.65)),6.,da);
    d0 = min(d0, da/5.);
    
    stroke(d0,.035, d0);
    d = max(d, -d0);
}

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
    d /= 5.;
    col = mix(col, 1.9*col1, sm(d));
    col = mix(col, mix(col, 3.*col1, .5+.5*sin(iTime)), sm((abs(d-.01)-.001)/22.));
    
    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}
