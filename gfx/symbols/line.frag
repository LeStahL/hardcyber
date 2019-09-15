// Distance to line segment
void line(in vec3 x, in vec3 p1, in vec3 p2, out float dst)
{
    vec3 d = p2-p1;
    dst = length(x-mix(p1, p2, clamp(dot(x-p1, d)/dot(d,d),0.,1.)));
}
