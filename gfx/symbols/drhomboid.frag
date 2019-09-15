#version 130

void dbox(in vec2 x, in vec2 b, out float dst);

void drhomboid(in vec2 x, in vec2 b, in float tilt, out float dst)
{
    x.x -= tilt/2./b.y*x.y;
    dbox(x,b,dst);
}
