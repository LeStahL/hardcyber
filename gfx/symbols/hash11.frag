// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash11(in float p, out float d)
{
    p = fract(p * .1031);
    p *= p + 33.33;
    p *= p + p;
    d = fract(p);
}
