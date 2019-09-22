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

uniform float iFSAA;
uniform vec2 iResolution;
uniform sampler2D iChannel0;
uniform float iTime;

out vec4 gl_FragColor;

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);
float a = 1.0;

float lscale, rscale;
float size;

float nbeats;
float iScale;


void rand(in vec2 x, out float n);
void lfnoise(in vec2 t, out float n);
void stroke(in float d0, in float s, out float d);
void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);
void hash22(in vec2 x, out vec2 y);
float sm(float d)
{
    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);
}

float dot2( in vec3 v ) { return dot(v,v); }

// Adapted from https://www.shadertoy.com/view/4sXXRN
void dtriangle3(in vec3 p,  in vec3 v1, in vec3 v2, in vec3 v3, out float dst)
{
    vec3 v21 = v2 - v1; vec3 p1 = p - v1;
    vec3 v32 = v3 - v2; vec3 p2 = p - v2;
    vec3 v13 = v1 - v3; vec3 p3 = p - v3;
    vec3 nor = cross( v21, v13 );

    dst = sqrt( (sign(dot(cross(v21,nor),p1)) + 
                  sign(dot(cross(v32,nor),p2)) + 
                  sign(dot(cross(v13,nor),p3))<2.0) 
                  ?
                  min( min( 
                  dot2(v21*clamp(dot(v21,p1)/dot2(v21),0.0,1.0)-p1), 
                  dot2(v32*clamp(dot(v32,p2)/dot2(v32),0.0,1.0)-p2) ), 
                  dot2(v13*clamp(dot(v13,p3)/dot2(v13),0.0,1.0)-p3) )
                  :
                  dot(nor,p1)*dot(nor,p1)/dot2(nor) );
}

void rot3(in vec3 p, out mat3 rot);
void dbox3(in vec3 x, in vec3 b, out float d);
void add(in vec2 sda, in vec2 sdb, out vec2 sdf);
mat3 R;
void scene(in vec3 x, out vec2 sdf)
{
    float d;
    
	// Big red box    
    dbox3(x, .2*c.xxx, sdf.x);
    sdf.y = 1.;
    
    // Holes
    
    // 2 upper bar
    dbox3(x-.1*c.xyy, vec3(.02,.3,.12), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));
    
    // 2 right bar
    dbox3(x-.05*c.xyy-.1*c.yyx, vec3(.07,.3,.02), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));
    
    // 2 mid bar
    dbox3(x, vec3(.02,.3,.1), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));
    
    // 2 left bar
    dbox3(x+.05*c.xyy+.1*c.yyx, vec3(.07,.3,.02), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));
    
    // 2 dot
    dbox3(x+.1*c.xyy-.1*c.yyx, vec3(.02,.3,.02), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));
    
    // 1 bar
    dbox3(x+.04*c.yyx, vec3(.3,.02,.08), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));
    
    // 1 dot
    dbox3(x-.1*c.yyx, vec3(.3,.02,.02), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));
    
    // 0 big stripes
    vec3 y = vec3(x.x, abs(x.y), x.z);
    dbox3(y-.05*c.yxy, vec3(.1,.03,.3), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));

	// 0 small stripes
    dbox3(y-.1*c.yxy-.06*c.xyy, vec3(.08,.021,.3), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));

    // 0 upper/lower stripes
    vec3 z = vec3(abs(x.x), x.yz);
	dbox3(z-.119*c.xyy, vec3(.021,.08,.3), d);
    sdf.x = max(-d, sdf.x);
    sdf.y = mix(sdf.y, 2., step(d, sdf.x));
}

void scene2(in vec3 x, out vec2 sdf)
{
    float v = 0., vn;
    vec2 vi = c.yy;
    dvoronoi(x.xy/size, v, vi, vn);
    vec3 y = vec3(x.xy-vi*size, x.z);
    vec2 yi = vi*size;
    
    float n = 0.;
    lfnoise(4.*(yi-.5*iTime), n);
    lfnoise(12.*vec2(n,1.)*yi-(.8+.2*n)*c.xy, n);
    n *= iScale;
    //sdf = vec2(length(y-.05*n*c.yyx)-.5*size, 1.);
    sdf = vec2(length(y-.05*n*c.yyx)-mix(.05,1.,length(texture(iChannel0, yi/vec2(a,1.)).rgb)/sqrt(3.))*size, 1.);
}

