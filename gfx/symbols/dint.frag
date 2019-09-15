#version 130

const vec3 c = vec3(1.,0.,-1.);

void dglyph(in vec2 x, in float ordinal, in float size, out float dst);

void dint(in vec2 x, in float num, in float size, in float ndigits, out float dst)
{
    float d = 1., index = 0.;
    
    if(num == 0.)
    {
        index = ndigits;
        dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48., .7*size, dst);
        return;
    } 
    
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
    
    int hit = 0;
    
    // Determine the significand and output it
    for(float i = ndigits; i >= 0.; i -= 1.)
    {
        float po = pow(10.,i);
        float ca = floor(num/po);
        if(ca == 0.) 
        {
            if(hit == 0)
            {
                index += 1.;
                continue;
            }
            
        }
        else hit = 1;
        num -= ca*po;
        
        float da;
        dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);
        d = min(d, da);
        index += 1.;
    }
    
    
    
    dst = d;
}
