/* Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19
 * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#version 130

uniform float iTime;
uniform vec2 iResolution;

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);
float a = 1.0;

void rand(in vec2 x, out float n)
{
    x += 400.;
    n = fract(sin(dot(sign(x)*abs(x) ,vec2(12.9898,78.233)))*43758.5453);
}

void lfnoise(in vec2 t, out float n)
{
    vec2 i = floor(t);
    t = fract(t);
    t = smoothstep(c.yy, c.xx, t);
    vec2 v1, v2;
    rand(i, v1.x);
    rand(i+c.xy, v1.y);
    rand(i+c.yx, v2.x);
    rand(i+c.xx, v2.y);
    v1 = c.zz+2.*mix(v1, v2, t.y);
    n = mix(v1.x, v1.y, t.x);
}

//distance to spline with parameter t
float dist2(vec2 p0,vec2 p1,vec2 p2,vec2 x,float t)
{
    t = clamp(t, 0., 1.);
    return length(x-pow(1.-t,2.)*p0-2.*(1.-t)*t*p1-t*t*p2);
}

//minimum dist3ance to spline
void dspline2(in vec2 x, in vec2 p0, in vec2 p1, in vec2 p2, out float ds)
{
    //coefficients for 0 = t^3 + a * t^2 + b * t + c
    vec2 E = x-p0, F = p2-2.*p1+p0, G = p1-p0;
    vec3 ai = vec3(3.*dot(G,F), 2.*dot(G,G)-dot(E,F), -dot(E,G))/dot(F,F);

	//discriminant and helpers
    float tau = ai.x/3., p = ai.y-tau*ai.x, q = - tau*(tau*tau+p)+ai.z, dis = q*q/4.+p*p*p/27.;
    
    //triple real root
    if(dis > 0.) 
    {
        vec2 ki = -.5*q*c.xx+sqrt(dis)*c.xz, ui = sign(ki)*pow(abs(ki), c.xx/3.);
        ds = dist2(p0,p1,p2,x,ui.x+ui.y-tau);
        return;
    }
    
    //three dist3inct real roots
    float fac = sqrt(-4./3.*p), arg = acos(-.5*q*sqrt(-27./p/p/p))/3.;
    vec3 t = c.zxz*fac*cos(arg*c.xxx+c*pi/3.)-tau;
    ds = min(
        dist2(p0,p1,p2,x, t.x),
        min(
            dist2(p0,p1,p2,x,t.y),
            dist2(p0,p1,p2,x,t.z)
        )
    );
}

void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d)
{
    vec2 da = p2-p1;
    d = length(x-mix(p1, p2, clamp(dot(x-p1, da)/dot(da,da),0.,1.)));
}

void stroke(in float d0, in float s, out float d)
{
    d = abs(d0)-s;
}

// iq's smooth minimum
void smoothmin(in float a, in float b, in float k, out float dst)
{
    float h = max( k-abs(a-b), 0.0 )/k;
    dst = min( a, b ) - h*h*h*k*(1.0/6.0);
}

void d_h(in vec2 x, out float d)
{
    float da;
    dspline2(vec2(abs(x.x)-.1, abs(x.y)), vec2(.15,.25), vec2(.05,.25), vec2(.05,0.), d);
    dlinesegment(x, vec2(-.075,0.), vec2(.075,0.), da);
    smoothmin(d, da, .1, d);
}

void d_a(in vec2 x, out float d)
{
    float da;
    dspline2(vec2(abs(x.x)-.1, x.y), vec2(.15,-.25), vec2(.05,-.25), vec2(.05, 0.), d);
    dspline2(vec2(abs(x.x)-.1, x.y), vec2(.05,0.), vec2(.05,.25), vec2(-.1,.25), da);
    d = min(d,da);
    dlinesegment(x, vec2(-.075,0.), vec2(.075,0.), da);
    smoothmin(d, da, .1, d);
}

void d_r(in vec2 x, out float d)
{
    float da;
    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);
    dspline2(vec2(x.x,abs(x.y-.1)-.15), vec2(.0,-.05), vec2(.25,.05), vec2(.25,-.15), da);
    smoothmin(d,da,.1,d);
    dspline2(x,vec2(0.,-.05), vec2(0.,-.25), vec2(.35,-.25), da);
    smoothmin(d,da,.1,d);
}

void d_d(in vec2 x, out float d)
{
    float da;
    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);
    dspline2(vec2(x.x,abs(x.y)-.1), vec2(-.05,.15), vec2(.25,.25), vec2(.25,-.1), da);
    smoothmin(d,da,.1,d);
}

void d_c(in vec2 x, out float d)
{
    float da;
    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);
    dspline2(vec2(x.x,abs(x.y)-.1), vec2(-.05,.15), vec2(.25,.25), vec2(.25,0.), da);
    smoothmin(d,da,.1,d);
}

void d_y(in vec2 x, out float d)
{
    float da;
    dspline2(vec2(abs(x.x)-.2, x.y), vec2(-.05,0.25), vec2(-.05,.1), vec2(-.2,.1), d);
    dlinesegment(x, vec2(0.,-.25), vec2(0.,.1), da);
    smoothmin(d,da,.1,d);
}

void d_b(in vec2 x, out float d)
{
    float da;
    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);
    dspline2(vec2(x.x,abs(abs(x.y)-.125)-.15), vec2(.0,-.05), vec2(.25,.05), vec2(.25,-.15), da);
    smoothmin(d,da,.1,d);
}

void d_e(in vec2 x, out float d)
{
    float da;
    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);
    dspline2(vec2(x.x,abs(x.y)-.1), vec2(-.05,.05), vec2(-.05,.15), vec2(.25,.15), da);
    smoothmin(d,da,.1,d);
    dlinesegment(x,vec2(-.05,0.), vec2(.15,0.), da);
    smoothmin(d,da,.1,d);
}

void dhardcyber(in vec2 x, out float d)
{
//     x = floor(96.*x)/96.;
    x *= 3.;
    float da;
    d_h(x+1.8*c.xy,d);
    d_a(x+1.3*c.xy,da);
    d = min(d,da);
    d_r(x+.9*c.xy,da);
    d = min(d,da);
    d_d(x+.4*c.xy,da);
    d = min(d,da);
    d_c(x-.1*c.xy,da);
    d = min(d,da);
    d_y(x-.6*c.xy,da);
    d = min(d,da);
    d_b(x-.925*c.xy,da);
    d = min(d,da);
    d_e(x-1.4*c.xy,da);
    d = min(d,da);
    d_r(x-1.8*c.xy,da);
    d = min(d,da);
    
    stroke(d, .07, d);
    
    d /= 3.;
}

float sm(float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void palette(in float scale, out vec3 col)
{
    const int N = 5;
    const vec3 colors[N] = vec3[N](
            vec3(0.27,0.13,0.26),
            vec3(0.43,0.21,0.33),
            vec3(0.69,0.36,0.42),
            vec3(0.87,0.52,0.45),
            vec3(0.99,0.68,0.53)
    );
	float index = floor(scale*float(N)), 
        remainder = scale*float(N)-index;
    col = mix(colors[int(index)],colors[int(index)+1], remainder);
}

void dvoronoi(in vec2 x, out float d, out vec2 z)
{
    vec2 y = floor(x);
       float ret = 1.;
    vec2 pf=c.yy, p;
    float df=10.;
    
    for(int i=-1; i<=1; i+=1)
        for(int j=-1; j<=1; j+=1)
        {
            p = y + vec2(float(i), float(j));
            float pa;
            rand(p, pa);
            p += pa;
            
            d = length(x-p);
            
            if(d < df)
            {
                df = d;
                pf = p;
            }
        }
    for(int i=-1; i<=1; i+=1)
        for(int j=-1; j<=1; j+=1)
        {
            p = y + vec2(float(i), float(j));
            float pa;
            rand(p, pa);
            p += pa;
            
            vec2 o = p - pf;
            d = length(.5*o-dot(x-pf, o)/dot(o,o)*o);
            ret = min(ret, d);
        }
    
    d = ret;
    z = pf;
}

// Extrusion
void zextrude(in float z, in float d2d, in float h, out float d)
{
    vec2 w = vec2(-d2d, abs(z)-0.5*h);
    d = length(max(w,0.0));
}

void scene(in vec3 x, out vec2 sdf)
{    
    dhardcyber(x.xy, sdf.x);
    zextrude(x.z, -sdf.x, .1, sdf.x);
    smoothmin(sdf.x, x.z,.1, sdf.x);
    sdf.y = 1.;
    stroke(sdf.x, .01, sdf.x);
//     sdf.x = abs(sdf.x);
//     sdf.x /= 4.;
}

void normal(in vec3 x, out vec3 n, in float dx)
{
    vec2 s, na;
    
    scene(x,s);
    scene(x+dx*c.xyy, na);
    n.x = na.x;
    scene(x+dx*c.yxy, na);
    n.y = na.x;
    scene(x+dx*c.yyx, na);
    n.z = na.x;
    n = normalize(n-s.x);
}

void colorize(in vec2 uv, inout vec3 col)
{
    vec3 c1;
    float d = floor(8.*(.5+.4*tanh(6.*uv.y+uv.x)))/8.;
    vec2 ind;
    float v;
    dvoronoi(16.*uv, v, ind);
    float r;
    rand(ind,r);
    d = (uv.y+.25)/.5-.2*r;
    palette(clamp(d,0.,1.),c1);
//     c1 = mix(c1, c.yyy, sm(abs(v)-.02));
    col = (.5+.5*r)*c.xxx;
    
    dhardcyber(uv, d);
    col = mix(col, .7*c.xxx, sm(d-.04));
    col = mix(col, c1, sm(d));
    col = mix(col, c.yyy, sm(abs(d-.01)-.01));
    col = mix(col, vec3(0.99,0.68,0.53), sm(abs(d-.005)-.005));
    col = mix(col, 1.2*vec3(0.99,0.68,0.53), sm(abs(d-.005)-.001));
    
    col = mix(col, c.yyy, sm(abs(v)-.02));
}

void main()
{
    a = iResolution.x/iResolution.y;
    vec2 uv = (gl_FragCoord.xy-.5*iResolution)/iResolution.y,
        s;
    //uv.x *= 1.-.1*abs(sin(2.*pi*uv.y));
    vec3 col = c.xxx,
        o = c.yyx+.4*c.yzy,
        r = c.xyy,
        t = c.yyy, 
        u = cross(normalize(t-o),-r),
        dir,
        n, 
        x;
    int N = 650,
        i;
    t = uv.x * r + uv.y * u;
    dir = normalize(t-o);

    vec3 c1;
    float d = -(o.z-.1)/dir.z;
    
    for(i = 0; i<N; ++i)
    {
     	x = o + d * dir;
        scene(x,s);
        if(s.x < 1.e-5)break;
        if(x.z<0.)
        {
            i = N;
            break;
        }
        d += s.x;
//         d += min(s.x,1.e-1);
        //d += s.x;
    }
    
    if(i < N)
    {
        vec3 l = x+c.yyx;
        normal(x,n, 2.e-6);
        colorize(x.xy, col);
        col = .1*col 
            + .1*col*dot(l, n)
            + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);
    }
    
    col = 2.*col*col;
    
    gl_FragColor = vec4(clamp(col,0.,1.), 1.);
}
