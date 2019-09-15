#version 130

void rshort(in float off, out float val);

void rfloat(in float off, out float val)
{
    // Convert the bytes to unsigned short as first step.
    float d;
    rshort(off, d);
    
    // Convert bytes to IEEE 754 float16. That is
    // 1 sign bit, 5 bit exponent, 11 bit mantissa.
    // Also it has a weird conversion rule that is not evident at all.
    float sign = floor(d/32768.),
        exponent = floor(d/1024.-sign*32.),
        significand = d-sign*32768.-exponent*1024.;

    // Return full float16
    if(exponent == 0.)
    {
        val = mix(1., -1., sign) * 5.960464477539063e-08 * significand;
    }
    else
    {
        val = mix(1., -1., sign) * (1. + significand * 9.765625e-4) * pow(2.,exponent-15.);
    }
}
