#version 130
const float pi = acos(-1.);
void hsv2rgb(in vec3 hsv, out vec3 rgb)
{
    float C = hsv.y * hsv.z,
        Hprime = hsv.x / pi * 3.,
        X = C * (1.-abs(mod(Hprime,2.)-1.));
    
    if(0. <= Hprime && Hprime <= 1.) rgb = vec3(C, X, 0.);
    else if( 1. < Hprime && Hprime <= 2.) rgb = vec3(X, C, 0.);
    else if( 2. < Hprime && Hprime <= 3.) rgb = vec3(0., C, X);
    else if( 3. < Hprime && Hprime <= 4.) rgb = vec3(0., X, C);
    else if( 4. < Hprime && Hprime <= 5.) rgb = vec3(X, 0., C);
    else if( 5. < Hprime && Hprime <= 6.) rgb = vec3(C, 0., X);
        
    float m = hsv.z - C;
    rgb += m;
}