void normal2(in vec3 x, out vec3 n, in float dx)
{
    vec2 s, na;
    
    scene2(x,s);
    scene2(x+dx*c.xyy, na);
    n.x = na.x;
    scene2(x+dx*c.yxy, na);
    n.y = na.x;
    scene2(x+dx*c.yyx, na);
    n.z = na.x;
    n = normalize(n-s.x);
}

void scene3(in vec3 x, out vec2 sdf)
{
    vec3 y = vec3(mod(x.xy,2.*size)-size, x.z);
    vec2 yi = x.xy-y.xy;
    float ss = mix(.0,.05,size/.01);
    
    vec2 p0 = .8*size*c.xx,
        p1 = .8*size*c.zx,
        p2 = .8*size*c.xz;
    
    vec2 ind;
    
    float y0, y1, y2;
    lfnoise(4.e1*(yi+p0-.5e-4*iTime), y0);
    lfnoise(12.e1*vec2(y0,1.)*(yi+p0)-1.e-4*(.8+.2*y0)*iTime*c.xy, y0);
    lfnoise(4.e1*(yi+p1-.5e-4*iTime), y1);
    lfnoise(12.e1*vec2(y1,1.)*(yi+p1)-1.e-4*(.8+.2*y1)*iTime*c.xy, y1);
    lfnoise(4.e1*(yi+p2-.5e-4*iTime), y2);
    lfnoise(12.e1*vec2(y2,1.)*(yi+p2)-1.e-4*(.8+.2*y2)*iTime*c.xy, y2);
    y0 *= ss;
    y1 *= ss;
    y2 *= ss;
    
    dtriangle3(y, vec3(p0,y0), vec3(p1,y1), vec3(p2,y2), sdf.x);
    
    float d;
    vec2 p3 = .8*size*c.zz,
        p4 = .8*size*c.xz,
        p5 = .8*size*c.zx;
    
    float y3, y4, y5;
    lfnoise(4.e1*(yi+p3-.5e-4*iTime), y3);
    lfnoise(12.e1*vec2(y3,1.)*(yi+p3)-1.e-4*(.8+.2*y3)*iTime*c.xy, y3);
    lfnoise(4.e1*(yi+p4-.5e-4*iTime), y4);
    lfnoise(12.e1*vec2(y4,1.)*(yi+p4)-1.e-4*(.8+.2*y4)*iTime*c.xy, y4);
    lfnoise(4.e1*(yi+p5-.5e-4*iTime), y5);
    lfnoise(12.e1*vec2(y5,1.)*(yi+p5)-1.e-4*(.8+.2*y5)*iTime*c.xy, y5);
    y3 *= ss;
    y4 *= ss;
    y5 *= ss;
    
    dtriangle3(y, vec3(p3,y3), vec3(p4,y4), vec3(p5,y5), d);
    sdf.x = min(sdf.x, d);

    stroke(sdf.x, .1*size, sdf.x);
    sdf.y = 1.;
}

void normal3(in vec3 x, out vec3 n, in float dx)
{
    vec2 s, na;
    
    scene3(x,s);
    scene3(x+dx*c.xyy, na);
    n.x = na.x;
    scene3(x+dx*c.yxy, na);
    n.y = na.x;
    scene3(x+dx*c.yyx, na);
    n.z = na.x;
    n = normalize(n-s.x);
}

