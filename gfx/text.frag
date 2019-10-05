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

uniform float iFontWidth, iTime;
uniform vec2 iResolution;
uniform sampler2D iChannel0, iFont;
uniform float iFSAA;

float iScale;

void scale(out float s);

out vec4 gl_FragColor;

// Global constants
const vec3 c = vec3(1.,0.,-1.);
const float pi = acos(-1.);
float a; // Aspect ratio

void rand(in vec2 x, out float num);
void lfnoise(in vec2 t, out float num);
void rshort(in float off, out float val);
void rfloat(in float off, out float val);
void dbox(in vec2 x, in vec2 b, out float dst);
void dcircle(in vec2 x, out float d);
void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);
void drhomboid(in vec2 x, in vec2 b, in float tilt, out float dst);
void dcirclesegment(in vec2 x, in float r, in float p0, in float p1, out float d);
void stroke(in float d0, in float s, out float d);
void dglyph(in vec2 x, in float ordinal, in float size, out float dst);
void dstring(in vec2 x, in float ordinal, in float size, out float dst);
void dfloat(in vec2 x, in float num, in float size, out float dst);
void smoothmin(in float a, in float b, in float k, out float dst);
void dint(in vec2 x, in float num, in float size, in float ndigits, out float dst);
void dtime(in vec2 x, in float num, in float size, out float dst);

void addwindow(in vec2 uv, inout vec3 col, in vec2 dimension);

