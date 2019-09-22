#version 130

float dspiral(vec2 x, float a, float d)
{
    float p = atan(x.y, x.x),
        n = floor((abs(length(x)-a*p)+d*p)/(2.*pi*a));
    p += (n*2.+1.)*pi;
    return -abs(length(x)-a*p)+d*p;
}
