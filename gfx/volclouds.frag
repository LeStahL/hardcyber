#version 130

uniform float iTime;
uniform vec2 iResolution;

const float pi = acos(-1.);
const vec3 c = vec3(1.,0.,-1.);
float a = 1.0;

out vec4 gl_FragColor;

float nbeats, iScale;

void scale(out float s)
{
    if(iTime >=  0.0  && iTime <  3.4286 )
    {
        s = mod(iTime+.3- 0.0 , 0.4286 )- 0.2143 ;
        s = smoothstep( -0.03571666666666667 ,0.,s)*(1.-smoothstep(0., 0.10715 ,s));
    }
    if(iTime >=  3.4286  && iTime <  16.9497 )
    {
        s = mod(iTime+.3- 3.4286 , 0.4225 )- 0.21125 ;
        s = smoothstep( -0.035208333333333335 ,0.,s)*(1.-smoothstep(0., 0.105625 ,s));
    }
    if(iTime >=  16.9497  && iTime <  30.283 )
    {
        s = mod(iTime+.3- 16.9497 , 0.416675 )- 0.2083375 ;
        s = smoothstep( -0.034722916666666666 ,0.,s)*(1.-smoothstep(0., 0.10416875 ,s));
    }
    if(iTime >=  30.283  && iTime <  41.7899 )
    {
        s = mod(iTime+.3- 30.283 , 0.410975 )- 0.2054875 ;
        s = smoothstep( -0.03424791666666666 ,0.,s)*(1.-smoothstep(0., 0.10274375 ,s));
    }
    if(iTime >=  41.7899  && iTime <  43.3899 )
    {
        s = mod(iTime+.3- 41.7899 , 0.4 )- 0.2 ;
        s = smoothstep( -0.03333333333333333 ,0.,s)*(1.-smoothstep(0., 0.1 ,s));
    }
    if(iTime >=  43.3899  && iTime <  44.9483 )
    {
        s = mod(iTime+.3- 43.3899 , 0.3896 )- 0.1948 ;
        s = smoothstep( -0.032466666666666665 ,0.,s)*(1.-smoothstep(0., 0.0974 ,s));
    }
    if(iTime >=  44.9483  && iTime <  157.4483 )
    {
        s = mod(iTime+.3- 44.9483 , 0.374975 )- 0.1874875 ;
        s = smoothstep( -0.031247916666666667 ,0.,s)*(1.-smoothstep(0., 0.09374375 ,s));
    }
    if(iTime >=  157.4483  && iTime <  169.6002 )
    {
        s = mod(iTime+.3- 157.4483 , 0.379775 )- 0.1898875 ;
        s = smoothstep( -0.031647916666666664 ,0.,s)*(1.-smoothstep(0., 0.09494375 ,s));
    }
    if(iTime >=  169.6002  && iTime <  181.9079 )
    {
        s = mod(iTime+.3- 169.6002 , 0.384625 )- 0.1923125 ;
        s = smoothstep( -0.032052083333333335 ,0.,s)*(1.-smoothstep(0., 0.09615625 ,s));
    }
    if(iTime >=  181.9079  && iTime <  194.3754 )
    {
        s = mod(iTime+.3- 181.9079 , 0.3896 )- 0.1948 ;
        s = smoothstep( -0.032466666666666665 ,0.,s)*(1.-smoothstep(0., 0.0974 ,s));
    }
    if(iTime >=  194.3754  && iTime <  222.7965 )
    {
        s = mod(iTime+.3- 194.3754 , 0.39475 )- 0.197375 ;
        s = smoothstep( -0.03289583333333333 ,0.,s)*(1.-smoothstep(0., 0.0986875 ,s));
    }
}

// Creative Commons Attribution-ShareAlike 4.0 International Public License
// Created by David Hoskins.
// See https://www.shadertoy.com/view/4djSRW
void hash13(in vec3 p3, out float d)
{
	p3  = fract(p3 * .1031);
    p3 += dot(p3, p3.yzx + 33.33);
    d = fract((p3.x + p3.y) * p3.z);
}

// Arbitrary-frequency 2D noise
void lfnoise3(in vec3 t, out float num)
{
    t -= vec3(11.,13.,5.);
    vec3 i = floor(t);
    t = fract(t);
    //t = ((6.*t-15.)*t+10.)*t*t*t;  // TODO: add this for slower perlin noise
    t = smoothstep(c.yyy, c.xxx, t); // TODO: add this for faster value noise
    vec2 v1, v2, v3, v4;
    hash13(i, v1.x);
    hash13(i+c.xyy, v1.y);
    hash13(i+c.yxy, v2.x);
    hash13(i+c.xxy, v2.y);
    hash13(i+c.yyx, v3.x);
    hash13(i+c.xyx, v3.y);
    hash13(i+c.yxx, v4.x);
    hash13(i+c.xxx, v4.y);
    v1 = c.zz+2.*mix(v1, v2, t.y);
    v3 = c.zz+2.*mix(v3, v4, t.y);
    v2.x = mix(v1.x, v1.y, t.x);
    v2.y = mix(v3.x, v3.y, t.x);
    num = mix(v2.x, v2.y, t.z);
}

