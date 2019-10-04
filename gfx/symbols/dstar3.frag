#version 130

void dstar(in vec2 x, in float N, in vec2 R, out float dst);
void smoothmax(in float a, in float b, in float k, out float res);

void dstar3(in vec3 x, in float N, in vec2 R, out float dst)
{
    float d;
    
    dstar(x.xy, N, R, dst);
    dstar(x.yz, N, R, d);
    smoothmax(-d,-dst,.15,dst);
    dstar(x.zx, N, R, d);
    smoothmax(-d,dst,.15,dst);
}
