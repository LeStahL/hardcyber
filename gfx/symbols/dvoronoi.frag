#version 130
const vec3 c = vec3(1.,0.,-1.);

void hash22(in vec2 a, out vec2 b);
void dist(in vec2 a, in vec2 b, out float d)
{
    d = length(b-a);
}

void nearest_controlpoint(in vec2 x, out vec2 p)
{
    float dmin = 1.e5, 
        d;
    vec2 dp,
        y = floor(x);
    
    float i = 0.;
    for(float i = -1.; i <= 1.; i += 1.)
        for(float j = -1.; j <= 1.; j += 1.)
        {
            hash22(y+vec2(i,j), dp);
            dp += y+vec2(i,j);
            dist(x, dp, d);
            if(d<dmin)
            {
                dmin = d;
                p = dp;
            }
        }
}

void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance)
{
    d = 1.e4;
    vec2 y,
        dp;
    
    nearest_controlpoint(x, p);
    y = floor(p);
    
    control_distance = 1.e4;
    
    for(float i = -2.; i <= 2.; i += 1.)
        for(float j = -2.; j <= 2.; j += 1.)
        {
            if(i==0. && j==0.) continue;
            hash22(y+vec2(i,j), dp);
            dp += y+vec2(i,j);
            vec2 o = p - dp;
            float l = length(o);
            d = min(d,abs(.5*l-dot(x-dp,o)/l));
            control_distance = min(control_distance,.5*l);
        }
}
