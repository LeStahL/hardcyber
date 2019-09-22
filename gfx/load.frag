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
uniform float iProgress;

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);

void rand(in vec2 x, out float n)
{
    x += 400.;
    n = fract(sin(dot(sign(x)*abs(x) ,vec2(12.9898,78.233)))*43758.5453);
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash11(in float p, out float d)
{
    p = fract(p * .1031);
    p *= p + 33.33;
    p *= p + p;
    d = fract(p);
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash12(in vec2 p, out float d)
{
	vec3 p3  = fract(vec3(p.xyx) * .1031);
    p3 += dot(p3, p3.yzx + 33.33);
    d = fract((p3.x + p3.y) * p3.z);
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash21(in float p, out vec2 d)
{
	vec3 p3 = fract(vec3(p) * vec3(.1031, .1030, .0973));
	p3 += dot(p3, p3.yzx + 33.33);
    d = fract((p3.xx+p3.yz)*p3.zy);
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash22(in vec2 p, out vec2 d)
{
	vec3 p3 = fract(vec3(p.xyx) * vec3(.1031, .1030, .0973));
    p3 += dot(p3, p3.yzx+33.33);
    d = fract((p3.xx+p3.yz)*p3.zy);
}

// Adapted from iq, https://www.shadertoy.com/view/XsXSz4
void dtriangle(in vec2 p, in vec2 p0, in vec2 p1, in vec2 p2, out float dst)
{
	vec2 e0 = p1 - p0;
	vec2 e1 = p2 - p1;
	vec2 e2 = p0 - p2;

	vec2 v0 = p - p0;
	vec2 v1 = p - p1;
	vec2 v2 = p - p2;

	vec2 pq0 = v0 - e0*clamp( dot(v0,e0)/dot(e0,e0), 0.0, 1.0 );
	vec2 pq1 = v1 - e1*clamp( dot(v1,e1)/dot(e1,e1), 0.0, 1.0 );
	vec2 pq2 = v2 - e2*clamp( dot(v2,e2)/dot(e2,e2), 0.0, 1.0 );
    
    float s = sign( e0.x*e2.y - e0.y*e2.x );
    vec2 d = min( min( vec2( dot( pq0, pq0 ), s*(v0.x*e0.y-v0.y*e0.x) ),
                       vec2( dot( pq1, pq1 ), s*(v1.x*e1.y-v1.y*e1.x) )),
                       vec2( dot( pq2, pq2 ), s*(v2.x*e2.y-v2.y*e2.x) ));

	dst = -sqrt(d.x)*sign(d.y);
}

void stroke(in float d0, in float s, out float d)
{
    d = abs(d0)-s;
}

void dist(in vec2 a, in vec2 b, out float d)
{
    d = length(b-a);
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

void dbox(in vec2 x, in vec2 b, out float d)
{
    vec2 da = abs(x)-b;
    d = length(max(da,c.yy)) + min(max(da.x,da.y),0.0);
}

void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d)
{
    vec2 da = p2-p1;
    d = length(x-mix(p1, p2, clamp(dot(x-p1, da)/dot(da,da),0.,1.)));
}

const vec3 orange =vec3(0.20,0.60,0.86),
    redorange = vec3(0.27,0.70,0.62);
void ddecorations(in vec2 x, in float decs, out float d)
{
    float r, v, vz;
    vec2 y, yi;
    
    dvoronoi(x/decs, v, yi, vz);
    y = x-yi*decs;
 
    hash12(yi*decs, r);
    if(r < .5)
    {
        dbox(y, vz*decs/sqrt(2.)*c.xx, d);
    }
    else
    {
        hash11(r, r);
        d = length(y)-vz*decs;
    }
}

void modgradient(in vec2 x, in float decs, inout vec3 col)
{
    float y = mod(x.y, decs)-.5*decs;
    
    col = mix(orange, redorange, 2.*abs(y)/decs);
}

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void smoothmin(in float a, in float b, in float k, out float dst)
{
    float h = max( k-abs(a-b), 0.0 )/k;
    dst = min( a, b ) - h*h*h*k*(1.0/6.0);
}

void dloading(in vec2 uv, out float d)
{
    d = 1.;
    float da = 1.,
        db,
        dc = 1.;
    
    //L
    dlinesegment(uv, vec2(-.75,-.75), vec2(-.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.75,-.75), vec2(.65, -.75), da);
    d = min(d, da);
    
    dlinesegment(uv, vec2(-.65,-.1), vec2(-.65,-.65), db);
    dc = min(dc, db);
    
    uv -= 2.*c.xy;
    
    //O
    dlinesegment(uv, vec2(-.75,-.75), vec2(.75, -.75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.75,.75), vec2(.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.75,-.75), vec2(-.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(.75,-.75), vec2(.75, .75), da);
    d = min(d, da);
    
    dlinesegment(uv, vec2(.65,.35), vec2(.65,.65), db);
    dc = min(dc, db);
    
    uv -= 2.*c.xy;
    
    //A
    dlinesegment(uv, vec2(-.65,-.75), vec2(-.65,.75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(.65,0.), vec2(.65,.75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.65,.75), vec2(.65, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.65,0.), vec2(.65, 0.), da);
    d = min(d, da);
    
    dlinesegment(uv, vec2(-.75,-.75), vec2(-.75,0.), db);
    dc = min(dc, db);
    dlinesegment(uv, vec2(.75,0.), vec2(.75,-.75), db);
    dc = min(dc, db);
    
    uv -= 2.*c.xy;
    
    //D
    dlinesegment(uv, vec2(-.75,-.75), vec2(.75, -.75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.75,.75), vec2(.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.75,-.75), vec2(-.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(.75,-.75), vec2(.75, .75), da);
    d = min(d, da);
    
    dlinesegment(uv, vec2(-.65,-.1), vec2(-.65,-.65), db);
    dc = min(dc, db);
    
    uv -= 2.*c.xy;
    
    //I
    dlinesegment(uv, vec2(0.,-.75), vec2(0., .75), da);
    d = min(d, da);
    
    dlinesegment(uv, vec2(.1,-.75), vec2(.1,0.), db);
    dc = min(dc, db);
    
    uv -= 2.*c.xy;
    
    //N
    dlinesegment(uv, vec2(-.75,.75), vec2(.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.75,-.75), vec2(-.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(.75,-.75), vec2(.75, .75), da);
    d = min(d, da);
    
    dlinesegment(uv, vec2(-.65,-.1), vec2(-.65,-.75), db);
    dc = min(dc, db);
    
    uv -= 2.*c.xy;
    
    //G
    dlinesegment(uv, vec2(-.75,-.75), vec2(.75, -.75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.75,.75), vec2(.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(-.75,-.75), vec2(-.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(.75,.5), vec2(.75, .75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(.75,0.), vec2(.75, -.75), da);
    d = min(d, da);
    dlinesegment(uv, vec2(.75,0.), vec2(.25, 0.), da);
    d = min(d, da);
    
    dlinesegment(uv, vec2(-.65,-.1), vec2(-.65,-.65), db);
    dc = min(dc, db);
    
    for(int i=0; i<3; ++i)
    {
        uv -= 2.*c.xy;
        dlinesegment(uv, vec2(0.,-.55), vec2(0., -.65), da);
        d = min(d, da);
        
        dlinesegment(uv, vec2(.1,-.55), vec2(.1,-.65), db);
        dc = min(dc, db);
    }
    stroke(d,.1,d);
    stroke(dc, .1, dc);
    smoothmin(d,dc,.1,d);
}

void main()
{
    float d;
    vec2 uv = (gl_FragCoord.xy-.5*iResolution)/iResolution.y;
    vec3 col = c.yyy,
        c1 = col;
    
    // Background geraffel
    for(float decs = .05; decs <= 1.; decs += .05)
    {
        modgradient(uv, decs, c1);
        
        ddecorations(uv-1337.-12.*decs*c.yx, decs, d);
        
        float m;
        lfnoise((1.+5.*decs)*uv-1337.-12.*decs*c.yx, m);
        
        col = mix(col, mix(col,c1,mix(.6,.1,.8+.2*m)* mix(1., 0., clamp(length(uv),0.,1.))), sm(d));
        stroke(d, .001, d);
        col = mix(col, orange, sm(d));
    }
    
    col = mix(col, c.yyy, .2);
    
    // Background loading bar window
    dbox(uv, vec2(.3,.2), d);
    vec3 gcol = length(col)/sqrt(3.)*c.xxx;
    vec3 window_raw = vec3(0.08,0.07,0.16);
    vec3 window_background = mix(mix(col,window_raw,.2), mix(gcol,window_raw,.8), clamp((.5-uv.y/.4),0.,1.));
    col = mix(col, window_background, sm(d));
    
    // White border on loading bar window
    d = abs(d-.002)-.002;
    d = mix(d, 1., step(abs(uv.y),.19));
    col = mix(col, c.xxx, sm(d));
    
    // Progress bar outline
    dbox(uv, vec2(.28,.02), d);
    d = abs(d-.001)-.001;
    d = mix(d, 1., step(abs(uv.y),.015));
    col = mix(col, c.xxx, sm(d));
    
    // Progress bar value
    float w = .275;
    dbox(uv+mix(w,0.,iProgress)*c.xy, vec2(mix(0.,w,iProgress),.01), d);
    col = mix(col, c.xxx, sm(d));
    
    // X box
    dbox(uv-vec2(.26,.16), .015*c.xx, d);
    col = mix(col, c.xxx, sm(d+.005));
    stroke(d, .001, d);
    col = mix(col, c.xxx, sm(d));
    
    // Actual x
    dlinesegment(uv,vec2(.25,.15),vec2(.27,.17),d);
    float da;
    dlinesegment(uv,vec2(.25,.17),vec2(.27,.15),da);
    d = min(d,da);
    stroke(d,.002, d);
    col = mix(col, c.yyy, sm(d));
    
    // Loading... text
    dloading(60.*(uv-vec2(-.26,.05)),d);
    d /= 60.;
    d -= .002;
    col = mix(col, c.xxx, sm(d));
    
    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}
