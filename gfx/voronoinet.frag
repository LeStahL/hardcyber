/* Corfield Imitation 1
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

void scale(out float s);

float iScale = 1.,
    iNote = 0.;

// Global constants
const float pi = acos(-1.);
const vec3 c = vec3(1.0, 0.0, -1.0);
float a = 1.0;

void hash22(in vec2 p, out vec2 d);
void rand(in vec2 x, out float n);
void zextrude(in float z, in float d2d, in float h, out float d);
void stroke(in float d0, in float s, out float d);
void dbox(in vec2 x, in vec2 b, out float d);
void dbox3(in vec3 x, in vec3 b, out float d);
void smoothmin(in float a, in float b, in float k, out float dst);
void dvoronoi(in vec2 x, out float d, out vec2 z, out float pc);
void dquadvoronoi(in vec2 x, in float threshold, in float depth, out float d, out float faco)
{
    d = 1.;
    vec2 y = x, 
        yi;
    float size = .5,
	    fac = 1.;
    faco = 1.;
    for(float i=0.; i<depth; i+=1.)
    {
        float dd, dp;
            vec2 ind;
            dvoronoi(y/size/.5,dd, ind, dp);
        vec2 y0 = y;
		float r;
        rand(ind+fac,r);
        fac *= r*step(r,threshold);
        faco *= r;
        if(fac != 0.)
        {
            
            //dd = mix(dd,length(y)-.5*size,step(r,threshold));
            dd = abs(dd);
            smoothmin(d,dd,.01,d);
        }
        
        size *= .5;
    }
    faco += fac*fac;
}
void analytical_box(in vec3 o, in vec3 dir, in vec3 size, out float d);
void rot3(in vec3 p, out mat3 rot);

// Scene
float mat;
void scene(in vec3 x, out vec2 d)
{
    d = c.xx;
    float dbound;
    dbox3(x,vec3(.3*c.xx, .2),dbound);
    float da, fac;
    dquadvoronoi(x.xy-.1*iTime, .71, 4., da, fac);
    
    float p = pi/4.;
    vec2 cs = vec2(cos(p),sin(p));
    mat2 m = mat2(cs.x,cs.y,-cs.y,cs.x);
    vec2 y = m*x.xy;
    float da9, fac9;
    dquadvoronoi(y-12.-.1*iTime, .41,2., da9, fac9);
    smoothmin(da,da9,.01,da);
    
    float r;
    rand(202.*fac*fac9*c.xx+3., r);
    mat = r;
    zextrude(x.z,da,r*.3,da9);
    smoothmin(d.x,da9,.4, d.x);
    
    stroke(da, .015+6.*.045*clamp(iScale,0.,1.), da);
    float db;
    stroke(da, .011+6.*.033*clamp(iScale,0.,1.), db);
   
    stroke(d.x,.003,d.x);
    dbox3(x,vec3(.33*c.xx, .02),da);
    smoothmin(d.x,da,.2,d.x);
    smoothmin(d.x,db,.05,d.x);
    //d.x = min(d.x, da);
    //d.x = min(d.x, db);
    
//     d.x = max(d.x, dbound);
}

// Normal
void normal(in vec3 x, out vec3 n, in float dx);

// Texture
void colorize(in vec2 x, out vec3 col)
{    
    float phi = .1*iTime;
    
    vec3 white = .4*vec3(0.99,0.29,0.09),
        gray = vec3(0.95,0.25,0.05);
    float size = .1;
    
    
    vec2 y = mod(x,size)-.5*size;
    y = abs(y)-.001;
    float d = min(y.x,y.y);

    y = mod(x,.2*size)-.1*size;
    y = abs(y)-.0002;
    d = min(d, min(y.x,y.y));
    
    col = mix(white, gray, smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d));
	col = mix(col, length(col)/length(c.xxx)*c.xxx, .7);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    scale(iScale);
    
     // Set up coordinates
    a = iResolution.x/iResolution.y;
    vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);
    vec3 col = c.yyy;

    float dhex,
                na,
                nal;
            vec2 ind;
            rand(floor(.33*iTime)*c.xx, na);
            rand(floor(.33*iTime)*c.xx+1., nal);
            na = mix(na,nal,clamp(((.33*iTime-floor(.33*iTime))-.9)/.1,0.,1.));
    uv = mix(uv,.5*uv.yx,na);
    
    // Camera setup
    float pp = .3*iTime;
    vec3 o = c.yyx+.2*c.yzy,
        t = c.yyy,
        dir = normalize(t-o),
        r = normalize(c.xyy),
        u = normalize(cross(r,dir)),
        n,
        x,
        l;
    t += uv.x*r + uv.y*u;
    dir = normalize(t-o);
    vec2 s;
    float d = -(o.z-.2)/dir.z;
    int N = 250,
        i;
    
    // Graph
    //analytical_box(o,dir,vec3(.3*c.xx,.2),d);
    x = o + d * dir;
    
    // Actual Scene
    if(x.z>0.)
    {

        // Raymarching
        for(i=0; i<N; ++i)
        {
            x = o + d * dir;
            scene(x,s);
            if(s.x < 1.e-4) break;
            d += min(1.e-2,s.x);
        }

        // Illumination
        l = normalize(x+c.yxx);
        if(i<N)
        {
            normal(x,n,5.e-4);
            
            mat3 RR;
            rot3(na*1.e3*vec3(1.1,1.5,1.9)+iNote*210.,RR);
            col = mix(mix(.0,.3,clamp(x.z/.3,0.,1.))*(.5+.5*mat)*c.xxx,(1.+.8*mat)*abs(RR*RR*vec3(.7,.5,.26)),step(x.z,.08));
            col = mix(col,(1.+.8*mat)*abs(RR*vec3(.6,.12,.06)),step(.19,x.z));

            col = mix((.5+.5*mat)*col,(1.+.8*mat)*abs(RR*vec3(0.89,0.44,0.23)),(.5+.5*sin(x.z))*step(.19,x.z));
            col = mix(col,vec3(0.25,0.23,0.21),(.5+.5*cos(4.*x.z+mat))*step(.19,x.z));
            
            col = mix(col, clamp(1.9*col,c.yyy,c.xxx), mat*step(.19,x.z));
            
             col = mix(col, 4.*col, smoothstep(0., 1., 1.-abs(dot(n, 3.*c.xyy))));
//             col = mix(col, c.xxx, smoothstep(.63, 1.2, 1.-abs(dot(n, 3.*c.zyy))));
        }
        else
        {
            d = -o.z/dir.z;
            x = o + d * dir;
            n = c.yyx;
            l = vec3(x.xy, .8);
            colorize(x.xy, col);
        }
    }
    else // Floor with grid
    {
        d = -o.z/dir.z;
        x = o + d * dir;
        n = c.yyx;
        l = vec3(x.xy, .8);
        colorize(x.xy, col);
    }
    
    // Colorize
    col = .2*col
        + .9*col*abs(dot(l,n))
        +.4*col*abs(pow(dot(reflect(-l,n),dir),3.));
    
//     col = sqrt(col);
    col = 1.*col * col;
    
    fragColor = clamp(vec4(col,1.0),0.,1.);
}

void main()
{
    mainImage(gl_FragColor, gl_FragCoord.xy);
}
