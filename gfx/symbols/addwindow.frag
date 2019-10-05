#version 130

uniform vec2 iResolution;

const vec3 c = vec3(1.,0.,-1.);

void dbox(in vec2 x, in vec2 b, out float d);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void stroke(in float d0, in float s, out float d);

#define sm(d) smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d) #CRLF 
// #define sm(d) smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d)

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
