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

uniform float iFader0;
uniform float iFader1;
uniform float iFader2;
uniform float iFader3;
uniform float iFader4;
uniform float iFader5;
uniform float iFader6;
uniform float iFader7;

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);
float a = 1.0;

void hash22(in vec2 x, out vec2 y);
void rand(in vec2 x, out float n);
void lfnoise(in vec2 t, out float n);
void mfnoise(in vec2 x, in float d, in float b, in float e, out float n);
void dvoronoi(in vec2 x, out float d, out vec2 z, out float dv);
float dspiral(vec2 x, float a, float d);
float sm(float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

float dspiral(vec2 x, float a, float d)
{
    float p = atan(x.y, x.x),
        n = floor((abs(length(x)-a*p)+d*p)/(2.*pi*a));
    p += (n*2.+1.)*pi;
    return -abs(length(x)-a*p)+d*p;
}

void stroke(in float d0, in float s, out float d);
void colorize(in vec2 x, inout vec3 col)
{
    float v, n = 64., r, vn;
    vec2 ind;
    dvoronoi(n*x, v, ind, vn);
    rand(ind, r);
    vec2 y = x-ind/n;
    vec3 c1;
    rand(ind+1337., c1.x);
    rand(ind+2337., c1.y);
    rand(ind+3337., c1.z);
    c1 *= vec3(1.,.7,.3);
    c1 = .5+.5*c1;
    c1 *= vec3(.4,.6,1.);
    float d = length(y)-.002*r;
    if(r > .75)
        col = mix(col, c1, sm(d));
//     r *= cos(pi*x.y);
    if(r>.5)
    {
        col = mix(col, mix(col, 2.*c1, .8), sm(d-.004*r*r));
        col = mix(col, mix(col, 3.*c1, .4), sm(d-.01*r*r));
    }
    
    dvoronoi(2.*n*x, v, ind, vn);
    y = x-ind/n/2.;
    rand(ind, r);
    d = length(y)-.002*r;
    col = mix(col, c.xxx, sm(d));
    
    lfnoise(x.xy-v*v*v, d);
    col = mix(col, c.yyy, .5+.5*d);
    
    col = .6*col+.3*step(.8,col);
    col *= 2.;
    
    v = dspiral(x, .1,.01);
    col = mix(col, c.yyy, 1.-sm(v*6.e-3));
    col = mix(col, 2.5*col, sm(v*2.e-3));
}

void dbox(in vec2 x, in vec2 b, out float d);
void street(in vec2 x, out vec3 col)
{
    x.y += .3*iTime;
    
    float dx;
    lfnoise(x.y*c.xx, dx);
    x.x += .1*dx;
    
    col = .4*c.xxx;
    float da = mod(x.y, .1)-.05;
    dbox(vec2(x.x,da), vec2(.005,.025), da);
    col = mix(col, c.xxx, sm(da));
    col = mix(col, c.xxx, sm(abs(abs(x.x)-.1)-.01));
    
    float n;
    mfnoise(x.xy, mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),200., .35,n);
    col = mix(col, .5*col, .5+.5*n);
    
    col = mix(col, .6*c.xxx, abs(n)-.1);
    
    vec2 ind;
    float v, vn;
    dvoronoi(256.*x, v, ind, vn);
    ind = x-ind/256.;
    col = mix(col, .0*c.xxx, sm(length(ind)-.0001));
}

void dbox3(in vec3 x, in vec3 b, out float d);
void add(in vec2 sda, in vec2 sdb, out vec2 sdf);
void scene(in vec3 x, out vec2 sdf)
{
    x.y += .3*iTime;
    
    float dx;
    lfnoise((x.y)*c.xx, dx);
    x.x += .1*dx;
    
    sdf = c.xx;
    float n;
    mfnoise(x.xy, mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),2000., mix(.35,.45,smoothstep(.4,1.6,abs(x.x))),n);
    float n0 = n;
    n = .5+.5*n;
    n *= smoothstep(.1,.3,abs(x.x))+smoothstep(.4,1.2,abs(x.x));
    sdf.x = x.z-.1*n;
    sdf.y = 1.;
    
    float d;
    dbox3(x-c.yyx*.005*step(.1,abs(n0)-.01), vec3(.1,1.e3,.001+.01*n0), d);
    
    add(sdf, vec2(d, 2.), sdf);
}

void normal(in vec3 x, out vec3 n, in float dx);
void palette(in float scale, out vec3 col)
{
    const int N = 5;
    const vec3 colors[N] = vec3[N](
            vec3(0.27,0.13,0.26),
            vec3(0.43,0.21,0.33),
            vec3(0.69,0.36,0.42),
            vec3(0.87,0.52,0.45),
            vec3(0.99,0.68,0.53)
// vec3(0.04,0.04,0.15),
// vec3(0.18,0.32,0.46),
// vec3(0.66,0.43,0.62),
// vec3(0.96,0.78,0.88),
// vec3(0.40,0.00,0.18)
    );
	float index = floor(scale*float(N)), 
        remainder = scale*float(N)-index;
    col = mix(colors[int(index)],colors[int(index)+1], remainder);
}

void main()
{
    a = iResolution.x/iResolution.y;
    vec2 uv = (gl_FragCoord.xy-.5*iResolution)/iResolution.y,
        s;

        vec3 col = c.yyy,
        o = .3*c.yyx+c.yzy,
        r = c.xyy,
        t = c.yyy, 
        u = cross(normalize(t-o),-r),
        dir,
        n, 
        x;
    int N = 250,
        i;
    t = uv.x * r + uv.y * u;
    
    dir = normalize(t-o);

    vec3 c1;
    float d = -(o.z-.2)/dir.z;
    
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
        vec3 l = c.yyx;
        normal(x,n, 2.e-6);
        
        if(s.y == 1.)
        {
            palette(x.z/.22, col);
//             float na;
//             mfnoise(x.xy, mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),2000., mix(.35,.45,smoothstep(.4,1.6,abs(x.x))),na);
//             col = mix(col, 2.*col, abs(abs(na)-.1)-.001);
            col = .1*col 
                + .1*col*dot(l, n)
                + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);
        }
        else if(s.y == 2.)
        {
            street(x.xy, col);
            col = .1*col 
                + .1*col*dot(l, n)
                + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);
        }
        else 
        {
            colorize(x.xy, col);
            col = .1*col 
                + .1*col*dot(l, n)
                + .8*col*pow(abs(dot(reflect(-l,n),dir)),2.);
        }
        if(x.z>.05)
            col = mix(col, 3.*col, smoothstep(.95,.951, n.z));
    }

    col = 12.*col*col;
    
    col = mix(col, c.yyy, tanh(2.e-1*d));
    
    vec3 c2;
    colorize(4.*uv, c2);
    col = mix(col, 2.*c2, smoothstep(.3,.5, uv.y));
    
    col = mix(c.yyy, col, clamp(iTime,0.,1.));
    
    gl_FragColor = vec4(clamp(col,0.,1.), 1.);
}
