#version 130

const vec3 c = vec3(1.,0.,-1.);

void dbox(in vec2 x, in vec2 b, out float d);
void dpolygon(in vec2 x, in float N, out float d);

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
