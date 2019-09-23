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
        dtime((uv-.45*vec2(.975*a,1.05)), iTime+11., .01, d);
        new.gba = mix(new.gba, c.xxx, sm(d));
        
        // Add exact millisecond
        dint(uv-.45*vec2(.975*a,1.0), floor(1.e3*fract(iTime)), .01, 4., d);
//         new.gba = mix(new.gba, vec3(1.00,0.40,0.39), sm(d));
        stroke(d-.001, .0005, d);
        new.gba = mix(new.gba, c.xxx, sm(d));
    }
    
    if(iTime < 0.) 
    {
        float sc = smoothstep(0.,1.,clamp(iTime+3.,0.,1.))*(1.-smoothstep(0.,1.,clamp(iTime+1.,0.,1.)));
        
        vec3 c1 = new.gba;
        addwindow(uv-vec2(0.,-.3), c1, vec2(.15,.1));
        
        dstring((uv-vec2(-.085,-.3)), 3., .02, d); // Team210
        float da;
        dstring((uv-vec2(-.08,-.35)), 26., .02, da); // present
        d = min(d,da);

        c1 = mix(c1,c.xxx, sm(d));
        
        new.gba = mix(new.gba, c1, sc);
    }

    else if(iTime < 44.)
    {
        float da, db;
        
        // Once
        dstring((uv-vec2(-.3,.3)), 21., .1, da);
        
        db = abs(mod(uv.x+uv.y,.3)-.15)-.075;
        vec3 c1 = mix(mix(new.gba,.3*c.xxx,.5), c.xxx, sm(db));
        
        db = smoothstep(33.,34.,iTime);
        da = mix(1., da, db);
        new.gba = mix(new.gba, c1, sm(da));
        
        stroke(da-.02,.001,da);
        new.gba = mix(new.gba, c.xxx, sm(da));
        
        // You
        dstring(uv-vec2(.35,.34), 22., .05, da);
        
        dbox(uv-vec2(.35,.34), vec2(.15,.06), db);
        db = max(db,-da);
        float mx = smoothstep(34.,35., iTime);
        db = mix(1., db, mx);
        new.gba = mix(new.gba, c.xxx, sm(db));
        
        // Offend
        dstring(uv-vec2(.25,.24), 23., .0277, da);
        mx = smoothstep(35.,36.,iTime);
        da = mix(1., da, mx);
        new.gba = mix(new.gba, .8*c.xxy, sm(da));
        
        // You
        dstring(uv-vec2(.25,.15), 22., .05, da);
        mx = smoothstep(36.,37.,iTime);
        da = mix(1., da, mx);
        new.gba = mix(new.gba, .8*c.xxy, sm(da));
        
        // Cannot
        dstring((uv-vec2(.45,.05)).yx*c.zx, 24., .05, da);
        
        dbox((uv-vec2(.45,-.1)), vec2(.05,.3), db);
        db = max(db,-da);
        mx = smoothstep(37.,38., iTime);
        db = mix(1., db, mx);
        new.gba = mix(new.gba, c.xxx, sm(db));

        // Stop
        dstring((uv-vec2(.6,.1)).yx*c.zx, 25., .1, da);
        
        db = smoothstep(38.,39.,iTime);
        da = mix(1., da, db);
        new.gba = mix(new.gba, c1, sm(da));
        
        stroke(da-.02,.001,da);
        new.gba = mix(new.gba, c.xxx, sm(da));
    }
    else if(iTime < 60.)
    {
        //vec3(0.93,0.36,0.44)
        float da, db;
        
        db = abs(mod(uv.x+uv.y,.3)-.15)-.075;
        vec3 c1 = mix(mix(new.gba,vec3(0.93,0.36,0.44),.5), c.xxx, sm(db));
        
        // Banging your head against 
        dstring((uv-vec2(-.3,.3)), 38., .02, da);
        
        db = smoothstep(45.,46.,iTime)-smoothstep(50.,51.,iTime);
        da = mix(1., da, db);
        stroke(da-.005,.0025,db);
        new.gba = mix(new.gba, c.yyy, sm(db));
        
        new.gba = mix(new.gba, c1, sm(da-.0025));
        
        db = da+.0025;
        new.gba = mix(new.gba,2.*c1, sm(db));
        
        // a wall for one hour burns 
        dstring((uv-vec2(-.3,.25)), 39., .02, da);
        
        db = smoothstep(46.,47.,iTime)-smoothstep(51.,52.,iTime);
        da = mix(1., da, db);
        stroke(da-.005,.0025,db);
        new.gba = mix(new.gba,c.yyy, sm(db));
        
        new.gba = mix(new.gba, c1, sm(da-.0025));
        
        db = da+.0025;
        new.gba = mix(new.gba,2.*c1, sm(db));
        
        // 150 kilocalories. Want to
        dstring((uv-vec2(-.3,.2)), 40., .02, da);
        
        db = smoothstep(47.,48.,iTime)-smoothstep(52.,53.,iTime);
        da = mix(1., da, db);
        stroke(da-.005,.0025,db);
        new.gba = mix(new.gba,c.yyy, sm(db));
        
        new.gba = mix(new.gba, c1, sm(da-.0025));
        
        db = da+.0025;
        new.gba = mix(new.gba, 2.*c1, sm(db));
        
        // start losing some weight?
        dstring((uv-vec2(-.3,.15)), 41., .02, da);
        
        db = smoothstep(48.,49.,iTime)-smoothstep(53.,54.,iTime);
        da = mix(1., da, db);
        stroke(da-.005,.0025,db);
        new.gba = mix(new.gba, c.yyy, sm(db));
        
        new.gba = mix(new.gba, c1, sm(da-.0025));
        
        db = da+.0025;
        new.gba = mix(new.gba, 2.*c1, sm(db));
        
        new.gba = clamp(new.gba,0.,1.);
    }
    else if(iTime < 130.)
    {
        float da, db;
        
        dbox(uv-vec2(.05,.3), vec2(1.6,.055), da);
        da = mix(1.,da,smoothstep(125.,126.,iTime));
        new.gba = mix(new.gba, mix(new.gba,c.xxx,.5), sm(da));
        
        // Wait, what?
        dstring((uv-vec2(-.4,.3)), 28., .05, da);
        
        lfnoise(55.*uv, db);
        stroke(db,0.535,db);
        vec3 c1 = mix(mix(new.gba,c.yyy,.3), c.yyy, sm(db/50.));
        
        db = smoothstep(125.,126.,iTime);
        da = mix(1., da, db);
        new.gba = mix(new.gba, c1, sm(da));
        
        stroke(da-.01,.001,da);
        new.gba = mix(new.gba, c.yyy, sm(da));
    }
    else
    {
        float da;
        dstring(uv-vec2(-.55,0.), 27., .025, da);
        da = mix(1., da, smoothstep(172.,172.5,iTime));
        new.gba = mix(new.gba, c.yyy, smoothstep(172.,172.5,iTime));
        new.gba = mix(new.gba, vec3(.9,.2,.03), sm(da));
        stroke(da-.005, .001, da);
        new.gba = mix(new.gba, c.xxx, sm(da));
    }
    
    //FIXME: remove debug lines
//     vec2 ad = abs(mod(uv-.05,.02)-.01)-.001;
//     new.gba = mix(new.gba, c.yyx, sm(min(ad.x,ad.y)));
//     
//     ad = abs(mod(uv-.05,.1)-.05)-.001;
//     new.gba = mix(new.gba, c.yxy, sm(min(ad.x,ad.y)));
//     
//     ad = abs(uv)-.002;
//     new.gba = mix(new.gba, c.xxx, sm(min(ad.x,ad.y)));
    //FIXME remove until here
    
    
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
