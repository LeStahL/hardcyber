#version 130

void smoothmin(in float a, in float b, in float k, out float dst);

void smoothmax(in float a, in float b, in float k, out float res)
{
    smoothmin(a,b,k,res);
    res = a + b - res;
}
