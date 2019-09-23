//Generated with Symbolize (c) 2019 Alexander Kraus <nr4@z10.info>.
#ifndef SYMBOLIZE_H
#define SYMBOLIZE_H

extern float progress;int rand_handle, hash11_handle, hash12_handle, hash21_handle, hash22_handle, hash31_handle, stroke_handle, lfnoise_handle, dvoronoi_handle, dbox_handle, dlinesegment_handle, smoothmin_handle, add_handle, normal_handle, dbox3_handle, rot3_handle, dbox210_handle, dspline2_handle, zextrude_handle, mfnoise_handle, rshort_handle, rfloat_handle, dcircle_handle, drhomboid_handle, dcirclesegment_handle, dglyph_handle, dstring_handle, dfloat_handle, dint_handle, dtime_handle, window_handle, progressbar_handle;
const int nsymbols = 32;
const char *rand_source = "#version 130\n\n"
"void rand(in vec2 x, out float n)\n"
"{\n"
"    x += 400.;\n"
"    n = fract(sin(dot(sign(x)*abs(x) ,vec2(12.9898,78.233)))*43758.5453);\n"
"}\n"
"\0";
const char *hash11_source = "// Creative Commons Attribution-ShareAlike 4.0 International Public License\n"
"// Created by David Hoskins.\n"
"// See https://www.shadertoy.com/view/4djSRW\n"
"void hash11(in float p, out float d)\n"
"{\n"
"    p = fract(p * .1031);\n"
"    p *= p + 33.33;\n"
"    p *= p + p;\n"
"    d = fract(p);\n"
"}\n"
"\0";
const char *hash12_source = "// Creative Commons Attribution-ShareAlike 4.0 International Public License\n"
"// Created by David Hoskins.\n"
"// See https://www.shadertoy.com/view/4djSRW\n"
"void hash12(in vec2 p, out float d)\n"
"{\n"
"	vec3 p3  = fract(vec3(p.xyx) * .1031);\n"
"    p3 += dot(p3, p3.yzx + 33.33);\n"
"    d = fract((p3.x + p3.y) * p3.z);\n"
"}\n"
"\0";
const char *hash21_source = "// Creative Commons Attribution-ShareAlike 4.0 International Public License\n"
"// Created by David Hoskins.\n"
"// See https://www.shadertoy.com/view/4djSRW\n"
"void hash21(in float p, out vec2 d)\n"
"{\n"
"	vec3 p3 = fract(vec3(p) * vec3(.1031, .1030, .0973));\n"
"	p3 += dot(p3, p3.yzx + 33.33);\n"
"    d = fract((p3.xx+p3.yz)*p3.zy);\n"
"}\n"
"\0";
const char *hash22_source = "// Creative Commons Attribution-ShareAlike 4.0 International Public License\n"
"// Created by David Hoskins.\n"
"// See https://www.shadertoy.com/view/4djSRW\n"
"void hash22(in vec2 p, out vec2 d)\n"
"{\n"
"	vec3 p3 = fract(vec3(p.xyx) * vec3(.1031, .1030, .0973));\n"
"    p3 += dot(p3, p3.yzx+33.33);\n"
"    d = fract((p3.xx+p3.yz)*p3.zy);\n"
"}\n"
"\0";
const char *hash31_source = "// Creative Commons Attribution-ShareAlike 4.0 International Public License\n"
"// Created by David Hoskins.\n"
"// See https://www.shadertoy.com/view/4djSRW\n"
"void hash31(in float p, out vec3 d)\n"
"{\n"
"   vec3 p3 = fract(vec3(p) * vec3(.1031, .1030, .0973));\n"
"   p3 += dot(p3, p3.yzx+33.33);\n"
"   d = fract((p3.xxy+p3.yzz)*p3.zyx); \n"
"}\n"
"\0";
const char *stroke_source = "// Stroke\n"
"void stroke(in float d0, in float s, out float d)\n"
"{\n"
"    d = abs(d0)-s;\n"
"}\n"
"\0";
const char *lfnoise_source = "#version 130\n\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"void rand(in vec2 x, out float d);\n"
"void lfnoise(in vec2 t, out float n)\n"
"{\n"
"    vec2 i = floor(t);\n"
"    t = fract(t);\n"
"    t = smoothstep(c.yy, c.xx, t);\n"
"    vec2 v1, v2;\n"
"    rand(i, v1.x);\n"
"    rand(i+c.xy, v1.y);\n"
"    rand(i+c.yx, v2.x);\n"
"    rand(i+c.xx, v2.y);\n"
"    v1 = c.zz+2.*mix(v1, v2, t.y);\n"
"    n = mix(v1.x, v1.y, t.x);\n"
"}\n"
"\0";
const char *dvoronoi_source = "#version 130\n\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"void hash22(in vec2 a, out vec2 b);\n"
"void dist(in vec2 a, in vec2 b, out float d)\n"
"{\n"
"    d = length(b-a);\n"
"}\n"
"\n"
"void nearest_controlpoint(in vec2 x, out vec2 p)\n"
"{\n"
"    float dmin = 1.e5, \n"
"        d;\n"
"    vec2 dp,\n"
"        y = floor(x);\n"
"    \n"
"    float i = 0.;\n"
"    for(float i = -1.; i <= 1.; i += 1.)\n"
"        for(float j = -1.; j <= 1.; j += 1.)\n"
"        {\n"
"            hash22(y+vec2(i,j), dp);\n"
"            dp += y+vec2(i,j);\n"
"            dist(x, dp, d);\n"
"            if(d<dmin)\n"
"            {\n"
"                dmin = d;\n"
"                p = dp;\n"
"            }\n"
"        }\n"
"}\n"
"\n"
"void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance)\n"
"{\n"
"    d = 1.e4;\n"
"    vec2 y,\n"
"        dp;\n"
"    \n"
"    nearest_controlpoint(x, p);\n"
"    y = floor(p);\n"
"    \n"
"    control_distance = 1.e4;\n"
"    \n"
"    for(float i = -2.; i <= 2.; i += 1.)\n"
"        for(float j = -2.; j <= 2.; j += 1.)\n"
"        {\n"
"            if(i==0. && j==0.) continue;\n"
"            hash22(y+vec2(i,j), dp);\n"
"            dp += y+vec2(i,j);\n"
"            vec2 o = p - dp;\n"
"            float l = length(o);\n"
"            d = min(d,abs(.5*l-dot(x-dp,o)/l));\n"
"            control_distance = min(control_distance,.5*l);\n"
"        }\n"
"}\n"
"\0";
const char *dbox_source = "#version 130\n\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"void dbox(in vec2 x, in vec2 b, out float d)\n"
"{\n"
"    vec2 da = abs(x)-b;\n"
"    d = length(max(da,c.yy)) + min(max(da.x,da.y),0.0);\n"
"}\n"
"\0";
const char *dlinesegment_source = "#version 130\n\n"
"\n"
"void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d)\n"
"{\n"
"    vec2 da = p2-p1;\n"
"    d = length(x-mix(p1, p2, clamp(dot(x-p1, da)/dot(da,da),0.,1.)));\n"
"}\n"
"\0";
const char *smoothmin_source = "// iq's smooth minimum\n"
"void smoothmin(in float a, in float b, in float k, out float dst)\n"
"{\n"
"    float h = max( k-abs(a-b), 0.0 )/k;\n"
"    dst = min( a, b ) - h*h*h*k*(1.0/6.0);\n"
"}\n"
"\0";
const char *add_source = "void add(in vec2 sda, in vec2 sdb, out vec2 sdf)\n"
"{\n"
"    sdf = (sda.x<sdb.x)?sda:sdb;\n"
"}\n"
"\0";
const char *normal_source = "const vec3 c = vec3(1.0, 0.0, -1.0);\n"
"void scene(in vec3 x, out vec2 s);\n"
"void normal(in vec3 x, out vec3 n, in float dx)\n"
"{\n"
"    vec2 s, na;\n"
"    \n"
"    scene(x,s);\n"
"    scene(x+dx*c.xyy, na);\n"
"    n.x = na.x;\n"
"    scene(x+dx*c.yxy, na);\n"
"    n.y = na.x;\n"
"    scene(x+dx*c.yyx, na);\n"
"    n.z = na.x;\n"
"    n = normalize(n-s.x);\n"
"}\n"
"\0";
const char *dbox3_source = "#version 130\n\n"
"void dbox3(in vec3 x, in vec3 b, out float d)\n"
"{\n"
"  vec3 da = abs(x) - b;\n"
"  d = length(max(da,0.0))\n"
"         + min(max(da.x,max(da.y,da.z)),0.0);\n"
"}\n"
"\0";
const char *rot3_source = "const vec3 c = vec3(1.,0.,-1.);\n"
"void rot3(in vec3 p, out mat3 rot)\n"
"{\n"
"    rot = mat3(c.xyyy, cos(p.x), sin(p.x), 0., -sin(p.x), cos(p.x))\n"
"        *mat3(cos(p.y), 0., -sin(p.y), c.yxy, sin(p.y), 0., cos(p.y))\n"
"        *mat3(cos(p.z), -sin(p.z), 0., sin(p.z), cos(p.z), c.yyyx);\n"
"}\n"
"\0";
const char *dbox210_source = "#version 130\n\n"
"\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"void dbox3(in vec3 x, in vec3 b, out float d);\n"
"\n"
"void dbox210(in vec3 x, in float size, out vec2 sdf)\n"
"{\n"
"    x /= size;\n"
"    \n"
"    float d = 1.;\n"
"    \n"
"    // Big red box    \n"
"    dbox3(x, .2*c.xxx, sdf.x);\n"
"    sdf.y = 1.;\n"
"    \n"
"    // Holes\n"
"    \n"
"    // 2 upper bar\n"
"    dbox3(x-.1*c.xyy, vec3(.02,.3,.12), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 2 right bar\n"
"    dbox3(x-.05*c.xyy-.1*c.yyx, vec3(.07,.3,.02), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 2 mid bar\n"
"    dbox3(x, vec3(.02,.3,.1), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 2 left bar\n"
"    dbox3(x+.05*c.xyy+.1*c.yyx, vec3(.07,.3,.02), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 2 dot\n"
"    dbox3(x+.1*c.xyy-.1*c.yyx, vec3(.02,.3,.02), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 1 bar\n"
"    dbox3(x+.04*c.yyx, vec3(.3,.02,.08), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 1 dot\n"
"    dbox3(x-.1*c.yyx, vec3(.3,.02,.02), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 0 big stripes\n"
"    vec3 y = vec3(x.x, abs(x.y), x.z);\n"
"    dbox3(y-.05*c.yxy, vec3(.1,.03,.3), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"\n"
"	// 0 small stripes\n"
"    dbox3(y-.1*c.yxy-.06*c.xyy, vec3(.08,.021,.3), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"\n"
"    // 0 upper/lower stripes\n"
"    vec3 z = vec3(abs(x.x), x.yz);\n"
"	dbox3(z-.119*c.xyy, vec3(.021,.08,.3), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    sdf.x *= size;\n"
"}\n"
"\0";
const char *dspline2_source = "#version 130\n\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"const float pi = acos(-1.);\n"
"\n"
"//distance to spline with parameter t\n"
"float dist2(vec2 p0,vec2 p1,vec2 p2,vec2 x,float t)\n"
"{\n"
"    t = clamp(t, 0., 1.);\n"
"    return length(x-pow(1.-t,2.)*p0-2.*(1.-t)*t*p1-t*t*p2);\n"
"}\n"
"\n"
"//minimum dist3ance to spline\n"
"void dspline2(in vec2 x, in vec2 p0, in vec2 p1, in vec2 p2, out float ds)\n"
"{\n"
"    //coefficients for 0 = t^3 + a * t^2 + b * t + c\n"
"    vec2 E = x-p0, F = p2-2.*p1+p0, G = p1-p0;\n"
"    vec3 ai = vec3(3.*dot(G,F), 2.*dot(G,G)-dot(E,F), -dot(E,G))/dot(F,F);\n"
"\n"
"	//discriminant and helpers\n"
"    float tau = ai.x/3., p = ai.y-tau*ai.x, q = - tau*(tau*tau+p)+ai.z, dis = q*q/4.+p*p*p/27.;\n"
"    \n"
"    //triple real root\n"
"    if(dis > 0.) \n"
"    {\n"
"        vec2 ki = -.5*q*c.xx+sqrt(dis)*c.xz, ui = sign(ki)*pow(abs(ki), c.xx/3.);\n"
"        ds = dist2(p0,p1,p2,x,ui.x+ui.y-tau);\n"
"        return;\n"
"    }\n"
"    \n"
"    //three dist3inct real roots\n"
"    float fac = sqrt(-4./3.*p), arg = acos(-.5*q*sqrt(-27./p/p/p))/3.;\n"
"    vec3 t = c.zxz*fac*cos(arg*c.xxx+c*pi/3.)-tau;\n"
"    ds = min(\n"
"        dist2(p0,p1,p2,x, t.x),\n"
"        min(\n"
"            dist2(p0,p1,p2,x,t.y),\n"
"            dist2(p0,p1,p2,x,t.z)\n"
"        )\n"
"    );\n"
"}\n"
"\0";
const char *zextrude_source = "// Extrusion\n"
"void zextrude(in float z, in float d2d, in float h, out float d)\n"
"{\n"
"    vec2 w = vec2(-d2d, abs(z)-0.5*h);\n"
"    d = length(max(w,0.0));\n"
"}\n"
"\0";
const char *mfnoise_source = "#version 130\n\n"
"// const vec3 c = vec3(1.,0.,-1.);\n"
"void lfnoise(in vec2 x, out float d);\n"
"void mfnoise(in vec2 x, in float d, in float b, in float e, out float n)\n"
"{\n"
"    n = 0.;\n"
"    float a = 1., nf = 0., buf;\n"
"    for(float f = d; f<b; f *= 2.)\n"
"    {\n"
"        lfnoise(f*x, buf);\n"
"        n += a*buf;\n"
"        a *= e;\n"
"        nf += 1.;\n"
"    }\n"
"    n *= (1.-e)/(1.-pow(e, nf));\n"
"}\n"
"\0";
const char *rshort_source = "#version 130\n\n"
"\n"
"uniform float iFontWidth;\n"
"uniform sampler2D iFont;\n"
"\n"
"void rshort(in float off, out float val)\n"
"{\n"
"    // Parity of offset determines which byte is required.\n"
"    float hilo = mod(off, 2.);\n"
"    // Find the pixel offset your data is in (2 unsigned shorts per pixel).\n"
"    off *= .5;\n"
"    // - Determine texture coordinates.\n"
"    //     offset = i*iFontWidth+j for (i,j) in [0,iFontWidth]^2\n"
"    //     floor(offset/iFontWidth) = floor((i*iFontwidth+j)/iFontwidth)\n"
"    //                              = floor(i)+floor(j/iFontWidth) = i\n"
"    //     mod(offset, iFontWidth) = mod(i*iFontWidth + j, iFontWidth) = j\n"
"    // - For texture coordinates (i,j) has to be rescaled to [0,1].\n"
"    // - Also we need to add an extra small offset to the texture coordinate\n"
"    //   in order to always \"hit\" the right pixel. Pixel width is\n"
"    //     1./iFontWidth.\n"
"    //   Half of it is in the center of the pixel.\n"
"    vec2 ind = (vec2(mod(off, iFontWidth), floor(off/iFontWidth))+.05)/iFontWidth;\n"
"    // Get 4 bytes of data from the texture\n"
"    vec4 block = texture(iFont, ind);\n"
"    // Select the appropriate word\n"
"    vec2 data = mix(block.rg, block.ba, hilo);\n"
"    // Convert bytes to unsigned short. The lower bytes operate on 255,\n"
"    // the higher bytes operate on 65280, which is the maximum range \n"
"    // of 65535 minus the lower 255.\n"
"    val = round(dot(vec2(255., 65280.), data));\n"
"}\n"
"\0";
const char *rfloat_source = "#version 130\n\n"
"\n"
"void rshort(in float off, out float val);\n"
"\n"
"void rfloat(in float off, out float val)\n"
"{\n"
"    // Convert the bytes to unsigned short as first step.\n"
"    float d;\n"
"    rshort(off, d);\n"
"    \n"
"    // Convert bytes to IEEE 754 float16. That is\n"
"    // 1 sign bit, 5 bit exponent, 11 bit mantissa.\n"
"    // Also it has a weird conversion rule that is not evident at all.\n"
"    float sign = floor(d/32768.),\n"
"        exponent = floor(d/1024.-sign*32.),\n"
"        significand = d-sign*32768.-exponent*1024.;\n"
"\n"
"    // Return full float16\n"
"    if(exponent == 0.)\n"
"    {\n"
"        val = mix(1., -1., sign) * 5.960464477539063e-08 * significand;\n"
"    }\n"
"    else\n"
"    {\n"
"        val = mix(1., -1., sign) * (1. + significand * 9.765625e-4) * pow(2.,exponent-15.);\n"
"    }\n"
"}\n"
"\0";
const char *dcircle_source = "#version 130\n\n"
"\n"
"void dcircle(in vec2 x, out float d)\n"
"{\n"
"    d = length(x)-1.0;\n"
"}\n"
"\0";
const char *drhomboid_source = "#version 130\n\n"
"\n"
"void dbox(in vec2 x, in vec2 b, out float dst);\n"
"\n"
"void drhomboid(in vec2 x, in vec2 b, in float tilt, out float dst)\n"
"{\n"
"    x.x -= tilt/2./b.y*x.y;\n"
"    dbox(x,b,dst);\n"
"}\n"
"\0";
const char *dcirclesegment_source = "#version 130\n\n"
"const float pi = acos(-1.);\n"
"void dcirclesegment(in vec2 x, in float R, in float p0, in float p1, out float d)\n"
"{\n"
"    float p = atan(x.y, x.x);\n"
"    vec2 philo = vec2(max(p0, p1), min(p0, p1));\n"
"    if((p < philo.x && p > philo.y) || (p+2.0*pi < philo.x && p+2.0*pi > philo.y) || (p-2.0*pi < philo.x && p-2.0*pi > philo.y))\n"
"        d = abs(length(x)-R);\n"
"    else d = min(\n"
"        length(x-vec2(cos(p0), sin(p0))),\n"
"        length(x-vec2(cos(p1), sin(p1)))\n"
"        );\n"
"}\n"
"\0";
const char *dglyph_source = "#version 130\n\n"
"\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"void rfloat(in float off, out float val);\n"
"void dbox(in vec2 x, in vec2 b, out float dst);\n"
"void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);\n"
"void dcircle(in vec2 x, out float d);\n"
"void dcirclesegment(in vec2 x, in float r, in float p0, in float p1, out float d);\n"
"void stroke(in float d0, in float s, out float d);\n"
"void smoothmin(in float a, in float b, in float k, out float dst);\n"
"\n"
"void dglyph(in vec2 x, in float ordinal, in float size, out float dst)\n"
"{\n"
"    float dis;\n"
"    dbox(x, 2.*size*c.xx, dis);\n"
"    if(dis > 0.)\n"
"    {\n"
"        dst = dis+.5*size;\n"
"        return;\n"
"    }\n"
"\n"
"    // Find glyph offset in glyph index\n"
"    float nglyphs, offset = 0;\n"
"    rfloat(1., nglyphs);\n"
"        \n"
"    for(float i=0.; i<nglyphs; i+=1.)\n"
"    {\n"
"        float ord;\n"
"        rfloat(2.+2.*i, ord);\n"
"        ord = floor(ord);\n"
"        \n"
"        if(ord == ordinal)\n"
"        {\n"
"            rfloat(2.+2.*i+1., offset);\n"
"            offset = floor(offset);\n"
"            break;\n"
"        }\n"
"    }\n"
"    \n"
"    if(offset == 0.) \n"
"    {\n"
"        dst = 1.;\n"
"        return;\n"
"    }\n"
"    \n"
"    // Get distance from glyph data\n"
"    float d = 1., da = 1.;\n"
"    \n"
"    // Lines\n"
"    float nlines;\n"
"    rfloat(offset, nlines);\n"
"    nlines = floor(nlines);\n"
"    offset += 1.;\n"
"    for(float i=0.; i<nlines; i+=1.)\n"
"    {\n"
"        float x1;\n"
"        rfloat(offset, x1);\n"
"        offset += 1.;\n"
"        float y1;\n"
"        rfloat(offset, y1);\n"
"        offset += 1.;\n"
"        float x2;\n"
"        rfloat(offset, x2);\n"
"        offset += 1.;\n"
"        float y2;\n"
"        rfloat(offset, y2);\n"
"        offset += 1.;\n"
"        dlinesegment(x, size*vec2(x1,y1), size*vec2(x2, y2), da);\n"
"        d = min(d,da);\n"
"    }\n"
"    \n"
"    stroke(d,.2*size,d);\n"
"    \n"
"    // Smooth lines\n"
"    float nsmoothlines, db = 1.;\n"
"    da = 1.;\n"
"    rfloat(offset, nsmoothlines);\n"
"    nsmoothlines = floor(nsmoothlines);\n"
"    offset += 1.;\n"
"    for(float i=0.; i<nsmoothlines; i+=1.)\n"
"    {\n"
"        float x1;\n"
"        rfloat(offset, x1);\n"
"        offset += 1.;\n"
"        float y1;\n"
"        rfloat(offset, y1);\n"
"        offset += 1.;\n"
"        float x2;\n"
"        rfloat(offset, x2);\n"
"        offset += 1.;\n"
"        float y2;\n"
"        rfloat(offset, y2);\n"
"        offset += 1.;\n"
"        dlinesegment(x, size*vec2(x1,y1), size*vec2(x2, y2), db);\n"
"        da = min(da, db);\n"
"    }\n"
"    stroke(da,.2*size, da);\n"
"    smoothmin(d,da,.1*size,d);\n"
"    \n"
"    \n"
"//     if(nlines+nsmoothlines== 0.)\n"
"//         dst = dis;\n"
"//     else dst = d;\n"
"    dst = d;\n"
"}\n"
"\0";
const char *dstring_source = "#version 130\n\n"
"\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"void rfloat(in float off, out float val);\n"
"void dbox(in vec2 x, in vec2 b, out float dst);\n"
"void dglyph(in vec2 x, in float ordinal, in float size, out float dst);\n"
"\n"
"void dstring(in vec2 x, in float ordinal, in float size, out float dst)\n"
"{\n"
"    // Get string database offset\n"
"    float stroff0;\n"
"    rfloat(0., stroff0);\n"
"    stroff0 = floor(stroff0);\n"
"    \n"
"    // Return 1 if wrong ordinal is supplied\n"
"    float nstrings;\n"
"    rfloat(stroff0, nstrings);\n"
"    nstrings = floor(nstrings);\n"
"    if(ordinal >= nstrings)\n"
"    {\n"
"        dst = 1.;\n"
"        return;\n"
"    }\n"
"    \n"
"    // Get offset and length of string from string database index\n"
"    float stroff;\n"
"    rfloat(stroff0+1.+2.*ordinal, stroff);\n"
"    stroff = floor(stroff);\n"
"    float len;\n"
"    rfloat(stroff0+2.+2.*ordinal, len);\n"
"    len = floor(len);\n"
"    \n"
"    // Draw glyphs\n"
"    vec2 dx = mod(x-size, 2.*size)-size, \n"
"        ind = ceil((x-dx+size)/2./size);\n"
"    \n"
"    // Bounding box\n"
"    float bound;\n"
"    dbox(x-size*(len-3.)*c.xy, vec2(size*len, 1.*size), bound);\n"
"    if(bound > 0.)\n"
"    {\n"
"        dst = bound+.5*size;\n"
"        return;\n"
"    }\n"
"    \n"
"    float da;\n"
"    rfloat(stroff+ind.x, da);\n"
"    da = floor(da);\n"
"    dglyph(dx, da, .7*size, dst);\n"
"}\n"
"\0";
const char *dfloat_source = "#version 130\n\n"
"\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"void dglyph(in vec2 x, in float ordinal, in float size, out float dst);\n"
"\n"
"void dfloat(in vec2 x, in float num, in float size, out float dst)\n"
"{\n"
"    float d = 1., index = 0.;\n"
"    \n"
"    // Determine sign and output it if present\n"
"    float sign = sign(num), exp = 0.;\n"
"    if(sign<0.)\n"
"    {\n"
"        float da;\n"
"        dglyph(x, 45., .7*size, da);\n"
"        d = min(d, da);\n"
"        index += 1.;\n"
"        num *= -1.;\n"
"    }\n"
"    \n"
"    // The first power of ten that floors num to anything not zero is the exponent\n"
"    for(exp = -15.; exp < 15.; exp += 1.)\n"
"        if(floor(num*pow(10.,exp)) != 0.)\n"
"            break;\n"
"    exp *= -1.;\n"
"    // Determine the significand and output it\n"
"    for(float i = exp; i >= max(exp-5.,-33); i -= 1.)\n"
"    {\n"
"        float po = pow(10.,i);\n"
"        float ca = floor(num/po);\n"
"        num -= ca*po;\n"
"        \n"
"        float da;\n"
"        dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);\n"
"        d = min(d, da);\n"
"        index += 1.;\n"
"        if(i == exp) // decimal point\n"
"        {\n"
"            dglyph(x-2.*index*size*c.xy, 46., .7*size, da);\n"
"            d = min(d, da);\n"
"            index += 1.;\n"
"        }\n"
"    }\n"
"    \n"
"    // Output the exponent\n"
"    float db;\n"
"    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 101., .7*size, db);\n"
"    d = min(d, db);\n"
"    index += 1.;\n"
"    if(exp < 0.) // Sign\n"
"    {\n"
"        dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 45., .7*size,db);\n"
"        d = min(d, db);\n"
"        index += 1.;\n"
"        exp *= -1.;\n"
"    }\n"
"    float ca = floor(exp/10.);\n"
"    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, db);\n"
"    d = min(d, db);\n"
"    index += 1.;\n"
"    ca = floor(exp-10.*ca);\n"
"    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, db);\n"
"    d = min(d, db);\n"
"    index += 1.;\n"
"    \n"
"    dst = d;\n"
"}\n"
"\0";
const char *dint_source = "#version 130\n\n"
"\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"void dglyph(in vec2 x, in float ordinal, in float size, out float dst);\n"
"\n"
"void dint(in vec2 x, in float num, in float size, in float ndigits, out float dst)\n"
"{\n"
"    float d = 1., index = 0.;\n"
"    \n"
"    if(num == 0.)\n"
"    {\n"
"        index = ndigits;\n"
"        dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48., .7*size, dst);\n"
"        return;\n"
"    } \n"
"    \n"
"    // Determine sign and output it if present\n"
"    float sign = sign(num), exp = 0.;\n"
"    if(sign<0.)\n"
"    {\n"
"        float da;\n"
"        dglyph(x, 45., .7*size, da);\n"
"        d = min(d, da);\n"
"        index += 1.;\n"
"        num *= -1.;\n"
"    }\n"
"    \n"
"    // The first power of ten that floors num to anything not zero is the exponent\n"
"    for(exp = -15.; exp < 15.; exp += 1.)\n"
"        if(floor(num*pow(10.,exp)) != 0.)\n"
"            break;\n"
"    exp *= -1.;\n"
"    \n"
"    int hit = 0;\n"
"    \n"
"    // Determine the significand and output it\n"
"    for(float i = ndigits; i >= 0.; i -= 1.)\n"
"    {\n"
"        float po = pow(10.,i);\n"
"        float ca = floor(num/po);\n"
"        if(ca == 0.) \n"
"        {\n"
"            if(hit == 0)\n"
"            {\n"
"                index += 1.;\n"
"                continue;\n"
"            }\n"
"            \n"
"        }\n"
"        else hit = 1;\n"
"        num -= ca*po;\n"
"        \n"
"        float da;\n"
"        dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);\n"
"        d = min(d, da);\n"
"        index += 1.;\n"
"    }\n"
"    \n"
"    \n"
"    \n"
"    dst = d;\n"
"}\n"
"\0";
const char *dtime_source = "#version 130\n\n"
"\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"void dglyph(in vec2 x, in float ordinal, in float size, out float dst);\n"
"\n"
"// Time in format: 00:00\n"
"void dtime(in vec2 x, in float num, in float size, out float dst)\n"
"{\n"
"    float d = 1., index = 0.;\n"
"    \n"
"    num = floor(num);\n"
"\n"
"    // 10 minutes\n"
"    float ca = floor(num/600.), da = 1.;\n"
"    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);\n"
"    d = min(d, da);\n"
"    index += 1.;\n"
"    num -= ca*600.;\n"
"\n"
"    // minutes\n"
"    ca = floor(num/60.);\n"
"    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);\n"
"    d = min(d, da);\n"
"    index += 1.;\n"
"    num -= ca*60.;\n"
"\n"
"    // :\n"
"    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 58., .7*size, da);\n"
"    d = min(d, da);\n"
"    index += 1.;\n"
"    \n"
"    // 10 seconds\n"
"    ca = floor(num/10.);\n"
"    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);\n"
"    d = min(d, da);\n"
"    index += 1.;\n"
"    num -= ca*10.;\n"
"    \n"
"    // 1 seconds\n"
"    ca = floor(num/1.);\n"
"    dglyph(x+.7*size*c.xy-2.*index*size*c.xy, 48.+ca, .7*size, da);\n"
"    d = min(d, da);\n"
"    \n"
"    dst = d;\n"
"}\n"
"\0";
const char *window_source = "#version 130\n\n"
"\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"uniform float iTime;\n"
"\n"
"void dhexagonpattern(in vec2 p, out float d, out vec2 ind);\n"
"void stroke(in float d0, in float s, out float d);\n"
"void lfnoise(in vec2 t, out float num);\n"
"void box(in vec2 x, in vec2 b, out float dst);\n"
"void drhomboid(in vec2 x, in vec2 b, in float tilt, out float dst);\n"
"\n"
"// Fixme: Add\n"
"\n"
"void window(in vec2 x, in vec2 size, in vec3 bg, in float title_index, out vec4 col)\n"
"{\n"
"//     size.x *= .5;\n"
"//     col = vec4(1., bg);\n"
"//     \n"
"//     const float cellsize = .015, bordersize = .005;\n"
"//     vec3 titlecolor = mix(vec3(0.82,0.00,0.09),vec3(0.45,0.00,0.06),.5-.5*x.y/cellsize),\n"
"//         bordercolor = vec3(1.00,0.71,0.02);\n"
"//     vec4 c2 = vec4(1., titlecolor);\n"
"//     \n"
"//     float dhx, dhy;\n"
"//     vec2 ind;\n"
"//     dhexagonpattern(72.*x,  dhx, ind);\n"
"//     stroke(dhx, .1, dhx);\n"
"//     lfnoise(ind-iTime, dhy);\n"
"//     \n"
"//     // Window background\n"
"//     box(x+.5*size*c.yx,size*vec2(1.,.5),c2.x);\n"
"//     c2.gba = mix(bg, mix(vec3(0.82,0.00,0.09),vec3(0.45,0.00,0.06),-x.y/size.y), .5+.5*dhy*step(0.,dhx));\n"
"//     add(col, c2, col);\n"
"//     \n"
"//     // Title bar\n"
"//     c2.gba = titlecolor;\n"
"//     drhomboid(x+.8*size.x*c.xy, vec2(.1*size.x,cellsize), cellsize, c2.x);\n"
"//    	add(col, c2, col);\n"
"//     drhomboid(x, vec2(.65*size.x,cellsize), cellsize, c2.x);\n"
"//    	add(col, c2, col);\n"
"//     drhomboid(x-.8*size.x*c.xy, vec2(.1*size.x,cellsize), cellsize, c2.x);\n"
"//    	add(col, c2, col);\n"
"//     \n"
"//     // Border of title bar\n"
"//     c2 = vec4(1., bordercolor);\n"
"//     stroke(col.x,bordersize,c2.x);\n"
"//     add(col,c2,col);\n"
"//     \n"
"//     // Window Border\n"
"//     dlinesegment(x, -.9*size.x*c.xy, -size.x*c.xy, c2.x);\n"
"//     float d;\n"
"//     dlinesegment(x, -size.x*c.xy, -size, d);\n"
"//     c2.x = min(c2.x, d);\n"
"//     dlinesegment(x, -size, size*c.xz, d);\n"
"//     c2.x = min(c2.x, d);\n"
"//     dlinesegment(x, size*c.xz, size*c.xy, d);\n"
"//     c2.x = min(c2.x, d);\n"
"//     dlinesegment(x, .9*size.x*c.xy, size.x*c.xy, d);\n"
"//     c2.x = min(c2.x, d);\n"
"//     stroke(c2.x,.25*bordersize,c2.x);\n"
"//     add(col, c2, col);\n"
"}\n"
"\0";
const char *progressbar_source = "#version 130\n\n"
"\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"void progressbar(in vec2 x, in float width, in float progress, out vec4 col)\n"
"{\n"
"//     const float cellsize = .015, bordersize = .005;\n"
"//     vec3 titlecolor = mix(vec3(0.82,0.00,0.09),vec3(0.45,0.00,0.06),.5-.5*x.y/cellsize),\n"
"//         bordercolor = vec3(1.00,0.71,0.02), bg = c.yyy;\n"
"//     vec4 c2 = vec4(1., titlecolor);\n"
"//     \n"
"//     // Window background\n"
"//     box(x+.5*width*c.yx,width*c.xy,c2.x);\n"
"//     c2.gba = mix(bg, mix(vec3(0.82,0.00,0.09),vec3(0.45,0.00,0.06),-x.y/cellsize), .5);\n"
"//     add(col, c2, col);\n"
"//     \n"
"//     // Bar background\n"
"//     c2.gba = titlecolor;\n"
"//     drhomboid(x, vec2(.5*width,cellsize), cellsize, c2.x);\n"
"//    	add(col, c2, col);\n"
"//     \n"
"//     // Border\n"
"//     c2.gba = bordercolor;\n"
"//     stroke(c2.x,.5*bordersize,c2.x);\n"
"//     add(col, c2, col);\n"
"//     \n"
"//     // Progress\n"
"//     float wc = width/cellsize;\n"
"//     x.x -= .5*x.y;\n"
"//     vec2 y = vec2(mod(x.x, 1.2*cellsize)-.6*cellsize, x.y),\n"
"//         index = (x-y)/.6/cellsize;\n"
"//     if(abs(index.x) < .8*wc && -index.x > .8*wc*(1.-2.*progress))\n"
"//     {\n"
"//         box(y, vec2(.5*cellsize, .8*cellsize), c2.x);\n"
"//         add(col, c2, col);\n"
"//     }\n"
"}\n"
"\0";
const char *ocean_source = "#version 130\n\n"
"\n"
"uniform float iTime;\n"
"uniform vec2 iResolution;\n"
"\n"
"const float pi = acos(-1.);\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"\n"
"void rand(in vec2 x, out float n);\n"
"void hash11(in float p, out float d);\n"
"void hash12(in vec2 p, out float d);\n"
"void hash21(in float p, out vec2 d);\n"
"void hash22(in vec2 p, out vec2 d);\n"
"void hash31(in float p, out vec3 d);\n"
"void stroke(in float d0, in float s, out float d);\n"
"void lfnoise(in vec2 t, out float n);\n"
"void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);\n"
"void dbox(in vec2 x, in vec2 b, out float d);\n"
"void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);\n"
"float sm(in float d)\n"
"{\n"
"    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);\n"
"}\n"
"\n"
"void smoothmin(in float a, in float b, in float k, out float dst);\n"
"\n"
"void gerst(in vec2 x, out float z)\n"
"{\n"
"    float df, \n"
"        A = 1.,\n"
"        da;\n"
"    vec2 dk,\n"
"        k;\n"
"    \n"
"    z = 0.;\n"
"    \n"
"    for(float f = 1.; f < 6.; f *= 1.1)\n"
"    {\n"
"        hash11(f,df);\n"
"        f *= (.95+.2*df);\n"
"        hash21(f+2337.,k);\n"
"        k *= 64./f+.5;\n"
"        hash11(f+1337., da);\n"
"        A *= (1.+.3*da);\n"
"        \n"
"        z += A*pow(.5*(1.+sin(dot(k,x)+f*iTime)),2.);\n"
"    }\n"
"    \n"
"}\n"
"\n"
"void add(in vec2 sda, in vec2 sdb, out vec2 sdf);\n"
"\n"
"void scene(in vec3 x, out vec2 sdf)\n"
"{\n"
"    float g;\n"
"    gerst(x.xy, g);\n"
"    sdf = vec2(x.z-.002*g, 1.);\n"
"    sdf.x = abs(sdf.x) - .002;\n"
"    \n"
"    add(sdf, vec2(x.z+.2, 2.), sdf);\n"
"}\n"
"\n"
"void normal(in vec3 x, out vec3 n, in float dx);\n"
"\n"
"void palette(in float scale, out vec3 col)\n"
"{\n"
"    const int N = 5;\n"
"    const vec3 colors[N] = vec3[N](\n"
"//             vec3(0.27,0.13,0.26),\n"
"//             vec3(0.43,0.21,0.33),\n"
"//             vec3(0.69,0.36,0.42),\n"
"//             vec3(0.87,0.52,0.45),\n"
"//             vec3(0.99,0.68,0.53)\n"
"vec3(0.04,0.04,0.15),\n"
"vec3(0.18,0.32,0.46),\n"
"vec3(0.66,0.43,0.62),\n"
"vec3(0.96,0.78,0.88),\n"
"vec3(0.40,0.00,0.18)\n"
"    );\n"
"	float index = floor(scale*float(N)), \n"
"        remainder = scale*float(N)-index;\n"
"    col = mix(colors[int(index)],colors[int(index)+1], remainder);\n"
"}\n"
"\n"
"float dspiral(vec2 x, float a, float d);\n"
"\n"
"void colorize(in vec2 x, inout vec3 col)\n"
"{\n"
"    float v, n = 64., r;\n"
"    vec2 ind;\n"
"    dvoronoi(n*x, v, ind, r);\n"
"    rand(ind, r);\n"
"    vec2 y = x-ind/n;\n"
"    vec3 c1;\n"
"    rand(ind+1337., c1.x);\n"
"    rand(ind+2337., c1.y);\n"
"    rand(ind+3337., c1.z);\n"
"    c1 *= vec3(1.,.7,.3);\n"
"    c1 = .5+.5*c1;\n"
"    c1 *= vec3(.4,.6,1.);\n"
"    float d = length(y)-.0002*r;\n"
"    if(r > .75)\n"
"        col = mix(col, c1, sm(d));\n"
"//     r *= cos(pi*x.y);\n"
"    if(r>.5)\n"
"    {\n"
"        col = mix(col, mix(col, 2.*c1, .8), sm(d-.004*r*r));\n"
"        col = mix(col, mix(col, 3.*c1, .4), sm(d-.01*r*r));\n"
"    }\n"
"    \n"
"    float cpa;\n"
"    dvoronoi(2.*n*x, v, ind, cpa);\n"
"    y = x-ind/n/2.;\n"
"    rand(ind, r);\n"
"    d = length(y)-.002*r;\n"
"    col = mix(col, c.xxx, sm(d));\n"
"    \n"
"    lfnoise(x.xy-v*v*v, d);\n"
"    col = mix(col, c.yyy, .5+.5*d);\n"
"    \n"
"    col = .6*col+.3*step(.8,col);\n"
"    col *= 2.;\n"
"    \n"
"    v = dspiral(x, .1,.01);\n"
"    col = mix(col, c.yyy, 1.-sm(v*6.e-3));\n"
"    col = mix(col, 2.5*col, sm(v*2.e-3));\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    vec2 uv = (gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,\n"
"        s;\n"
"    \n"
"    vec3 col = c.yyy,\n"
"        o = .5*c.yyx+c.yzy,\n"
"        r = c.xyy,\n"
"        t = c.yyy, \n"
"        u = cross(normalize(t-o),-r),\n"
"        dir,\n"
"        n, \n"
"        x;\n"
"    int N = 150,\n"
"        i;\n"
"    t = uv.x * r + uv.y * u;\n"
"    dir = normalize(t-o);\n"
"\n"
"    vec3 c1;\n"
"    float d = -(o.z-.15)/dir.z;\n"
"    \n"
"    vec3 o0, dir0;\n"
"    float d0;\n"
"    \n"
"    for(i = 0; i<N; ++i)\n"
"    {\n"
"     	x = o + d * dir;\n"
"        scene(x,s);\n"
"        if(s.x < 1.e-4) break;\n"
"        d += s.x;\n"
"//         d += min(s.x,1.e-2);\n"
"        //d += s.x;\n"
"    }\n"
"    \n"
"    if(i < N)\n"
"    {\n"
"        vec3 l = c.yyx;\n"
"        normal(x,n, 1.e-4);\n"
"        \n"
"        if(s.y == 1.)\n"
"        {\n"
"            palette(x.z/.22, col);\n"
"\n"
"            col = .1*col \n"
"                + .1*col*dot(l, n)\n"
"                + 1.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);\n"
"        }\n"
"        \n"
"        o = x;\n"
"        d = 1.e-2;\n"
"        dir = refract(dir,n,.5);\n"
"        vec3 c1;\n"
"        \n"
"        for(i = 0; i<N; ++i)\n"
"        {\n"
"            x = o + d * dir;\n"
"            scene(x,s);\n"
"            if(s.x < 1.e-3)break;\n"
"            d += s.x;\n"
"    //         d += min(s.x,1.e-1);\n"
"            //d += s.x;\n"
"        }\n"
"        \n"
"        if(i < N)\n"
"        {\n"
"            vec3 l = c.yyx;\n"
"            normal(x,n, 2.e-3);\n"
"            \n"
"            \n"
"            if(s.y == 1.)\n"
"            {\n"
"                palette(x.z/.22, c1);\n"
"\n"
"                c1 = .1*c1 \n"
"                    + .1*c1*dot(l, n)\n"
"                    + 1.6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);\n"
"            }\n"
"            else if(s.y == 2.)\n"
"            {\n"
"                c1 = vec3(0.26,0.16,0.32);\n"
"//                 float v, cv;\n"
"//                 vec2 ind;\n"
"//                 dvoronoi(12.*x.xy, v, ind, cv);\n"
"//                 c1 = mix(c1, c.xxx, sm(abs(v)-.02));\n"
"                float v = .5+.5*sin(100.*x.y);\n"
"                c1 = mix(c1,2.*c1, v);\n"
"                \n"
"                c1 = .1*c1 \n"
"                    + .1*c1*dot(l, n)\n"
"                    + 1.6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);\n"
"            }\n"
"        }\n"
"        col = mix(col, c1, .1);\n"
"    }\n"
"\n"
"    col = 3.*col*col;\n"
"    \n"
"    //col = mix(col, c.yyy, tanh(2.e-1*d));\n"
"    \n"
"    \n"
"    gl_FragColor = vec4(clamp(col,0.,1.),1.);\n"
"}\n"
"\n"
"\0";
const char *logo210_source = "/* Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19\n"
" * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>\n"
" * \n"
" * This program is free software: you can redistribute it and/or modify\n"
" * it under the terms of the GNU General Public License as published by\n"
" * the Free Software Foundation, either version 3 of the License, or\n"
" * (at your option) any later version.\n"
" * \n"
" * This program is distributed in the hope that it will be useful,\n"
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" * GNU General Public License for more details.\n"
" * \n"
" * You should have received a copy of the GNU General Public License\n"
" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
" */\n"
" \n"
"#version 130\n \n"
" \n"
"uniform float iTime;\n"
"uniform vec2 iResolution;\n"
"\n"
"const float pi = acos(-1.);\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"float a = 1.0;\n"
"\n"
"float nbeats, iScale;\n"
"\n"
"void dbox3(in vec3 x, in vec3 b, out float d);\n"
"void rot3(in vec3 p, out mat3 rot);\n"
"void stroke(in float d0, in float s, out float d);\n"
"void add(in vec2 sda, in vec2 sdb, out vec2 sdf);\n"
"void dbox210(in vec3 x, in float size, out vec2 sdf);\n"
"\n"
"mat3 R;\n"
"void scene(in vec3 x, out vec2 sdf)\n"
"{\n"
"    sdf = c.xy;\n"
"    \n"
"    float d, da;\n"
"    \n"
"    rot3(vec3(-pi/2.,0.,pi/2.), R);\n"
"    x = R * x;\n"
"    \n"
"    vec2 sda = c.xy;\n"
"    \n"
"	dbox210(x+.1*c.xyy, .5, sdf);\n"
"	rot3(vec3(pi/2.,0.,pi/2.), R);\n"
"    x = R * x;\n"
"    //add(sdf,sda,sdf);\n"
"    \n"
"    dbox210(x,5.,sda);\n"
"    add(sdf,sda,sdf);\n"
"    \n"
"    rot3(vec3(pi/2.,-pi/2.,pi/2.), R);\n"
"    x = R * x;\n"
"    \n"
"    dbox210(x-2.*c.yxy,50.,sda);\n"
"    add(sdf,sda,sdf);\n"
"    \n"
"    stroke(sdf.x,.001, sdf.x);\n"
"    \n"
"    dbox3(x, 100.*c.xxx, sda.x);\n"
"    sda.y = 2.;\n"
"    \n"
"    add(sdf, sda*c.zx, sdf);\n"
"}\n"
"\n"
"void normal(in vec3 x, out vec3 n, in float dx);\n"
"\n"
"void mainImage( out vec4 fragColor, in vec2 fragCoord )\n"
"{\n"
"    float a = iResolution.x/iResolution.y;\n"
"    vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);\n"
"    \n"
"    vec3 col = c.xxx;\n"
"    \n"
"    float d = 0.;\n"
"    vec2 s;\n"
"    vec3 o, t, dir, x, n;\n"
"    \n"
"    mat3 Ra;\n"
"    rot3(mix(c.yyy,vec3(-5.7884463,2.4242211,0.3463173),clamp((iTime-6.)/1.5,0.,1.)), Ra);\n"
"    //vec3 a = vec3(uv,-1.);\n"
"	\n"
"    //rot3(mix(c.yyy,vec3(-3.*pi/4.,3.*pi/4.,-7.*pi/4.),clamp((iTime-6.)/1.5,0.,1.)), Ra);\n"
"    //Ra *= mix(1.,-1.,clamp((iTime-6.)/1.5,0.,1.));\n"
"       \n"
"    \n"
"    o = Ra * mix(mix(mix(c.yyy-.1*c.yxy,c.yyx,clamp(iTime/2.,0.,1.)),10.*c.yyx,clamp((iTime-2.)/2.,0.,1.)), 100.*c.yyx, clamp((iTime-4.)/2.,0.,1.));\n"
"	t = c.yyy;\n"
"    int N = 650,\n"
"        i;\n"
"    dir = Ra *normalize(vec3(uv,-1.));//normalize(t-o);\n"
"    \n"
"    for(i = 0; i<N; ++i)\n"
"    {\n"
"        x = o + d * dir;\n"
"        scene(x,s);\n"
"        if(s.x < 1.e-4)break;\n"
"        d += s.x;\n"
"    }\n"
"        \n"
"    if(s.x < 1.e-4)\n"
"    {\n"
"        normal(x,n, 5.e-4);\n"
"        vec3 l = normalize(x+.1*n);\n"
"        \n"
"        if(s.y == 1.)\n"
"        {\n"
"            // cube color\n"
"            col = vec3(0.27,0.36,0.48);\n"
"            col = .3*col\n"
"                + .4*col * abs(dot(l,n))\n"
"                + .6 * col * abs(pow(dot(reflect(-l,n),dir),3.));\n"
"        }\n"
"        else if(s.y == 2.)\n"
"        {\n"
"            col = .7*c.xxx;\n"
"            col = .5*col\n"
"                + .4*col * abs(dot(l,n))\n"
"                + .8 * col * abs(pow(dot(reflect(-l,n),dir),3.));\n"
"            \n"
"            vec3 c1 = c.yyy;\n"
"            \n"
"            o = x;\n"
"            dir = reflect(dir,n);\n"
"            d = 1.e-1;\n"
"            \n"
"            N = 150;\n"
"            \n"
"            for(i = 0; i<N; ++i)\n"
"            {\n"
"                x = o + d * dir;\n"
"                scene(x,s);\n"
"                if(s.x < 1.e-4)break;\n"
"                d += s.x;\n"
"            }\n"
"                \n"
"            if(s.x < 1.e-4)\n"
"            {\n"
"                normal(x,n, 5.e-4);\n"
"                vec3 l = normalize(x+.1*n);\n"
"\n"
"                if(s.y == 1.)\n"
"                {\n"
"                    c1 = vec3(0.27,0.36,0.48);\n"
"                    c1 = .3*c1\n"
"                        + .4*c1 * abs(dot(l,n))\n"
"                        + .6 * c1 * abs(pow(dot(reflect(-l,n),dir),3.));\n"
"                }\n"
"                else if(s.y == 2.)\n"
"                {\n"
"                    c1 = .7*c.xxx;\n"
"                    c1 = .5*c1\n"
"                        + .4*c1 * abs(dot(l,n))\n"
"                        + .8 * c1 * abs(pow(dot(reflect(-l,n),dir),3.));\n"
"                }\n"
"                c1 = clamp(c1, 0., 1.);\n"
"                \n"
"                col = mix(col, c1, .2);\n"
"            }\n"
"            \n"
"            col = clamp(col, 0., 1.);\n"
"        }\n"
"        \n"
"    }\n"
"    col = mix(col,vec3(0.14,0.01,0.2),smoothstep(0.,1.,iTime-10.));\n"
"    \n"
"    fragColor = vec4(clamp(col,0.,1.),1.0);\n"
"}\n"
"\n"
"\n"
"void main()\n"
"{\n"
"    mainImage(gl_FragColor, gl_FragCoord.xy);\n"
"}\n"
"\0";
const char *graffiti_source = "/* Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19\n"
" * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>\n"
" * \n"
" * This program is free software: you can redistribute it and/or modify\n"
" * it under the terms of the GNU General Public License as published by\n"
" * the Free Software Foundation, either version 3 of the License, or\n"
" * (at your option) any later version.\n"
" * \n"
" * This program is distributed in the hope that it will be useful,\n"
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" * GNU General Public License for more details.\n"
" * \n"
" * You should have received a copy of the GNU General Public License\n"
" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
" */\n"
"\n"
"#version 130\n\n"
"\n"
"uniform float iTime;\n"
"uniform vec2 iResolution;\n"
"\n"
"const float pi = acos(-1.);\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"float a = 1.0;\n"
"\n"
"void hash22(in vec2 x, out vec2 y);\n"
"void rand(in vec2 x, out float n);\n"
"void lfnoise(in vec2 t, out float n);\n"
"void dspline2(in vec2 x, in vec2 p0, in vec2 p1, in vec2 p2, out float ds);\n"
"void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);\n"
"void stroke(in float d0, in float s, out float d);\n"
"void smoothmin(in float a, in float b, in float k, out float dst);\n"
"void d_h(in vec2 x, out float d)\n"
"{\n"
"    float da;\n"
"    dspline2(vec2(abs(x.x)-.1, abs(x.y)), vec2(.15,.25), vec2(.05,.25), vec2(.05,0.), d);\n"
"    dlinesegment(x, vec2(-.075,0.), vec2(.075,0.), da);\n"
"    smoothmin(d, da, .1, d);\n"
"}\n"
"\n"
"void d_a(in vec2 x, out float d)\n"
"{\n"
"    float da;\n"
"    dspline2(vec2(abs(x.x)-.1, x.y), vec2(.15,-.25), vec2(.05,-.25), vec2(.05, 0.), d);\n"
"    dspline2(vec2(abs(x.x)-.1, x.y), vec2(.05,0.), vec2(.05,.25), vec2(-.1,.25), da);\n"
"    d = min(d,da);\n"
"    dlinesegment(x, vec2(-.075,0.), vec2(.075,0.), da);\n"
"    smoothmin(d, da, .1, d);\n"
"}\n"
"\n"
"void d_r(in vec2 x, out float d)\n"
"{\n"
"    float da;\n"
"    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);\n"
"    dspline2(vec2(x.x,abs(x.y-.1)-.15), vec2(.0,-.05), vec2(.25,.05), vec2(.25,-.15), da);\n"
"    smoothmin(d,da,.1,d);\n"
"    dspline2(x,vec2(0.,-.05), vec2(0.,-.25), vec2(.35,-.25), da);\n"
"    smoothmin(d,da,.1,d);\n"
"}\n"
"\n"
"void d_d(in vec2 x, out float d)\n"
"{\n"
"    float da;\n"
"    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);\n"
"    dspline2(vec2(x.x,abs(x.y)-.1), vec2(-.05,.15), vec2(.25,.25), vec2(.25,-.1), da);\n"
"    smoothmin(d,da,.1,d);\n"
"}\n"
"\n"
"void d_c(in vec2 x, out float d)\n"
"{\n"
"    float da;\n"
"    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);\n"
"    dspline2(vec2(x.x,abs(x.y)-.1), vec2(-.05,.15), vec2(.25,.25), vec2(.25,0.), da);\n"
"    smoothmin(d,da,.1,d);\n"
"}\n"
"\n"
"void d_y(in vec2 x, out float d)\n"
"{\n"
"    float da;\n"
"    dspline2(vec2(abs(x.x)-.2, x.y), vec2(-.05,0.25), vec2(-.05,.1), vec2(-.2,.1), d);\n"
"    dlinesegment(x, vec2(0.,-.25), vec2(0.,.1), da);\n"
"    smoothmin(d,da,.1,d);\n"
"}\n"
"\n"
"void d_b(in vec2 x, out float d)\n"
"{\n"
"    float da;\n"
"    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);\n"
"    dspline2(vec2(x.x,abs(abs(x.y)-.125)-.15), vec2(.0,-.05), vec2(.25,.05), vec2(.25,-.15), da);\n"
"    smoothmin(d,da,.1,d);\n"
"}\n"
"\n"
"void d_e(in vec2 x, out float d)\n"
"{\n"
"    float da;\n"
"    dspline2(vec2(x.x, abs(x.y)), vec2(-.15,.25), vec2(-.05,.25), vec2(-.05,0.), d);\n"
"    dspline2(vec2(x.x,abs(x.y)-.1), vec2(-.05,.05), vec2(-.05,.15), vec2(.25,.15), da);\n"
"    smoothmin(d,da,.1,d);\n"
"    dlinesegment(x,vec2(-.05,0.), vec2(.15,0.), da);\n"
"    smoothmin(d,da,.1,d);\n"
"}\n"
"\n"
"void dhardcyber(in vec2 x, out float d)\n"
"{\n"
"//     x = floor(96.*x)/96.;\n"
"    x *= 3.;\n"
"    float da;\n"
"    d_h(x+1.8*c.xy,d);\n"
"    d_a(x+1.3*c.xy,da);\n"
"    d = min(d,da);\n"
"    d_r(x+.9*c.xy,da);\n"
"    d = min(d,da);\n"
"    d_d(x+.4*c.xy,da);\n"
"    d = min(d,da);\n"
"    d_c(x-.1*c.xy,da);\n"
"    d = min(d,da);\n"
"    d_y(x-.6*c.xy,da);\n"
"    d = min(d,da);\n"
"    d_b(x-.925*c.xy,da);\n"
"    d = min(d,da);\n"
"    d_e(x-1.4*c.xy,da);\n"
"    d = min(d,da);\n"
"    d_r(x-1.8*c.xy,da);\n"
"    d = min(d,da);\n"
"    \n"
"    stroke(d, .07, d);\n"
"    \n"
"    d /= 3.;\n"
"}\n"
"\n"
"float sm(float d)\n"
"{\n"
"    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);\n"
"}\n"
"\n"
"void palette(in float scale, out vec3 col)\n"
"{\n"
"    const int N = 5;\n"
"    const vec3 colors[N] = vec3[N](\n"
"            vec3(0.27,0.13,0.26),\n"
"            vec3(0.43,0.21,0.33),\n"
"            vec3(0.69,0.36,0.42),\n"
"            vec3(0.87,0.52,0.45),\n"
"            vec3(0.99,0.68,0.53)\n"
"    );\n"
"	float index = floor(scale*float(N)), \n"
"        remainder = scale*float(N)-index;\n"
"    col = mix(colors[int(index)],colors[int(index)+1], remainder);\n"
"}\n"
"\n"
"void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);\n"
"void zextrude(in float z, in float d2d, in float h, out float d);\n"
"void scene(in vec3 x, out vec2 sdf)\n"
"{    \n"
"    dhardcyber(x.xy, sdf.x);\n"
"    zextrude(x.z, -sdf.x, .1, sdf.x);\n"
"    smoothmin(sdf.x, x.z,.1, sdf.x);\n"
"    sdf.y = 1.;\n"
"    stroke(sdf.x, .01, sdf.x);\n"
"//     sdf.x = abs(sdf.x);\n"
"//     sdf.x /= 4.;\n"
"}\n"
"\n"
"void normal(in vec3 x, out vec3 n, in float dx);\n"
"void colorize(in vec2 uv, inout vec3 col)\n"
"{\n"
"    vec3 c1;\n"
"    float d = floor(8.*(.5+.4*tanh(6.*uv.y+uv.x)))/8.;\n"
"    vec2 ind;\n"
"    float v,vn;\n"
"    dvoronoi(16.*uv, v, ind,vn);\n"
"    float r;\n"
"    rand(ind,r);\n"
"    d = (uv.y+.25)/.5-.2*r;\n"
"    palette(clamp(d,0.,1.),c1);\n"
"//     c1 = mix(c1, c.yyy, sm(abs(v)-.02));\n"
"    col = (.5+.5*r)*c.xxx;\n"
"    \n"
"    dhardcyber(uv, d);\n"
"    col = mix(col, .7*c.xxx, sm(d-.04));\n"
"    col = mix(col, c1, sm(d));\n"
"    col = mix(col, c.yyy, sm(abs(d-.01)-.01));\n"
"    col = mix(col, vec3(0.99,0.68,0.53), sm(abs(d-.005)-.005));\n"
"    col = mix(col, 1.2*vec3(0.99,0.68,0.53), sm(abs(d-.005)-.001));\n"
"    \n"
"    col = mix(col, c.yyy, sm(abs(v)-.02));\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    a = iResolution.x/iResolution.y;\n"
"    vec2 uv = (gl_FragCoord.xy-.5*iResolution)/iResolution.y,\n"
"        s;\n"
"    //uv.x *= 1.-.1*abs(sin(2.*pi*uv.y));\n"
"    vec3 col = c.xxx,\n"
"        o = c.yyx+.4*c.yzy,\n"
"        r = c.xyy,\n"
"        t = c.yyy, \n"
"        u = cross(normalize(t-o),-r),\n"
"        dir,\n"
"        n, \n"
"        x;\n"
"    int N = 650,\n"
"        i;\n"
"    t = uv.x * r + uv.y * u;\n"
"    dir = normalize(t-o);\n"
"\n"
"    vec3 c1;\n"
"    float d = -(o.z-.1)/dir.z;\n"
"    \n"
"    for(i = 0; i<N; ++i)\n"
"    {\n"
"     	x = o + d * dir;\n"
"        scene(x,s);\n"
"        if(s.x < 1.e-5)break;\n"
"        if(x.z<0.)\n"
"        {\n"
"            i = N;\n"
"            break;\n"
"        }\n"
"        d += s.x;\n"
"//         d += min(s.x,1.e-1);\n"
"        //d += s.x;\n"
"    }\n"
"    \n"
"    if(i < N)\n"
"    {\n"
"        vec3 l = x+c.yyx;\n"
"        normal(x,n, 2.e-6);\n"
"        colorize(x.xy, col);\n"
"        col = .1*col \n"
"            + .1*col*dot(l, n)\n"
"            + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);\n"
"    }\n"
"    \n"
"    col = 2.*col*col;\n"
"    \n"
"    gl_FragColor = vec4(clamp(col,0.,1.), 1.);\n"
"}\n"
"\0";
const char *starsky_source = "/* Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19\n"
" * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>\n"
" * \n"
" * This program is free software: you can redistribute it and/or modify\n"
" * it under the terms of the GNU General Public License as published by\n"
" * the Free Software Foundation, either version 3 of the License, or\n"
" * (at your option) any later version.\n"
" * \n"
" * This program is distributed in the hope that it will be useful,\n"
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" * GNU General Public License for more details.\n"
" * \n"
" * You should have received a copy of the GNU General Public License\n"
" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
" */\n"
" \n"
"#version 130\n\n"
"\n"
"uniform float iTime;\n"
"uniform vec2 iResolution;\n"
"\n"
"const float pi = acos(-1.);\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"float a = 1.0;\n"
"\n"
"void hash22(in vec2 x, out vec2 y);\n"
"void rand(in vec2 x, out float n);\n"
"void lfnoise(in vec2 t, out float n);\n"
"void mfnoise(in vec2 x, in float d, in float b, in float e, out float n);\n"
"void dvoronoi(in vec2 x, out float d, out vec2 z, out float dv);\n"
"float dspiral(vec2 x, float a, float d)\n"
"{\n"
"    float p = atan(x.y, x.x),\n"
"        n = floor((abs(length(x)-a*p)+d*p)/(2.*pi*a));\n"
"    p += (n*2.+1.)*pi;\n"
"    return -abs(length(x)-a*p)+d*p;\n"
"}\n"
"float sm(float d)\n"
"{\n"
"    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);\n"
"}\n"
"\n"
"void stroke(in float d0, in float s, out float d);\n"
"void colorize(in vec2 x, inout vec3 col)\n"
"{\n"
"    float v, n = 64., r, vn;\n"
"    vec2 ind;\n"
"    dvoronoi(n*x, v, ind, vn);\n"
"    rand(ind, r);\n"
"    vec2 y = x-ind/n;\n"
"    vec3 c1;\n"
"    rand(ind+1337., c1.x);\n"
"    rand(ind+2337., c1.y);\n"
"    rand(ind+3337., c1.z);\n"
"    c1 *= vec3(1.,.7,.3);\n"
"    c1 = .5+.5*c1;\n"
"    c1 *= vec3(.4,.6,1.);\n"
"    float d = length(y)-.002*r;\n"
"    if(r > .75)\n"
"        col = mix(col, c1, sm(d));\n"
"//     r *= cos(pi*x.y);\n"
"    if(r>.5)\n"
"    {\n"
"        col = mix(col, mix(col, 2.*c1, .8), sm(d-.004*r*r));\n"
"        col = mix(col, mix(col, 3.*c1, .4), sm(d-.01*r*r));\n"
"    }\n"
"    \n"
"    dvoronoi(2.*n*x, v, ind, vn);\n"
"    y = x-ind/n/2.;\n"
"    rand(ind, r);\n"
"    d = length(y)-.002*r;\n"
"    col = mix(col, c.xxx, sm(d));\n"
"    \n"
"    lfnoise(x.xy-v*v*v, d);\n"
"    col = mix(col, c.yyy, .5+.5*d);\n"
"    \n"
"    col = .6*col+.3*step(.8,col);\n"
"    col *= 2.;\n"
"    \n"
"    v = dspiral(x, .1,.01);\n"
"    col = mix(col, c.yyy, 1.-sm(v*6.e-3));\n"
"    col = mix(col, 2.5*col, sm(v*2.e-3));\n"
"}\n"
"\n"
"void dbox(in vec2 x, in vec2 b, out float d);\n"
"void street(in vec2 x, out vec3 col)\n"
"{\n"
"    float dx;\n"
"    lfnoise(x.y*c.xx, dx);\n"
"    x.x += .1*dx;\n"
"    \n"
"    col = .4*c.xxx;\n"
"    float da = mod(x.y, .1)-.05;\n"
"    dbox(vec2(x.x,da), vec2(.005,.025), da);\n"
"    col = mix(col, c.xxx, sm(da));\n"
"    col = mix(col, c.xxx, sm(abs(abs(x.x)-.1)-.01));\n"
"    \n"
"    float n;\n"
"    mfnoise(x.xy, mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),200., .35,n);\n"
"    col = mix(col, .5*col, .5+.5*n);\n"
"    \n"
"    col = mix(col, .6*c.xxx, abs(n)-.1);\n"
"    \n"
"    vec2 ind;\n"
"    float v, vn;\n"
"    dvoronoi(256.*x, v, ind, vn);\n"
"    ind = x-ind/256.;\n"
"    col = mix(col, .0*c.xxx, sm(length(ind)-.0001));\n"
"}\n"
"\n"
"void dbox3(in vec3 x, in vec3 b, out float d);\n"
"void add(in vec2 sda, in vec2 sdb, out vec2 sdf);\n"
"void scene(in vec3 x, out vec2 sdf)\n"
"{\n"
"    float dx;\n"
"    lfnoise(x.y*c.xx, dx);\n"
"    x.x += .1*dx;\n"
"\n"
"    sdf = c.xx;\n"
"    float n;\n"
"    mfnoise(x.xy, mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),2000., mix(.35,.45,smoothstep(.4,1.6,abs(x.x))),n);\n"
"    float n0 = n;\n"
"    n = .5+.5*n;\n"
"    n *= smoothstep(.1,.3,abs(x.x))+smoothstep(.4,1.2,abs(x.x));\n"
"    sdf.x = x.z-.1*n;\n"
"    sdf.y = 1.;\n"
"    \n"
"    float d;\n"
"    dbox3(x-c.yyx*.005*step(.1,abs(n0)-.01), vec3(.1,1.e3,.001+.01*n0), d);\n"
"    \n"
"    add(sdf, vec2(d, 2.), sdf);\n"
"}\n"
"\n"
"void normal(in vec3 x, out vec3 n, in float dx);\n"
"void palette(in float scale, out vec3 col)\n"
"{\n"
"    const int N = 5;\n"
"    const vec3 colors[N] = vec3[N](\n"
"            vec3(0.27,0.13,0.26),\n"
"            vec3(0.43,0.21,0.33),\n"
"            vec3(0.69,0.36,0.42),\n"
"            vec3(0.87,0.52,0.45),\n"
"            vec3(0.99,0.68,0.53)\n"
"// vec3(0.04,0.04,0.15),\n"
"// vec3(0.18,0.32,0.46),\n"
"// vec3(0.66,0.43,0.62),\n"
"// vec3(0.96,0.78,0.88),\n"
"// vec3(0.40,0.00,0.18)\n"
"    );\n"
"	float index = floor(scale*float(N)), \n"
"        remainder = scale*float(N)-index;\n"
"    col = mix(colors[int(index)],colors[int(index)+1], remainder);\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    a = iResolution.x/iResolution.y;\n"
"    vec2 uv = (gl_FragCoord.xy-.5*iResolution)/iResolution.y,\n"
"        s;\n"
"\n"
"        vec3 col = c.yyy,\n"
"        o = .3*c.yyx+c.yzy,\n"
"        r = c.xyy,\n"
"        t = c.yyy, \n"
"        u = cross(normalize(t-o),-r),\n"
"        dir,\n"
"        n, \n"
"        x;\n"
"    int N = 250,\n"
"        i;\n"
"    t = uv.x * r + uv.y * u;\n"
"    dir = normalize(t-o);\n"
"\n"
"    vec3 c1;\n"
"    float d = -(o.z-.2)/dir.z;\n"
"    \n"
"    for(i = 0; i<N; ++i)\n"
"    {\n"
"     	x = o + d * dir;\n"
"        scene(x,s);\n"
"        if(s.x < 1.e-5)break;\n"
"        if(x.z<0.)\n"
"        {\n"
"            i = N;\n"
"            break;\n"
"        }\n"
"        d += s.x;\n"
"//         d += min(s.x,1.e-1);\n"
"        //d += s.x;\n"
"    }\n"
"    \n"
"    if(i < N)\n"
"    {\n"
"        vec3 l = c.yyx;\n"
"        normal(x,n, 2.e-6);\n"
"        \n"
"        if(s.y == 1.)\n"
"        {\n"
"            palette(x.z/.22, col);\n"
"//             float na;\n"
"//             mfnoise(x.xy, mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),2000., mix(.35,.45,smoothstep(.4,1.6,abs(x.x))),na);\n"
"//             col = mix(col, 2.*col, abs(abs(na)-.1)-.001);\n"
"            col = .1*col \n"
"                + .1*col*dot(l, n)\n"
"                + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);\n"
"        }\n"
"        else if(s.y == 2.)\n"
"        {\n"
"            street(x.xy, col);\n"
"            col = .1*col \n"
"                + .1*col*dot(l, n)\n"
"                + .6*col*pow(abs(dot(reflect(-l,n),dir)),2.);\n"
"        }\n"
"        else \n"
"        {\n"
"            colorize(x.xy, col);\n"
"            col = .1*col \n"
"                + .1*col*dot(l, n)\n"
"                + .8*col*pow(abs(dot(reflect(-l,n),dir)),2.);\n"
"        }\n"
"        if(x.z>.05)\n"
"            col = mix(col, 3.*col, smoothstep(.95,.951, n.z));\n"
"    }\n"
"\n"
"    col = 12.*col*col;\n"
"    \n"
"    col = mix(col, c.yyy, tanh(2.e-1*d));\n"
"    \n"
"    vec3 c2;\n"
"    colorize(4.*uv, c2);\n"
"    col = mix(col, 2.*c2, smoothstep(.3,.5, uv.y));\n"
"    \n"
"    gl_FragColor = vec4(clamp(col,0.,1.), 1.);\n"
"}\n"
"\0";
const char *text_source = "/* Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19\n"
" * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>\n"
" * \n"
" * This program is free software: you can redistribute it and/or modify\n"
" * it under the terms of the GNU General Public License as published by\n"
" * the Free Software Foundation, either version 3 of the License, or\n"
" * (at your option) any later version.\n"
" * \n"
" * This program is distributed in the hope that it will be useful,\n"
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" * GNU General Public License for more details.\n"
" * \n"
" * You should have received a copy of the GNU General Public License\n"
" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
" */\n"
" \n"
"#version 130\n\n"
"\n"
"uniform float iFontWidth, iTime;\n"
"uniform vec2 iResolution;\n"
"uniform sampler2D iChannel0, iFont;\n"
"uniform float iFSAA;\n"
"\n"
"out vec4 gl_FragColor;\n"
"\n"
"// Global constants\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"const float pi = acos(-1.);\n"
"float a; // Aspect ratio\n"
"\n"
"void rand(in vec2 x, out float num);\n"
"void lfnoise(in vec2 t, out float num);\n"
"void rshort(in float off, out float val);\n"
"void rfloat(in float off, out float val);\n"
"void dbox(in vec2 x, in vec2 b, out float dst);\n"
"void dcircle(in vec2 x, out float d);\n"
"void dlinesegment(in vec2 x, in vec2 p1, in vec2 p2, out float d);\n"
"void drhomboid(in vec2 x, in vec2 b, in float tilt, out float dst);\n"
"void dcirclesegment(in vec2 x, in float r, in float p0, in float p1, out float d);\n"
"void stroke(in float d0, in float s, out float d);\n"
"void dglyph(in vec2 x, in float ordinal, in float size, out float dst);\n"
"void dstring(in vec2 x, in float ordinal, in float size, out float dst);\n"
"void dfloat(in vec2 x, in float num, in float size, out float dst);\n"
"void smoothmin(in float a, in float b, in float k, out float dst);\n"
"void dint(in vec2 x, in float num, in float size, in float ndigits, out float dst);\n"
"void dtime(in vec2 x, in float num, in float size, out float dst);\n"
"\n"
"// Fixme: remove vec4 technique in favor of separate distance\n"
"// void blendadd(in vec4 src1, in vec4 src2, in float tlo, in float thi, out vec4 dst)\n"
"// {\n"
"//     vec4 added;\n"
"//     add(src1, src2, added);\n"
"//     dst = mix(src1, added, smoothstep(tlo-.5,tlo+.5,iTime)*(1.-smoothstep(thi-.5,thi+.5,iTime)));\n"
"// }\n"
"\n"
"void window(in vec2 x, in vec2 size, in vec3 bg, in float title_index, out vec4 col);\n"
"void progressbar(in vec2 x, in float width, in float progress, out vec4 col);\n"
"\n"
"float sm(float d)\n"
"{\n"
"    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);\n"
"}\n"
"\n"
"void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);\n"
"void colorize(in vec2 x, out vec3 col)\n"
"{\n"
"    vec3 c1;\n"
"    vec2 ind,\n"
"        xv,\n"
"        xi;\n"
"    float d,\n"
"        vs = 16.,\n"
"        n,\n"
"        size = .1,\n"
"        xix = mod(x.x, size)-.5*size,\n"
"        xixj = (x.x - xix),\n"
"        ri,\n"
"        rim1,\n"
"        rip1,\n"
"        lines = 8.,\n"
"        da,\n"
"        op,\n"
"        s;\n"
"    \n"
"    // Background blending\n"
"    s = smoothstep(0.,.5,.5-abs(x.y));\n"
"    col = mix(1.e-4*c.xxx, vec3(0.04,0.18,0.24), s);\n"
"    \n"
"    // Background circles\n"
"    float vn;\n"
"    dvoronoi(vs*x, d, ind, vn);\n"
"    xv = ind/vs-x;\n"
"    lfnoise(vec2(3.,33.)*ind/vs-3.*iTime*c.xy,n);\n"
"    n = .5+.5*n;\n"
"    d = length(xv)-mix(.0,.35,n)/vs;\n"
"    col = mix(col, n*.5*vec3(1.00,0.40,0.39), sm(d));\n"
"    d = abs(d-.005) -.002;\n"
"    col = mix(col, (1.-n)*vec3(0.49,0.71,0.78), sm(d));\n"
"    \n"
"    for(float i = 1.; i < 9.; i += 1.)\n"
"    {\n"
"        rand((9.-i)*c.xx, op);\n"
"        op = .5+.5*round(16.*op)/16.;\n"
"        x += -.1+.2*op;\n"
"        \n"
"        xix = mod(x.x, size)-.5*size;\n"
"        xixj = (x.x - xix);\n"
"        \n"
"        // Edges\n"
"        lfnoise(2.e0*xixj*c.xx+14.*i, ri);\n"
"        lfnoise(2.e0*(xixj+size)*c.xx+14.*i, rip1);\n"
"        lfnoise(2.e0*(xixj-size)*c.xx+14.*i, rim1);\n"
"\n"
"        float h = .2;\n"
"        \n"
"        ri = h*round(lines*ri)/lines;\n"
"        rip1 = h*round(lines*rip1)/lines;\n"
"        rim1 = h*round(lines*rim1)/lines;\n"
"\n"
"        //if(ri < 0.)\n"
"        {\n"
"            dlinesegment(vec2(xix, x.y), vec2(-.5*size, mix(ri,rim1,.5)), vec2(-.25*size, ri), d);\n"
"            dlinesegment(vec2(xix, x.y), vec2(-.25*size, ri), vec2(.25*size, ri), da);\n"
"            d = min(d, da);\n"
"            dlinesegment(vec2(xix, x.y), vec2(.25*size, ri), vec2(.5*size, mix(ri,rip1,.5)), da);\n"
"            d = min(d, da);\n"
"            stroke(d, .002+.002*op, d);\n"
"            col = mix(col, op*(1.-n)*vec3(1.00,0.40,0.39), sm(d));\n"
"\n"
"            // Dots\n"
"            lfnoise(8.*xixj*c.xx-3.*iTime*c.xy+14.*i, n);\n"
"            n = .5+.5*n;\n"
"            d = length(vec2(xix, x.y-ri))-mix(.0,.35,n)/vs;\n"
"            c1 = mix(vec3(1.00,0.40,0.39), vec3(0.85,0.87,0.89), n);\n"
"            col = mix(col, op*(1.-n)*c1, sm(d));\n"
"            stroke(d - .009, (1.-n)*.005, d);\n"
"            c1 *= 2.4;\n"
"            col = mix(col, op*(1.-n)*c1, sm(d));\n"
"        }\n"
"        \n"
"        x -= -.1+.2*op;\n"
"    }\n"
"    \n"
"    //mix to blackish\n"
"    lfnoise(3.*x.xy-vec2(1.,.1)*iTime, n);\n"
"    stroke(n, .3, n);\n"
"    col = mix(col, 1.e-4*c.xxx, n);\n"
"    col = mix(col, .1*col, 1.-s);\n"
"    \n"
"    col = mix(col, mix(col, vec3(1.00,0.40,0.39), mix(.4,.8,.5+.5*x.y/.1)), sm(abs(x.y)-.1));\n"
"    col = mix(col, c.xxx, sm(abs(abs(x.y)-.11)-.001));\n"
"    \n"
"    col = mix(col, col*col, clamp(-x.y/.1,0.,1.));\n"
"    col *= col;\n"
"}\n"
"\n"
"void mainImage( out vec4 fragColor, in vec2 fragCoord )\n"
"{\n"
"    a = iResolution.x/iResolution.y;\n"
"    vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);\n"
"    \n"
"    float d;\n"
"\n"
"    vec4 old = c.yyyy, \n"
"        new = c.yyyy;\n"
"    \n"
"    float bound = sqrt(iFSAA)-1.;\n"
"\n"
"    for(float i = -.5*bound; i<=.5*bound; i+=1.)\n"
"        for(float j=-.5*bound; j<=.5*bound; j+=1.)\n"
"        {\n"
"            old.gba += texture(iChannel0, (fragCoord+vec2(i,j)*3./max(bound, 1.))/iResolution.xy).xyz;\n"
"        }\n"
"    old.gba /= iFSAA;\n"
"    \n"
"    new = old;\n"
"    \n"
"//     if(uv.y < -.3 && iTime > 12.)\n"
"//     {\n"
"//         // Add overlay\n"
"//         colorize(2.*(c.xz*uv-.45*vec2(-a,1.)-12.*c.xy), new.gba);\n"
"//         new.gba = mix(old.gba, mix(old.gba, new.gba,.4), smoothstep(3.e-2, 5.e-2,length(new.gba)));\n"
"//     }\n"
"    \n"
"    if(uv.y > .4)\n"
"    {\n"
"        float da;\n"
"        dstring((uv-.45*vec2(-.55*a,1.+4.*.008)), 9., .004, d);\n"
"        dstring((uv-.45*vec2(-.55*a,1.+2.*.008)), 10., .004, da);\n"
"        d = min(d,da);\n"
"        dstring((uv-.45*vec2(-.55*a,1.)), 11., .004, da);\n"
"        d = min(d,da);\n"
"        dstring((uv-.45*vec2(-.55*a,1.-2.*.008)), 12., .004, da);\n"
"        d = min(d,da);\n"
"        dstring((uv-.45*vec2(-.55*a,1.-4.*.008)), 13., .004, da);\n"
"        d = min(d,da);\n"
"        new.gba = mix(new.gba, mix(new.gba, c.xxx, .5), sm(d));\n"
"        \n"
"        // Add Static text\n"
"        dstring((uv-.45*vec2(-.85*a,1.)), 3., .02, d); // Team210\n"
"        \n"
"        stroke(d-.002, .001, d);\n"
"        new.gba = mix(new.gba, vec3(1.00,0.40,0.39), sm(d));\n"
"\n"
"        // Add time overlay\n"
"        dtime((uv-.45*vec2(.975*a,1.05)), iTime+11., .01, d);\n"
"        new.gba = mix(new.gba, c.xxx, sm(d));\n"
"        \n"
"        // Add exact millisecond\n"
"        dint(uv-.45*vec2(.975*a,1.0), floor(1.e3*fract(iTime)), .01, 4., d);\n"
"//         new.gba = mix(new.gba, vec3(1.00,0.40,0.39), sm(d));\n"
"        stroke(d-.001, .0005, d);\n"
"        new.gba = mix(new.gba, c.xxx, sm(d));\n"
"    }\n"
"    \n"
"    if(iTime < 0.) \n"
"    {\n"
"        new.gba = old.gba;\n"
"        \n"
"        float sc = smoothstep(0.,1.,clamp(iTime+3.,0.,1.))*(1.-smoothstep(0.,1.,clamp(iTime+1.,0.,1.)));\n"
"        \n"
"        dstring((uv-vec2(-.085,-.3)), 3., .02, d); // Team210\n"
"        float da;\n"
"        dstring((uv-vec2(-.08,-.35)), 26., .02, da); // present\n"
"        d = min(d,da);\n"
"\n"
"        new.gba = mix(new.gba, mix(new.gba,c.yyy,sc), sm(d));\n"
"    }\n"
"    else if(iTime < 6.)\n"
"    {\n"
"        vec2 dx = (.25*a+.3*c.xy)*c.xy;\n"
"        if(iTime < 3.)\n"
"        {\n"
"            float ind = mix(100000., 2., clamp(iTime/3.,0.,1)), da;\n"
"            dint(uv+dx*c.xy, ind, .02, 6., d);\n"
"            \n"
"            dstring(uv+dx-2.*9.*.02*c.xy, 4., .02, da);\n"
"            d = min(d, da);\n"
"        }\n"
"        else if(iTime < 4.)\n"
"        {\n"
"            dint(uv+dx, 2., .02, 6., d);\n"
"            \n"
"            float da;\n"
"            dstring(uv+dx-2.*9.*.02*c.xy, 4., .02, da);\n"
"            d = min(d, da);\n"
"        }\n"
"        else if(iTime < 5.)\n"
"        {\n"
"            dint(uv+dx+.04*c.yx, 1., .02, 6., d);\n"
"         \n"
"            float da;\n"
"            dint(uv+dx, 2., .02, 6., da);\n"
"            d = min(d, da);\n"
"            \n"
"            dstring(uv+dx-2.*9.*.02*c.xy+.04*c.yx, 4., .02, da);\n"
"            d = min(d, da);\n"
"        }\n"
"        else if(iTime < 6.)\n"
"        {\n"
"            dint(uv+dx+.08*c.yx, 0., .02, 6., d);\n"
"            \n"
"            float da;\n"
"            dint(uv+dx+.04*c.yx, 1., .02, 6., da);\n"
"            d = min(d, da);\n"
"            \n"
"            dint(uv+dx, 2., .02, 6., da);\n"
"            d = min(d, da);\n"
"            \n"
"            dstring(uv+dx-2.*9.*.02*c.xy+.08*c.yx, 4., .02, da);\n"
"            d = min(d, da);\n"
"        }\n"
"        \n"
"            \n"
"        new.gba = mix(new.gba, mix(new.gba, vec3(1.00,0.87,0.57), .7), sm(d));\n"
"        stroke(d-.002, .001, d);\n"
"        new.gba = mix(new.gba, c.xxx, sm(d));\n"
"    }\n"
"    \n"
"    else if(iTime < 12. && iTime > 7.)\n"
"    {\n"
"        // EVK\n"
"        float da, db;\n"
"        dbox(vec2(uv.x+.75,uv.y-.35), vec2(.013,.035), da);\n"
"        stroke(da, .002, da);\n"
"        \n"
"        // E\n"
"        dglyph(vec2(uv.x+.75,uv.y-.35-.02).yx*c.zx, 101., .01, db);\n"
"        da = min(da, db);\n"
"        \n"
"        // V\n"
"        dglyph(vec2(uv.x+.75,uv.y-.35), 118., .01, db);\n"
"        da = min(da, db);\n"
"        \n"
"        // K\n"
"        dglyph(vec2(uv.x+.75,uv.y-.35+.02).yx*c.zx, 107., .01, db);\n"
"        da = min(da, db);\n"
"        \n"
"        // 333 block\n"
"        vec2 b = vec2(uv.x+.75,uv.y-.35+.02)-.01*c.xx-.02*c.xy,\n"
"            b1 = mod(b, .02)-.01,\n"
"            b1i = floor((b-b1)/.02);\n"
"        \n"
"        if(abs(b1i.y) <= 1. && b1i.x >= 0. && b1i.x <= 10.)\n"
"        {\n"
"            // random letter\n"
"            lfnoise(b1i-12.*iTime, db);\n"
"            db = 97.+mod(floor(26.*(.5+.5*db)),26.);\n"
"            dglyph(b1, db, .008, db);\n"
"            da = min(da, db);\n"
"        }\n"
"        \n"
"        dlinesegment(vec2(uv.x+.75,uv.y-.35+.06), -.015*c.xy, .25*c.xy, db);\n"
"        stroke(db, .001, db);\n"
"        da = min(da, db);\n"
"        \n"
"        // No more partycoding this time\n"
"        dstring(vec2(uv.x+.75,uv.y+.35), 5., .015, db);\n"
"        da = min(da, db);\n"
"        \n"
"        // Yeah. sure.\n"
"        dstring(vec2(uv.x-.2,uv.y+.35), 6., .015, db);\n"
"        float dc;\n"
"        dbox(vec2(uv.x-.2-.12,uv.y+.35), vec2(.165, .015), dc);\n"
"        db = max(dc,-db);\n"
"        da = min(da, db);\n"
"        \n"
"        // well, that worked.\n"
"        dstring(vec2(uv.x+.75,uv.y+.4),7., .015, db);\n"
"        da = min(da, db);\n"
"        \n"
"        // not\n"
"        dstring(vec2(uv.x-.2,uv.y+.4), 8., .015, db);\n"
"        dbox(vec2(uv.x-.2-.12,uv.y+.4), vec2(.165, .015), dc);\n"
"        db = max(dc,-db);\n"
"        da = min(da, db);\n"
"        \n"
"        \n"
"        new.gba = mix(new.gba, vec3(0.75,0.24,0.30), sm(da));\n"
"    }\n"
"    else if(iTime < 28.)\n"
"    {\n"
"        float da = length(uv)-.45, db;\n"
"        \n"
"        // Lightcyber\n"
"        dstring((uv+.3*c.xy), 2., .0415, db);\n"
"        db -= .001;\n"
"        da = max(da, -db);\n"
"        da = mix(1., da, smoothstep(0.,.5,clamp(iTime-18.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-22.,0.,1.))));\n"
"        new.gba = mix(new.gba, vec3(1.00,0.40,0.39), sm(da));\n"
"        \n"
"        // Team210\n"
"        da = length(uv - .3*c.xx)-.2, db;\n"
"        dstring(2.*(uv+.075*c.xy-.3*c.xx), 3., .0415, db);\n"
"        db -= .001;\n"
"//         da = max(da, -db);\n"
"        da = mix(1., da, smoothstep(0.,.5,clamp(iTime-19.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-22.,0.,1.))));\n"
"        db = mix(1., db, smoothstep(0.,.5,clamp(iTime-19.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-22.,0.,1.))));\n"
"        new.gba = mix(new.gba, vec3(1.00,0.40,0.39)*vec3(1.00,0.40,0.39), sm(da));\n"
"        new.gba = mix(new.gba, c.yyy, sm(db));\n"
"        \n"
"        // Graffiti tricks.\n"
"        dstring((uv-vec2(-.75,-.35)).yx*c.xz, 18., .045, db);\n"
"        dstring((uv-vec2(-.65,-.35)).yx*c.xz, 19., .045, da);\n"
"        db = min(db,da);\n"
"        db = mix(1., db, smoothstep(0.,.5,clamp(iTime-24.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-28.,0.,1.))));\n"
"        new.gba = mix(new.gba, mix(new.gba, c.xxx, .8), sm(db));\n"
"        \n"
"        stroke(db-.005, .0005, db);\n"
"        new.gba = mix(new.gba, mix(new.gba, vec3(1.00,0.40,0.39), .8), sm(db));\n"
"        \n"
"        // Nice!\n"
"        da = length((uv-vec2(-.6,-.325)).yx*c.xz)-.1;\n"
"        dstring((uv-vec2(-.6,-.35)).yx*c.xz, 20., .015, db);\n"
"        da = max(da, -db);\n"
"        da = mix(1., da, smoothstep(0.,.5,clamp(iTime-25.5, 0., 1.))*(1.-smoothstep(0.,.5,clamp(iTime-28.,0.,1.))));\n"
"        new.gba = mix(new.gba, mix(new.gba, c.xxx, .6), sm(da));\n"
"    }\n"
"    else if(iTime < 44.)\n"
"    {\n"
"        float da, db;\n"
"        \n"
"        // Once\n"
"        dstring((uv-vec2(-.3,.3)), 21., .1, da);\n"
"        \n"
"        db = abs(mod(uv.x+uv.y,.3)-.15)-.075;\n"
"        vec3 c1 = mix(mix(new.gba,.3*c.xxx,.5), c.xxx, sm(db));\n"
"        \n"
"        db = smoothstep(33.,34.,iTime);\n"
"        da = mix(1., da, db);\n"
"        new.gba = mix(new.gba, c1, sm(da));\n"
"        \n"
"        stroke(da-.02,.001,da);\n"
"        new.gba = mix(new.gba, c.xxx, sm(da));\n"
"        \n"
"        // You\n"
"        dstring(uv-vec2(.35,.34), 22., .05, da);\n"
"        \n"
"        dbox(uv-vec2(.35,.34), vec2(.15,.06), db);\n"
"        db = max(db,-da);\n"
"        float mx = smoothstep(34.,35., iTime);\n"
"        db = mix(1., db, mx);\n"
"        new.gba = mix(new.gba, c.xxx, sm(db));\n"
"        \n"
"        // Offend\n"
"        dstring(uv-vec2(.25,.24), 23., .0277, da);\n"
"        mx = smoothstep(35.,36.,iTime);\n"
"        da = mix(1., da, mx);\n"
"        new.gba = mix(new.gba, .8*c.xxy, sm(da));\n"
"        \n"
"        // You\n"
"        dstring(uv-vec2(.25,.15), 22., .05, da);\n"
"        mx = smoothstep(36.,37.,iTime);\n"
"        da = mix(1., da, mx);\n"
"        new.gba = mix(new.gba, .8*c.xxy, sm(da));\n"
"        \n"
"        // Cannot\n"
"        dstring((uv-vec2(.45,.05)).yx*c.zx, 24., .05, da);\n"
"        \n"
"        dbox((uv-vec2(.45,-.1)), vec2(.05,.3), db);\n"
"        db = max(db,-da);\n"
"        mx = smoothstep(37.,38., iTime);\n"
"        db = mix(1., db, mx);\n"
"        new.gba = mix(new.gba, c.xxx, sm(db));\n"
"\n"
"        // Stop\n"
"        dstring((uv-vec2(.6,.1)).yx*c.zx, 25., .1, da);\n"
"        \n"
"        db = smoothstep(38.,39.,iTime);\n"
"        da = mix(1., da, db);\n"
"        new.gba = mix(new.gba, c1, sm(da));\n"
"        \n"
"        stroke(da-.02,.001,da);\n"
"        new.gba = mix(new.gba, c.xxx, sm(da));\n"
"    }\n"
"    else if(iTime < 60.)\n"
"    {\n"
"        //vec3(0.93,0.36,0.44)\n"
"        float da, db;\n"
"        \n"
"        db = abs(mod(uv.x+uv.y,.3)-.15)-.075;\n"
"        vec3 c1 = mix(mix(new.gba,vec3(0.93,0.36,0.44),.5), c.xxx, sm(db));\n"
"        \n"
"        // Banging your head against \n"
"        dstring((uv-vec2(-.3,.3)), 38., .02, da);\n"
"        \n"
"        db = smoothstep(45.,46.,iTime)-smoothstep(50.,51.,iTime);\n"
"        da = mix(1., da, db);\n"
"        stroke(da-.005,.0025,db);\n"
"        new.gba = mix(new.gba, c.yyy, sm(db));\n"
"        \n"
"        new.gba = mix(new.gba, c1, sm(da-.0025));\n"
"        \n"
"        db = da+.0025;\n"
"        new.gba = mix(new.gba,2.*c1, sm(db));\n"
"        \n"
"        // a wall for one hour burns \n"
"        dstring((uv-vec2(-.3,.25)), 39., .02, da);\n"
"        \n"
"        db = smoothstep(46.,47.,iTime)-smoothstep(51.,52.,iTime);\n"
"        da = mix(1., da, db);\n"
"        stroke(da-.005,.0025,db);\n"
"        new.gba = mix(new.gba,c.yyy, sm(db));\n"
"        \n"
"        new.gba = mix(new.gba, c1, sm(da-.0025));\n"
"        \n"
"        db = da+.0025;\n"
"        new.gba = mix(new.gba,2.*c1, sm(db));\n"
"        \n"
"        // 150 kilocalories. Want to\n"
"        dstring((uv-vec2(-.3,.2)), 40., .02, da);\n"
"        \n"
"        db = smoothstep(47.,48.,iTime)-smoothstep(52.,53.,iTime);\n"
"        da = mix(1., da, db);\n"
"        stroke(da-.005,.0025,db);\n"
"        new.gba = mix(new.gba,c.yyy, sm(db));\n"
"        \n"
"        new.gba = mix(new.gba, c1, sm(da-.0025));\n"
"        \n"
"        db = da+.0025;\n"
"        new.gba = mix(new.gba, 2.*c1, sm(db));\n"
"        \n"
"        // start losing some weight?\n"
"        dstring((uv-vec2(-.3,.15)), 41., .02, da);\n"
"        \n"
"        db = smoothstep(48.,49.,iTime)-smoothstep(53.,54.,iTime);\n"
"        da = mix(1., da, db);\n"
"        stroke(da-.005,.0025,db);\n"
"        new.gba = mix(new.gba, c.yyy, sm(db));\n"
"        \n"
"        new.gba = mix(new.gba, c1, sm(da-.0025));\n"
"        \n"
"        db = da+.0025;\n"
"        new.gba = mix(new.gba, 2.*c1, sm(db));\n"
"        \n"
"        new.gba = clamp(new.gba,0.,1.);\n"
"    }\n"
"    else if(iTime < 130.)\n"
"    {\n"
"        float da, db;\n"
"        \n"
"        dbox(uv-vec2(.05,.3), vec2(1.6,.055), da);\n"
"        da = mix(1.,da,smoothstep(125.,126.,iTime));\n"
"        new.gba = mix(new.gba, mix(new.gba,c.xxx,.5), sm(da));\n"
"        \n"
"        // Wait, what?\n"
"        dstring((uv-vec2(-.4,.3)), 28., .05, da);\n"
"        \n"
"        lfnoise(55.*uv, db);\n"
"        stroke(db,0.535,db);\n"
"        vec3 c1 = mix(mix(new.gba,c.yyy,.3), c.yyy, sm(db/50.));\n"
"        \n"
"        db = smoothstep(125.,126.,iTime);\n"
"        da = mix(1., da, db);\n"
"        new.gba = mix(new.gba, c1, sm(da));\n"
"        \n"
"        stroke(da-.01,.001,da);\n"
"        new.gba = mix(new.gba, c.yyy, sm(da));\n"
"    }\n"
"    else\n"
"    {\n"
"        float da;\n"
"        dstring(uv-vec2(-.55,0.), 27., .025, da);\n"
"        da = mix(1., da, smoothstep(172.,172.5,iTime));\n"
"        new.gba = mix(new.gba, c.yyy, smoothstep(172.,172.5,iTime));\n"
"        new.gba = mix(new.gba, vec3(.9,.2,.03), sm(da));\n"
"        stroke(da-.005, .001, da);\n"
"        new.gba = mix(new.gba, c.xxx, sm(da));\n"
"    }\n"
"    \n"
"    //FIXME: remove debug lines\n"
"//     vec2 ad = abs(mod(uv-.05,.02)-.01)-.001;\n"
"//     new.gba = mix(new.gba, c.yyx, sm(min(ad.x,ad.y)));\n"
"//     \n"
"//     ad = abs(mod(uv-.05,.1)-.05)-.001;\n"
"//     new.gba = mix(new.gba, c.yxy, sm(min(ad.x,ad.y)));\n"
"//     \n"
"//     ad = abs(uv)-.002;\n"
"//     new.gba = mix(new.gba, c.xxx, sm(min(ad.x,ad.y)));\n"
"    //FIXME remove until here\n"
"    \n"
"    \n"
"    // \n"
"    float dc;\n"
"    dbox(uv, .5*vec2(a,1.), dc);\n"
"    stroke(dc, .005, dc);\n"
"    new.gba = mix(new.gba, c.yyy, sm(dc));\n"
"    \n"
"    fragColor = vec4(new.gba, 1.);\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    mainImage(gl_FragColor, gl_FragCoord.xy);\n"
"}\n"
"\0";
const char *post_source = "/* Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19\n"
" * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>\n"
" * \n"
" * This program is free software: you can redistribute it and/or modify\n"
" * it under the terms of the GNU General Public License as published by\n"
" * the Free Software Foundation, either version 3 of the License, or\n"
" * (at your option) any later version.\n"
" * \n"
" * This program is distributed in the hope that it will be useful,\n"
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" * GNU General Public License for more details.\n"
" * \n"
" * You should have received a copy of the GNU General Public License\n"
" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
" */\n"
" \n"
"#version 130\n\n"
"\n"
"uniform float iFSAA;\n"
"uniform vec2 iResolution;\n"
"uniform sampler2D iChannel0;\n"
"uniform float iTime;\n"
"\n"
"out vec4 gl_FragColor;\n"
"\n"
"const float pi = acos(-1.);\n"
"const vec3 c = vec3(1.,0.,-1.);\n"
"float a = 1.0;\n"
"\n"
"float lscale, rscale;\n"
"float size;\n"
"\n"
"float nbeats;\n"
"float iScale;\n"
"\n"
"\n"
"void rand(in vec2 x, out float n);\n"
"void lfnoise(in vec2 t, out float n);\n"
"void stroke(in float d0, in float s, out float d);\n"
"void dvoronoi(in vec2 x, out float d, out vec2 p, out float control_distance);\n"
"void hash22(in vec2 x, out vec2 y);\n"
"float sm(float d)\n"
"{\n"
"    return smoothstep(1.5/iResolution.y, -1.5/iResolution.y, d);\n"
"}\n"
"\n"
"float dot2( in vec3 v ) { return dot(v,v); }\n"
"\n"
"// Adapted from https://www.shadertoy.com/view/4sXXRN\n"
"void dtriangle3(in vec3 p,  in vec3 v1, in vec3 v2, in vec3 v3, out float dst)\n"
"{\n"
"    vec3 v21 = v2 - v1; vec3 p1 = p - v1;\n"
"    vec3 v32 = v3 - v2; vec3 p2 = p - v2;\n"
"    vec3 v13 = v1 - v3; vec3 p3 = p - v3;\n"
"    vec3 nor = cross( v21, v13 );\n"
"\n"
"    dst = sqrt( (sign(dot(cross(v21,nor),p1)) + \n"
"                  sign(dot(cross(v32,nor),p2)) + \n"
"                  sign(dot(cross(v13,nor),p3))<2.0) \n"
"                  ?\n"
"                  min( min( \n"
"                  dot2(v21*clamp(dot(v21,p1)/dot2(v21),0.0,1.0)-p1), \n"
"                  dot2(v32*clamp(dot(v32,p2)/dot2(v32),0.0,1.0)-p2) ), \n"
"                  dot2(v13*clamp(dot(v13,p3)/dot2(v13),0.0,1.0)-p3) )\n"
"                  :\n"
"                  dot(nor,p1)*dot(nor,p1)/dot2(nor) );\n"
"}\n"
"\n"
"void rot3(in vec3 p, out mat3 rot);\n"
"void dbox3(in vec3 x, in vec3 b, out float d);\n"
"void add(in vec2 sda, in vec2 sdb, out vec2 sdf);\n"
"mat3 R;\n"
"void scene(in vec3 x, out vec2 sdf)\n"
"{\n"
"    float d;\n"
"    \n"
"	// Big red box    \n"
"    dbox3(x, .2*c.xxx, sdf.x);\n"
"    sdf.y = 1.;\n"
"    \n"
"    // Holes\n"
"    \n"
"    // 2 upper bar\n"
"    dbox3(x-.1*c.xyy, vec3(.02,.3,.12), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 2 right bar\n"
"    dbox3(x-.05*c.xyy-.1*c.yyx, vec3(.07,.3,.02), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 2 mid bar\n"
"    dbox3(x, vec3(.02,.3,.1), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 2 left bar\n"
"    dbox3(x+.05*c.xyy+.1*c.yyx, vec3(.07,.3,.02), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 2 dot\n"
"    dbox3(x+.1*c.xyy-.1*c.yyx, vec3(.02,.3,.02), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 1 bar\n"
"    dbox3(x+.04*c.yyx, vec3(.3,.02,.08), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 1 dot\n"
"    dbox3(x-.1*c.yyx, vec3(.3,.02,.02), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"    \n"
"    // 0 big stripes\n"
"    vec3 y = vec3(x.x, abs(x.y), x.z);\n"
"    dbox3(y-.05*c.yxy, vec3(.1,.03,.3), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"\n"
"	// 0 small stripes\n"
"    dbox3(y-.1*c.yxy-.06*c.xyy, vec3(.08,.021,.3), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"\n"
"    // 0 upper/lower stripes\n"
"    vec3 z = vec3(abs(x.x), x.yz);\n"
"	dbox3(z-.119*c.xyy, vec3(.021,.08,.3), d);\n"
"    sdf.x = max(-d, sdf.x);\n"
"    sdf.y = mix(sdf.y, 2., step(d, sdf.x));\n"
"}\n"
"\n"
"void scene2(in vec3 x, out vec2 sdf)\n"
"{\n"
"    float v = 0., vn;\n"
"    vec2 vi = c.yy;\n"
"    dvoronoi(x.xy/size, v, vi, vn);\n"
"    vec3 y = vec3(x.xy-vi*size, x.z);\n"
"    vec2 yi = vi*size;\n"
"    \n"
"    float n = 0.;\n"
"    lfnoise(4.*(yi-.5*iTime), n);\n"
"    lfnoise(12.*vec2(n,1.)*yi-(.8+.2*n)*c.xy, n);\n"
"    n *= iScale;\n"
"    //sdf = vec2(length(y-.05*n*c.yyx)-.5*size, 1.);\n"
"    sdf = vec2(length(y-.05*n*c.yyx)-mix(.05,1.,length(texture(iChannel0, yi/vec2(a,1.)).rgb)/sqrt(3.))*size, 1.);\n"
"}\n"
"\n"
"void normal2(in vec3 x, out vec3 n, in float dx)\n"
"{\n"
"    vec2 s, na;\n"
"    \n"
"    scene2(x,s);\n"
"    scene2(x+dx*c.xyy, na);\n"
"    n.x = na.x;\n"
"    scene2(x+dx*c.yxy, na);\n"
"    n.y = na.x;\n"
"    scene2(x+dx*c.yyx, na);\n"
"    n.z = na.x;\n"
"    n = normalize(n-s.x);\n"
"}\n"
"\n"
"void scene3(in vec3 x, out vec2 sdf)\n"
"{\n"
"    vec3 y = vec3(mod(x.xy,2.*size)-size, x.z);\n"
"    vec2 yi = x.xy-y.xy;\n"
"    float ss = mix(.0,.05,size/.01);\n"
"    \n"
"    vec2 p0 = .8*size*c.xx,\n"
"        p1 = .8*size*c.zx,\n"
"        p2 = .8*size*c.xz;\n"
"    \n"
"    vec2 ind;\n"
"    \n"
"    float y0, y1, y2;\n"
"    lfnoise(4.e1*(yi+p0-.5e-4*iTime), y0);\n"
"    lfnoise(12.e1*vec2(y0,1.)*(yi+p0)-1.e-4*(.8+.2*y0)*iTime*c.xy, y0);\n"
"    lfnoise(4.e1*(yi+p1-.5e-4*iTime), y1);\n"
"    lfnoise(12.e1*vec2(y1,1.)*(yi+p1)-1.e-4*(.8+.2*y1)*iTime*c.xy, y1);\n"
"    lfnoise(4.e1*(yi+p2-.5e-4*iTime), y2);\n"
"    lfnoise(12.e1*vec2(y2,1.)*(yi+p2)-1.e-4*(.8+.2*y2)*iTime*c.xy, y2);\n"
"    y0 *= ss;\n"
"    y1 *= ss;\n"
"    y2 *= ss;\n"
"    \n"
"    dtriangle3(y, vec3(p0,y0), vec3(p1,y1), vec3(p2,y2), sdf.x);\n"
"    \n"
"    float d;\n"
"    vec2 p3 = .8*size*c.zz,\n"
"        p4 = .8*size*c.xz,\n"
"        p5 = .8*size*c.zx;\n"
"    \n"
"    float y3, y4, y5;\n"
"    lfnoise(4.e1*(yi+p3-.5e-4*iTime), y3);\n"
"    lfnoise(12.e1*vec2(y3,1.)*(yi+p3)-1.e-4*(.8+.2*y3)*iTime*c.xy, y3);\n"
"    lfnoise(4.e1*(yi+p4-.5e-4*iTime), y4);\n"
"    lfnoise(12.e1*vec2(y4,1.)*(yi+p4)-1.e-4*(.8+.2*y4)*iTime*c.xy, y4);\n"
"    lfnoise(4.e1*(yi+p5-.5e-4*iTime), y5);\n"
"    lfnoise(12.e1*vec2(y5,1.)*(yi+p5)-1.e-4*(.8+.2*y5)*iTime*c.xy, y5);\n"
"    y3 *= ss;\n"
"    y4 *= ss;\n"
"    y5 *= ss;\n"
"    \n"
"    dtriangle3(y, vec3(p3,y3), vec3(p4,y4), vec3(p5,y5), d);\n"
"    sdf.x = min(sdf.x, d);\n"
"\n"
"    stroke(sdf.x, .1*size, sdf.x);\n"
"    sdf.y = 1.;\n"
"}\n"
"\n"
"void normal3(in vec3 x, out vec3 n, in float dx)\n"
"{\n"
"    vec2 s, na;\n"
"    \n"
"    scene3(x,s);\n"
"    scene3(x+dx*c.xyy, na);\n"
"    n.x = na.x;\n"
"    scene3(x+dx*c.yxy, na);\n"
"    n.y = na.x;\n"
"    scene3(x+dx*c.yyx, na);\n"
"    n.z = na.x;\n"
"    n = normalize(n-s.x);\n"
"}\n"
"\n"
"void normal(in vec3 x, out vec3 n, in float dx);\n"
"void mainImage( out vec4 fragColor, in vec2 fragCoord_ )\n"
"{\n"
"    vec2 fragCoord = fragCoord_;\n"
"    \n"
"    if(iTime < 159.5456 && iTime > 155.9092)\n"
"    {\n"
"        vec2 n;\n"
"        lfnoise(22.*fragCoord/iResolution-3.*iTime, n.x);\n"
"        lfnoise(22.*fragCoord/iResolution-3.*iTime-1337., n.y);\n"
"        fragCoord += 22.*n;\n"
"    }\n"
"    else if(iTime < 165. && iTime > 163.182)\n"
"    {\n"
"        vec2 n;\n"
"        lfnoise(22.*fragCoord/iResolution-3.*iTime, n.x);\n"
"        lfnoise(22.*fragCoord/iResolution-3.*iTime-1337., n.y);\n"
"        fragCoord += 22.*n;\n"
"    }\n"
"    \n"
"//     vec3 as = texture(iChannel0, fragCoord/iResolution).rgb;\n"
"//     vec2 nb;\n"
"//     lfnoise((as.xy+as.yz+as.xz), nb.x);\n"
"//     lfnoise((as.xy+as.yz+as.xz), nb.y);\n"
"//     fragCoord += 22.*(.1*as.r + .2*as.g + .3*as.b);\n"
"    \n"
"    float a = iResolution.x/iResolution.y;\n"
"    vec2 uv = fragCoord/iResolution.yy-0.5*vec2(a, 1.0);\n"
"    \n"
"    nbeats = mod(iTime, 60./29.);\n"
"    iScale = nbeats-30./29.;\n"
"    iScale = smoothstep(-5./29., 0., iScale)*(1.-smoothstep(0., 15./29., iScale));\n"
"    \n"
"    vec3 col = texture(iChannel0, fragCoord/iResolution).rgb;\n"
"    float delta = 0.;\n"
"//     vec2 n = c.yy;\n"
"    \n"
"    // Box\n"
"    rot3(vec3(-2.*pi/8.,2.*pi/8.,2.*pi/4.)-iTime*vec3(1.1,1.3,1.5), R);\n"
"    \n"
"    float d;\n"
"    vec2 s;\n"
"    vec3 o, r, u, t, ssize, dir, x, n;\n"
"    vec2 uv2 = 10.*(uv-vec2(-.45*a,.45));\n"
"    o = R * c.yyx;\n"
"	r = c.xyy; \n"
"	u = c.yxy;\n"
"	t = c.yyy; \n"
"    int N = 250,\n"
"        i;\n"
"    t = uv2.x * r + uv2.y * u;\n"
"    t = R * t;\n"
"    dir = normalize(t-o);\n"
"\n"
"    ssize = .2*c.xxx;\n"
"\n"
"	vec3 tlo = min((ssize-o)/dir,(-ssize-o)/dir); // Select 3 visible planes\n"
"    vec2 abxlo = abs(o.yz + tlo.x*dir.yz),\n"
"        abylo = abs(o.xz + tlo.y*dir.xz),\n"
"        abzlo = abs(o.xy + tlo.z*dir.xy);\n"
"\n"
"    vec4 dn = 100.*c.xyyy;\n"
"\n"
"    dn = mix(dn, vec4(tlo.x,c.xyy), float(all(lessThan(abxlo,ssize.yz)))*step(tlo.x,dn.x));\n"
"    dn = mix(dn, vec4(tlo.y,c.yxy), float(all(lessThan(abylo,ssize.xz)))*step(tlo.y,dn.x));\n"
"    dn = mix(dn, vec4(tlo.z,c.yyx), float(all(lessThan(abzlo,ssize.xy)))*step(tlo.z,dn.x));\n"
"    \n"
"    uv = (fragCoord)/iResolution.xy*vec2(a,1.);\n"
"    \n"
"    d = dn.r;\n"
"    \n"
"    float nan;\n"
"    lfnoise(iTime*c.xx, nan);\n"
"    nan += .5;\n"
"    if(nan > 0.) d = 3.;\n"
"    \n"
"    if(d<=2.)\n"
"    {\n"
"        x = o + d * dir;\n"
"        scene(x,s);\n"
"        \n"
"        if(s.x > 1.e-4)\n"
"        {\n"
"            for(i = 0; i<N; ++i)\n"
"            {\n"
"                x = o + d * dir;\n"
"                scene(x,s);\n"
"                if(s.x < 1.e-4)break;\n"
"                d += s.x;\n"
"            }\n"
"        }\n"
"        \n"
"        if(i<N)\n"
"        {\n"
"            normal(x,n, 5.e-4);\n"
"            \n"
"            if(s.y == 1.)\n"
"            {\n"
"                vec3 l = normalize(x+c.zzx*vec3(1.3,.9,1.2));\n"
"                col = vec3(0.81,0.15,0.18);\n"
"                col = .3*col\n"
"                    + .4*col * abs(dot(l,n))\n"
"                    + .6 * col * abs(pow(dot(reflect(-l,n),dir),2.));\n"
"            }\n"
"            else if(s.y == 2.)\n"
"            {\n"
"                vec3 l = normalize(x+c.zzx*vec3(1.3,.9,1.2));\n"
"                col = .7*c.xxx;\n"
"                col = .5*col\n"
"                    + .4*col * abs(dot(l,n))\n"
"                    + .8 * col * abs(pow(dot(reflect(-l,n),dir),2.));\n"
"            }\n"
"        }\n"
"        \n"
"        if(iTime < 0.) col = texture(iChannel0, fragCoord/iResolution).rgb;\n"
"    }\n"
"    else\n"
"    {\n"
"        iScale = nbeats-30./29.;\n"
"        iScale = smoothstep(-5./29., 0., iScale)*(1.-smoothstep(0./29., 35./29., iScale));\n"
"//         lscale = iScale;\n"
"        lscale = smoothstep(0.,.5,clamp((iTime-10.),0.,1.))*(1.-smoothstep(0.,.5,clamp((iTime-18.),0.,1.)));\n"
"//         lscale += smoothstep(0.,.5,clamp((iTime-10.),0.,1.))*(1.-smoothstep(0.,.5,clamp((iTime-18.),0.,1.)));\n"
"        rscale = smoothstep(167.,167.5,iTime)-smoothstep(172.,172.5,iTime);\n"
"        \n"
"//         rscale = iScale;\n"
"//         rscale = 0.;\n"
"        size = mix(.005, .01, rscale);\n"
"        size = mix(0., size, max(rscale, lscale));\n"
"     \n"
"        if(lscale > 0.)\n"
"        {\n"
"            col = c.yyy;\n"
"            \n"
"            o = c.yyx+.5*vec3(cos(iTime), sin(iTime),0.);\n"
"            r = c.xyy;\n"
"            u = c.yxy;\n"
"            t = c.yyy;\n"
"            dir = c.yyy;\n"
"            n = c.yyy;\n"
"            x = c.yyy;\n"
"            N = 200;\n"
"            t = uv.x * r + uv.y * u;\n"
"            dir = normalize(t-o);\n"
"\n"
"            d = -(o.z-.05-.5*size)/dir.z;\n"
"            \n"
"            for(i = 0; i<N; ++i)\n"
"            {\n"
"                x = o + d * dir;\n"
"                scene2(x,s);\n"
"                if(s.x < 1.e-4)break;\n"
"                \n"
"                if(x.z<-.05-.5*size)\n"
"                {\n"
"                    col = c.yyy;\n"
"                    i = N;\n"
"                    break;\n"
"                }\n"
"                d += min(s.x,1.e-3);\n"
"                //d += s.x;\n"
"            }\n"
"            \n"
"            if(i < N)\n"
"            {\n"
"                normal2(x,n, 5.e-4);\n"
"                vec3 l = normalize(x+.5*n);\n"
"            \n"
"                if(s.y == 1.)\n"
"                {\n"
"                    float v, vn;\n"
"                    vec2 vi;\n"
"                    dvoronoi(x.xy/size, v, vi, vn);\n"
"                    vec3 y = vec3(x.xy-vi*size, x.z);\n"
"                    vec2 yi = vi*size;\n"
"                    \n"
"                    float bound = sqrt(iFSAA)-1.;\n"
"\n"
"                    for(float i = -.5*bound; i<=.5*bound; i+=1.)\n"
"                        for(float j=-.5*bound; j<=.5*bound; j+=1.)\n"
"                        {\n"
"                            col += texture(iChannel0, yi/vec2(a,1.)+vec2(i,j)*3./max(bound, 1.)/iResolution.xy).xyz;\n"
"                        }\n"
"                    col /= iFSAA;   \n"
"                    \n"
"                    col = .4*col\n"
"                        + .9*col * abs(dot(l,n))\n"
"                        + .6*col * pow(abs(dot(reflect(-l,n),dir)),3.);\n"
"                }\n"
"            }\n"
"            else col = c.yyy;\n"
"        }\n"
"        else if(rscale > 0.)\n"
"        {\n"
"            col = c.yyy;\n"
"            \n"
"            o = c.yyx+.5*vec3(-1., -1.,0.);\n"
"            r = c.xyy;\n"
"            u = c.yxy;\n"
"            t = c.yyy;\n"
"            dir = c.yyy;\n"
"            n = c.yyy;\n"
"            x = c.yyy;\n"
"            N = 300;\n"
"            t = uv.x * r + uv.y * u;\n"
"            dir = normalize(t-o);\n"
"\n"
"            d = -(o.z-.05-.5*size)/dir.z;\n"
"            \n"
"            for(i = 0; i<N; ++i)\n"
"            {\n"
"                x = o + d * dir;\n"
"                scene3(x,s);\n"
"                if(s.x < 1.e-4)break;\n"
"                \n"
"                if(x.z<-.05-.5*size)\n"
"                {\n"
"                    col = c.yyy;\n"
"                    i = N;\n"
"                    break;\n"
"                }\n"
"                d += min(s.x,1.e-3);\n"
"                //d += s.x;\n"
"            }\n"
"            \n"
"            if(i < N)\n"
"            {\n"
"                normal3(x,n, 5.e-4);\n"
"                vec3 l = normalize(x+.5*n);\n"
"            \n"
"                if(s.y == 1.)\n"
"                {\n"
"                    vec3 y = vec3(mod(x.xy,size)-.5*size, x.z);\n"
"                    vec2 yi = x.xy-y.xy;\n"
"                    \n"
"                    col = texture(iChannel0, yi/vec2(a,1.)).rgb;\n"
"                    \n"
"//                     col = .7*c.xxy;\n"
"                    \n"
"                    col = .4*col\n"
"                        + .9*col * abs(dot(l,n))\n"
"                        + .6*col * pow(abs(dot(reflect(-l,n),dir)),3.);\n"
"                    \n"
"                }\n"
"            }\n"
"            else col = c.yyy;\n"
"        }\n"
"    }\n"
"    \n"
"    // Scan lines\n"
"    col += vec3(0., 0.05, 0.1)*sin(uv.y*1050.+ 5.*iTime);\n"
"    \n"
"    fragColor = vec4(clamp(col,0.,1.),1.0);\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    mainImage(gl_FragColor, gl_FragCoord.xy);\n"
"}\n"
"\0";
void Loadrand()
{
    int rand_size = strlen(rand_source);
    rand_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rand_handle, 1, (GLchar **)&rand_source, &rand_size);
    glCompileShader(rand_handle);
