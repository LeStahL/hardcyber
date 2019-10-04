#version 130

void doctahedron(in vec3 x, in float h, in float w, out float d)
{
    x.xz = abs(x.xz);
    x.y = abs(x.y)-h;
    d = max(x.z,x.x)+(x.y*w);    
}
