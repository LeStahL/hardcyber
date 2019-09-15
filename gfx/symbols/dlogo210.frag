#version 130
const vec3 c = vec3(1.,0.,-1.);
const float pi = acos(-1.);
void dcirclesegment(in vec2 x, in float R, in float p0, in float p1, out float d);
void dcircle(in vec2 x, in float R, out float d);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void dlogo210(in vec2 x, in float R, out float d)
{
    float d2;
    dcircle(x+R*c.zy, R, d);
    dlinesegment(x, R*c.yz, R*c.yx, d2);
    d = min(d, d2);
    dcirclesegment(x+R*c.xy, R, -.5*pi, .5*pi, d2);
    d = min(d, d2);
}
