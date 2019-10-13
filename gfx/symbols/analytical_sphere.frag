#version 130

const vec3 c = vec3(1.,0.,-1.);

void analytical_sphere(in vec3 o, in vec3 dir, in float R, out vec2 d)
{
    float a = dot(dir,dir),
        b = 2.*dot(o,dir),
        cc = dot(o,o)-R*R,
        dis = b*b-4.*a*cc;
    vec2 dd = (dis<0.)?1.e4*c.xx:(c.xz*sqrt(dis)-b)/2./a;
    d = vec2(min(dd.x, dd.y), max(dd.x, dd.y));
}
