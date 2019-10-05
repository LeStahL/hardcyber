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

float iScale;

void scale(out float s);

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);
float a = 1.0;

void hash22(in vec2 x, out vec2 y);
void rand(in vec2 x, out float n);
void lfnoise(in vec2 t, out float n);
void dspline2(in vec2 x, in vec2 p0, in vec2 p1, in vec2 p2, out float ds);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void stroke(in float d0, in float s, out float d);
void smoothmin(in float a, in float b, in float k, out float dst);
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
    
    stroke(d, .05, d);
    
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

void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void zextrude(in float z, in float d2d, in float h, out float d);
void scene(in vec3 x, out vec2 sdf)
{    
    dhardcyber(x.xy, sdf.x);
    zextrude(x.z, -sdf.x, mix(.0,.1,clamp((iTime-3.5)/.5,0.,1.)), sdf.x);
    smoothmin(sdf.x, x.z, mix(.001,.1,clamp((iTime-3.5)/.5,0.,1.)), sdf.x);
    sdf.y = 1.;
    stroke(sdf.x, mix(0.,.01,clamp((iTime-3.5)/.5,0.,1.)), sdf.x);
//     sdf.x = abs(sdf.x);
//     sdf.x /= 4.;
}

void normal(in vec3 x, out vec3 n, in float dx);
void colorize(in vec2 uv, inout vec3 col)
{
    vec3 c1;
    float d = floor(8.*(.5+.4*tanh(6.*uv.y+uv.x)))/8.;
    vec2 ind;
    float v,vn;
    dvoronoi(16.*uv, v, ind,vn);
    float r;
    rand(ind,r);
    d = (uv.y+.25)/.5-.2*r;
    palette(clamp(d,0.,1.),c1);
//     c1 = mix(c1, c.yyy, sm(abs(v)-.02));
    col = (.5+.5*r)*c.xxx;
    
    dhardcyber(uv, d);
    d = mix(1.,d,clamp((iTime-3.)/.5,0.,1.));
    col = mix(col, .7*c.xxx, sm(d-.04));
    col = mix(col, c1, sm(d));
    col = mix(col, c.yyy, sm(abs(d-.01)-.01));
    col = mix(col, vec3(0.99,0.68,0.53), sm(abs(d-.005)-.005));
    col = mix(col, 1.2*vec3(0.99,0.68,0.53), sm(abs(d-.005)-.001));
    
    col = mix(col, c.yyy, sm(abs(v)-.02));
}

void main()
{
    scale(iScale);
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
    int N = 150,
        i;
    t = uv.x * r + uv.y * u;
    dir = normalize(t-o);

    vec3 c1;
    float d = -o.z/dir.z;
    
    d = -(o.z-.1)/dir.z;
    
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
        col = mix(c.xxx, col, clamp(iTime/(1.+length(x.xy)),0.,1.));
    }
    
    col = 2.*col*col;
    col = mix(col, c.yyy, clamp(iTime-9.,0.,1.));
    
    col = mix(col, 1.5*col, iScale);
    
    gl_FragColor = vec4(clamp(col,0.,1.), 1.);
}
