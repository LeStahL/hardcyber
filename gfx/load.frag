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

uniform float iTime, iProgress;
uniform vec2 iResolution;

// Global constants
const float pi = acos(-1.);
const vec3 c = vec3(1.0, 0.0, -1.0);
float a = 1.0;

float sm(float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d)
{
    vec2 da = p2-p1;
    d = length(x-mix(p1, p2, clamp(dot(x-p1, da)/dot(da,da),0.,1.)));
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    a = iResolution.x/iResolution.y;
    vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);
    vec3 col = .1*c.xxx;
    col = mix(col, .3*c.xxx, sm(-min(abs(mod(uv.x,.01)-.005)-.003,abs(mod(uv.y,.01)-.005)-.003)));
    
    float d, d0;
    dlinesegment(uv, -.25*a*c.xy, .25*a*c.xy, d);
 	d = abs(d)-.05;
    col = mix(col, .3*c.xxx, sm(d));
    d = abs(d)-.001;
    col = mix(col, c.xxx, sm(d));
    dlinesegment(uv, -.25*a*c.xy, -.25*a*c.xy+.5*a*iProgress*c.xy, d);
    d = abs(d)-.045;
    col = mix(col, mix(vec3(0.41,0.00,0.11), vec3(1.00,0.36,0.51), clamp((uv.y+.05)/.1,0.,1.)), sm(d));
    
    col += col;
    col *= col;
    
    col = .5*c.xxx/sqrt(3.)*length(col);
    
    fragColor = vec4(clamp(col,0.,1.),1.0);
}

void main()
{
    mainImage(gl_FragColor, gl_FragCoord.xy);
}