float sm(float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    scale(iScale);
    a = iResolution.x/iResolution.y;
    vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);
    
    float d;

    vec4 old = c.yyyy, 
        new = c.yyyy;
    
    float bound = sqrt(iFSAA)-1.;

    for(float i = -.5*bound; i<=.5*bound; i+=1.)
        for(float j=-.5*bound; j<=.5*bound; j+=1.)
        {
            old.gba += texture(iChannel0, (fragCoord+vec2(i,j)*3./max(bound, 1.))/iResolution.xy).xyz;
        }
    old.gba /= iFSAA;
    
    new = old;
    
    if(uv.y > .38) // Ui overlay with time counter and credits
    {
        addwindow(uv-.45*vec2(-.45*a,1.-2.*.008*c.yx), new.gba, vec2(.4,.04));
        addwindow((uv-.45*vec2(.97*a,1.-2.*.008*c.yx))*c.zx, new.gba, vec2(.1,.04));
        float da;
        dstring((uv-.45*vec2(-.55*a,1.+4.*.008)), 9., .004, d);
        dstring((uv-.45*vec2(-.55*a,1.+2.*.008)), 10., .004, da);
        d = min(d,da);
        dstring((uv-.45*vec2(-.55*a,1.)), 11., .004, da);
        d = min(d,da);
        dstring((uv-.45*vec2(-.55*a,1.-2.*.008)), 12., .004, da);
        d = min(d,da);
        dstring((uv-.45*vec2(-.55*a,1.-4.*.008)), 13., .004, da);
        d = min(d,da);
        new.gba = mix(new.gba, mix(new.gba, c.xxx, 1.), sm(d));
        
        // Add Static text
        dstring((uv-.45*vec2(-.85*a,1.)), 3., .02, d); // Team210
        
        new.gba = mix(new.gba, mix(new.gba,c.xxx,.5), sm(d));
        stroke(d-.002, .002, d);
        new.gba = mix(new.gba, vec3(1.00,0.40,0.39), sm(d));

        // Add time overlay
        dtime((uv-.45*vec2(.975*a,1.05)), iTime, .01, d);
        new.gba = mix(new.gba, c.xxx, sm(d));
        
        // Add exact millisecond
        dint(uv-.45*vec2(.975*a,1.0), floor(1.e3*fract(iTime)), .01, 4., d);
//         new.gba = mix(new.gba, vec3(1.00,0.40,0.39), sm(d));
        stroke(d-.001, .0005, d);
        new.gba = mix(new.gba, c.xxx, sm(d));
    }
    
    if(iTime < 20.)
    {
        float sc = clamp(iTime-10.,0.,1.)*(1.-clamp(iTime-18.,0.,1.)),
            da;
        
        // window
        vec3 c1 = new.gba;
        addwindow(uv, c1, vec2(.72,.15));
        new.gba = mix(new.gba, c1, sc);
        
        // No more partycoding this time!
        dstring(uv-vec2(-.55,.05), 5., .02, d);
        
        // yeah sure.
        dstring(uv-vec2(-.55,0.), 6., .02, da);
        d = min(d, da);
        
        // well, that worked!
        dstring(uv-vec2(-.55,-.05), 7., .02, da);
        d = min(d, da);
        
        d = mix(1., d, sc);
        
        new.gba = mix(new.gba, c.yyy, sm(d-.005));
        new.gba = mix(new.gba, c.xxx, sm(d));
    }
    else if(iTime < 32.) 
    {
        float sc = smoothstep(0.,1.,clamp(iTime-25.,0.,1.))*(1.-smoothstep(0.,1.,clamp(iTime-30.,0.,1.)));
        
        vec3 c1 = new.gba;
        addwindow(uv-vec2(0.,-.3), c1, vec2(.15,.1));
        
        dstring((uv-vec2(-.085,-.3)), 3., .02, d); // Team210
        float da;
        dstring((uv-vec2(-.08,-.35)), 26., .02, da); // present
        d = min(d,da);

//         c1 = mix(c1, c.yyy, sm(d-.01));
        c1 = mix(c1,c.xxx, sm(d));
        
        
        new.gba = mix(new.gba, c1, sc);
    }
    else if(iTime < 60.) // star sky, once you offend
    {
        float da;
        vec3 c_1 = vec3(1.00,0.33,0.38),
            c_2 = vec3(0.94,0.91,0.60);
            
        float sc = smoothstep(54.,55.,iTime)*(1.-smoothstep(60., 61., iTime));
        
        dstring(uv-vec2(-.55,.025), 18., .03, d);
        dstring(uv-vec2(-.55,-.025), 19., .03, da);
        d = min(d, da);
        
        d = mix(1., d, sc);
        
        // window
        vec3 c1 = new.gba;
        addwindow(uv, c1, vec2(.72,.15));
        new.gba = mix(new.gba, c1, sc);
        
        new.gba = mix(new.gba, c_1, sm(abs(d-.002)-.001));
        new.gba = mix(new.gba, c_2, sm(d));
    }
    
    else if(iTime < 121.) // greetings
    {
        
    }
    else if(iTime < 135.) // spacepigs diss
    {
        float da;
        vec3 c_1 = vec3(1.00,0.33,0.38),
            c_2 = vec3(0.94,0.91,0.60);
            
        float sc = smoothstep(125.,126.,iTime)*(1.-smoothstep(133., 134., iTime));
        
        dstring(uv-vec2(-.55,.075), 20., .027, d);
        dstring(uv-vec2(-.55,.025), 21., .027, da);
        d = min(d, da);
        dstring(uv-vec2(-.55,-.025), 22., .027, da);
        d = min(d, da);
        dstring(uv-vec2(-.55,-.075), 23., .027, da);//eurer
        d = min(d, da);
        
        d = mix(1., d, sc);
        
        // window
        vec3 c1 = new.gba;
        addwindow(uv, c1, vec2(.72,.15));
        new.gba = mix(new.gba, c1, sc);
        
        new.gba = mix(new.gba, c_1, sm(abs(d-.002)-.001));
        new.gba = mix(new.gba, c_2, sm(d));
    }
    else
    {
//         col = mix(col, c.yyy, clamp((iTime-212)/5., 0., 1.));
        float da;
        dstring(uv-vec2(-.55,0.), 27., .025, da);
        da = mix(1., da, smoothstep(212.,217.,iTime));
        new.gba = mix(new.gba, c.yyy, smoothstep(212.,217.,iTime));
        new.gba = mix(new.gba, vec3(.9,.2,.03), sm(da));
        stroke(da-.005, .001, da);
        new.gba = mix(new.gba, c.xxx, sm(da));
    }
    
    
    // 
    float dc;
    dbox(uv, .5*vec2(a,1.), dc);
    stroke(dc, .005, dc);
    new.gba = mix(new.gba, c.yyy, sm(dc));
    
    fragColor = vec4(new.gba, 1.);
}

void main()
{
    mainImage(gl_FragColor, gl_FragCoord.xy);
}
