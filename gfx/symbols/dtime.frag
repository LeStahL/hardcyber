#version 130

const vec3 c = vec3(1.,0.,-1.);

void dglyph(in vec2 x, in float ordinal, in float size, out float dst);

// Time in format: 00:00
void dtime(in vec2 x, in float num, in float size, out float dst)
{
    float d = 1., index = 0.;
    
    num = floor(num);

    // 10 minutes
    float ca = floor(num/600.), da = 1.;
    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);
    d = min(d, da);
    index += 1.;
    num -= ca*600.;

    // minutes
    ca = floor(num/60.);
    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);
    d = min(d, da);
    index += 1.;
    num -= ca*60.;

    // :
    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 58., .7*size, da);
    d = min(d, da);
    index += 1.;
    
    // 10 seconds
    ca = floor(num/10.);
    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);
    d = min(d, da);
    index += 1.;
    num -= ca*10.;
    
    // 1 seconds
    ca = floor(num/1.);
    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);
    d = min(d, da);
    
    dst = d;
}
