#version 130

void dbox(in vec2 x, in vec2 b, out float d);
void dpolygon(in vec2 x, in float N, out float d);

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
