#version 130

// Revision logo of width 1.
void lfnoise(in vec2 t, out float num);

void drevision(in vec2 x, in float r, out float dst)
{
    float l = length(x),
        p = atan(x.y,x.x),
	    d = abs(l-r*.07)-.02, 
        k1 = abs(l-r*.16)-.03,
        k2 = abs(l-r*.21)-.02, 
        k3 = abs(l-r*.35)-.03,
        k4 = abs(l-r*.45)-.02;
    vec4 n1;
    lfnoise(1.*c.xx-3.*iTime, n1.x);
    lfnoise(2.*c.xx-2.4*iTime, n1.y);
    lfnoise(3.*c.xx-2.9*iTime, n1.z);
    lfnoise(4.*c.xx-3.1*iTime, n1.w);
    n1 = mix(n1,c.yyyy, clamp((iTime-24.)/2.,0.,1.));
    d = min(d, mix(d, abs(l-.11)-.03, step(p, -1.71)*step(-2.73, p)));
    d = min(d, mix(d, k1, step(p+n1.x, 3.08)*step(2.82,p)));
    d = min(d, mix(d, k1, step(p+n1.x, 1.47)*step(.81,p)));
    d = min(d, mix(d, k1, step(p+n1.x, -.43)*step(-1.19,p)));
    d = min(d, mix(d, k2, step(p+n1.y, -2.88)*step(-pi,p)));
    d = min(d, mix(d, k2, step(p+n1.y, pi)*step(2.38,p)));
    d = min(d, mix(d, k2, step(p+n1.y, 2.1)*step(.51,p)));
    d = min(d, mix(d, k2, step(p+n1.y, .3)*step(-1.6,p)));
    d = min(d, abs(l-.24)-.02);
    d = min(d, mix(d, k3, step(p+n1.z, -2.18)*step(-pi, p)));
    d = min(d, mix(d, k3, step(p+n1.z, -1.23)*step(-1.7, p)));
    d = min(d, mix(d, k3, step(p+n1.z, -.58)*step(-.78, p)));
    d = min(d, mix(d, k3, step(p+n1.z, 0.)*step(-.29, p)));
    d = min(d, mix(d, k3, step(p+n1.z, 1.25)*step(1.06, p)));
    d = min(d, mix(d, k3, step(p+n1.z, 1.99)*step(.5*pi, p)));
    d = min(d, abs(l-.41)-.03);
    d = min(d, mix(d, k4, step(p+n1.w, 1.04)*step(.04, p)));
    d = min(d, mix(d, k4, step(p+n1.w, -2.2)*step(-2.34, p)));
    
    dst = d-.005;
}
