#version 130

const vec3 c = vec3(1.,0.,-1.);

void rfloat(in float off, out float val);
void dbox(in vec2 x, in vec2 b, out float dst);
void dglyph(in vec2 x, in float ordinal, in float size, out float dst);

void dstring(in vec2 x, in float ordinal, in float size, out float dst)
{
    // Get string database offset
    float stroff0;
    rfloat(0., stroff0);
    stroff0 = floor(stroff0);
    
    // Return 1 if wrong ordinal is supplied
    float nstrings;
    rfloat(stroff0, nstrings);
    nstrings = floor(nstrings);
    if(ordinal >= nstrings)
    {
        dst = 1.;
        return;
    }
    
    // Get offset and length of string from string database index
    float stroff;
    rfloat(stroff0+1.+2.*ordinal, stroff);
    stroff = floor(stroff);
    float len;
    rfloat(stroff0+2.+2.*ordinal, len);
    len = floor(len);
    
    // Draw glyphs
    vec2 dx = mod(x-size, 2.*size)-size, 
        ind = ceil((x-dx+size)/2./size);
    
    // Bounding box
    float bound;
    dbox(x-size*(len-3.)*c.xy, vec2(size*len, 1.*size), bound);
    if(bound > 0.)
    {
        dst = bound+.5*size;
        return;
    }
    
    float da;
    rfloat(stroff+ind.x, da);
    da = floor(da);
    dglyph(dx, da, .7*size, dst);
}
