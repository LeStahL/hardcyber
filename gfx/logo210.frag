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

float nbeats, iScale;

void dbox3(in vec3 x, in vec3 b, out float d);
void rot3(in vec3 p, out mat3 rot);
void stroke(in float d0, in float s, out float d);
void add(in vec2 sda, in vec2 sdb, out vec2 sdf);
void dbox210(in vec3 x, in float size, out vec2 sdf);

mat3 R;
void scene(in vec3 x, out vec2 sdf)
{
    sdf = c.xy;
    
    float d, da;
    
    rot3(vec3(-pi/2.,0.,pi/2.), R);
    x = R * x;
    
    vec2 sda = c.xy;
    
	dbox210(x+.1*c.xyy, .5, sdf);
	rot3(vec3(pi/2.,0.,pi/2.), R);
    x = R * x;
    //add(sdf,sda,sdf);
    
    dbox210(x,5.,sda);
    add(sdf,sda,sdf);
    
    rot3(vec3(pi/2.,-pi/2.,pi/2.), R);
    x = R * x;
    
    dbox210(x-2.*c.yxy,50.,sda);
    add(sdf,sda,sdf);
    
    stroke(sdf.x,.001, sdf.x);
    
    dbox3(x, 100.*c.xxx, sda.x);
    sda.y = 2.;
    
    add(sdf, sda*c.zx, sdf);
}

void normal(in vec3 x, out vec3 n, in float dx);

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    float a = iResolution.x/iResolution.y;
    vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);
    
    vec3 col = c.xxx;
    
    float d = 0.;
    vec2 s;
    vec3 o, t, dir, x, n;
    
    mat3 Ra, Rb;
    rot3(mix(c.yyy,vec3(-5.7884463,2.4242211,0.3463173),clamp((iTime-6.)/1.5,0.,1.)), Ra);
    rot3(mix(c.yyy,vec3(-2.*pi+5.7884463,-2.4242211,-0.3463173)+pi*c.xyy,clamp((iTime-10.),0.,1.)), Rb);
    
    
    o = Ra * mix(mix(mix(c.yyy-.005*c.yyx,c.yyx,clamp(iTime/2.,0.,1.)),10.*c.yyx,clamp((iTime-2.)/2.,0.,1.)), 100.*c.yyx, clamp((iTime-4.)/2.,0.,1.));
	t = c.yyy;
    int N = 650,
        i;
    dir = Rb * Ra *normalize(vec3(uv,-1.));//normalize(t-o);
//     dir = mix(dir, normalize(vec3(uv,1.)), clamp(iTime-10.,0.,1.));
    
    for(i = 0; i<N; ++i)
    {
        x = o + d * dir;
        scene(x,s);
        if(s.x < 1.e-4)break;
        d += s.x;
    }
        
    if(s.x < 1.e-4)
    {
        normal(x,n, 5.e-4);
        vec3 l = normalize(x+.1*n);
        
        if(s.y == 1.)
        {
            // cube color
            col = vec3(0.27,0.36,0.48);
            col = .3*col
                + .4*col * abs(dot(l,n))
                + .6 * col * abs(pow(dot(reflect(-l,n),dir),3.));
        }
        else if(s.y == 2.)
        {
            col = .7*c.xxx;
            col = .5*col
                + .4*col * abs(dot(l,n))
                + .8 * col * abs(pow(dot(reflect(-l,n),dir),3.));
            
            vec3 c1 = c.yyy;
            
            o = x;
            dir = reflect(dir,n);
            d = 1.e-1;
            
            N = 150;
            
            for(i = 0; i<N; ++i)
            {
                x = o + d * dir;
                scene(x,s);
                if(s.x < 1.e-4)break;
                d += s.x;
            }
                
            if(s.x < 1.e-4)
            {
                normal(x,n, 5.e-4);
                vec3 l = normalize(x+.1*n);

                if(s.y == 1.)
                {
                    c1 = vec3(0.27,0.36,0.48);
                    c1 = .3*c1
                        + .4*c1 * abs(dot(l,n))
                        + .6 * c1 * abs(pow(dot(reflect(-l,n),dir),3.));
                }
                else if(s.y == 2.)
                {
                    c1 = .7*c.xxx;
                    c1 = .5*c1
                        + .4*c1 * abs(dot(l,n))
                        + .8 * c1 * abs(pow(dot(reflect(-l,n),dir),3.));
                }
                c1 = clamp(c1, 0., 1.);
                
                col = mix(col, c1, .2);
            }
            
            col = clamp(col, 0., 1.);
        }
        
    }
    col = mix(col,c.xxx,smoothstep(0.,1.,iTime-11.));
    
    col = mix(vec3(0.18,0.24,0.31), col, clamp(iTime,0.,1.));
    
    fragColor = vec4(clamp(col,0.,1.),1.0);
}


void main()
{
    mainImage(gl_FragColor, gl_FragCoord.xy);
}