#ifdef DEBUG
    printf("---> rand Shader:\n");
    debug(rand_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadhash11()
{
    int hash11_size = strlen(hash11_source);
    hash11_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(hash11_handle, 1, (GLchar **)&hash11_source, &hash11_size);
    glCompileShader(hash11_handle);
#ifdef DEBUG
    printf("---> hash11 Shader:\n");
    debug(hash11_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadhash12()
{
    int hash12_size = strlen(hash12_source);
    hash12_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(hash12_handle, 1, (GLchar **)&hash12_source, &hash12_size);
    glCompileShader(hash12_handle);
#ifdef DEBUG
    printf("---> hash12 Shader:\n");
    debug(hash12_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadhash21()
{
    int hash21_size = strlen(hash21_source);
    hash21_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(hash21_handle, 1, (GLchar **)&hash21_source, &hash21_size);
    glCompileShader(hash21_handle);
#ifdef DEBUG
    printf("---> hash21 Shader:\n");
    debug(hash21_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadhash22()
{
    int hash22_size = strlen(hash22_source);
    hash22_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(hash22_handle, 1, (GLchar **)&hash22_source, &hash22_size);
    glCompileShader(hash22_handle);
#ifdef DEBUG
    printf("---> hash22 Shader:\n");
    debug(hash22_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadhash31()
{
    int hash31_size = strlen(hash31_source);
    hash31_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(hash31_handle, 1, (GLchar **)&hash31_source, &hash31_size);
    glCompileShader(hash31_handle);
#ifdef DEBUG
    printf("---> hash31 Shader:\n");
    debug(hash31_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadstroke()
{
    int stroke_size = strlen(stroke_source);
    stroke_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(stroke_handle, 1, (GLchar **)&stroke_source, &stroke_size);
    glCompileShader(stroke_handle);
#ifdef DEBUG
    printf("---> stroke Shader:\n");
    debug(stroke_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadlfnoise()
{
    int lfnoise_size = strlen(lfnoise_source);
    lfnoise_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(lfnoise_handle, 1, (GLchar **)&lfnoise_source, &lfnoise_size);
    glCompileShader(lfnoise_handle);
#ifdef DEBUG
    printf("---> lfnoise Shader:\n");
    debug(lfnoise_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddvoronoi()
{
    int dvoronoi_size = strlen(dvoronoi_source);
    dvoronoi_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dvoronoi_handle, 1, (GLchar **)&dvoronoi_source, &dvoronoi_size);
    glCompileShader(dvoronoi_handle);
#ifdef DEBUG
    printf("---> dvoronoi Shader:\n");
    debug(dvoronoi_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddbox()
{
    int dbox_size = strlen(dbox_source);
    dbox_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dbox_handle, 1, (GLchar **)&dbox_source, &dbox_size);
    glCompileShader(dbox_handle);
#ifdef DEBUG
    printf("---> dbox Shader:\n");
    debug(dbox_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddlinesegment()
{
    int dlinesegment_size = strlen(dlinesegment_source);
    dlinesegment_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dlinesegment_handle, 1, (GLchar **)&dlinesegment_source, &dlinesegment_size);
    glCompileShader(dlinesegment_handle);
#ifdef DEBUG
    printf("---> dlinesegment Shader:\n");
    debug(dlinesegment_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadsmoothmin()
{
    int smoothmin_size = strlen(smoothmin_source);
    smoothmin_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(smoothmin_handle, 1, (GLchar **)&smoothmin_source, &smoothmin_size);
    glCompileShader(smoothmin_handle);
#ifdef DEBUG
    printf("---> smoothmin Shader:\n");
    debug(smoothmin_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadadd()
{
    int add_size = strlen(add_source);
    add_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(add_handle, 1, (GLchar **)&add_source, &add_size);
    glCompileShader(add_handle);
#ifdef DEBUG
    printf("---> add Shader:\n");
    debug(add_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadnormal()
{
    int normal_size = strlen(normal_source);
    normal_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(normal_handle, 1, (GLchar **)&normal_source, &normal_size);
    glCompileShader(normal_handle);
#ifdef DEBUG
    printf("---> normal Shader:\n");
    debug(normal_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddbox3()
{
    int dbox3_size = strlen(dbox3_source);
    dbox3_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dbox3_handle, 1, (GLchar **)&dbox3_source, &dbox3_size);
    glCompileShader(dbox3_handle);
#ifdef DEBUG
    printf("---> dbox3 Shader:\n");
    debug(dbox3_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadrot3()
{
    int rot3_size = strlen(rot3_source);
    rot3_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rot3_handle, 1, (GLchar **)&rot3_source, &rot3_size);
    glCompileShader(rot3_handle);
#ifdef DEBUG
    printf("---> rot3 Shader:\n");
    debug(rot3_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddbox210()
{
    int dbox210_size = strlen(dbox210_source);
    dbox210_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dbox210_handle, 1, (GLchar **)&dbox210_source, &dbox210_size);
    glCompileShader(dbox210_handle);
#ifdef DEBUG
    printf("---> dbox210 Shader:\n");
    debug(dbox210_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddspline2()
{
    int dspline2_size = strlen(dspline2_source);
    dspline2_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dspline2_handle, 1, (GLchar **)&dspline2_source, &dspline2_size);
    glCompileShader(dspline2_handle);
#ifdef DEBUG
    printf("---> dspline2 Shader:\n");
    debug(dspline2_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadzextrude()
{
    int zextrude_size = strlen(zextrude_source);
    zextrude_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(zextrude_handle, 1, (GLchar **)&zextrude_source, &zextrude_size);
    glCompileShader(zextrude_handle);
#ifdef DEBUG
    printf("---> zextrude Shader:\n");
    debug(zextrude_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadmfnoise()
{
    int mfnoise_size = strlen(mfnoise_source);
    mfnoise_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mfnoise_handle, 1, (GLchar **)&mfnoise_source, &mfnoise_size);
    glCompileShader(mfnoise_handle);
#ifdef DEBUG
    printf("---> mfnoise Shader:\n");
    debug(mfnoise_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadrshort()
{
    int rshort_size = strlen(rshort_source);
    rshort_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rshort_handle, 1, (GLchar **)&rshort_source, &rshort_size);
    glCompileShader(rshort_handle);
#ifdef DEBUG
    printf("---> rshort Shader:\n");
    debug(rshort_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadrfloat()
{
    int rfloat_size = strlen(rfloat_source);
    rfloat_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rfloat_handle, 1, (GLchar **)&rfloat_source, &rfloat_size);
    glCompileShader(rfloat_handle);
#ifdef DEBUG
    printf("---> rfloat Shader:\n");
    debug(rfloat_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddcircle()
{
    int dcircle_size = strlen(dcircle_source);
    dcircle_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dcircle_handle, 1, (GLchar **)&dcircle_source, &dcircle_size);
    glCompileShader(dcircle_handle);
#ifdef DEBUG
    printf("---> dcircle Shader:\n");
    debug(dcircle_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddrhomboid()
{
    int drhomboid_size = strlen(drhomboid_source);
    drhomboid_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(drhomboid_handle, 1, (GLchar **)&drhomboid_source, &drhomboid_size);
    glCompileShader(drhomboid_handle);
#ifdef DEBUG
    printf("---> drhomboid Shader:\n");
    debug(drhomboid_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddcirclesegment()
{
    int dcirclesegment_size = strlen(dcirclesegment_source);
    dcirclesegment_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dcirclesegment_handle, 1, (GLchar **)&dcirclesegment_source, &dcirclesegment_size);
    glCompileShader(dcirclesegment_handle);
#ifdef DEBUG
    printf("---> dcirclesegment Shader:\n");
    debug(dcirclesegment_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddglyph()
{
    int dglyph_size = strlen(dglyph_source);
    dglyph_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dglyph_handle, 1, (GLchar **)&dglyph_source, &dglyph_size);
    glCompileShader(dglyph_handle);
#ifdef DEBUG
    printf("---> dglyph Shader:\n");
    debug(dglyph_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddstring()
{
    int dstring_size = strlen(dstring_source);
    dstring_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dstring_handle, 1, (GLchar **)&dstring_source, &dstring_size);
    glCompileShader(dstring_handle);
#ifdef DEBUG
    printf("---> dstring Shader:\n");
    debug(dstring_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddfloat()
{
    int dfloat_size = strlen(dfloat_source);
    dfloat_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dfloat_handle, 1, (GLchar **)&dfloat_source, &dfloat_size);
    glCompileShader(dfloat_handle);
#ifdef DEBUG
    printf("---> dfloat Shader:\n");
    debug(dfloat_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddint()
{
    int dint_size = strlen(dint_source);
    dint_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dint_handle, 1, (GLchar **)&dint_source, &dint_size);
    glCompileShader(dint_handle);
#ifdef DEBUG
    printf("---> dint Shader:\n");
    debug(dint_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddtime()
{
    int dtime_size = strlen(dtime_source);
    dtime_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dtime_handle, 1, (GLchar **)&dtime_source, &dtime_size);
    glCompileShader(dtime_handle);
#ifdef DEBUG
    printf("---> dtime Shader:\n");
    debug(dtime_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadwindow()
{
    int window_size = strlen(window_source);
    window_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(window_handle, 1, (GLchar **)&window_source, &window_size);
    glCompileShader(window_handle);
#ifdef DEBUG
    printf("---> window Shader:\n");
    debug(window_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadprogressbar()
{
    int progressbar_size = strlen(progressbar_source);
    progressbar_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(progressbar_handle, 1, (GLchar **)&progressbar_source, &progressbar_size);
    glCompileShader(progressbar_handle);
#ifdef DEBUG
    printf("---> progressbar Shader:\n");
    debug(progressbar_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}

void LoadSymbols()
{
    Loadrand();
    updateBar();
    Loadhash11();
    updateBar();
    Loadhash12();
    updateBar();
    Loadhash21();
    updateBar();
    Loadhash22();
    updateBar();
    Loadhash31();
    updateBar();
    Loadstroke();
    updateBar();
    Loadlfnoise();
    updateBar();
    Loaddvoronoi();
    updateBar();
    Loaddbox();
    updateBar();
    Loaddlinesegment();
    updateBar();
    Loadsmoothmin();
    updateBar();
    Loadadd();
    updateBar();
    Loadnormal();
    updateBar();
    Loaddbox3();
    updateBar();
    Loadrot3();
    updateBar();
    Loaddbox210();
    updateBar();
    Loaddspline2();
    updateBar();
    Loadzextrude();
    updateBar();
    Loadmfnoise();
    updateBar();
    Loadrshort();
    updateBar();
    Loadrfloat();
    updateBar();
    Loaddcircle();
    updateBar();
    Loaddrhomboid();
    updateBar();
    Loaddcirclesegment();
    updateBar();
    Loaddglyph();
    updateBar();
    Loaddstring();
    updateBar();
    Loaddfloat();
    updateBar();
    Loaddint();
    updateBar();
    Loaddtime();
    updateBar();
    Loadwindow();
    updateBar();
    Loadprogressbar();
    updateBar();
}
int ocean_program, ocean_handle, logo210_program, logo210_handle, graffiti_program, graffiti_handle, starsky_program, starsky_handle, text_program, text_handle, post_program, post_handle;
int ocean_iTime_location,ocean_iResolution_location;
int logo210_iTime_location,logo210_iResolution_location;
int graffiti_iTime_location,graffiti_iResolution_location;
int starsky_iTime_location,starsky_iResolution_location;
int text_iFontWidth_location,text_iTime_location,text_iResolution_location,text_iChannel0_location,text_iFont_location,text_iFSAA_location;
int post_iFSAA_location,post_iResolution_location,post_iChannel0_location,post_iTime_location;
const int nprograms = 6;

void Loadocean()
{
    int ocean_size = strlen(ocean_source);
    ocean_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(ocean_handle, 1, (GLchar **)&ocean_source, &ocean_size);
    glCompileShader(ocean_handle);
#ifdef DEBUG
    printf("---> ocean Shader:\n");
    debug(ocean_handle);
    printf(">>>>\n");
#endif
    ocean_program = glCreateProgram();
    glAttachShader(ocean_program,ocean_handle);
    glAttachShader(ocean_program,rand_handle);
    glAttachShader(ocean_program,hash11_handle);
    glAttachShader(ocean_program,hash12_handle);
    glAttachShader(ocean_program,hash21_handle);
    glAttachShader(ocean_program,hash22_handle);
    glAttachShader(ocean_program,hash31_handle);
    glAttachShader(ocean_program,stroke_handle);
    glAttachShader(ocean_program,lfnoise_handle);
    glAttachShader(ocean_program,dvoronoi_handle);
    glAttachShader(ocean_program,dbox_handle);
    glAttachShader(ocean_program,dlinesegment_handle);
    glAttachShader(ocean_program,smoothmin_handle);
    glAttachShader(ocean_program,add_handle);
    glAttachShader(ocean_program,normal_handle);
    glLinkProgram(ocean_program);
#ifdef DEBUG
    printf("---> ocean Program:\n");
    debugp(ocean_program);
    printf(">>>>\n");
#endif
    glUseProgram(ocean_program);
    ocean_iTime_location = glGetUniformLocation(ocean_program, "iTime");
    ocean_iResolution_location = glGetUniformLocation(ocean_program, "iResolution");
    progress += .2/(float)nprograms;
}

void Loadlogo210()
{
    int logo210_size = strlen(logo210_source);
    logo210_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(logo210_handle, 1, (GLchar **)&logo210_source, &logo210_size);
    glCompileShader(logo210_handle);
#ifdef DEBUG
    printf("---> logo210 Shader:\n");
    debug(logo210_handle);
    printf(">>>>\n");
#endif
    logo210_program = glCreateProgram();
    glAttachShader(logo210_program,logo210_handle);
    glAttachShader(logo210_program,dbox3_handle);
    glAttachShader(logo210_program,rot3_handle);
    glAttachShader(logo210_program,stroke_handle);
    glAttachShader(logo210_program,add_handle);
    glAttachShader(logo210_program,dbox210_handle);
    glAttachShader(logo210_program,normal_handle);
    glLinkProgram(logo210_program);
#ifdef DEBUG
    printf("---> logo210 Program:\n");
    debugp(logo210_program);
    printf(">>>>\n");
#endif
    glUseProgram(logo210_program);
    logo210_iTime_location = glGetUniformLocation(logo210_program, "iTime");
    logo210_iResolution_location = glGetUniformLocation(logo210_program, "iResolution");
    progress += .2/(float)nprograms;
}

void Loadgraffiti()
{
    int graffiti_size = strlen(graffiti_source);
    graffiti_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(graffiti_handle, 1, (GLchar **)&graffiti_source, &graffiti_size);
    glCompileShader(graffiti_handle);
#ifdef DEBUG
    printf("---> graffiti Shader:\n");
    debug(graffiti_handle);
    printf(">>>>\n");
#endif
    graffiti_program = glCreateProgram();
    glAttachShader(graffiti_program,graffiti_handle);
    glAttachShader(graffiti_program,hash22_handle);
    glAttachShader(graffiti_program,rand_handle);
    glAttachShader(graffiti_program,lfnoise_handle);
    glAttachShader(graffiti_program,dspline2_handle);
    glAttachShader(graffiti_program,dlinesegment_handle);
    glAttachShader(graffiti_program,stroke_handle);
    glAttachShader(graffiti_program,smoothmin_handle);
    glAttachShader(graffiti_program,dvoronoi_handle);
    glAttachShader(graffiti_program,zextrude_handle);
    glAttachShader(graffiti_program,normal_handle);
    glLinkProgram(graffiti_program);
#ifdef DEBUG
    printf("---> graffiti Program:\n");
    debugp(graffiti_program);
    printf(">>>>\n");
#endif
    glUseProgram(graffiti_program);
    graffiti_iTime_location = glGetUniformLocation(graffiti_program, "iTime");
    graffiti_iResolution_location = glGetUniformLocation(graffiti_program, "iResolution");
    progress += .2/(float)nprograms;
}

void Loadstarsky()
{
    int starsky_size = strlen(starsky_source);
    starsky_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(starsky_handle, 1, (GLchar **)&starsky_source, &starsky_size);
    glCompileShader(starsky_handle);
#ifdef DEBUG
    printf("---> starsky Shader:\n");
    debug(starsky_handle);
    printf(">>>>\n");
#endif
    starsky_program = glCreateProgram();
    glAttachShader(starsky_program,starsky_handle);
    glAttachShader(starsky_program,hash22_handle);
    glAttachShader(starsky_program,rand_handle);
    glAttachShader(starsky_program,lfnoise_handle);
    glAttachShader(starsky_program,mfnoise_handle);
    glAttachShader(starsky_program,dvoronoi_handle);
    glAttachShader(starsky_program,stroke_handle);
    glAttachShader(starsky_program,dbox_handle);
    glAttachShader(starsky_program,dbox3_handle);
    glAttachShader(starsky_program,add_handle);
    glAttachShader(starsky_program,normal_handle);
    glLinkProgram(starsky_program);
#ifdef DEBUG
    printf("---> starsky Program:\n");
    debugp(starsky_program);
    printf(">>>>\n");
#endif
    glUseProgram(starsky_program);
    starsky_iTime_location = glGetUniformLocation(starsky_program, "iTime");
    starsky_iResolution_location = glGetUniformLocation(starsky_program, "iResolution");
    progress += .2/(float)nprograms;
}

void Loadtext()
{
    int text_size = strlen(text_source);
    text_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(text_handle, 1, (GLchar **)&text_source, &text_size);
    glCompileShader(text_handle);
#ifdef DEBUG
    printf("---> text Shader:\n");
    debug(text_handle);
    printf(">>>>\n");
#endif
    text_program = glCreateProgram();
    glAttachShader(text_program,text_handle);
    glAttachShader(text_program,rand_handle);
    glAttachShader(text_program,lfnoise_handle);
    glAttachShader(text_program,rshort_handle);
    glAttachShader(text_program,rfloat_handle);
    glAttachShader(text_program,dbox_handle);
    glAttachShader(text_program,dcircle_handle);
    glAttachShader(text_program,dlinesegment_handle);
    glAttachShader(text_program,drhomboid_handle);
    glAttachShader(text_program,dcirclesegment_handle);
    glAttachShader(text_program,stroke_handle);
    glAttachShader(text_program,dglyph_handle);
    glAttachShader(text_program,dstring_handle);
    glAttachShader(text_program,dfloat_handle);
    glAttachShader(text_program,smoothmin_handle);
    glAttachShader(text_program,dint_handle);
    glAttachShader(text_program,dtime_handle);
    glAttachShader(text_program,window_handle);
    glAttachShader(text_program,progressbar_handle);
    glAttachShader(text_program,dvoronoi_handle);
    glLinkProgram(text_program);
#ifdef DEBUG
    printf("---> text Program:\n");
    debugp(text_program);
    printf(">>>>\n");
#endif
    glUseProgram(text_program);
    text_iFontWidth_location = glGetUniformLocation(text_program, "iFontWidth");
    text_iTime_location = glGetUniformLocation(text_program, "iTime");
    text_iResolution_location = glGetUniformLocation(text_program, "iResolution");
    text_iChannel0_location = glGetUniformLocation(text_program, "iChannel0");
    text_iFont_location = glGetUniformLocation(text_program, "iFont");
    text_iFSAA_location = glGetUniformLocation(text_program, "iFSAA");
    progress += .2/(float)nprograms;
}

void Loadpost()
{
    int post_size = strlen(post_source);
    post_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(post_handle, 1, (GLchar **)&post_source, &post_size);
    glCompileShader(post_handle);
#ifdef DEBUG
    printf("---> post Shader:\n");
    debug(post_handle);
    printf(">>>>\n");
#endif
    post_program = glCreateProgram();
    glAttachShader(post_program,post_handle);
    glAttachShader(post_program,rand_handle);
    glAttachShader(post_program,lfnoise_handle);
    glAttachShader(post_program,stroke_handle);
    glAttachShader(post_program,dvoronoi_handle);
    glAttachShader(post_program,hash22_handle);
    glAttachShader(post_program,rot3_handle);
    glAttachShader(post_program,dbox3_handle);
    glAttachShader(post_program,add_handle);
    glAttachShader(post_program,normal_handle);
    glLinkProgram(post_program);
#ifdef DEBUG
    printf("---> post Program:\n");
    debugp(post_program);
    printf(">>>>\n");
#endif
    glUseProgram(post_program);
    post_iFSAA_location = glGetUniformLocation(post_program, "iFSAA");
    post_iResolution_location = glGetUniformLocation(post_program, "iResolution");
    post_iChannel0_location = glGetUniformLocation(post_program, "iChannel0");
    post_iTime_location = glGetUniformLocation(post_program, "iTime");
    progress += .2/(float)nprograms;
}

void LoadPrograms()
{
    Loadocean();
    updateBar();
    Loadlogo210();
    updateBar();
    Loadgraffiti();
    updateBar();
    Loadstarsky();
    updateBar();
    Loadtext();
    updateBar();
    Loadpost();
    updateBar();
}
#endif