void mfnoise3(in vec3 x, in float d, in float b, in float e, out float n)
{
    n = 0.;
    float a = 1., nf = 0., buf;
    for(float f = d; f<b; f *= 2.)
    {
        lfnoise3(f*x-1.e3*vec3(11.,13.,5.), buf);
        n += a*buf;
        a *= e;
        nf += 1.;
    }
    n *= (1.-e)/(1.-pow(e, nf));
}

// Stroke
void stroke(in float d0, in float s, out float d)
{
    d = abs(d0)-s;
}

void rot3(in vec3 p, out mat3 rot)
{
    rot = mat3(c.xyyy, cos(p.x), sin(p.x), 0., -sin(p.x), cos(p.x))
        *mat3(cos(p.y), 0., -sin(p.y), c.yxy, sin(p.y), 0., cos(p.y))
        *mat3(cos(p.z), -sin(p.z), 0., sin(p.z), cos(p.z), c.yyyx);
}

mat3 R;
vec3 ind;
void scene(in vec3 x, out vec2 sdf)
{
    x = R * x;
    
    float n;
    mfnoise3(x-.1*iTime*c.yyx,10.,400.,.25,n);
    n = .5+.5*n;
    sdf = vec2(-n, 2.);
}

void normal(in vec3 x, out vec3 n, in float dx)
{
    vec2 s, na;
    
    scene(x,s);
    scene(x+dx*c.xyy, na);
    n.x = na.x;
    scene(x+dx*c.yxy, na);
    n.y = na.x;
    scene(x+dx*c.yyx, na);
    n.z = na.x;
    n = normalize(n-s.x);
}

void palette2(in float scale, out vec3 col)
{
    const int N = 5;
    const vec3 colors[N] = vec3[N](
            vec3(1.00,0.00,0.47),
            vec3(0.80,0.00,0.47),
            vec3(0.60,0.00,0.47),
            vec3(0.40,0.00,0.47),
            vec3(0.20,0.00,0.47)
    );
	float index = floor(scale*float(N)), 
        remainder = scale*float(N)-index;
    col = mix(colors[int(index)],colors[int(index)+1], remainder);
}

void palette3(in float scale, out vec3 col)
{
    const int N = 5;
	const vec3 colors[N] = vec3[N](
       	vec3(0.68,1.00,0.00),
        vec3(0.45,0.84,0.00),
        vec3(0.01,0.54,0.00),
        vec3(0.00,0.82,0.50),
        vec3(0.00,1.00,0.51)
    );
	float index = floor(scale*float(N)), 
        remainder = scale*float(N)-index;
    col = mix(colors[int(index)],colors[int(index)+1], remainder);
}

void palette1(in float scale, out vec3 col)
{
    const int N = 5;

    vec3 colors[N];
    colors = vec3[N](
       	vec3(0.00,0.33,0.42),
        vec3(0.46,0.69,0.53),
        vec3(0.94,0.91,0.59),
        vec3(1.00,0.62,0.52),
        c.yyy);

	float index = floor(scale*float(N)), 
        remainder = scale*float(N)-index;
    col = mix(colors[int(index)],colors[int(index)+1], remainder);
}

void main()
{
    rot3(mix(mix(mix(0.,pi/2.,clamp((iTime/5.),0.,1.)),0.,clamp((iTime-5.)/5.,0.,1.)), pi/2.,clamp((iTime-10.)/5.,0.,1.))*c.xyx, R);
    
    scale(iScale);
    
    float a = iResolution.x/iResolution.y;
    vec2 uv = gl_FragCoord.xy/iResolution.yy-0.5*vec2(a, 1.0);
    vec3 col = c.yyy;
    
    float d = 0.;
    vec2 s;
    vec3 o, t, dir, x, n;
    
	o = c.yyx;
    t = c.yyy;
    int N = 40,
        i;
    dir = normalize(vec3(uv,-1.));//normalize(t-o);
    
    for(i = 0; i<N; ++i)
    {
        d += .5/float(N);
        x = o + d * dir;
        scene(x,s);
        normal(x,n,5.e-4);
        vec3 l = normalize(x+.1*n);
        vec3 c1;
        palette1(-s.x, c1);
        if(iTime < 150.)
        {
            vec3 c2;
            palette2(-s.x, c2);
            c1 = mix(c1, c2, smoothstep(5.,6.,iTime));
            palette3(-s.x, c2);
            c1 = mix(c1, c2, smoothstep(10.,11.,iTime));
        }
        c1 = .1*c1
                            + .1*c1 * abs(dot(l,n))
                            + 1.354 * c1 * abs(pow(dot(reflect(-l,n),dir),2.));
    	c1 = mix(c1, 2.*c1, smoothstep(mix(1.,.6,iScale), 1.02, 1.-abs(dot(n, c.xyy))));
        c1 = mix(c1, 2.*c1, smoothstep(mix(1.,.6,iScale), 1.02, abs(dot(n, c.zyy))));
        c1 = clamp(c1, 0., 1.);
        col = mix(col, c1, d*d);
    }

    col *= col;
    gl_FragColor = vec4(clamp(col,0.,1.),1.0);
}
