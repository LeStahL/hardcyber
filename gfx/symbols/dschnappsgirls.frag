#version 130

void dtriangle(in vec2 x, in vec2 p0, in vec2 p1, in vec2 p2, out float d);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void stroke(in float d0, in float s, out float d);
void dcircle(in vec2 x, out float d);
void dpolygon(in vec2 x, in float N, out float d);

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
