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

out vec4 gl_FragColor;

uniform vec2 iResolution;
uniform float iProgress;

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);

float sm(in float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void rand(in vec2 x, out float d);
void hash11(in float p, out float d);
void hash12(in vec2 p, out float d);
void hash21(in float p, out vec2 d);
void hash22(in vec2 p, out vec2 d);
void stroke(in float d0, in float s, out float d);
void lfnoise(in vec2 t, out float n);
void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void dbox(in vec2 x, in vec2 b, out float d);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);

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

void smoothmin(in float a, in float b, in float k, out float dst);
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

void addwindow(in vec2 uv, inout vec3 col, in vec2 dimensions);
void addprogressbar(in vec2 uv, inout vec3 col, in vec2 dimensions, in float progress);

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
        col = mix(col, mix(orange,c.xxx,decs), sm(d));
    }
    
    col = mix(col, c.yyy, .2);
    
    addwindow(uv, col, vec2(.3,.2));
    addprogressbar(uv, col, vec2(.28,.02), iProgress);
    
    // Loading... text
    dloading(60.*(uv-vec2(-.26,.05)),d);
    d /= 60.;
    d -= .002;
    col = mix(col, c.xxx, sm(d));
    
    gl_FragColor = vec4(clamp(col,0.,1.),1.);
}