void normal(in vec3 x, out vec3 n, in float dx);
void mainImage( out vec4 fragColor, in vec2 fragCoord_ )
{
    vec2 fragCoord = fragCoord_;
    
    if(iTime < 159.5456 && iTime > 155.9092)
    {
        vec2 n;
        lfnoise(22.*fragCoord/iResolution-3.*iTime, n.x);
        lfnoise(22.*fragCoord/iResolution-3.*iTime-1337., n.y);
        fragCoord += 22.*n;
    }
    else if(iTime < 165. && iTime > 163.182)
    {
        vec2 n;
        lfnoise(22.*fragCoord/iResolution-3.*iTime, n.x);
        lfnoise(22.*fragCoord/iResolution-3.*iTime-1337., n.y);
        fragCoord += 22.*n;
    }
    
//     vec3 as = texture(iChannel0, fragCoord/iResolution).rgb;
//     vec2 nb;
//     lfnoise((as.xy+as.yz+as.xz), nb.x);
//     lfnoise((as.xy+as.yz+as.xz), nb.y);
//     fragCoord += 22.*(.1*as.r + .2*as.g + .3*as.b);
    
    float a = iResolution.x/iResolution.y;
    vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);
    
    nbeats = mod(iTime, 60./29.);
    iScale = nbeats-30./29.;
    iScale = smoothstep(-5./29., 0., iScale)*(1.-smoothstep(0., 15./29., iScale));
    
    vec3 col = texture(iChannel0, fragCoord/iResolution).rgb;
    float delta = 0.;
