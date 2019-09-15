#version 130
void rand3(in vec3 x, out float num)
{
    x += 400.;
    num = fract(sin(dot(sign(x)*abs(x) ,vec3(12.9898,78.233,121.112)))*43758.5453);
}
