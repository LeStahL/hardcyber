#version 130

const vec3 c = vec3(1.,0.,-1.);

void hash33(in vec3 p3, out vec3 d);

void dist3(in vec3 a, in vec3 b, out float d)
{
    d = length(b-a);
}

void nearest_controlpoint3(in vec3 x, out vec3 p)
{
    float dmin = 1.e5, 
        d;
    vec3 dp,
        y = floor(x);
    
    for(float i = -1.; i <= 1.; i += 1.)
        for(float j = -1.; j <= 1.; j += 1.)
        {
            for(float k = -1.; k <= 1.; k += 1.)
            {
                hash33(y+vec3(i,j,k), dp);
                dp += y+vec3(i,j,k);
                dist3(x, dp, d);
                if(d<dmin)
                {
                    dmin = d;
                    p = dp;
                }
            }
        }
}

void dvoronoi3(in vec3 x, out float d, out vec3 p, out float control_distance)
{
    d = 1.e4;
    vec3 y,
        dp;
    
    nearest_controlpoint3(x, p);
    y = floor(p);
    
    control_distance = 1.e4;
    
    for(float i = -2.; i <= 2.; i += 1.)
        for(float j = -2.; j <= 2.; j += 1.)
        {
            for(float k = -1.; k <= 1.; k += 1.)
            {
                if(i==0. && j==0. && k == 0.) continue;
                hash33(y+vec3(i,j,k), dp);
                dp += y+vec3(i,j,k);
                vec3 o = p - dp;
                float l = length(o);
                d = min(d,abs(.5*l-dot(x-dp,o)/l));
                control_distance = min(control_distance,.5*l);
            }
        }
}
