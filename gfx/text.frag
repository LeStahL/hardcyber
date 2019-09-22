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

// Fixme: remove vec4 technique in favor of separate distance
// void blendadd(in vec4 src1, in vec4 src2, in float tlo, in float thi, out vec4 dst)
// {
//     vec4 added;
//     add(src1, src2, added);
//     dst = mix(src1, added, smoothstep(tlo-.5,tlo+.5,iTime)*(1.-smoothstep(thi-.5,thi+.5,iTime)));
// }

void window(in vec2 x, in vec2 size, in vec3 bg, in float title_index, out vec4 col);
void progressbar(in vec2 x, in float width, in float progress, out vec4 col);

float sm(float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void colorize(in vec2 x, out vec3 col)
{
    vec3 c1;
    vec2 ind,
        xv,
        xi;
    float d,
        vs = 16.,
        n,
        size = .1,
        xix = mod(x.x, size)-.5*size,
        xixj = (x.x - xix),
        ri,
        rim1,
        rip1,
        lines = 8.,
        da,
        op,
        s;
    
    // Background blending
    s = smoothstep(0.,.5,.5-abs(x.y));
    col = mix(1.e-4*c.xxx, vec3(0.04,0.18,0.24), s);
    
    // Background circles
    float vn;
    dvoronoi(vs*x, d, ind, vn);
    xv = ind/vs-x;
    lfnoise(vec2(3.,33.)*ind/vs-3.*iTime*c.xy,n);
    n = .5+.5*n;
    d = length(xv)-mix(.0,.35,n)/vs;
    col = mix(col, n*.5*vec3(1.00,0.40,0.39), sm(d));
    d = abs(d-.005) -.002;
    col = mix(col, (1.-n)*vec3(0.49,0.71,0.78), sm(d));
    
    for(float i = 1.; i < 9.; i += 1.)
    {
        rand((9.-i)*c.xx, op);
        op = .5+.5*round(16.*op)/16.;
        x += -.1+.2*op;
        
        xix = mod(x.x, size)-.5*size;
        xixj = (x.x - xix);
        
        // Edges
        lfnoise(2.e0*xixj*c.xx+14.*i, ri);
        lfnoise(2.e0*(xixj+size)*c.xx+14.*i, rip1);
        lfnoise(2.e0*(xixj-size)*c.xx+14.*i, rim1);

        float h = .2;
        
        ri = h*round(lines*ri)/lines;
        rip1 = h*round(lines*rip1)/lines;
        rim1 = h*round(lines*rim1)/lines;

        //if(ri < 0.)
        {
            dlinesegment(vec2(xix, x.y), vec2(-.5*size, mix(ri,rim1,.5)), vec2(-.25*size, ri), d);
            dlinesegment(vec2(xix, x.y), vec2(-.25*size, ri), vec2(.25*size, ri), da);
            d = min(d, da);
            dlinesegment(vec2(xix, x.y), vec2(.25*size, ri), vec2(.5*size, mix(ri,rip1,.5)), da);
            d = min(d, da);
            stroke(d, .002+.002*op, d);
            col = mix(col, op*(1.-n)*vec3(1.00,0.40,0.39), sm(d));

            // Dots
            lfnoise(8.*xixj*c.xx-3.*iTime*c.xy+14.*i, n);
            n = .5+.5*n;
            d = length(vec2(xix, x.y-ri))-mix(.0,.35,n)/vs;
            c1 = mix(vec3(1.00,0.40,0.39), vec3(0.85,0.87,0.89), n);
            col = mix(col, op*(1.-n)*c1, sm(d));
            stroke(d - .009, (1.-n)*.005, d);
            c1 *= 2.4;
            col = mix(col, op*(1.-n)*c1, sm(d));
        }
        
        x -= -.1+.2*op;
    }
    
    //mix to blackish
    lfnoise(3.*x.xy-vec2(1.,.1)*iTime, n);
    stroke(n, .3, n);
    col = mix(col, 1.e-4*c.xxx, n);
    col = mix(col, .1*col, 1.-s);
    
    col = mix(col, mix(col, vec3(1.00,0.40,0.39), mix(.4,.8,.5+.5*x.y/.1)), sm(abs(x.y)-.1));
    col = mix(col, c.xxx, sm(abs(abs(x.y)-.11)-.001));
    
    col = mix(col, col*col, clamp(-x.y/.1,0.,1.));
    col *= col;
}

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
    
//     if(uv.y < -.3 && iTime > 12.)
//     {
//         // Add overlay
//         colorize(2.*(c.xz*uv-.45*vec2(-a,1.)-12.*c.xy), new.gba);
//         new.gba = mix(old.gba, mix(old.gba, new.gba,.4), smoothstep(3.e-2, 5.e-2,length(new.gba)));
//     }
    
    if(uv.y > .4)
    {
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
        new.gba = mix(new.gba, mix(new.gba, c.xxx, .5), sm(d));
        
        // Add Static text
        dstring((uv-.45*vec2(-.85*a,1.)), 3., .02, d); // Team210
        
        stroke(d-.002, .001, d);
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
        new.gba = old.gba;
        
        float sc = smoothstep(0.,1.,clamp(iTime+3.,0.,1.))*(1.-smoothstep(0.,1.,clamp(iTime+1.,0.,1.)));
        
        dstring((uv-vec2(-.085,-.3)), 3., .02, d); // Team210
        float da;
        dstring((uv-vec2(-.08,-.35)), 26., .02, da); // present
        d = min(d,da);

        new.gba = mix(new.gba, mix(new.gba,c.yyy,sc), sm(d));
    }
    else if(iTime < 6.)
    {
        vec2 dx = (.25*a+.3*c.xy)*c.xy;
        if(iTime < 3.)
        {
            float ind = mix(100000., 2., clamp(iTime/3.,0.,1)), da;
            dint(uv+dx*c.xy, ind, .02, 6., d);
            
            dstring(uv+dx-2.*9.*.02*c.xy, 4., .02, da);
            d = min(d, da);
        }
        else if(iTime < 4.)
        {
            dint(uv+dx, 2., .02, 6., d);
            
            float da;
            dstring(uv+dx-2.*9.*.02*c.xy, 4., .02, da);
            d = min(d, da);
        }
        else if(iTime < 5.)
        {
            dint(uv+dx+.04*c.yx, 1., .02, 6., d);
         
            float da;
            dint(uv+dx, 2., .02, 6., da);
            d = min(d, da);
            
            dstring(uv+dx-2.*9.*.02*c.xy+.04*c.yx, 4., .02, da);
            d = min(d, da);
        }
        else if(iTime < 6.)
        {
            dint(uv+dx+.08*c.yx, 0., .02, 6., d);
            
            float da;
            dint(uv+dx+.04*c.yx, 1., .02, 6., da);
            d = min(d, da);
            
            dint(uv+dx, 2., .02, 6., da);
            d = min(d, da);
            
            dstring(uv+dx-2.*9.*.02*c.xy+.08*c.yx, 4., .02, da);
            d = min(d, da);
        }
        
            
        new.gba = mix(new.gba, mix(new.gba, vec3(1.00,0.87,0.57), .7), sm(d));
        stroke(d-.002, .001, d);
        new.gba = mix(new.gba, c.xxx, sm(d));
    }
    
    else if(iTime < 12. && iTime > 7.)
    {
        // EVK
        float da, db;
        dbox(vec2(uv.x+.75,uv.y-.35), vec2(.013,.035), da);
        stroke(da, .002, da);
        
        // E
        dglyph(vec2(uv.x+.75,uv.y-.35-.02).yx*c.zx, 101., .01, db);
        da = min(da, db);
        
        // V
        dglyph(vec2(uv.x+.75,uv.y-.35), 118., .01, db);
        da = min(da, db);
        
        // K
        dglyph(vec2(uv.x+.75,uv.y-.35+.02).yx*c.zx, 107., .01, db);
        da = min(da, db);
        
        // 333 block
        vec2 b = vec2(uv.x+.75,uv.y-.35+.02)-.01*c.xx-.02*c.xy,
            b1 = mod(b, .02)-.01,
            b1i = floor((b-b1)/.02);
        
        if(abs(b1i.y) <= 1. && b1i.x >= 0. && b1i.x <= 10.)
        {
            // random letter
            lfnoise(b1i-12.*iTime, db);
            db = 97.+mod(floor(26.*(.5+.5*db)),26.);
            dglyph(b1, db, .008, db);
            da = min(da, db);
        }
        
        dlinesegment(vec2(uv.x+.75,uv.y-.35+.06), -.015*c.xy, .25*c.xy, db);
        stroke(db, .001, db);
        da = min(da, db);
        
        // No more partycoding this time
        dstring(vec2(uv.x+.75,uv.y+.35), 5., .015, db);
        da = min(da, db);
        
        // Yeah. sure.
        dstring(vec2(uv.x-.2,uv.y+.35), 6., .015, db);
        float dc;
        dbox(vec2(uv.x-.2-.12,uv.y+.35), vec2(.165, .015), dc);
        db = max(dc,-db);
        da = min(da, db);
        
        // well, that worked.
        dstring(vec2(uv.x+.75,uv.y+.4),7., .015, db);
        da = min(da, db);
        
        // not
        dstring(vec2(uv.x-.2,uv.y+.4), 8., .015, db);
        dbox(vec2(uv.x-.2-.12,uv.y+.4), vec2(.165, .015), dc);
        db = max(dc,-db);
        da = min(da, db);
        
        
        new.gba = mix(new.gba, vec3(0.75,0.24,0.30), sm(da));
    }
    else if(iTime < 28.)
    {
        float da = length(uv)-.45, db;
        
        // Lightcyber
        dstring((uv+.3*c.xy), 2., .0415, db);
        db -= .001;
        da = max(da, -db);
        da = mix(1., da, smoothstep(0.,.5,clamp(iTime-18.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-22.,0.,1.))));
        new.gba = mix(new.gba, vec3(1.00,0.40,0.39), sm(da));
        
        // Team210
        da = length(uv - .3*c.xx)-.2, db;
        dstring(2.*(uv+.075*c.xy-.3*c.xx), 3., .0415, db);
        db -= .001;
//         da = max(da, -db);
        da = mix(1., da, smoothstep(0.,.5,clamp(iTime-19.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-22.,0.,1.))));
        db = mix(1., db, smoothstep(0.,.5,clamp(iTime-19.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-22.,0.,1.))));
        new.gba = mix(new.gba, vec3(1.00,0.40,0.39)*vec3(1.00,0.40,0.39), sm(da));
        new.gba = mix(new.gba, c.yyy, sm(db));
        
        // Graffiti tricks.
        dstring((uv-vec2(-.75,-.35)).yx*c.xz, 18., .045, db);
        dstring((uv-vec2(-.65,-.35)).yx*c.xz, 19., .045, da);
        db = min(db,da);
        db = mix(1., db, smoothstep(0.,.5,clamp(iTime-24.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-28.,0.,1.))));
        new.gba = mix(new.gba, mix(new.gba, c.xxx, .8), sm(db));
        
        stroke(db-.005, .0005, db);
        new.gba = mix(new.gba, mix(new.gba, vec3(1.00,0.40,0.39), .8), sm(db));
        
        // Nice!
        da = length((uv-vec2(-.6,-.325)).yx*c.xz)-.1;
        dstring((uv-vec2(-.6,-.35)).yx*c.xz, 20., .015, db);
        da = max(da, -db);
        da = mix(1., da, smoothstep(0.,.5,clamp(iTime-25.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-28.,0.,1.))));
        new.gba = mix(new.gba, mix(new.gba, c.xxx, .6), sm(da));
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