//     vec2 n = c.yy;
    
    // Box
    rot3(vec3(-2.*pi/8.,2.*pi/8.,2.*pi/4.)-iTime*vec3(1.1,1.3,1.5), R);
    
    float d;
    vec2 s;
    vec3 o, r, u, t, ssize, dir, x, n;
    vec2 uv2 = 10.*(uv-vec2(-.45*a,.45));
    o = R * c.yyx;
	r = c.xyy; 
	u = c.yxy;
	t = c.yyy; 
    int N = 250,
        i;
    t = uv2.x * r + uv2.y * u;
    t = R * t;
    dir = normalize(t-o);

    ssize = .2*c.xxx;

	vec3 tlo = min((ssize-o)/dir,(-ssize-o)/dir); // Select 3 visible planes
    vec2 abxlo = abs(o.yz + tlo.x*dir.yz),
        abylo = abs(o.xz + tlo.y*dir.xz),
        abzlo = abs(o.xy + tlo.z*dir.xy);

    vec4 dn = 100.*c.xyyy;

    dn = mix(dn, vec4(tlo.x,c.xyy), float(all(lessThan(abxlo,ssize.yz)))*step(tlo.x,dn.x));
    dn = mix(dn, vec4(tlo.y,c.yxy), float(all(lessThan(abylo,ssize.xz)))*step(tlo.y,dn.x));
    dn = mix(dn, vec4(tlo.z,c.yyx), float(all(lessThan(abzlo,ssize.xy)))*step(tlo.z,dn.x));
    
    uv = (fragCoord)/iResolution.xy*vec2(a,1.);
    
    d = dn.r;
    
    float nan;
    lfnoise(iTime*c.xx, nan);
    nan += .5;
    if(nan > 0.) d = 3.;
    
    if(d<=2.)
    {
        x = o + d * dir;
        scene(x,s);
        
        if(s.x > 1.e-4)
        {
            for(i = 0; i<N; ++i)
            {
                x = o + d * dir;
                scene(x,s);
                if(s.x < 1.e-4)break;
                d += s.x;
            }
        }
        
        if(i<N)
        {
            normal(x,n, 5.e-4);
            
            if(s.y == 1.)
            {
                vec3 l = normalize(x+c.zzx*vec3(1.3,.9,1.2));
                col = vec3(0.81,0.15,0.18);
                col = .3*col
                    + .4*col * abs(dot(l,n))
                    + .6 * col * abs(pow(dot(reflect(-l,n),dir),2.));
            }
            else if(s.y == 2.)
            {
                vec3 l = normalize(x+c.zzx*vec3(1.3,.9,1.2));
                col = .7*c.xxx;
                col = .5*col
                    + .4*col * abs(dot(l,n))
                    + .8 * col * abs(pow(dot(reflect(-l,n),dir),2.));
            }
        }
        
        if(iTime < 0.) col = texture(iChannel0, fragCoord/iResolution).rgb;
    }
    else
    {
        iScale = nbeats-30./29.;
        iScale = smoothstep(-5./29., 0., iScale)*(1.-smoothstep(0./29., 35./29., iScale));
//         lscale = iScale;
        lscale = smoothstep(0.,.5,clamp((iTime-10.),0.,1.))*(1.-smoothstep(0.,.5,clamp((iTime-18.),0.,1.)));
//         lscale += smoothstep(0.,.5,clamp((iTime-10.),0.,1.))*(1.-smoothstep(0.,.5,clamp((iTime-18.),0.,1.)));
        rscale = smoothstep(167.,167.5,iTime)-smoothstep(172.,172.5,iTime);
        
//         rscale = iScale;
//         rscale = 0.;
        size = mix(.005, .01, rscale);
        size = mix(0., size, max(rscale, lscale));
     
        if(lscale > 0.)
        {
            col = c.yyy;
            
            o = c.yyx+.5*vec3(cos(iTime), sin(iTime),0.);
            r = c.xyy;
            u = c.yxy;
            t = c.yyy;
            dir = c.yyy;
            n = c.yyy;
            x = c.yyy;
            N = 200;
            t = uv.x * r + uv.y * u;
            dir = normalize(t-o);

            d = -(o.z-.05-.5*size)/dir.z;
            
            for(i = 0; i<N; ++i)
            {
                x = o + d * dir;
                scene2(x,s);
                if(s.x < 1.e-4)break;
                
                if(x.z<-.05-.5*size)
                {
                    col = c.yyy;
                    i = N;
                    break;
                }
                d += min(s.x,1.e-3);
                //d += s.x;
            }
            
            if(i < N)
            {
                normal2(x,n, 5.e-4);
                vec3 l = normalize(x+.5*n);
            
                if(s.y == 1.)
                {
                    float v, vn;
                    vec2 vi;
                    dvoronoi(x.xy/size, v, vi, vn);
                    vec3 y = vec3(x.xy-vi*size, x.z);
                    vec2 yi = vi*size;
                    
                    float bound = sqrt(iFSAA)-1.;

                    for(float i = -.5*bound; i<=.5*bound; i+=1.)
                        for(float j=-.5*bound; j<=.5*bound; j+=1.)
                        {
                            col += texture(iChannel0, yi/vec2(a,1.)+vec2(i,j)*3./max(bound, 1.)/iResolution.xy).xyz;
                        }
                    col /= iFSAA;   
                    
                    col = .4*col
                        + .9*col * abs(dot(l,n))
                        + .6*col * pow(abs(dot(reflect(-l,n),dir)),3.);
                }
            }
            else col = c.yyy;
        }
        else if(rscale > 0.)
        {
            col = c.yyy;
            
            o = c.yyx+.5*vec3(-1., -1.,0.);
            r = c.xyy;
            u = c.yxy;
            t = c.yyy;
            dir = c.yyy;
            n = c.yyy;
            x = c.yyy;
            N = 300;
            t = uv.x * r + uv.y * u;
            dir = normalize(t-o);

            d = -(o.z-.05-.5*size)/dir.z;
            
            for(i = 0; i<N; ++i)
            {
                x = o + d * dir;
                scene3(x,s);
                if(s.x < 1.e-4)break;
                
                if(x.z<-.05-.5*size)
                {
                    col = c.yyy;
                    i = N;
                    break;
                }
                d += min(s.x,1.e-3);
                //d += s.x;
            }
            
            if(i < N)
            {
                normal3(x,n, 5.e-4);
                vec3 l = normalize(x+.5*n);
            
                if(s.y == 1.)
                {
                    vec3 y = vec3(mod(x.xy,size)-.5*size, x.z);
                    vec2 yi = x.xy-y.xy;
                    
                    col = texture(iChannel0, yi/vec2(a,1.)).rgb;
                    
//                     col = .7*c.xxy;
                    
                    col = .4*col
                        + .9*col * abs(dot(l,n))
                        + .6*col * pow(abs(dot(reflect(-l,n),dir)),3.);
                    
                }
            }
            else col = c.yyy;
        }
    }
    
    // Scan lines
    col += vec3(0., 0.05, 0.1)*sin(uv.y*1050.+ 5.*iTime);
    
    fragColor = vec4(clamp(col,0.,1.),1.0);
}

void main()
{
    mainImage(gl_FragColor, gl_FragCoord.xy);
}
