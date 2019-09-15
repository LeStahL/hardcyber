#version 130

void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void dpolygon(in vec2 x, in float N, out float d);
void stroke(in float d0, in float s, out float d);

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
