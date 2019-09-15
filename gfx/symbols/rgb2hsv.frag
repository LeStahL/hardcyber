#version 130
const float pi = acos(-1.);
void rgb2hsv(in vec3 rgb, out vec3 hsv)
{
    float MAX = max(rgb.r, max(rgb.g, rgb.b)),
        MIN = min(rgb.r, min(rgb.g, rgb.b)),
        C = MAX-MIN;
    
    if(MAX == MIN) hsv.x = 0.;
    else if(MAX == rgb.r) hsv.x = pi/3.*(rgb.g-rgb.b)/C;
    else if(MAX == rgb.g) hsv.x = pi/3.*(2.+(rgb.b-rgb.r)/C);
    else if(MAX == rgb.b) hsv.x = pi/3.*(4.+(rgb.r-rgb.g)/C);
    hsv.x = mod(hsv.x, 2.*pi);
        
    if(MAX == 0.) hsv.y = 0.;
    else hsv.y = (MAX-MIN)/MAX;
        
    hsv.z = MAX;
}
