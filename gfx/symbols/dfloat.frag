#version 130

const vec3 c = vec3(1.,0.,-1.);

void dglyph(in vec2 x, in float ordinal, in float size, out float dst);

void dfloat(in vec2 x, in float num, in float size, out float dst)
{
    float d = 1., index = 0.;
    
    // Determine sign and output it if present
    float sign = sign(num), exp = 0.;
    if(sign<0.)
    {
        float da;
        dglyph(x, 45., .7*size, da);
        d = min(d, da);
        index += 1.;
        num *= -1.;
    }
    
    // The first power of ten that floors num to anything not zero is the exponent
    for(exp = -15.; exp < 15.; exp += 1.)
        if(floor(num*pow(10.,exp)) != 0.)
            break;
    exp *= -1.;
    // Determine the significand and output it
    for(float i = exp; i >= max(exp-5.,-33); i -= 1.)
    {
        float po = pow(10.,i);
        float ca = floor(num/po);
        num -= ca*po;
        
        float da;
        dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);
        d = min(d, da);
        index += 1.;
        if(i == exp) // decimal point
        {
            dglyph(x-2.*index*size*c.xy, 46., .7*size, da);
            d = min(d, da);
            index += 1.;
        }
    }
    
    // Output the exponent
    float db;
    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 101., .7*size, db);
    d = min(d, db);
    index += 1.;
    if(exp < 0.) // Sign
    {
        dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 45., .7*size,db);
        d = min(d, db);
        index += 1.;
        exp *= -1.;
    }
    float ca = floor(exp/10.);
    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, db);
    d = min(d, db);
    index += 1.;
    ca = floor(exp-10.*ca);
    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, db);
    d = min(d, db);
    index += 1.;
    
    dst = d;
}
