//Generated with Symbolize (c) 2019 Alexander Kraus <nr4@z10.info>.
#ifndef SYMBOLIZE_H
#define SYMBOLIZE_H

extern float progress;int rand_handle, hash11_handle, hash12_handle, hash21_handle, hash22_handle, hash31_handle, stroke_handle, lfnoise_handle, dvoronoi_handle, dbox_handle, dlinesegment_handle, smoothmin_handle, add_handle, normal_handle, dbox3_handle, rot3_handle, dbox210_handle, dspline2_handle, zextrude_handle, mfnoise_handle, rshort_handle, rfloat_handle, dcircle_handle, drhomboid_handle, dcirclesegment_handle, dglyph_handle, dstring_handle, dfloat_handle, dint_handle, dtime_handle, addwindow_handle, ddeadline_handle, dpolygon_handle, dspacepigs_handle, analytical_box_handle, hash33_handle, dvoronoi3_handle, dsmoothvoronoi3_handle, dstar_handle, smoothmax_handle, dstar3_handle, dhexagonpattern_handle, dmercury_handle, dtriangle_handle, rot_handle, dschnappsgirls_handle, dhaujobb_handle, dkewlers_handle, dfarbrausch_handle, d5711_handle, sub_handle, doctahedron_handle;
const int nsymbols = 52;
const char *rand_source = "#version 130\nvoid rand(in vec2 x,out float n){x+=400.;n=fract(sin(dot(sign(x)*abs(x),vec2 (12.9898,78.233)))*43758.5453);}\0";
const char *hash11_source = "void hash11(in float p,out float d){p=fract(p*.1031);p*=p+33.33;p*=p+p;d=fract(p);}\0";
const char *hash12_source = "void hash12(in vec2 p,out float d){vec3 p3=fract(vec3 (p.xyx)*.1031);p3+=dot(p3,p3.yzx+33.33);d=fract((p3.x+p3.y)*p3.z);}\0";
const char *hash21_source = "void hash21(in float p,out vec2 d){vec3 p3=fract(vec3 (p)*vec3 (.1031,.1030,.0973));p3+=dot(p3,p3.yzx+33.33);d=fract((p3.xx+p3.yz)*p3.zy);}\0";
const char *hash22_source = "void hash22(in vec2 p,out vec2 d){vec3 p3=fract(vec3 (p.xyx)*vec3 (.1031,.1030,.0973));p3+=dot(p3,p3.yzx+33.33);d=fract((p3.xx+p3.yz)*p3.zy);}\0";
const char *hash31_source = "void hash31(in float p,out vec3 d){vec3 p3=fract(vec3 (p)*vec3 (.1031,.1030,.0973));p3+=dot(p3,p3.yzx+33.33);d=fract((p3.xxy+p3.yzz)*p3.zyx);}\0";
const char *stroke_source = "void stroke(in float d0,in float s,out float d){d=abs(d0)-s;}\0";
const char *lfnoise_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rand(in vec2 x,out float d);void lfnoise(in vec2 t,out float n){vec2 i=floor(t);t=fract(t);t=smoothstep(c.yy,c.xx,t);vec2 v1,v2;rand(i,v1.x);rand(i+c.xy,v1.y);rand(i+c.yx,v2.x);rand(i+c.xx,v2.y);v1=c.zz+2.*mix(v1,v2,t.y);n=mix(v1.x,v1.y,t.x);}\0";
const char *dvoronoi_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void hash22(in vec2 a,out vec2 b);void dist(in vec2 a,in vec2 b,out float d){d=length(b-a);}void nearest_controlpoint(in vec2 x,out vec2 p){float dmin=1.e5,d;vec2 dp,y=floor(x);float i=0.;for(float i=-1.;i<=1.;i+=1.)for(float j=-1.;j<=1.;j+=1.){hash22(y+vec2 (i,j),dp);dp+=y+vec2 (i,j);dist(x,dp,d);if(d<dmin){dmin=d;p=dp;}}}void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance){d=1.e4;vec2 y,dp;nearest_controlpoint(x,p);y=floor(p);control_distance=1.e4;for(float i=-2.;i<=2.;i+=1.)for(float j=-2.;j<=2.;j+=1.){if(i==0.&&j==0.)continue;hash22(y+vec2 (i,j),dp);dp+=y+vec2 (i,j);vec2 o=p-dp;float l=length(o);d=min(d,abs(.5*l-dot(x-dp,o)/l));control_distance=min(control_distance,.5*l);}}\0";
const char *dbox_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dbox(in vec2 x,in vec2 b,out float d){vec2 da=abs(x)-b;d=length(max(da,c.yy))+min(max(da.x,da.y),0.0);}\0";
const char *dlinesegment_source = "#version 130\nvoid dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d){vec2 da=p2-p1;d=length(x-mix(p1,p2,clamp(dot(x-p1,da)/dot(da,da),0.,1.)));}\0";
const char *smoothmin_source = "void smoothmin(in float a,in float b,in float k,out float dst){float h=max(k-abs(a-b),0.0)/k;dst=min(a,b)-h*h*h*k*(1.0/6.0);}\0";
const char *add_source = "void add(in vec2 sda,in vec2 sdb,out vec2 sdf){sdf=(sda.x<sdb.x)?sda:sdb;}\0";
const char *normal_source = "const vec3 c=vec3 (1.0,0.0,-1.0);void scene(in vec3 x,out vec2 s);void normal(in vec3 x,out vec3 n,in float dx){vec2 s,na;scene(x,s);scene(x+dx*c.xyy,na);n.x=na.x;scene(x+dx*c.yxy,na);n.y=na.x;scene(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}\0";
const char *dbox3_source = "#version 130\nvoid dbox3(in vec3 x,in vec3 b,out float d){vec3 da=abs(x)-b;d=length(max(da,0.0))+min(max(da.x,max(da.y,da.z)),0.0);}\0";
const char *rot3_source = "const vec3 c=vec3 (1.,0.,-1.);void rot3(in vec3 p,out mat3 rot){rot=mat3 (c.xyyy,cos(p.x),sin(p.x),0.,-sin(p.x),cos(p.x))*mat3 (cos(p.y),0.,-sin(p.y),c.yxy,sin(p.y),0.,cos(p.y))*mat3 (cos(p.z),-sin(p.z),0.,sin(p.z),cos(p.z),c.yyyx);}\0";
const char *dbox210_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dbox3(in vec3 x,in vec3 b,out float d);void dbox210(in vec3 x,in float size,out vec2 sdf){x/=size;float d=1.;dbox3(x,.2*c.xxx,sdf.x);sdf.y=1.;dbox3(x-.1*c.xyy,vec3 (.02,.3,.12),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x-.05*c.xyy-.1*c.yyx,vec3 (.07,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x,vec3 (.02,.3,.1),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.05*c.xyy+.1*c.yyx,vec3 (.07,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.1*c.xyy-.1*c.yyx,vec3 (.02,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.04*c.yyx,vec3 (.3,.02,.08),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x-.1*c.yyx,vec3 (.3,.02,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));vec3 y=vec3 (x.x,abs(x.y),x.z);dbox3(y-.05*c.yxy,vec3 (.1,.03,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(y-.1*c.yxy-.06*c.xyy,vec3 (.08,.021,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));vec3 z=vec3 (abs(x.x),x.yz);dbox3(z-.119*c.xyy,vec3 (.021,.08,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));sdf.x*=size;}\0";
const char *dspline2_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);const float pi=acos(-1.);float dist2(vec2 p0,vec2 p1,vec2 p2,vec2 x,float t){t=clamp(t,0.,1.);return length(x-pow(1.-t,2.)*p0-2.*(1.-t)*t*p1-t*t*p2);}void dspline2(in vec2 x,in vec2 p0,in vec2 p1,in vec2 p2,out float ds){vec2 E=x-p0,F=p2-2.*p1+p0,G=p1-p0;vec3 ai=vec3 (3.*dot(G,F),2.*dot(G,G)-dot(E,F),-dot(E,G))/dot(F,F);float tau=ai.x/3.,p=ai.y-tau*ai.x,q=-tau*(tau*tau+p)+ai.z,dis=q*q/4.+p*p*p/27.;if(dis>0.){vec2 ki=-.5*q*c.xx+sqrt(dis)*c.xz,ui=sign(ki)*pow(abs(ki),c.xx/3.);ds=dist2(p0,p1,p2,x,ui.x+ui.y-tau);return ;}float fac=sqrt(-4./3.*p),arg=acos(-.5*q*sqrt(-27./p/p/p))/3.;vec3 t=c.zxz*fac*cos(arg*c.xxx+c*pi/3.)-tau;ds=min(dist2(p0,p1,p2,x,t.x),min(dist2(p0,p1,p2,x,t.y),dist2(p0,p1,p2,x,t.z)));}\0";
const char *zextrude_source = "void zextrude(in float z,in float d2d,in float h,out float d){vec2 w=vec2 (-d2d,abs(z)-0.5*h);d=length(max(w,0.0));}\0";
const char *mfnoise_source = "#version 130\nvoid lfnoise(in vec2 x,out float d);void mfnoise(in vec2 x,in float d,in float b,in float e,out float n){n=0.;float a=1.,nf=0.,buf;for(float f=d;f<b;f*=2.){lfnoise(f*x,buf);n+=a*buf;a*=e;nf+=1.;}n*=(1.-e)/(1.-pow(e,nf));}\0";
const char *rshort_source = "#version 130\nuniform float iFontWidth;uniform sampler2D iFont;void rshort(in float off,out float val){float hilo=mod(off,2.);off*=.5;vec2 ind=(vec2 (mod(off,iFontWidth),floor(off/iFontWidth))+.05)/iFontWidth;vec4 block=texture(iFont,ind);vec2 data=mix(block.rg,block.ba,hilo);val=round(dot(vec2 (255.,65280.),data));}\0";
const char *rfloat_source = "#version 130\nvoid rshort(in float off,out float val);void rfloat(in float off,out float val){float d;rshort(off,d);float sign=floor(d/32768.),exponent=floor(d/1024.-sign*32.),significand=d-sign*32768.-exponent*1024.;if(exponent==0.){val=mix(1.,-1.,sign)*5.960464477539063e-08*significand;}else {val=mix(1.,-1.,sign)*(1.+significand*9.765625e-4)*pow(2.,exponent-15.);}}\0";
const char *dcircle_source = "#version 130\nvoid dcircle(in vec2 x,out float d){d=length(x)-1.0;}\0";
const char *drhomboid_source = "#version 130\nvoid dbox(in vec2 x,in vec2 b,out float dst);void drhomboid(in vec2 x,in vec2 b,in float tilt,out float dst){x.x-=tilt/2./b.y*x.y;dbox(x,b,dst);}\0";
const char *dcirclesegment_source = "#version 130\nconst float pi=acos(-1.);void dcirclesegment(in vec2 x,in float R,in float p0,in float p1,out float d){float p=atan(x.y,x.x);vec2 philo=vec2 (max(p0,p1),min(p0,p1));if((p<philo.x&&p>philo.y)||(p+2.0*pi<philo.x&&p+2.0*pi>philo.y)||(p-2.0*pi<philo.x&&p-2.0*pi>philo.y))d=abs(length(x)-R);else d=min(length(x-vec2 (cos(p0),sin(p0))),length(x-vec2 (cos(p1),sin(p1))));}\0";
const char *dglyph_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rfloat(in float off,out float val);void dbox(in vec2 x,in vec2 b,out float dst);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void dcircle(in vec2 x,out float d);void dcirclesegment(in vec2 x,in float r,in float p0,in float p1,out float d);void stroke(in float d0,in float s,out float d);void smoothmin(in float a,in float b,in float k,out float dst);void dglyph(in vec2 x,in float ordinal,in float size,out float dst){float dis;dbox(x,2.*size*c.xx,dis);if(dis>0.){dst=dis+.5*size;return ;}float nglyphs,offset=0;rfloat(1.,nglyphs);for(float i=0.;i<nglyphs;i+=1.){float ord;rfloat(2.+2.*i,ord);ord=floor(ord);if(ord==ordinal){rfloat(2.+2.*i+1.,offset);offset=floor(offset);break;}}if(offset==0.){dst=1.;return ;}float d=1.,da=1.;float nlines;rfloat(offset,nlines);nlines=floor(nlines);offset+=1.;for(float i=0.;i<nlines;i+=1.){float x1;rfloat(offset,x1);offset+=1.;float y1;rfloat(offset,y1);offset+=1.;float x2;rfloat(offset,x2);offset+=1.;float y2;rfloat(offset,y2);offset+=1.;dlinesegment(x,size*vec2 (x1,y1),size*vec2 (x2,y2),da);d=min(d,da);}stroke(d,.2*size,d);float nsmoothlines,db=1.;da=1.;rfloat(offset,nsmoothlines);nsmoothlines=floor(nsmoothlines);offset+=1.;for(float i=0.;i<nsmoothlines;i+=1.){float x1;rfloat(offset,x1);offset+=1.;float y1;rfloat(offset,y1);offset+=1.;float x2;rfloat(offset,x2);offset+=1.;float y2;rfloat(offset,y2);offset+=1.;dlinesegment(x,size*vec2 (x1,y1),size*vec2 (x2,y2),db);da=min(da,db);}stroke(da,.2*size,da);smoothmin(d,da,.1*size,d);dst=d;}\0";
const char *dstring_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rfloat(in float off,out float val);void dbox(in vec2 x,in vec2 b,out float dst);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dstring(in vec2 x,in float ordinal,in float size,out float dst){float stroff0;rfloat(0.,stroff0);stroff0=floor(stroff0);float nstrings;rfloat(stroff0,nstrings);nstrings=floor(nstrings);if(ordinal>=nstrings){dst=1.;return ;}float stroff;rfloat(stroff0+1.+2.*ordinal,stroff);stroff=floor(stroff);float len;rfloat(stroff0+2.+2.*ordinal,len);len=floor(len);vec2 dx=mod(x-size,2.*size)-size,ind=ceil((x-dx+size)/2./size);float bound;dbox(x-size*(len-3.)*c.xy,vec2 (size*len,1.*size),bound);if(bound>0.){dst=bound+.5*size;return ;}float da;rfloat(stroff+ind.x,da);da=floor(da);dglyph(dx,da,.7*size,dst);}\0";
const char *dfloat_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dfloat(in vec2 x,in float num,in float size,out float dst){float d=1.,index=0.;float sign=sign(num),exp=0.;if(sign<0.){float da;dglyph(x,45.,.7*size,da);d=min(d,da);index+=1.;num*=-1.;}for(exp=-15.;exp<15.;exp+=1.)if(floor(num*pow(10.,exp))!=0.)break;exp*=-1.;for(float i=exp;i>=max(exp-5.,-33);i-=1.){float po=pow(10.,i);float ca=floor(num/po);num-=ca*po;float da;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;if(i==exp){dglyph(x-2.*index*size*c.xy,46.,.7*size,da);d=min(d,da);index+=1.;}}float db;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,101.,.7*size,db);d=min(d,db);index+=1.;if(exp<0.){dglyph(x+.7*size*c.xy-2.*index*size*c.xy,45.,.7*size,db);d=min(d,db);index+=1.;exp*=-1.;}float ca=floor(exp/10.);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,db);d=min(d,db);index+=1.;ca=floor(exp-10.*ca);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,db);d=min(d,db);index+=1.;dst=d;}\0";
const char *dint_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dint(in vec2 x,in float num,in float size,in float ndigits,out float dst){float d=1.,index=0.;if(num==0.){index=ndigits;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.,.7*size,dst);return ;}float sign=sign(num),exp=0.;if(sign<0.){float da;dglyph(x,45.,.7*size,da);d=min(d,da);index+=1.;num*=-1.;}for(exp=-15.;exp<15.;exp+=1.)if(floor(num*pow(10.,exp))!=0.)break;exp*=-1.;int hit=0;for(float i=ndigits;i>=0.;i-=1.){float po=pow(10.,i);float ca=floor(num/po);if(ca==0.){if(hit==0){index+=1.;continue;}}else hit=1;num-=ca*po;float da;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;}dst=d;}\0";
const char *dtime_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dtime(in vec2 x,in float num,in float size,out float dst){float d=1.,index=0.;num=floor(num);float ca=floor(num/600.),da=1.;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;num-=ca*600.;ca=floor(num/60.);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;num-=ca*60.;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,58.,.7*size,da);d=min(d,da);index+=1.;ca=floor(num/10.);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;num-=ca*10.;ca=floor(num/1.);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);dst=d;}\0";
const char *addwindow_source = "#version 130\nuniform vec2 iResolution;const vec3 c=vec3 (1.,0.,-1.);void dbox(in vec2 x,in vec2 b,out float d);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void stroke(in float d0,in float s,out float d);\n"
"#define sm(d)smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d)\n"
"void addwindow(in vec2 uv,inout vec3 col,in vec2 dimensions){float d=1.;dbox(uv,dimensions,d);vec3 gcol=length(col)/sqrt(3.)*c.xxx;const vec3 window_raw=vec3 (0.08,0.07,0.16);vec3 window_background=mix(mix(col,window_raw,.2),mix(gcol,window_raw,.8),clamp((.5-uv.y/dimensions.y*.5),0.,1.));col=mix(col,.1*gcol,sm(d/8.));col=mix(col,window_background,sm(d));d=abs(d-.002)-.002;d=mix(d,1.,step(abs(uv.y),dimensions.y-.01));col=mix(col,c.xxx,sm(d));dbox(uv-(dimensions-.04*c.xx),.015*c.xx,d);col=mix(col,c.xxx,sm(d+.005));stroke(d,.001,d);col=mix(col,c.xxx,sm(d));dlinesegment(uv,dimensions-.05*c.xx,dimensions-.03*c.xx,d);float da;dlinesegment(uv,dimensions-vec2 (.05,.03),dimensions-vec2 (.03,.05),da);d=min(d,da);stroke(d,.002,d);col=mix(col,c.yyy,sm(d));}\0";
const char *ddeadline_source = "#version 130\nvoid dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);const int npts=368;const float path[npts]=float [npts](0.114,-0.123,0.102,-0.137,0.102,-0.137,0.040,-0.137,0.040,-0.137,-0.013,-0.078,-0.013,-0.078,-0.064,-0.137,-0.064,-0.137,-0.153,-0.137,-0.153,-0.137,-0.165,-0.123,-0.165,-0.123,-0.176,-0.137,-0.176,-0.137,-0.380,-0.137,-0.380,-0.137,-0.500,0.002,-0.500,0.002,-0.412,0.104,-0.412,0.104,-0.393,0.104,-0.393,0.104,-0.480,0.002,-0.480,0.002,-0.467,0.002,-0.467,0.002,-0.380,0.104,-0.380,0.104,-0.297,0.104,-0.297,0.104,-0.253,0.054,-0.253,0.054,-0.238,0.073,-0.238,0.073,-0.259,0.073,-0.259,0.073,-0.288,0.104,-0.288,0.104,0.030,0.104,0.030,0.104,-0.039,0.023,-0.039,0.023,-0.196,0.023,-0.196,0.023,-0.205,0.033,-0.205,0.033,-0.228,0.002,-0.228,0.002,-0.044,0.002,-0.044,0.002,0.042,0.104,0.042,0.104,0.067,0.104,0.067,0.104,-0.020,0.002,-0.020,0.002,-0.011,0.002,-0.011,0.002,0.077,0.104,0.077,0.104,0.090,0.104,0.090,0.104,0.057,0.145,0.057,0.145,0.123,0.145,0.123,0.145,0.156,0.104,0.156,0.104,0.357,0.105,0.357,0.105,0.332,0.072,0.332,0.072,0.260,0.072,0.260,0.072,0.301,0.023,0.301,0.023,0.404,0.145,0.404,0.145,0.470,0.145,0.470,0.145,0.349,0.001,0.349,0.001,0.255,0.001,0.255,0.001,0.195,0.072,0.195,0.072,0.185,0.072,0.185,0.072,0.251,-0.009,0.251,-0.009,0.352,-0.009,0.352,-0.009,0.481,0.145,0.481,0.145,0.500,0.145,0.500,0.145,0.376,-0.009,0.376,-0.009,0.442,-0.086,0.442,-0.086,0.143,-0.086,0.143,-0.086,0.127,-0.107,0.127,-0.107,0.396,-0.107,0.396,-0.107,0.428,-0.145,0.428,-0.145,0.133,-0.145,0.133,-0.145,0.114,-0.123,-0.155,-0.050,-0.131,-0.050,-0.131,-0.050,-0.094,-0.093,-0.094,-0.093,-0.047,-0.039,-0.047,-0.039,-0.144,-0.038,-0.144,-0.038,-0.240,-0.037,-0.240,-0.037,-0.252,-0.025,-0.252,-0.025,-0.263,-0.037,-0.263,-0.037,-0.398,-0.039,-0.398,-0.039,-0.340,-0.107,-0.340,-0.107,-0.180,-0.107,-0.180,-0.107,-0.231,-0.050,-0.231,-0.050,-0.164,-0.050,-0.164,-0.050,-0.112,-0.116,-0.112,-0.116,-0.107,-0.109,-0.107,-0.109,-0.155,-0.050,0.125,-0.038,0.032,-0.036,0.032,-0.036,0.065,0.003,0.065,0.003,0.175,0.003,0.175,0.003,0.115,0.072,0.115,0.072,0.022,-0.037,0.022,-0.037,0.073,-0.098,0.073,-0.098,0.125,-0.038,0.350,-0.056,0.336,-0.037,0.336,-0.037,0.210,-0.037,0.210,-0.037,0.200,-0.024,0.200,-0.024,0.172,-0.056,0.172,-0.056,0.350,-0.056,-0.281,0.023,-0.299,0.023,-0.299,0.023,-0.341,0.071,-0.341,0.071,-0.401,0.002,-0.401,0.002,-0.297,0.002,-0.297,0.002,-0.281,0.023,-0.063,0.073,-0.172,0.073,-0.172,0.073,-0.186,0.055,-0.186,0.055,-0.076,0.055,-0.076,0.055,-0.063,0.073);void ddeadline(in vec2 x,out float ret){ret=1.;float da;float n=0.;for(int i=0;i<npts/4;++i){vec2 ptsi=vec2 (path[4*i],path[4*i+1]),ptsip1=vec2 (path[4*i+2],path[4*i+3]),k=x-ptsi,d=ptsip1-ptsi;float beta=k.x/d.x,alpha=d.y*k.x/d.x-k.y;n+=step(.0,beta)*step(beta,1.)*step(0.,alpha);dlinesegment(x,ptsi,ptsip1,da);ret=min(ret,da);}ret=mix(ret,-ret,mod(n,2.));}\0";
const char *dpolygon_source = "#version 130\nconst float pi=acos(-1.);void dpolygon(in vec2 x,in float N,out float d){d=2.0*pi/N;float t=mod(acos(x.x/length(x)),d)-0.5*d;d=-0.5+length(x)*cos(t)/cos(0.5*d);}\0";
const char *dspacepigs_source = "#version 130\nvoid dpolygon(in vec2 x,in float N,out float d);void dcircle(in vec2 x,out float d);void dear(in vec2 x,out float d){d=abs(2.*x.y)-.95+smoothstep(0.,.5,clamp(abs(x.x),0.,1.))-.5*min(-abs(x.x),.01);}void dspacepigs(in vec2 x,out float d){dpolygon(.5*x,6.0,d);float da,d0;dcircle(2.5*x,d0);d0/=2.5;dear(vec2 (2.,5.)*x-vec2 (.8,1.3),da);d0=min(d0,da/10.);dear(vec2 (2.,5.)*x+vec2 (.8,-1.3),da);d0=min(d0,da/10.);dcircle(6.*x-vec2 (0.,-.5),da);d0=max(d0,-da/6.);dcircle(24.*x-vec2 (-1.5,-2.),da);d0=min(d0,da/24.);dcircle(24.*x-vec2 (1.5,-2.),da);d0=min(d0,da/24.);dcircle(16.*x-vec2 (-3.5,2.5),da);d0=max(d0,-da/16.);dcircle(16.*x-vec2 (3.5,2.5),da);d0=max(d0,-da/16.);dcircle(24.*x-vec2 (-5.,3.5),da);d0=min(d0,da/24.);dcircle(24.*x-vec2 (5.,3.5),da);d0=min(d0,da/24.);d=max(d,-d0);}\0";
const char *analytical_box_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void analytical_box(in vec3 o,in vec3 dir,in vec3 size,out float d){vec3 tlo=min((size-o)/dir,(-size-o)/dir);vec2 abxlo=abs(o.yz+tlo.x*dir.yz),abylo=abs(o.xz+tlo.y*dir.xz),abzlo=abs(o.xy+tlo.z*dir.xy);vec4 dn=100.*c.xyyy;dn=mix(dn,vec4 (tlo.x,c.xyy),float (all(lessThan(abxlo,size.yz)))*step(tlo.x,dn.x));dn=mix(dn,vec4 (tlo.y,c.yxy),float (all(lessThan(abylo,size.xz)))*step(tlo.y,dn.x));dn=mix(dn,vec4 (tlo.z,c.yyx),float (all(lessThan(abzlo,size.xy)))*step(tlo.z,dn.x));d=dn.r;}\0";
const char *hash33_source = "void hash33(in vec3 p3,out vec3 d){p3=fract(p3*vec3 (.1031,.1030,.0973));p3+=dot(p3,p3.yxz+33.33);d=fract((p3.xxy+p3.yxx)*p3.zyx);}\0";
const char *dvoronoi3_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void hash33(in vec3 p3,out vec3 d);void dist3(in vec3 a,in vec3 b,out float d){d=length(b-a);}void nearest_controlpoint3(in vec3 x,out vec3 p){float dmin=1.e5,d;vec3 dp,y=floor(x);for(float i=-1.;i<=1.;i+=1.)for(float j=-1.;j<=1.;j+=1.){for(float k=-1.;k<=1.;k+=1.){hash33(y+vec3 (i,j,k),dp);dp+=y+vec3 (i,j,k);dist3(x,dp,d);if(d<dmin){dmin=d;p=dp;}}}}void dvoronoi3(in vec3 x,out float d,out vec3 p,out float control_distance){d=1.e4;vec3 y,dp;nearest_controlpoint3(x,p);y=floor(p);control_distance=1.e4;for(float i=-2.;i<=2.;i+=1.)for(float j=-2.;j<=2.;j+=1.){for(float k=-1.;k<=1.;k+=1.){if(i==0.&&j==0.&&k==0.)continue;hash33(y+vec3 (i,j,k),dp);dp+=y+vec3 (i,j,k);vec3 o=p-dp;float l=length(o);d=min(d,abs(.5*l-dot(x-dp,o)/l));control_distance=min(control_distance,.5*l);}}}\0";
const char *dsmoothvoronoi3_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void hash33(in vec3 p3,out vec3 d);void smoothmin(in float a,in float b,in float k,out float dst);void dist3_s(in vec3 a,in vec3 b,out float d){d=length(b-a);}void nearest_controlpoint3_s(in vec3 x,out vec3 p){float dmin=1.e5,d;vec3 dp,y=floor(x);for(float i=-1.;i<=1.;i+=1.)for(float j=-1.;j<=1.;j+=1.){for(float k=-1.;k<=1.;k+=1.){hash33(y+vec3 (i,j,k),dp);dp+=y+vec3 (i,j,k);dist3_s(x,dp,d);if(d<dmin){dmin=d;p=dp;}}}}void dsmoothvoronoi3(in vec3 x,out float d,out vec3 p,out float control_distance){d=1.e4;vec3 y,dp;nearest_controlpoint3_s(x,p);y=floor(p);control_distance=1.e4;for(float i=-2.;i<=2.;i+=1.)for(float j=-2.;j<=2.;j+=1.){for(float k=-1.;k<=1.;k+=1.){if(i==0.&&j==0.&&k==0.)continue;hash33(y+vec3 (i,j,k),dp);dp+=y+vec3 (i,j,k);vec3 o=p-dp;float l=length(o);smoothmin(d,abs(.5*l-dot(x-dp,o)/l),.15,d);smoothmin(control_distance,.5*l,.15,control_distance);}}}\0";
const char *dstar_source = "#version 130\nconst float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);void dstar(in vec2 x,in float N,in vec2 R,out float dst){float d=pi/N,p0=acos(x.x/length(x)),p=mod(p0,d),i=mod(round((p-p0)/d),2.);x=length(x)*vec2 (cos(p),sin(p));vec2 a=mix(R,R.yx,i),p1=a.x*c.xy,ff=a.y*vec2 (cos(d),sin(d))-p1;ff=ff.yx*c.zx;dst=dot(x-p1,ff)/length(ff);}\0";
const char *smoothmax_source = "#version 130\nvoid smoothmin(in float a,in float b,in float k,out float dst);void smoothmax(in float a,in float b,in float k,out float res){smoothmin(a,b,k,res);res=a+b-res;}\0";
const char *dstar3_source = "#version 130\nvoid dstar(in vec2 x,in float N,in vec2 R,out float dst);void smoothmax(in float a,in float b,in float k,out float res);void dstar3(in vec3 x,in float N,in vec2 R,out float dst){float d;dstar(x.xy,N,R,dst);dstar(x.yz,N,R,d);smoothmax(-d,-dst,.15,dst);dstar(x.zx,N,R,d);smoothmax(-d,dst,.15,dst);}\0";
const char *dhexagonpattern_source = "void dhexagonpattern(in vec2 p,out float d,out vec2 ind){vec2 q=vec2 (p.x*1.2,p.y+p.x*0.6);vec2 pi=floor(q);vec2 pf=fract(q);float v=mod(pi.x+pi.y,3.0);float ca=step(1.,v);float cb=step(2.,v);vec2 ma=step(pf.xy,pf.yx);d=dot(ma,1.0-pf.yx+ca*(pf.x+pf.y-1.0)+cb*(pf.yx-2.0*pf.xy));ind=pi+ca-cb*ma;ind=vec2 (ind.x/1.2,ind.y);ind=vec2 (ind.x,ind.y-ind.x*.6);}\0";
const char *dmercury_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dbox(in vec2 x,in vec2 b,out float d);void dpolygon(in vec2 x,in float N,out float d);void dmercury(in vec2 x,out float d){dpolygon(.5*x,6.0,d);float da;x+=.1*c.yx;dbox(x-.35*c.yx,vec2 (.4,.35),da);d=max(d,-da);dbox(x-.7*c.yx,vec2 (.2,.2),da);d=min(d,da);dbox(x-.25*c.yx,vec2 (.2,.05),da);d=min(d,da);dbox(x+.2*c.yx,vec2 (.1,.4),da);d=max(d,-da);dbox(x+.2*c.yx,vec2 (.4,.1),da);d=max(d,-da);}\0";
const char *dtriangle_source = "void dtriangle(in vec2 p,in vec2 p0,in vec2 p1,in vec2 p2,out float dst){vec2 e0=p1-p0;vec2 e1=p2-p1;vec2 e2=p0-p2;vec2 v0=p-p0;vec2 v1=p-p1;vec2 v2=p-p2;vec2 pq0=v0-e0*clamp(dot(v0,e0)/dot(e0,e0),0.0,1.0);vec2 pq1=v1-e1*clamp(dot(v1,e1)/dot(e1,e1),0.0,1.0);vec2 pq2=v2-e2*clamp(dot(v2,e2)/dot(e2,e2),0.0,1.0);float s=sign(e0.x*e2.y-e0.y*e2.x);vec2 d=min(min(vec2 (dot(pq0,pq0),s*(v0.x*e0.y-v0.y*e0.x)),vec2 (dot(pq1,pq1),s*(v1.x*e1.y-v1.y*e1.x))),vec2 (dot(pq2,pq2),s*(v2.x*e2.y-v2.y*e2.x)));dst=-sqrt(d.x)*sign(d.y);}\0";
const char *rot_source = "#version 130\nvoid rot(in float phi,out mat2 m){vec2 cs=vec2 (cos(phi),sin(phi));m=mat2 (cs.x,-cs.y,cs.y,cs.x);}\0";
const char *dschnappsgirls_source = "#version 130\nvoid dtriangle(in vec2 x,in vec2 p0,in vec2 p1,in vec2 p2,out float d);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void stroke(in float d0,in float s,out float d);void dcircle(in vec2 x,out float d);void dpolygon(in vec2 x,in float N,out float d);void dschnappsgirls(in vec2 x,out float d){dpolygon(.5*x,6.0,d);float da,d0;dtriangle(x,vec2 (-.1,-.3),vec2 (.5,-.3),vec2 (.2,.6),d0);dlinesegment(x,vec2 (-.1,.325),vec2 (.5,.325),da);stroke(da,.06,da);d0=max(d0,-da);dcircle(7.*(x-vec2 (.2,.5)),da);d0=max(d0,-da+.5);d0=min(d0,da/7.);dlinesegment(x,vec2 (.125,-.3),vec2 (.125,-.6),da);stroke(da,.06,da);d0=min(d0,da);dlinesegment(x,vec2 (.275,-.3),vec2 (.275,-.6),da);stroke(da,.06,da);d0=min(d0,da);dlinesegment(x,vec2 (0.05,.25),vec2 (.35,.25),da);stroke(da,.085,da);d0=min(d0,da);dlinesegment(x,vec2 (.385,.25),vec2 (.5,-.1),da);stroke(da,.055,da);d0=min(d0,da);dlinesegment(x,vec2 (.017,.25),vec2 (-.1,-.1),da);stroke(da,.055,da);d0=min(d0,da);dtriangle(x,vec2 (-.6,.3),vec2 (-.4,.1),vec2 (-.2,.3),da);stroke(da,.0125,da);d0=min(d0,da);dlinesegment(x,vec2 (-.4,.15),vec2 (-.4,-.1),da);stroke(da,.0125,da);d0=min(d0,da);dtriangle(x,vec2 (-.5,-.15),vec2 (-.3,-.15),vec2 (-.4,-.1),da);d0=min(d0,da);dtriangle(x,vec2 (-.55,.25),vec2 (-.4,.1),vec2 (-.25,.25),da);d0=min(d0,da);dlinesegment(x,vec2 (-.4,.1),vec2 (-.2,.5),da);stroke(da,.01,da);d0=min(d0,da);dcircle(24.*(x-vec2 (-.3,.3)),da);d0=min(d0,da/24.);dcircle(24.*(x-vec2 (-.25,.4)),da);d0=min(d0,da/24.);d=max(d,-d0);}\0";
const char *dhaujobb_source = "#version 130\nconst vec3 c=vec3 (1.0,0.0,-1.0);const float pi=acos(-1.);void dpolygon(in vec2 x,in float N,out float d);void rot(in float phi,out mat2 m);void dcircle(in vec2 x,out float d);void dbox(in vec2 x,in vec2 b,out float d);void dhaujobb(in vec2 x,out float d){dpolygon(.5*x,6.0,d);float da,d0;mat2 m;rot(.3,m);x=1.1*x*m;x.x*=1.1;x+=vec2 (-.05,.2);dbox(x+.35*c.xx,vec2 (.1,.05),d0);dbox(x+vec2 (.3,.25),vec2 (.05,.15),da);d0=min(d0,da);dbox(x+vec2 (.2,.15),vec2 (.1,.05),da);d0=min(d0,da);dbox(x+vec2 (.15,.05),vec2 (.05,.15),da);d0=min(d0,da);dbox(x-vec2 (.65,.35),vec2 (.05,.15),da);d0=min(d0,da);rot(.2,m);dbox(m*(x-vec2 (.25,.15)),vec2 (.45,.05),da);d0=min(d0,da);dbox(m*(x-vec2 (-.15,.35)),vec2 (.45,.05),da);d0=min(d0,da);rot(pi/8.,m);dbox(m*(x-vec2 (.0,.25)),vec2 (.1,.15),da);d0=min(d0,da);dbox(m*(x-vec2 (.1,-.0)),vec2 (.025,.1),da);d0=min(d0,da);rot(.3,m);dbox(m*(x-vec2 (.235,.535)),vec2 (.035,.15),da);d0=min(d0,da);dbox(m*(x-vec2 (.225,.7)),vec2 (.075,.025),da);d0=min(d0,da);rot(-.2,m);dbox(m*(x+vec2 (.585,-.2)),vec2 (.0375,.1),da);d0=min(d0,da);dcircle(6.*(x-vec2 (-.15,.58)),da);d0=min(d0,da/6.);d0-=.05*(abs(x.x)+abs(x.y)-.2);d=max(d,-d0);}\0";
const char *dkewlers_source = "#version 130\nvoid dbox(in vec2 x,in vec2 b,out float d);void dpolygon(in vec2 x,in float N,out float d);void dkewlers(in vec2 x,out float d){dpolygon(.5*x,6.0,d);float da,d0;x*=1.2;dbox(x-vec2 (0.,-.3),vec2 (.6,.1),d0);dbox(x-vec2 (-.5,-.0),vec2 (.1,.25),da);d0=min(d0,da);dbox(x-vec2 (-.5+1./3.,.25),vec2 (.1,.5),da);d0=min(d0,da);dbox(x-vec2 (-.5+2./3.,-.0),vec2 (.1,.25),da);d0=min(d0,da);dbox(x-vec2 (.5,-.0),vec2 (.1,.25),da);d0=min(d0,da);d=max(d,-d0);}\0";
const char *dfarbrausch_source = "#version 130\nvoid dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void dpolygon(in vec2 x,in float N,out float d);void stroke(in float d0,in float s,out float d);void dfarbrausch(in vec2 x,out float d){dpolygon(.5*x,6.0,d);float da,d0;x+=vec2 (.1,0.);x*=1.2;dlinesegment(x,vec2 (-.65,.05),vec2 (-.5,.05),d0);dlinesegment(x,vec2 (-.5,.05),vec2 (-.2,-.49),da);d0=min(d0,da);dlinesegment(x,vec2 (-.2,-.49),vec2 (-.0,-.49),da);d0=min(d0,da);dlinesegment(x,vec2 (-.0,-.49),vec2 (-.27,.0),da);d0=min(d0,da);dlinesegment(x,vec2 (-.07,0.),vec2 (-.27,.0),da);d0=min(d0,da);dlinesegment(x,vec2 (.2,-.49),vec2 (-.07,.0),da);d0=min(d0,da);dlinesegment(x,vec2 (.4,-.49),vec2 (.13,.0),da);d0=min(d0,da);dlinesegment(x,vec2 (.4,-.49),vec2 (.2,-.49),da);d0=min(d0,da);dlinesegment(x,vec2 (.33,0.),vec2 (.13,.0),da);d0=min(d0,da);dlinesegment(x,vec2 (.33,0.),vec2 (.51,-.33),da);d0=min(d0,da);dlinesegment(x,vec2 (.6,-.15),vec2 (.51,-.33),da);d0=min(d0,da);dlinesegment(x,vec2 (.53,0.),vec2 (.6,-.15),da);d0=min(d0,da);dlinesegment(x,vec2 (.7,0.),vec2 (.53,.0),da);d0=min(d0,da);dlinesegment(x,vec2 (.7,0.),vec2 (.68,-.04),da);d0=min(d0,da);dpolygon(5.*(x+vec2 (.3,.65)),6.,da);d0=min(d0,da/5.);dpolygon(5.*(x+vec2 (-.5,.65)),6.,da);d0=min(d0,da/5.);stroke(d0,.035,d0);d=max(d,-d0);}\0";
const char *d5711_source = "#version 130\nvoid dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void dpolygon(in vec2 x,in float N,out float d);const int npts=208;const float path[npts]=float [npts](-0.500,0.145,-0.500,-0.029,-0.500,-0.029,-0.353,-0.029,-0.353,-0.029,-0.353,-0.087,-0.353,-0.087,-0.500,-0.087,-0.500,-0.087,-0.500,-0.145,-0.500,-0.145,-0.280,-0.145,-0.280,-0.145,-0.280,0.029,-0.280,0.029,-0.427,0.029,-0.427,0.029,-0.427,0.087,-0.427,0.087,-0.280,0.087,-0.280,0.087,-0.280,0.145,-0.280,0.145,-0.500,0.145,-0.500,0.145,-0.500,0.145,-0.240,0.145,-0.240,0.087,-0.240,0.087,-0.093,0.087,-0.093,0.087,-0.093,0.029,-0.093,0.029,-0.020,0.029,-0.020,0.029,-0.020,0.145,-0.020,0.145,-0.240,0.145,-0.093,0.029,-0.167,0.029,-0.167,0.029,-0.167,-0.087,-0.167,-0.087,-0.093,-0.087,-0.093,-0.087,-0.093,0.029,-0.093,0.029,-0.093,0.029,-0.167,-0.087,-0.240,-0.087,-0.240,-0.087,-0.240,-0.145,-0.240,-0.145,-0.167,-0.145,-0.167,-0.145,-0.167,-0.087,0.093,0.145,0.093,0.087,0.093,0.087,0.020,0.087,0.020,0.087,0.020,0.029,0.020,0.029,0.093,0.029,0.093,0.029,0.093,-0.087,0.093,-0.087,0.020,-0.087,0.020,-0.087,0.020,-0.145,0.020,-0.145,0.240,-0.145,0.240,-0.145,0.240,-0.087,0.240,-0.087,0.167,-0.087,0.167,-0.087,0.167,0.145,0.167,0.145,0.093,0.145,0.353,0.145,0.353,0.087,0.353,0.087,0.280,0.087,0.280,0.087,0.280,0.029,0.280,0.029,0.353,0.029,0.353,0.029,0.353,-0.087,0.353,-0.087,0.280,-0.087,0.280,-0.087,0.280,-0.145,0.280,-0.145,0.500,-0.145,0.500,-0.145,0.500,-0.087,0.500,-0.087,0.427,-0.087,0.427,-0.087,0.427,0.145,0.427,0.145,0.353,0.145);void d5711(in vec2 x,out float ret){float d;dpolygon(.5*x,6.0,d);x*=.7;ret=1.;float da;float n=0.;for(int i=0;i<npts/4;++i){vec2 ptsi=vec2 (path[4*i],path[4*i+1]),ptsip1=vec2 (path[4*i+2],path[4*i+3]),k=x-ptsi,d=ptsip1-ptsi;float beta=k.x/d.x,alpha=d.y*k.x/d.x-k.y;n+=step(.0,beta)*step(beta,1.)*step(0.,alpha);dlinesegment(x,ptsi,ptsip1,da);ret=min(ret,da);}ret=mix(ret,-ret,mod(n,2.));ret=max(d,-ret);ret/=.7;}\0";
const char *sub_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void sub(in vec2 sda,in vec2 sdb,out vec2 sdf){sdf=(sda.x>sdb.x)?abs(sda):abs(sdb)*c.zx;}\0";
const char *doctahedron_source = "#version 130\nvoid doctahedron(in vec3 x,in float h,in float w,out float d){x.xz=abs(x.xz);x.y=abs(x.y)-h;d=max(x.z,x.x)+(x.y*w);}\0";
const char *ocean_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);void rand(in vec2 x,out float n);void hash11(in float p,out float d);void hash12(in vec2 p,out float d);void hash21(in float p,out vec2 d);void hash22(in vec2 p,out vec2 d);void hash31(in float p,out vec3 d);void stroke(in float d0,in float s,out float d);void lfnoise(in vec2 t,out float n);void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance);void dbox(in vec2 x,in vec2 b,out float d);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);float sm(in float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void smoothmin(in float a,in float b,in float k,out float dst);void gerst(in vec2 x,out float z){float df,A=1.,da;vec2 dk,k;z=0.;for(float f=1.;f<6.;f*=1.1){hash11(f,df);f*=(.95+.2*df);hash21(f+2337.,k);k*=64./f+.5;hash11(f+1337.,da);A*=(1.+.3*da);z+=A*pow(.5*(1.+sin(dot(k,x)+f*iTime)),2.);}}void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void scene(in vec3 x,out vec2 sdf){float g;gerst(x.xy,g);sdf=vec2 (x.z-.002*g,1.);sdf.x=abs(sdf.x)-.002;add(sdf,vec2 (x.z+.2,2.),sdf);}void normal(in vec3 x,out vec3 n,in float dx);void palette(in float scale,out vec3 col){const int N=5;const vec3 colors[N]=vec3 [N](vec3 (0.04,0.04,0.15),vec3 (0.18,0.32,0.46),vec3 (0.66,0.43,0.62),vec3 (0.96,0.78,0.88),vec3 (0.40,0.00,0.18));float index=floor(scale*float (N)),remainder=scale*float (N)-index;col=mix(colors[int (index)],colors[int (index)+1],remainder);}float dspiral(vec2 x,float a,float d);void colorize(in vec2 x,inout vec3 col){float v,n=64.,r;vec2 ind;dvoronoi(n*x,v,ind,r);rand(ind,r);vec2 y=x-ind/n;vec3 c1;rand(ind+1337.,c1.x);rand(ind+2337.,c1.y);rand(ind+3337.,c1.z);c1*=vec3 (1.,.7,.3);c1=.5+.5*c1;c1*=vec3 (.4,.6,1.);float d=length(y)-.0002*r;if(r>.75)col=mix(col,c1,sm(d));if(r>.5){col=mix(col,mix(col,2.*c1,.8),sm(d-.004*r*r));col=mix(col,mix(col,3.*c1,.4),sm(d-.01*r*r));}float cpa;dvoronoi(2.*n*x,v,ind,cpa);y=x-ind/n/2.;rand(ind,r);d=length(y)-.002*r;col=mix(col,c.xxx,sm(d));lfnoise(x.xy-v*v*v,d);col=mix(col,c.yyy,.5+.5*d);col=.6*col+.3*step(.8,col);col*=2.;v=dspiral(x,.1,.01);col=mix(col,c.yyy,1.-sm(v*6.e-3));col=mix(col,2.5*col,sm(v*2.e-3));}void main(){vec2 uv=(gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,s;vec3 col=c.yyy,o=.5*c.yyx+c.yzy,r=c.xyy,t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x;int N=150,i;t=uv.x*r+uv.y*u;dir=normalize(t-o);vec3 c1;float d=-(o.z-.15)/dir.z;vec3 o0,dir0;float d0;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=s.x;}if(i<N){vec3 l=c.yyx;normal(x,n,1.e-4);if(s.y==1.){palette(x.z/.22,col);col=.1*col+.1*col*dot(l,n)+1.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);}o=x;d=1.e-2;dir=refract(dir,n,.5);vec3 c1;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-3)break;d+=s.x;}if(i<N){vec3 l=c.yyx;normal(x,n,2.e-3);if(s.y==1.){palette(x.z/.22,c1);c1=.1*c1+.1*c1*dot(l,n)+1.6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);}else if(s.y==2.){c1=vec3 (0.26,0.16,0.32);float v=.5+.5*sin(100.*x.y);c1=mix(c1,2.*c1,v);c1=.1*c1+.1*c1*dot(l,n)+1.6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);}}col=mix(col,c1,.1);}col=3.*col*col;gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *logo210_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);float a=1.0;float nbeats,iScale;void dbox3(in vec3 x,in vec3 b,out float d);void rot3(in vec3 p,out mat3 rot);void stroke(in float d0,in float s,out float d);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void dbox210(in vec3 x,in float size,out vec2 sdf);mat3 R;void scene(in vec3 x,out vec2 sdf){sdf=c.xy;float d,da;rot3(vec3 (-pi/2.,0.,pi/2.),R);x=R*x;vec2 sda=c.xy;dbox210(x+.1*c.xyy,.5,sdf);rot3(vec3 (pi/2.,0.,pi/2.),R);x=R*x;dbox210(x,5.,sda);add(sdf,sda,sdf);rot3(vec3 (pi/2.,-pi/2.,pi/2.),R);x=R*x;dbox210(x-2.*c.yxy,50.,sda);add(sdf,sda,sdf);stroke(sdf.x,.001,sdf.x);dbox3(x,100.*c.xxx,sda.x);sda.y=2.;add(sdf,sda*c.zx,sdf);}void normal(in vec3 x,out vec3 n,in float dx);void mainImage(out vec4 fragColor,in vec2 fragCoord){float a=iResolution.x/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);vec3 col=c.xxx;float d=0.;vec2 s;vec3 o,t,dir,x,n;mat3 Ra,Rb;rot3(mix(c.yyy,vec3 (-5.7884463,2.4242211,0.3463173),clamp((iTime-6.)/1.5,0.,1.)),Ra);rot3(mix(c.yyy,vec3 (-2.*pi+5.7884463,-2.4242211,-0.3463173)+pi*c.xyy,clamp((iTime-10.),0.,1.)),Rb);o=Ra*mix(mix(mix(c.yyy-.005*c.yyx,c.yyx,clamp(iTime/2.,0.,1.)),10.*c.yyx,clamp((iTime-2.)/2.,0.,1.)),100.*c.yyx,clamp((iTime-4.)/2.,0.,1.));t=c.yyy;int N=650,i;dir=Rb*Ra*normalize(vec3 (uv,-1.));for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=s.x;}if(s.x<1.e-4){normal(x,n,5.e-4);vec3 l=normalize(x+.1*n);if(s.y==1.){col=vec3 (0.27,0.36,0.48);col=.3*col+.4*col*abs(dot(l,n))+.6*col*abs(pow(dot(reflect(-l,n),dir),3.));}else if(s.y==2.){col=.7*c.xxx;col=.5*col+.4*col*abs(dot(l,n))+.8*col*abs(pow(dot(reflect(-l,n),dir),3.));vec3 c1=c.yyy;o=x;dir=reflect(dir,n);d=1.e-1;N=150;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=s.x;}if(s.x<1.e-4){normal(x,n,5.e-4);vec3 l=normalize(x+.1*n);if(s.y==1.){c1=vec3 (0.27,0.36,0.48);c1=.3*c1+.4*c1*abs(dot(l,n))+.6*c1*abs(pow(dot(reflect(-l,n),dir),3.));}else if(s.y==2.){c1=.7*c.xxx;c1=.5*c1+.4*c1*abs(dot(l,n))+.8*c1*abs(pow(dot(reflect(-l,n),dir),3.));}c1=clamp(c1,0.,1.);col=mix(col,c1,.2);}col=clamp(col,0.,1.);}}col=mix(col,c.xxx,smoothstep(0.,1.,iTime-11.));col=mix(vec3 (0.18,0.24,0.31),col,clamp(iTime,0.,1.));fragColor=vec4 (clamp(col,0.,1.),1.0);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
const char *graffiti_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);float a=1.0;void hash22(in vec2 x,out vec2 y);void rand(in vec2 x,out float n);void lfnoise(in vec2 t,out float n);void dspline2(in vec2 x,in vec2 p0,in vec2 p1,in vec2 p2,out float ds);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void stroke(in float d0,in float s,out float d);void smoothmin(in float a,in float b,in float k,out float dst);void d_h(in vec2 x,out float d){float da;dspline2(vec2 (abs(x.x)-.1,abs(x.y)),vec2 (.15,.25),vec2 (.05,.25),vec2 (.05,0.),d);dlinesegment(x,vec2 (-.075,0.),vec2 (.075,0.),da);smoothmin(d,da,.1,d);}void d_a(in vec2 x,out float d){float da;dspline2(vec2 (abs(x.x)-.1,x.y),vec2 (.15,-.25),vec2 (.05,-.25),vec2 (.05,0.),d);dspline2(vec2 (abs(x.x)-.1,x.y),vec2 (.05,0.),vec2 (.05,.25),vec2 (-.1,.25),da);d=min(d,da);dlinesegment(x,vec2 (-.075,0.),vec2 (.075,0.),da);smoothmin(d,da,.1,d);}void d_r(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(x.y-.1)-.15),vec2 (.0,-.05),vec2 (.25,.05),vec2 (.25,-.15),da);smoothmin(d,da,.1,d);dspline2(x,vec2 (0.,-.05),vec2 (0.,-.25),vec2 (.35,-.25),da);smoothmin(d,da,.1,d);}void d_d(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(x.y)-.1),vec2 (-.05,.15),vec2 (.25,.25),vec2 (.25,-.1),da);smoothmin(d,da,.1,d);}void d_c(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(x.y)-.1),vec2 (-.05,.15),vec2 (.25,.25),vec2 (.25,0.),da);smoothmin(d,da,.1,d);}void d_y(in vec2 x,out float d){float da;dspline2(vec2 (abs(x.x)-.2,x.y),vec2 (-.05,0.25),vec2 (-.05,.1),vec2 (-.2,.1),d);dlinesegment(x,vec2 (0.,-.25),vec2 (0.,.1),da);smoothmin(d,da,.1,d);}void d_b(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(abs(x.y)-.125)-.15),vec2 (.0,-.05),vec2 (.25,.05),vec2 (.25,-.15),da);smoothmin(d,da,.1,d);}void d_e(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(x.y)-.1),vec2 (-.05,.05),vec2 (-.05,.15),vec2 (.25,.15),da);smoothmin(d,da,.1,d);dlinesegment(x,vec2 (-.05,0.),vec2 (.15,0.),da);smoothmin(d,da,.1,d);}void dhardcyber(in vec2 x,out float d){x*=3.;float da;d_h(x+1.8*c.xy,d);d_a(x+1.3*c.xy,da);d=min(d,da);d_r(x+.9*c.xy,da);d=min(d,da);d_d(x+.4*c.xy,da);d=min(d,da);d_c(x-.1*c.xy,da);d=min(d,da);d_y(x-.6*c.xy,da);d=min(d,da);d_b(x-.925*c.xy,da);d=min(d,da);d_e(x-1.4*c.xy,da);d=min(d,da);d_r(x-1.8*c.xy,da);d=min(d,da);stroke(d,.05,d);d/=3.;}float sm(float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void palette(in float scale,out vec3 col){const int N=5;const vec3 colors[N]=vec3 [N](vec3 (0.27,0.13,0.26),vec3 (0.43,0.21,0.33),vec3 (0.69,0.36,0.42),vec3 (0.87,0.52,0.45),vec3 (0.99,0.68,0.53));float index=floor(scale*float (N)),remainder=scale*float (N)-index;col=mix(colors[int (index)],colors[int (index)+1],remainder);}void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance);void zextrude(in float z,in float d2d,in float h,out float d);void scene(in vec3 x,out vec2 sdf){dhardcyber(x.xy,sdf.x);zextrude(x.z,-sdf.x,mix(.0,.1,clamp((iTime-3.5)/.5,0.,1.)),sdf.x);smoothmin(sdf.x,x.z,mix(.001,.1,clamp((iTime-3.5)/.5,0.,1.)),sdf.x);sdf.y=1.;stroke(sdf.x,mix(0.,.01,clamp((iTime-3.5)/.5,0.,1.)),sdf.x);}void normal(in vec3 x,out vec3 n,in float dx);void colorize(in vec2 uv,inout vec3 col){vec3 c1;float d=floor(8.*(.5+.4*tanh(6.*uv.y+uv.x)))/8.;vec2 ind;float v,vn;dvoronoi(16.*uv,v,ind,vn);float r;rand(ind,r);d=(uv.y+.25)/.5-.2*r;palette(clamp(d,0.,1.),c1);col=(.5+.5*r)*c.xxx;dhardcyber(uv,d);d=mix(1.,d,clamp((iTime-3.)/.5,0.,1.));col=mix(col,.7*c.xxx,sm(d-.04));col=mix(col,c1,sm(d));col=mix(col,c.yyy,sm(abs(d-.01)-.01));col=mix(col,vec3 (0.99,0.68,0.53),sm(abs(d-.005)-.005));col=mix(col,1.2*vec3 (0.99,0.68,0.53),sm(abs(d-.005)-.001));col=mix(col,c.yyy,sm(abs(v)-.02));}void main(){a=iResolution.x/iResolution.y;vec2 uv=(gl_FragCoord.xy-.5*iResolution)/iResolution.y,s;vec3 col=c.xxx,o=c.yyx+.4*c.yzy,r=c.xyy,t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x;int N=150,i;t=uv.x*r+uv.y*u;dir=normalize(t-o);vec3 c1;float d=-o.z/dir.z;d=-(o.z-.1)/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(x.z<0.){i=N;break;}d+=s.x;}if(i<N){vec3 l=x+c.yyx;normal(x,n,2.e-6);colorize(x.xy,col);col=.1*col+.1*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);col=mix(c.xxx,col,clamp(iTime/(1.+length(x.xy)),0.,1.));}col=2.*col*col;col=mix(col,c.yyy,clamp(iTime-9.,0.,1.));gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *starsky_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);float a=1.0;void hash22(in vec2 x,out vec2 y);void rand(in vec2 x,out float n);void lfnoise(in vec2 t,out float n);void mfnoise(in vec2 x,in float d,in float b,in float e,out float n);void dvoronoi(in vec2 x,out float d,out vec2 z,out float dv);float dspiral(vec2 x,float a,float d);float sm(float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}float dspiral(vec2 x,float a,float d){float p=atan(x.y,x.x),n=floor((abs(length(x)-a*p)+d*p)/(2.*pi*a));p+=(n*2.+1.)*pi;return -abs(length(x)-a*p)+d*p;}void stroke(in float d0,in float s,out float d);void colorize(in vec2 x,inout vec3 col){float v,n=64.,r,vn;vec2 ind;dvoronoi(n*x,v,ind,vn);rand(ind,r);vec2 y=x-ind/n;vec3 c1;rand(ind+1337.,c1.x);rand(ind+2337.,c1.y);rand(ind+3337.,c1.z);c1*=vec3 (1.,.7,.3);c1=.5+.5*c1;c1*=vec3 (.4,.6,1.);float d=length(y)-.002*r;if(r>.75)col=mix(col,c1,sm(d));if(r>.5){col=mix(col,mix(col,2.*c1,.8),sm(d-.004*r*r));col=mix(col,mix(col,3.*c1,.4),sm(d-.01*r*r));}dvoronoi(2.*n*x,v,ind,vn);y=x-ind/n/2.;rand(ind,r);d=length(y)-.002*r;col=mix(col,c.xxx,sm(d));lfnoise(x.xy-v*v*v,d);col=mix(col,c.yyy,.5+.5*d);col=.6*col+.3*step(.8,col);col*=2.;v=dspiral(x,.1,.01);col=mix(col,c.yyy,1.-sm(v*6.e-3));col=mix(col,2.5*col,sm(v*2.e-3));}void dbox(in vec2 x,in vec2 b,out float d);void street(in vec2 x,out vec3 col){x.y+=.3*iTime;float dx;lfnoise(x.y*c.xx,dx);x.x+=.1*dx;col=.4*c.xxx;float da=mod(x.y,.1)-.05;dbox(vec2 (x.x,da),vec2 (.005,.025),da);col=mix(col,c.xxx,sm(da));col=mix(col,c.xxx,sm(abs(abs(x.x)-.1)-.01));float n;mfnoise(x.xy,mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),200.,.35,n);col=mix(col,.5*col,.5+.5*n);col=mix(col,.6*c.xxx,abs(n)-.1);vec2 ind;float v,vn;dvoronoi(256.*x,v,ind,vn);ind=x-ind/256.;col=mix(col,.0*c.xxx,sm(length(ind)-.0001));}void dbox3(in vec3 x,in vec3 b,out float d);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void scene(in vec3 x,out vec2 sdf){x.y+=.3*iTime;float dx;lfnoise((x.y)*c.xx,dx);x.x+=.1*dx;sdf=c.xx;float n;mfnoise(x.xy,mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),2000.,mix(.35,.45,smoothstep(.4,1.6,abs(x.x))),n);float n0=n;n=.5+.5*n;n*=smoothstep(.1,.3,abs(x.x))+smoothstep(.4,1.2,abs(x.x));sdf.x=x.z-.1*n;sdf.y=1.;float d;dbox3(x-c.yyx*.005*step(.1,abs(n0)-.01),vec3 (.1,1.e3,.001+.01*n0),d);add(sdf,vec2 (d,2.),sdf);}void normal(in vec3 x,out vec3 n,in float dx);void palette(in float scale,out vec3 col){const int N=5;const vec3 colors[N]=vec3 [N](vec3 (0.27,0.13,0.26),vec3 (0.43,0.21,0.33),vec3 (0.69,0.36,0.42),vec3 (0.87,0.52,0.45),vec3 (0.99,0.68,0.53));float index=floor(scale*float (N)),remainder=scale*float (N)-index;col=mix(colors[int (index)],colors[int (index)+1],remainder);}void main(){a=iResolution.x/iResolution.y;vec2 uv=(gl_FragCoord.xy-.5*iResolution)/iResolution.y,s;vec3 col=c.yyy,o=.3*c.yyx+c.yzy,r=c.xyy,t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x;int N=250,i;t=uv.x*r+uv.y*u;dir=normalize(t-o);vec3 c1;float d=-(o.z-.2)/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(x.z<0.){i=N;break;}d+=s.x;}if(i<N){vec3 l=c.yyx;normal(x,n,2.e-6);if(s.y==1.){palette(x.z/.22,col);col=.1*col+.1*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);}else if(s.y==2.){street(x.xy,col);col=.1*col+.1*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);}else {colorize(x.xy,col);col=.1*col+.1*col*dot(l,n)+.8*col*pow(abs(dot(reflect(-l,n),dir)),2.);}if(x.z>.05)col=mix(col,3.*col,smoothstep(.95,.951,n.z));}col=12.*col*col;col=mix(col,c.yyy,tanh(2.e-1*d));vec3 c2;colorize(4.*uv,c2);col=mix(col,2.*c2,smoothstep(.3,.5,uv.y));col=mix(c.yyy,col,clamp(iTime,0.,1.));gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *text_source = "#version 130\nuniform float iFontWidth,iTime;uniform vec2 iResolution;uniform sampler2D iChannel0,iFont;uniform float iFSAA;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;out vec4 gl_FragColor;const vec3 c=vec3 (1.,0.,-1.);const float pi=acos(-1.);float a;void rand(in vec2 x,out float num);void lfnoise(in vec2 t,out float num);void rshort(in float off,out float val);void rfloat(in float off,out float val);void dbox(in vec2 x,in vec2 b,out float dst);void dcircle(in vec2 x,out float d);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void drhomboid(in vec2 x,in vec2 b,in float tilt,out float dst);void dcirclesegment(in vec2 x,in float r,in float p0,in float p1,out float d);void stroke(in float d0,in float s,out float d);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dstring(in vec2 x,in float ordinal,in float size,out float dst);void dfloat(in vec2 x,in float num,in float size,out float dst);void smoothmin(in float a,in float b,in float k,out float dst);void dint(in vec2 x,in float num,in float size,in float ndigits,out float dst);void dtime(in vec2 x,in float num,in float size,out float dst);void addwindow(in vec2 uv,inout vec3 col,in vec2 dimension);float sm(float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance);void mainImage(out vec4 fragColor,in vec2 fragCoord){a=iResolution.x/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);float d;vec4 old=c.yyyy,new=c.yyyy;float bound=sqrt(iFSAA)-1.;for(float i=-.5*bound;i<=.5*bound;i+=1.)for(float j=-.5*bound;j<=.5*bound;j+=1.){old.gba+=texture(iChannel0,(fragCoord+vec2 (i,j)*3./max(bound,1.))/iResolution.xy).xyz;}old.gba/=iFSAA;new=old;if(uv.y>.38){addwindow(uv-.45*vec2 (-.45*a,1.-2.*.008*c.yx),new.gba,vec2 (.4,.04));addwindow((uv-.45*vec2 (.97*a,1.-2.*.008*c.yx))*c.zx,new.gba,vec2 (.1,.04));float da;dstring((uv-.45*vec2 (-.55*a,1.+4.*.008)),9.,.004,d);dstring((uv-.45*vec2 (-.55*a,1.+2.*.008)),10.,.004,da);d=min(d,da);dstring((uv-.45*vec2 (-.55*a,1.)),11.,.004,da);d=min(d,da);dstring((uv-.45*vec2 (-.55*a,1.-2.*.008)),12.,.004,da);d=min(d,da);dstring((uv-.45*vec2 (-.55*a,1.-4.*.008)),13.,.004,da);d=min(d,da);new.gba=mix(new.gba,mix(new.gba,c.xxx,1.),sm(d));dstring((uv-.45*vec2 (-.85*a,1.)),3.,.02,d);new.gba=mix(new.gba,mix(new.gba,c.xxx,.5),sm(d));stroke(d-.002,.002,d);new.gba=mix(new.gba,vec3 (1.00,0.40,0.39),sm(d));dtime((uv-.45*vec2 (.975*a,1.05)),iTime,.01,d);new.gba=mix(new.gba,c.xxx,sm(d));dint(uv-.45*vec2 (.975*a,1.0),floor(1.e3*fract(iTime)),.01,4.,d);stroke(d-.001,.0005,d);new.gba=mix(new.gba,c.xxx,sm(d));}if(iTime<20.){float sc=clamp(iTime-10.,0.,1.)*(1.-clamp(iTime-18.,0.,1.)),da;vec3 c1=new.gba;addwindow(uv,c1,vec2 (.72,.15));new.gba=mix(new.gba,c1,sc);dstring(uv-vec2 (-.5,.05),5.,.02,d);dstring(uv-vec2 (-.5,0.),6.,.02,da);d=min(d,da);dstring(uv-vec2 (-.5,-.05),7.,.02,da);d=min(d,da);d=mix(1.,d,sc);new.gba=mix(new.gba,c.xxx,sm(d));}else if(iTime<32.){float sc=smoothstep(0.,1.,clamp(iTime-25.,0.,1.))*(1.-smoothstep(0.,1.,clamp(iTime-30.,0.,1.)));vec3 c1=new.gba;addwindow(uv-vec2 (0.,-.3),c1,vec2 (.15,.1));dstring((uv-vec2 (-.085,-.3)),3.,.02,d);float da;dstring((uv-vec2 (-.08,-.35)),26.,.02,da);d=min(d,da);c1=mix(c1,c.xxx,sm(d));new.gba=mix(new.gba,c1,sc);}float dc;dbox(uv,.5*vec2 (a,1.),dc);stroke(dc,.005,dc);new.gba=mix(new.gba,c.yyy,sm(dc));fragColor=vec4 (new.gba,1.);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
const char *post_source = "#version 130\nuniform float iFSAA;uniform vec2 iResolution;uniform sampler2D iChannel0;uniform float iTime;out vec4 gl_FragColor;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);float a=1.0;float lscale,rscale;float size;float nbeats;float iScale;void rand(in vec2 x,out float n);void lfnoise(in vec2 t,out float n);void stroke(in float d0,in float s,out float d);void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance);void hash22(in vec2 x,out vec2 y);float sm(float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}float dot2(in vec3 v){return dot(v,v);}void dtriangle3(in vec3 p,in vec3 v1,in vec3 v2,in vec3 v3,out float dst){vec3 v21=v2-v1;vec3 p1=p-v1;vec3 v32=v3-v2;vec3 p2=p-v2;vec3 v13=v1-v3;vec3 p3=p-v3;vec3 nor=cross(v21,v13);dst=sqrt((sign(dot(cross(v21,nor),p1))+sign(dot(cross(v32,nor),p2))+sign(dot(cross(v13,nor),p3))<2.0)?min(min(dot2(v21*clamp(dot(v21,p1)/dot2(v21),0.0,1.0)-p1),dot2(v32*clamp(dot(v32,p2)/dot2(v32),0.0,1.0)-p2)),dot2(v13*clamp(dot(v13,p3)/dot2(v13),0.0,1.0)-p3)):dot(nor,p1)*dot(nor,p1)/dot2(nor));}void rot3(in vec3 p,out mat3 rot);void dbox3(in vec3 x,in vec3 b,out float d);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);mat3 R;void scene(in vec3 x,out vec2 sdf){float d;dbox3(x,.2*c.xxx,sdf.x);sdf.y=1.;dbox3(x-.1*c.xyy,vec3 (.02,.3,.12),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x-.05*c.xyy-.1*c.yyx,vec3 (.07,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x,vec3 (.02,.3,.1),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.05*c.xyy+.1*c.yyx,vec3 (.07,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.1*c.xyy-.1*c.yyx,vec3 (.02,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.04*c.yyx,vec3 (.3,.02,.08),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x-.1*c.yyx,vec3 (.3,.02,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));vec3 y=vec3 (x.x,abs(x.y),x.z);dbox3(y-.05*c.yxy,vec3 (.1,.03,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(y-.1*c.yxy-.06*c.xyy,vec3 (.08,.021,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));vec3 z=vec3 (abs(x.x),x.yz);dbox3(z-.119*c.xyy,vec3 (.021,.08,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));}void scene2(in vec3 x,out vec2 sdf){float v=0.,vn;vec2 vi=c.yy;dvoronoi(x.xy/size,v,vi,vn);vec3 y=vec3 (x.xy-vi*size,x.z);vec2 yi=vi*size;float n=0.;lfnoise(4.*(yi-.5*iTime),n);lfnoise(12.*vec2 (n,1.)*yi-(.8+.2*n)*c.xy,n);n*=iScale;sdf=vec2 (length(y-.05*n*c.yyx)-size*vn*mix(1.,4.,length(texture(iChannel0,yi/vec2 (a,1.)).rgb)/sqrt(3.)),1.);}void normal2(in vec3 x,out vec3 n,in float dx){vec2 s,na;scene2(x,s);scene2(x+dx*c.xyy,na);n.x=na.x;scene2(x+dx*c.yxy,na);n.y=na.x;scene2(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}void scene3(in vec3 x,out vec2 sdf){vec3 y=vec3 (mod(x.xy,2.*size)-size,x.z);vec2 yi=x.xy-y.xy;float ss=mix(.0,.05,size/.01);vec2 p0=.8*size*c.xx,p1=.8*size*c.zx,p2=.8*size*c.xz;vec2 ind;float y0,y1,y2;lfnoise(4.e1*(yi+p0-.5e-4*iTime),y0);lfnoise(12.e1*vec2 (y0,1.)*(yi+p0)-1.e-4*(.8+.2*y0)*iTime*c.xy,y0);lfnoise(4.e1*(yi+p1-.5e-4*iTime),y1);lfnoise(12.e1*vec2 (y1,1.)*(yi+p1)-1.e-4*(.8+.2*y1)*iTime*c.xy,y1);lfnoise(4.e1*(yi+p2-.5e-4*iTime),y2);lfnoise(12.e1*vec2 (y2,1.)*(yi+p2)-1.e-4*(.8+.2*y2)*iTime*c.xy,y2);y0*=ss;y1*=ss;y2*=ss;dtriangle3(y,vec3 (p0,y0),vec3 (p1,y1),vec3 (p2,y2),sdf.x);float d;vec2 p3=.8*size*c.zz,p4=.8*size*c.xz,p5=.8*size*c.zx;float y3,y4,y5;lfnoise(4.e1*(yi+p3-.5e-4*iTime),y3);lfnoise(12.e1*vec2 (y3,1.)*(yi+p3)-1.e-4*(.8+.2*y3)*iTime*c.xy,y3);lfnoise(4.e1*(yi+p4-.5e-4*iTime),y4);lfnoise(12.e1*vec2 (y4,1.)*(yi+p4)-1.e-4*(.8+.2*y4)*iTime*c.xy,y4);lfnoise(4.e1*(yi+p5-.5e-4*iTime),y5);lfnoise(12.e1*vec2 (y5,1.)*(yi+p5)-1.e-4*(.8+.2*y5)*iTime*c.xy,y5);y3*=ss;y4*=ss;y5*=ss;dtriangle3(y,vec3 (p3,y3),vec3 (p4,y4),vec3 (p5,y5),d);sdf.x=min(sdf.x,d);stroke(sdf.x,.1*size,sdf.x);sdf.y=1.;}void normal3(in vec3 x,out vec3 n,in float dx){vec2 s,na;scene3(x,s);scene3(x+dx*c.xyy,na);n.x=na.x;scene3(x+dx*c.yxy,na);n.y=na.x;scene3(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}void normal(in vec3 x,out vec3 n,in float dx);void mainImage(out vec4 fragColor,in vec2 fragCoord_){vec2 fragCoord=fragCoord_;if(iTime<159.5456&&iTime>155.9092){vec2 n;lfnoise(22.*fragCoord/iResolution-3.*iTime,n.x);lfnoise(22.*fragCoord/iResolution-3.*iTime-1337.,n.y);fragCoord+=22.*n;}else if(iTime<165.&&iTime>163.182){vec2 n;lfnoise(22.*fragCoord/iResolution-3.*iTime,n.x);lfnoise(22.*fragCoord/iResolution-3.*iTime-1337.,n.y);fragCoord+=22.*n;}float a=iResolution.x/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);nbeats=mod(iTime,60./29.);iScale=nbeats-30./29.;iScale=smoothstep(-5./29.,0.,iScale)*(1.-smoothstep(0.,15./29.,iScale));vec3 col=texture(iChannel0,fragCoord/iResolution).rgb;float delta=0.;rot3(vec3 (-2.*pi/8.,2.*pi/8.,2.*pi/4.)-iTime*vec3 (1.1,1.3,1.5),R);float d;vec2 s;vec3 o,r,u,t,ssize,dir,x,n;vec2 uv2=10.*(uv-vec2 (-.45*a,.45));o=R*c.yyx;r=c.xyy;u=c.yxy;t=c.yyy;int N=250,i;t=uv2.x*r+uv2.y*u;t=R*t;dir=normalize(t-o);ssize=.2*c.xxx;vec3 tlo=min((ssize-o)/dir,(-ssize-o)/dir);vec2 abxlo=abs(o.yz+tlo.x*dir.yz),abylo=abs(o.xz+tlo.y*dir.xz),abzlo=abs(o.xy+tlo.z*dir.xy);vec4 dn=100.*c.xyyy;dn=mix(dn,vec4 (tlo.x,c.xyy),float (all(lessThan(abxlo,ssize.yz)))*step(tlo.x,dn.x));dn=mix(dn,vec4 (tlo.y,c.yxy),float (all(lessThan(abylo,ssize.xz)))*step(tlo.y,dn.x));dn=mix(dn,vec4 (tlo.z,c.yyx),float (all(lessThan(abzlo,ssize.xy)))*step(tlo.z,dn.x));uv=(fragCoord)/iResolution.xy*vec2 (a,1.);d=dn.r;float nan;lfnoise(iTime*c.xx,nan);nan+=.5;if(nan>0.)d=3.;if(d<=2.){x=o+d*dir;scene(x,s);if(s.x>1.e-4){for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=s.x;}}if(i<N){normal(x,n,5.e-4);if(s.y==1.){vec3 l=normalize(x+c.zzx*vec3 (1.3,.9,1.2));col=vec3 (0.81,0.15,0.18);col=.3*col+.4*col*abs(dot(l,n))+.6*col*abs(pow(dot(reflect(-l,n),dir),2.));}else if(s.y==2.){vec3 l=normalize(x+c.zzx*vec3 (1.3,.9,1.2));col=.7*c.xxx;col=.5*col+.4*col*abs(dot(l,n))+.8*col*abs(pow(dot(reflect(-l,n),dir),2.));}}if(iTime<0.)col=texture(iChannel0,fragCoord/iResolution).rgb;}else {iScale=nbeats-30./29.;iScale=smoothstep(-5./29.,0.,iScale)*(1.-smoothstep(0./29.,35./29.,iScale));rscale=0.;lscale=0.;size=mix(.005,.01,rscale);size=mix(0.,size,max(rscale,lscale));if(lscale>0.){col=c.yyy;o=c.yyx+.5*vec3 (cos(iTime),sin(iTime),0.);r=c.xyy;u=c.yxy;t=c.yyy;dir=c.yyy;n=c.yyy;x=c.yyy;N=200;t=uv.x*r+uv.y*u;dir=normalize(t-o);d=-(o.z-.05-.5*size)/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene2(x,s);if(s.x<1.e-4)break;if(x.z<-.05-.5*size){col=c.yyy;i=N;break;}d+=min(s.x,1.e-3);}if(i<N){normal2(x,n,5.e-4);vec3 l=normalize(x+.5*n);if(s.y==1.){float v,vn;vec2 vi;dvoronoi(x.xy/size,v,vi,vn);vec3 y=vec3 (x.xy-vi*size,x.z);vec2 yi=vi*size;float bound=sqrt(iFSAA)-1.;for(float i=-.5*bound;i<=.5*bound;i+=1.)for(float j=-.5*bound;j<=.5*bound;j+=1.){col+=texture(iChannel0,yi/vec2 (a,1.)+vec2 (i,j)*3./max(bound,1.)/iResolution.xy).xyz;}col/=iFSAA;col=.4*col+.9*col*abs(dot(l,n))+.6*col*pow(abs(dot(reflect(-l,n),dir)),3.);}}else col=c.yyy;}else if(rscale>0.){col=c.yyy;o=c.yyx+.5*vec3 (-1.,-1.,0.);r=c.xyy;u=c.yxy;t=c.yyy;dir=c.yyy;n=c.yyy;x=c.yyy;N=300;t=uv.x*r+uv.y*u;dir=normalize(t-o);d=-(o.z-.05-.5*size)/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene3(x,s);if(s.x<1.e-4)break;if(x.z<-.05-.5*size){col=c.yyy;i=N;break;}d+=min(s.x,1.e-3);}if(i<N){normal3(x,n,5.e-4);vec3 l=normalize(x+.5*n);if(s.y==1.){vec3 y=vec3 (mod(x.xy,size)-.5*size,x.z);vec2 yi=x.xy-y.xy;col=texture(iChannel0,yi/vec2 (a,1.)).rgb;col=.4*col+.9*col*abs(dot(l,n))+.6*col*pow(abs(dot(reflect(-l,n),dir)),3.);}}else col=c.yyy;}}col+=vec3 (0.,0.05,0.1)*sin(uv.y*1050.+5.*iTime);fragColor=vec4 (clamp(col,0.,1.),1.0);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
const char *deadline_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);void rand(in vec2 x,out float n);void lfnoise(in vec2 t,out float n);void hash11(in float p,out float d);void hash12(in vec2 p,out float d);void hash22(in vec2 p,out vec2 d);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance);void stroke(in float d0,in float s,out float d);void dbox(in vec2 x,in vec2 b,out float d);void ddeadline(in vec2 x,out float ret);void zextrude(in float z,in float d2d,in float h,out float d);vec2 pdec;void ddecorations(in vec2 x,in float decs,out float d){float r,v,vz;vec2 y,yi;dvoronoi(x/decs,v,yi,vz);y=x-yi*decs;hash12(yi*decs,r);if(r<.5){dbox(y,vz*decs/sqrt(2.)*c.xx,d);}else {hash11(r,r);d=length(y)-vz*decs;}pdec=yi/decs;}float m;void scene(in vec3 x,out vec2 sdf){if(iTime<8.){ddeadline(x.xy,sdf.x);zextrude(x.z,-sdf.x,mix(.0,.2,clamp(iTime-2.,0.,1.)*(1.-clamp(iTime-7.,0.,1.))),sdf.x);sdf.x=min(sdf.x,x.z);sdf.y=1.;}else {sdf.x=x.z;sdf.y=1.;}}void normal(in vec3 x,out vec3 n,in float dx);float sm(in float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}const vec3 orange=vec3 (0.20,0.60,0.86),redorange=vec3 (0.27,0.70,0.62);void modgradient(in vec2 x,in float decs,inout vec3 col){float y=mod(x.y,decs)-.5*decs;col=mix(orange,redorange,2.*abs(y)/decs);}float ddl;void colorize(in vec2 uv,out vec3 col){vec3 c1=col;float d;for(float decs=.05;decs<=1.;decs+=.05){modgradient(uv,decs,c1);ddecorations(uv-1337.-12.*decs*c.yx,decs,d);float ma;lfnoise((1.+5.*decs)*uv-1337.-12.*decs*c.yx-clamp(iTime/3.,0.,1.)*iTime*c.yx,ma);col=mix(col,mix(col,c1,mix(.6,.1,.8+.2*ma)*mix(1.,0.,clamp(length(uv),0.,1.))),sm(d));stroke(d,.001,d);col=mix(col,1.4*col,mix(0.,sm(d-.01),mix(0.,.5+.5*ma,clamp(iTime-10.,0.,1.))));col=mix(col,mix(orange,c.xxx,decs),sm(d));}col=mix(col,c.yyy,.2);if(iTime<8.){ddeadline(uv,d);ddl=d;c1=mix(col,mix(col,mix(3.5,5.5,.5+.5*sin(6.*iTime))*vec3 (0.27,0.36,0.48),.5),sm(ddl/150.));c1=mix(c1,mix(col,1.3*vec3 (0.27,0.36,0.48),.8),sm(d+.002));stroke(d,.002,d);c1=mix(c1,2.5*vec3 (0.27,0.36,0.48),sm(d));col=mix(col,c1,clamp((iTime-2.),0.,1.)*(1.-clamp(iTime-7.,0.,1.)));}}void main(){vec2 uv=(gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,s;vec3 col=c.xxx,o=mix((vec3 (uv,1.)),c.yyx+.4*c.yzy,clamp(iTime-1.,0.,1.)),r=c.xyy,t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x;int N=150,i;float d;t=uv.x*r+uv.y*u;dir=mix(c.yyz,normalize(t-o),clamp(iTime-1.,0.,1.));vec3 c0,c1;colorize(uv,c0);d=-(o.z-mix(0.,.2,step(2.,iTime)))/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(x.z<0.){i=N;break;}d+=s.x;}if(i<N){vec3 l=x+c.yyx;normal(x,n,2.e-6);colorize(x.xy,col);col=.1*col+.4*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);}col=2.*col*col;col=mix(c0,col,clamp(iTime,0.,1.));col=mix(col,vec3 (0.18,0.24,0.31),clamp(iTime-19.,0.,1.));gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *hydrant_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);void rand(in vec2 x,out float n);void lfnoise(in vec2 t,out float n);void mfnoise(in vec2 x,in float d,in float b,in float e,out float n);void hash11(in float p,out float d);void hash12(in vec2 p,out float d);void hash21(in float p,out vec2 d);void hash22(in vec2 p,out vec2 d);void hash31(in float p,out vec3 d);void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance);void stroke(in float d0,in float s,out float d);void dbox(in vec2 x,in vec2 b,out float d);void drhomboid(in vec2 x,in vec2 b,in float tilt,out float dst);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void zextrude(in float z,in float d2d,in float h,out float d);void dhydrantradius(in float lxy,in float z,in float phi,out float r){const float dx=2.e-2,rfoot=.3,rpipe=.5,rtop=.01;float y=abs(z)-.4;r=rfoot*step(y,6.*dx)*step(0.,y);r+=.1*rfoot*smoothstep(.3*dx,.7*dx,y)*(1.-smoothstep(5.3*dx,5.7*dx,y));r+=.1*rfoot*smoothstep(1.3*dx,1.7*dx,y)*(1.-smoothstep(4.3*dx,4.7*dx,y));r+=.6*rfoot*step(y,0.);y=z+.2;r+=.1*rfoot*smoothstep(.3*dx,.7*dx,y)*(1.-smoothstep(5.3*dx,5.7*dx,y));r+=.1*rfoot*smoothstep(1.3*dx,1.7*dx,y)*(1.-smoothstep(4.3*dx,4.7*dx,y));float phidep=clamp(-.5+2.*abs(cos(2.*pi*phi)),0.,1.);r+=step(.52,z)*mix(.8*rfoot*(1.+.05*phidep),rtop*(1.+.05*phidep),smoothstep(0.,24.*dx,z-.55));r*=step(z,.9);r+=.2*rfoot*step(.9,z)*step(z,.9+2.*dx);r+=.3*rfoot*smoothstep(9.,10.,z)*(1.-smoothstep(10.,11.,z));r+=.1*rfoot*smoothstep(.3*dx,.7*dx,z-9.)*(1.-smoothstep(1.3*dx,1.7*dx,z-9.));r=lxy-r;}void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void scene(in vec3 x,out vec2 sdf){vec3 y=2.*x;dhydrantradius(length(y.xy),y.z,atan(y.y,y.x),sdf.x);sdf.x/=10.;float rarm=.05;rarm-=.01*smoothstep(.05,.07,abs(x.x)-.05);rarm-=.01*smoothstep(.05,.07,abs(x.x)-.1);rarm-=.02*step(.08,abs(x.x)-.05)*step(abs(x.x)-.05,.09);rarm-=.02*step(.08,abs(x.x)-.1)*step(abs(x.x)-.1,.09);rarm+=.03*step(.17,abs(x.x))*step(abs(x.x),.19);sdf.x=min(sdf.x,length(x.yz-.05*c.yx)-rarm*(step(abs(x.x),.2)));rarm=.05;rarm-=.01*smoothstep(.05,.07,abs(x.y)-.05);rarm-=.01*smoothstep(.05,.07,abs(x.y)-.1);rarm-=.02*step(.08,abs(x.y)-.05)*step(abs(x.y)-.05,.09);rarm-=.02*step(.08,abs(x.y)-.1)*step(abs(x.y)-.1,.09);rarm+=.03*step(.17,abs(x.y))*step(abs(x.y),.2);sdf.x=min(sdf.x,.1*(length(x.xz-.05*c.yx)-rarm*step(abs(x.y),.2)));sdf.y=0.;add(sdf,vec2 (x.z+.4,1.),sdf);}void normal(in vec3 x,out vec3 n,in float dx);float sm(in float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void dcircle(in vec2 x,out float d){d=length(x)-1.;}void dpolygon(in vec2 x,in float N,out float d);void dspacepigs(in vec2 x,out float d);const vec3 orange=2.*vec3 (0.99,0.34,0.39),redorange=vec3 (0.97,0.60,0.33);void ddecorations(in vec2 x,in float decs,out float d){float r,v,vz;vec2 y,yi;dvoronoi(x/decs,v,yi,vz);y=x-yi*decs;dspacepigs(y/decs*2.5,d);d*=-decs/2.5;}void modgradient(in vec2 x,in float decs,inout vec3 col){float y=mod(x.y,decs)-.5*decs;col=mix(orange,redorange,2.*abs(y)/decs);}float ddl;void colorize(in vec2 uv,out vec3 col){vec3 c1=col;float d;for(float decs=.4;decs<=1.5;decs+=.3){modgradient(uv,decs,c1);ddecorations(uv-1337.-12.*decs*c.yx,decs,d);float m;lfnoise((1.+5.*decs)*uv-1337.-12.*decs*c.yx,m);col=mix(col,mix(col,c1,mix(.6,.1,.8+.0*m)),.8*decs*sm(d));stroke(d,.001,d);col=mix(col,mix(orange,c.xxx,decs),sm(d));}col=mix(col,c.yyy,.2);}void analytical_box(in vec3 o,in vec3 dir,in vec3 size,out float d);void main(){vec2 uv=(gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,s;vec3 col=c.xxx,o=c.yyx+1.4*c.yzy+.3*vec3 (cos(iTime),sin(iTime),0.),r=vec3 (sin(iTime),cos(iTime),0.),t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x;int N=250,i;float d;t=uv.x*r+uv.y*u;dir=normalize(t-o);vec3 c0,c1;colorize(uv,c0);analytical_box(o-.25*c.yyx,dir,vec3 (.2,.2,.5),d);if(d>4.)d=-o.z/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(x.y>.5){d=-(o.z+.4)/dir.z;x=o+d*dir;scene(x,s);break;}d+=s.x;}if(i<N){vec3 l=2.*normalize(x+2.*c.xxx);normal(x,n,2.e-3);if(s.y==0.){col=vec3 (0.47,0.21,0.22);float na;mfnoise(vec2 (12.*length(x),x.z)+vec2 (x.z,atan(x.y,x.x)),5.,500.,.45,na);col=mix(col,.1*c.xxx,sm(na+.3));col=mix(col,.5*col,.5+.5*na);col=.3*col+.5*col*dot(-l,n)+.7*col*pow(abs(dot(reflect(l,n),dir)),2.);}else if(s.y==1.){colorize(x.xy,col);col=.1*col+.1*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);}}col=2.*col*col;gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *watercubes_source = "uniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.0,0.0,-1.0);float a=1.0;vec3 color1,color2;void hash22(in vec2 p,out vec2 d);void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance);void hash33(in vec3 p3,out vec3 d);void dvoronoi3(in vec3 x,out float d,out vec3 p,out float control_distance);void smoothmin(in float a,in float b,in float k,out float dst);void dsmoothvoronoi3(in vec3 x,out float d,out vec3 p,out float control_distance);mat3 gR;void rot3(in vec3 p,out mat3 rot);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void dbox3(in vec3 x,in vec3 b,out float d);void dstar(in vec2 x,in float N,in vec2 R,out float dst);void smoothmax(in float a,in float b,in float k,out float res);void dstar3(in vec3 x,in float N,in vec2 R,out float dst);void scene(in vec3 x,out vec2 sdf){if(length(x)>.5)sdf=vec2 (length(x)-.5,-1.);x=gR*x;vec3 yi;float vi,vip,rel=8.,db=length(x)-.4,dc;dbox3(x,.2,dc);db=mix(db,dc,clamp(iTime-5.,0.,1.));dstar3(x,6.,vec2 (.2,.5),dc);db=mix(db,dc,clamp(iTime-10.,0.,1.));dsmoothvoronoi3(rel*x,vi,yi,vip);sdf=vec2 (abs(vi/rel)-.0001,0.);sdf.x=max(sdf.x,db);add(sdf,vec2 (abs(db+.0002)-.0001,1.),sdf);}void normal(in vec3 x,out vec3 n,in float dx);void dbox(in vec2 x,in vec2 b,out float d);float sm(in float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void colorize(in vec2 uv,out vec3 col){col=mix(color2,c.yyy,length(uv));vec2 s;scene(vec3 (uv,0.),s);float v,vip,res=mix(12.,100.,s.x);vec2 vi;dvoronoi(res*uv,v,vi,vip);float d=abs(v/res)-mix(.002,.0001,s.x);col=mix(col,4.*col,sm(-v/res+.01));col=mix(col,mix(4.*color2,c.yyy,2.*s.x),sm(d));}void main(){vec2 uv=(gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,s;rot3(vec3 (1.1,1.3,1.5)*iTime,gR);color1=mix(vec3 (0.47,0.21,0.22),vec3 (0.17,0.24,0.30),clamp(iTime-5.,0.,1.));color1=mix(color1,vec3 (0.52,0.85,0.31),clamp(iTime-10.,0.,1.));color2=mix(vec3 (0.22,0.21,0.47),.3*vec3 (1.00,0.59,0.22),clamp(iTime-5.,0.,1.));color2=mix(color2,.15*c.xxx,clamp(iTime-10.,0.,1.));vec3 col=c.xxx,o=c.yyx,r=c.xyy,t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x,c1,o0=o;int N=150,i;float d=.5;t=uv.x*r+uv.y*u;dir=normalize(t-o);for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(d>length(.6+.2*c.xx)){i=N;break;}d+=s.x;}if(i<N){vec3 l=2.*normalize(x+2.*c.xxx);normal(x,n,2.e-3);if(s.y==0.){col=color1;col=.3*col+.5*col*dot(-l,n)+.7*col*pow(abs(dot(reflect(l,n),dir)),2.);}else if(s.y==1.){col=color2;col=.1*col+.1*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);}for(float k=.5;k<.9;k+=.2){o=x;d=1.e-3;dir=refract(dir,n,.99);for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(d>length(o0)+.4001){i=N;break;}d+=s.x;}if(i<N){vec3 l=2.*normalize(x+2.*c.xxx);normal(x,n,2.e-3);if(s.y==0.){c1=color1;c1=.3*c1+.5*c1*dot(-l,n)+.7*c1*pow(abs(dot(reflect(l,n),dir)),2.);c1=mix(c1,c.xxx,smoothstep(0.458,.602,1.-abs(dot(n,c.yyz))));}else if(s.y==1.){c1=color2;c1=.1*c1+.1*c1*dot(l,n)+.6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);}else c1=c.yyx;col=mix(c1,col,k);}else colorize(uv,col);}}else colorize(uv,col);col=2.*col*col;gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *glitchcity_source = "#version 130\nout vec4 gl_FragColor;uniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.0,0.0,-1.0);float a=1.0;vec3 color1=vec3 (0.02,0.08,0.18),color2=2.*vec3 (0.08,0.08,0.24);void hash22(in vec2 p,out vec2 d);void hash12(in vec2 p,out float d);void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void dbox3(in vec3 x,in vec3 b,out float d);float h;void scene(in vec3 x,out vec2 sdf){x.x+=.1*iTime;vec2 vi;float v,vip,res=15.,d;dvoronoi(res*x.xz,v,vi,vip);vip/=res;vi/=res;v/=res;sdf=vec2 (x.y,0.);if(vi.y<.5){hash12(vi,h);vec2 cs=vec2 (cos(2.*pi*h),sin(2.*pi*h));mat2 R=mat2 (cs.x,cs.y,-cs.y,cs.x);vec3 y=vec3 (x.x-vi.x,x.y,x.z-vi.y);y.xz=R*y.xz;dbox3(y,vip/sqrt(2.)*c.xyx+(.1+.05*h)*c.yxy,d);add(sdf,vec2 (d,1.),sdf);}sdf.x-=.003;}void normal(in vec3 x,out vec3 n,in float dx);float sm(in float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void colorize(in vec2 uv,out vec3 col){col=c.yyy;}void housetexture(in vec2 uv,out vec3 col){uv.x+=.1*iTime;float dsta=.002;col=mix(.05*color1,4.*color2,sm(4.*(abs(mod(uv.y,dsta)-.5*dsta)-.25*dsta)));vec2 x=mod(uv,dsta)-.5*dsta,xi=(uv-x)/dsta;float f;hash12(xi,f);if(f<.3){col=mix(col,mix(4.*col,c.xxx,.5),sm(min(abs(x.x),abs(x.y))-.25*dsta));}}void palette2(in float scale,out vec3 col){const int N=5;const vec3 colors[N]=vec3 [N](vec3 (0.98,0.80,1.00),vec3 (0.52,1.00,0.42),vec3 (0.45,0.99,0.96),vec3 (1.00,0.09,0.31),vec3 (1.00,1.00,0.43));float index=floor(scale*float (N)),remainder=scale*float (N)-index;col=mix(colors[int (index)],colors[int (index)+1],remainder);}void main(){vec2 uv=(gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,s;if(uv.y>.16){gl_FragColor=vec4 (mix(vec3 (0.10,0.17,0.33),c.yyy,clamp((uv.y-.16)/(.5-.16),0.,1.)),1.);return ;}vec3 col=c.xxx,o=c.yyx+.2*c.yxy,r=c.xyy,t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x,c1,o0=o;int N=350,i;float d;t=uv.x*r+uv.y*u;dir=normalize(t-o);d=-(o.y-.15)/dir.y;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(x.y>.15){gl_FragColor=c.yyyx;return ;}d+=min(s.x,2.e-3);}float d0=d;if(i<N){vec3 l=x+c.yxy+.5*c.yyx;normal(x,n,2.e-5);if(s.y==0.){col=color1;col=.3*col+.5*col*dot(-l,n)+.7*col*pow(abs(dot(reflect(l,n),dir)),2.);{o=x;d=1.e-3;dir=reflect(dir,n);for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(x.y>.15){gl_FragColor=c.yyyx;return ;}d+=min(s.x,5.e-3);}if(i<N){vec3 l=x+c.yxy;normal(x,n,2.e-4);if(s.y==0.){c1=color1;c1=.3*c1+.5*c1*dot(-l,n)+.7*c1*pow(abs(dot(reflect(l,n),dir)),2.);}else if(s.y==1.){housetexture(x.xy,c1);c1=.1*c1+.1*c1*dot(l,n)+.6*c1*pow(abs(dot(reflect(-l,n),dir)),2.);}else c1=c.yyx;col=mix(c1,col,.5);}else colorize(uv,col);}}else if(s.y==1.){housetexture(x.xy,col);col=.1*col+.1*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);col=mix(col,c.xxx,smoothstep(.63,1.2,1.-abs(dot(n,3.*c.xyx))));col=mix(col,c.xxx,smoothstep(.63,1.2,1.-abs(dot(n,3.*c.zyx))));}}else colorize(uv,col);d=d0;float ha=mod(abs(x.y)-mix(-1.,1.,h)*iTime+12.*h,.15);palette2(fract(h),c1);col=mix(col,1.15*c1,smoothstep(-.2,1.,smoothstep(.1,1.3,(1.-8.*ha))));palette2(fract(h+13.37e-3),c1);col=mix(col,1.65*c1*c1,smoothstep(-.2,1.,smoothstep(.1,1.3,(1.-26.*ha))));col=2.*col*col;col=mix(col,c.yyy,smoothstep(0.,2.,d));col=clamp(col,0.,1.);col=mix(col,c.yyy,.3);col=mix(col,vec3 (0.10,0.17,0.33),smoothstep(.1,1.3,d));gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *greetings_source = "uniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.0,0.0,-1.0);float a=1.0;void rand(in vec2 x,out float n);void lfnoise(in vec2 t,out float n);void dhexagonpattern(in vec2 p,out float d,out vec2 ind);float sm(in float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void dbox(in vec2 x,in vec2 b,out float d);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void stroke(in float d0,in float s,out float d);void addwindow(in vec2 uv,inout vec3 col,in vec2 dimensions);void dpolygon(in vec2 x,in float N,out float d);void dmercury(in vec2 x,out float d);void dcircle(in vec2 x,out float d);void dtriangle(in vec2 p,in vec2 p0,in vec2 p1,in vec2 p2,out float dst);void rot(in float phi,out mat2 m);void dschnappsgirls(in vec2 x,out float d);void dhaujobb(in vec2 x,out float d);void dkewlers(in vec2 x,out float d);void dfarbrausch(in vec2 x,out float d);void d5711(in vec2 x,out float ret);void main(){vec2 uv=(gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,hind;vec3 col=c.yyy,col1=vec3 (0.00,0.42,0.84);float h,h0,res=34.;col1=mix(col1,vec3 (0.91,0.30,0.24),clamp(iTime-4.,0.,1.));col1=mix(col1,vec3 (0.44,0.65,0.35),clamp(iTime-9.,0.,1.));col1=mix(col1,vec3 (0.82,0.14,0.34),clamp(iTime-14.,0.,1.));col1=mix(col1,vec3 (0.92,0.76,0.20),clamp(iTime-19.,0.,1.));col1=mix(col1,.5*c.xxx,clamp(iTime-24.,0.,1.));dhexagonpattern(res*uv,h,hind);h/=res;h0=h;hind/=res;h=-abs(h)+.005;col=mix(col,col1,sm(h));h=abs(h+.005)-.0015;col=mix(col,2.*col,sm(h));float n;lfnoise(res*hind-iTime,n);col=mix(c.yyy,col,(.5+.5*n)*(1.-2.*abs(uv.y)));col=mix(col,2.*col1,sm(abs(h0)-.001*(.5+.5*n)));col=1.4*col;addwindow(uv,col,vec2 (.6,.4));float d,da;if(iTime<4.)dmercury(5.*uv,d);else if(iTime<9.){dmercury(5.*uv,d);dschnappsgirls(5.*uv,da);d=mix(d,da,clamp(iTime-4.,0.,1.));}else if(iTime<14.){dschnappsgirls(5.*uv,d);dhaujobb(5.*uv,da);d=mix(d,da,clamp(iTime-9.,0.,1.));}else if(iTime<19.){dhaujobb(5.*uv,d);dkewlers(5.*uv,da);d=mix(d,da,clamp(iTime-14.,0.,1.));}else if(iTime<24.){dkewlers(5.*uv,d);dfarbrausch(5.*uv,da);d=mix(d,da,clamp(iTime-19.,0.,1.));}else if(iTime<29.){dfarbrausch(5.*uv,d);d5711(5.*uv,da);d=mix(d,da,clamp(iTime-24.,0.,1.));}d/=5.;col=mix(col,1.9*col1,sm(d));col=mix(col,mix(col,3.*col1,.5+.5*sin(iTime)),sm((abs(d-.01)-.001)/22.));gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *fractal_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;const float pi=acos(-1.);const vec3 c=vec3 (1.0,0.0,-1.0);float a=1.0;void rand(in vec2 x,out float n);void lfnoise(in vec2 t,out float n);void hash22(in vec2 p,out vec2 d);void dvoronoi(in vec2 x,out float d,out vec2 p,out float control_distance);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void sub(in vec2 sda,in vec2 sdb,out vec2 sdf);void zextrude(in float z,in float d2d,in float h,out float d);void dbox3(in vec3 x,in vec3 b,out float d);void rot3(in vec3 p,out mat3 rot);void dbox(in vec2 x,in vec2 b,out float d);void dstar(in vec2 x,in float N,in vec2 R,out float dst);void doctahedron(in vec3 x,in float h,in float w,out float d);mat3 gR;vec2 ind=c.yy;void scene(in vec3 x,out vec2 sdf){vec3 y=x;x.xy+=vec2 (cos(.3*iTime),sin(.3*iTime));sdf.x=x.z;sdf.y=0.;float db=abs(length(y-.1*c.yyx)-.2),dc;dbox3(gR*(y-.1*c.yyx),.2*c.xxx,dc);db=mix(db,abs(dc)-.001,clamp(iTime-5.,0.,1.));doctahedron(gR*(y-.1*c.yyx),.4,.4,dc);db=mix(db,abs(dc)-.001,clamp(iTime-10.,0.,1.));add(sdf,vec2 (db,1.),sdf);}void texture_scene(in vec3 x,out vec2 sdf){vec3 y=x;x.xy+=vec2 (cos(.3*iTime),sin(.3*iTime));sdf.x=x.z;sdf.y=0.;float res=8.;vec2 sdb=c.xy;for(float f=0.;f<6.;f+=1.){float v,vp;vec2 vi;dvoronoi(res*x.xy,v,vi,vp);vp/=res;vi/=res;v/=res;add(sdb,vec2 (length(x-vec3 (vi,0.))-.5*vp,0.),sdb);res*=2.;ind+=vi/res;}sub(sdf,sdb,sdf);float db=abs(length(y-.1*c.yyx)-.2),dc;dbox3(gR*(y-.1*c.yyx),.2*c.xxx,dc);db=mix(db,abs(dc)-.001,clamp(iTime-5.,0.,1.));doctahedron(gR*(y-.1*c.yyx),.4,.4,dc);db=mix(db,abs(dc)-.001,clamp(iTime-10.,0.,1.));add(sdf,vec2 (db,1.),sdf);}void normal(in vec3 x,out vec3 n,in float dx);void texture_normal(in vec3 x,out vec3 n,in float dx){vec2 s,na;texture_scene(x,s);texture_scene(x+dx*c.xyy,na);n.x=na.x;texture_scene(x+dx*c.yxy,na);n.y=na.x;texture_scene(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}void palette(in float scale,out vec3 col){scale=clamp(scale,1.e-2,.99);const int N=5;vec3 colors[N]=vec3 [N](mix(vec3 (0.20,0.27,0.35),vec3 (1.00,0.00,0.47),clamp(iTime-5.,0.,1.)),mix(vec3 (0.29,0.37,0.45),vec3 (0.80,0.00,0.47),clamp(iTime-5.,0.,1.)),mix(vec3 (0.36,0.65,0.64),vec3 (0.60,0.00,0.47),clamp(iTime-5.,0.,1.)),mix(vec3 (0.66,0.85,0.80),vec3 (0.40,0.00,0.47),clamp(iTime-5.,0.,1.)),mix(vec3 (0.95,0.92,0.82),c.yyy,clamp(iTime-5.,0.,1.)));colors[0]=mix(colors[0],vec3 (0.68,1.00,0.00),clamp(iTime-10.,0.,1.));colors[1]=mix(colors[1],vec3 (0.45,0.84,0.00),clamp(iTime-10.,0.,1.));colors[2]=mix(colors[2],vec3 (0.01,0.54,0.00),clamp(iTime-10.,0.,1.));colors[3]=mix(colors[3],vec3 (0.00,0.82,0.50),clamp(iTime-10.,0.,1.));colors[4]=mix(colors[4],vec3 (0.00,1.00,0.51),clamp(iTime-10.,0.,1.));float index=floor(scale*float (N)),remainder=scale*float (N)-index;col=mix(colors[int (index)],colors[int (index)+1],remainder);}float sm(in float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void main(){rot3(vec3 (1.1,1.3,1.5)*iTime,gR);vec2 uv=(gl_FragCoord.xy-.5*iResolution.xy)/iResolution.y,s;vec3 col=c.yyy,o=c.yyx+.2*c.yzy,r=c.xyy,t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x,c1=c.yyy,o0=o,x0;int N=150,i;vec3 color1=vec3 (0.52,1.00,0.42);float d;t=uv.x*r+uv.y*u;dir=normalize(t-o);d=0.;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-3)break;d+=s.x;}if(i<N){if(s.y==1.){vec3 l=.5*c.yyz;normal(x,n,2.e-5);col=c.xxx;col=.3*col+.5*col*dot(-l,n)+1.7*col*pow(abs(dot(reflect(l,n),dir)),2.);}else col=c.yyy;}else col=c.yyy;for(i=0;i<N;++i){x=o+d*dir;texture_scene(x,s);if(s.x<1.e-3)break;d+=s.x;}if(i<N){x0=x;vec3 l=x+c.yxy+.5*c.yyx;texture_normal(x,n,2.e-5);if(s.y==0.){float na;lfnoise(2.*ind-iTime,na);palette(.5+.5*na,col);col=.3*col+.5*col*dot(-l,n)+.7*col*pow(abs(dot(reflect(l,n),dir)),2.);}else if(s.y==1.){vec3 c1;col=c.xxx;col=.3*col+.5*col*dot(-l,n)+.7*col*pow(abs(dot(reflect(l,n),dir)),2.);for(float k=0.;k<3.;k+=1.){o=x;dir=refract(dir,n,.5);d=1.e-2;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;d+=s.x;}if(i<N){if(s.y==1.){vec3 l=.5*c.yyz;normal(x,n,2.e-5);c1=c.xxx;c1=.3*c1+.5*c1*dot(-l,n)+1.7*c1*pow(abs(dot(reflect(l,n),dir)),2.);}else c1=c.yyy;}else c1=c.yyy;col=mix(col,c1,.54);for(i=0;i<N;++i){x=o+d*dir;texture_scene(x,s);if(s.x<1.e-3)break;d+=s.x;}if(i<N){vec3 l=x+c.yxy+.5*c.yyx;texture_normal(x,n,2.e-5);if(s.y==0.){float na;lfnoise(ind,na);palette(.5+.5*na,c1);c1=.4*c1+.5*c1*dot(-l,n)+.7*c1*pow(abs(dot(reflect(l,n),dir)),2.);}col=mix(col,c1,.3);}}}}float da=1.;scene(vec3 (uv,.2),s);da=abs(s.x-.1)-.003;col=mix(col,8.*col,sm(da/20.));col=1.5*col*col;gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *voronoinet_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;uniform float iFader0;uniform float iFader1;uniform float iFader2;uniform float iFader3;uniform float iFader4;uniform float iFader5;uniform float iFader6;uniform float iFader7;float iScale=1.,iNote=0.;const float pi=acos(-1.);const vec3 c=vec3 (1.0,0.0,-1.0);float a=1.0;void hash22(in vec2 p,out vec2 d);void rand(in vec2 x,out float n);void zextrude(in float z,in float d2d,in float h,out float d);void stroke(in float d0,in float s,out float d);void dbox(in vec2 x,in vec2 b,out float d);void dbox3(in vec3 x,in vec3 b,out float d);void smoothmin(in float a,in float b,in float k,out float dst);void dvoronoi(in vec2 x,out float d,out vec2 z,out float pc);void dquadvoronoi(in vec2 x,in float threshold,in float depth,out float d,out float faco){d=1.;vec2 y=x,yi;float size=.5,fac=1.;faco=1.;for(float i=0.;i<depth;i+=1.){float dd,dp;vec2 ind;dvoronoi(y/size/.5,dd,ind,dp);vec2 y0=y;float r;rand(ind+fac,r);fac*=r*step(r,threshold);faco*=r;if(fac!=0.){dd=abs(dd);smoothmin(d,dd,.01,d);}size*=.5;}faco+=fac*fac;}void analytical_box(in vec3 o,in vec3 dir,in vec3 size,out float d);void rot3(in vec3 p,out mat3 rot);float mat;void scene(in vec3 x,out vec2 d){d=c.xx;float dbound;dbox3(x,vec3 (.3*c.xx,.2),dbound);float da,fac;dquadvoronoi(x.xy-.1*iTime,.71,4.,da,fac);float p=pi/4.;vec2 cs=vec2 (cos(p),sin(p));mat2 m=mat2 (cs.x,cs.y,-cs.y,cs.x);vec2 y=m*x.xy;float da9,fac9;dquadvoronoi(y-12.-.1*iTime,.41,2.,da9,fac9);smoothmin(da,da9,.01,da);float r;rand(202.*fac*fac9*c.xx+3.,r);mat=r;zextrude(x.z,da,r*.3,da9);smoothmin(d.x,da9,.4,d.x);stroke(da,.015+6.*.045*clamp(iScale,0.,1.),da);float db;stroke(da,.011+6.*.033*clamp(iScale,0.,1.),db);stroke(d.x,.003,d.x);dbox3(x,vec3 (.33*c.xx,.02),da);smoothmin(d.x,da,.2,d.x);smoothmin(d.x,db,.05,d.x);}void normal(in vec3 x,out vec3 n,in float dx);void colorize(in vec2 x,out vec3 col){float phi=.1*iTime;vec3 white=.4*vec3 (0.99,0.29,0.09),gray=vec3 (0.95,0.25,0.05);float size=.1;vec2 y=mod(x,size)-.5*size;y=abs(y)-.001;float d=min(y.x,y.y);y=mod(x,.2*size)-.1*size;y=abs(y)-.0002;d=min(d,min(y.x,y.y));col=mix(white,gray,smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d));col=mix(col,length(col)/length(c.xxx)*c.xxx,.7);}void mainImage(out vec4 fragColor,in vec2 fragCoord){a=iResolution.x/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);vec3 col=c.yyy;float dhex,na,nal;vec2 ind;rand(floor(.33*iTime)*c.xx,na);rand(floor(.33*iTime)*c.xx+1.,nal);na=mix(na,nal,clamp(((.33*iTime-floor(.33*iTime))-.9)/.1,0.,1.));uv=mix(uv,.5*uv.yx,na);float pp=.3*iTime;vec3 o=c.yyx+.2*c.yzy,t=c.yyy,dir=normalize(t-o),r=normalize(c.xyy),u=normalize(cross(r,dir)),n,x,l;t+=uv.x*r+uv.y*u;dir=normalize(t-o);vec2 s;float d=-(o.z-.2)/dir.z;int N=250,i;x=o+d*dir;if(x.z>0.){for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=min(1.e-2,s.x);}l=normalize(x+c.yxx);if(i<N){normal(x,n,5.e-4);mat3 RR;rot3(na*1.e3*vec3 (1.1,1.5,1.9)+iNote*210.,RR);col=mix(mix(.0,.3,clamp(x.z/.3,0.,1.))*(.5+.5*mat)*c.xxx,(1.+.8*mat)*abs(RR*RR*vec3 (.7,.5,.26)),step(x.z,.08));col=mix(col,(1.+.8*mat)*abs(RR*vec3 (.6,.12,.06)),step(.19,x.z));col=mix((.5+.5*mat)*col,(1.+.8*mat)*abs(RR*vec3 (0.89,0.44,0.23)),(.5+.5*sin(x.z))*step(.19,x.z));col=mix(col,vec3 (0.25,0.23,0.21),(.5+.5*cos(4.*x.z+mat))*step(.19,x.z));col=mix(col,clamp(1.9*col,c.yyy,c.xxx),mat*step(.19,x.z));col=mix(col,4.*col,smoothstep(0.,1.,1.-abs(dot(n,3.*c.xyy))));}else {d=-o.z/dir.z;x=o+d*dir;n=c.yyx;l=vec3 (x.xy,.8);colorize(x.xy,col);}}else {d=-o.z/dir.z;x=o+d*dir;n=c.yyx;l=vec3 (x.xy,.8);colorize(x.xy,col);}col=.2*col+.9*col*abs(dot(l,n))+.4*col*abs(pow(dot(reflect(-l,n),dir),3.));col=1.*col*col;fragColor=clamp(vec4 (col,1.0),0.,1.);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
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
void Loadaddwindow()
{
    int addwindow_size = strlen(addwindow_source);
    addwindow_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(addwindow_handle, 1, (GLchar **)&addwindow_source, &addwindow_size);
    glCompileShader(addwindow_handle);
#ifdef DEBUG
    printf("---> addwindow Shader:\n");
    debug(addwindow_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadddeadline()
{
    int ddeadline_size = strlen(ddeadline_source);
    ddeadline_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(ddeadline_handle, 1, (GLchar **)&ddeadline_source, &ddeadline_size);
    glCompileShader(ddeadline_handle);
#ifdef DEBUG
    printf("---> ddeadline Shader:\n");
    debug(ddeadline_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddpolygon()
{
    int dpolygon_size = strlen(dpolygon_source);
    dpolygon_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dpolygon_handle, 1, (GLchar **)&dpolygon_source, &dpolygon_size);
    glCompileShader(dpolygon_handle);
#ifdef DEBUG
    printf("---> dpolygon Shader:\n");
    debug(dpolygon_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddspacepigs()
{
    int dspacepigs_size = strlen(dspacepigs_source);
    dspacepigs_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dspacepigs_handle, 1, (GLchar **)&dspacepigs_source, &dspacepigs_size);
    glCompileShader(dspacepigs_handle);
#ifdef DEBUG
    printf("---> dspacepigs Shader:\n");
    debug(dspacepigs_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadanalytical_box()
{
    int analytical_box_size = strlen(analytical_box_source);
    analytical_box_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(analytical_box_handle, 1, (GLchar **)&analytical_box_source, &analytical_box_size);
    glCompileShader(analytical_box_handle);
#ifdef DEBUG
    printf("---> analytical_box Shader:\n");
    debug(analytical_box_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadhash33()
{
    int hash33_size = strlen(hash33_source);
    hash33_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(hash33_handle, 1, (GLchar **)&hash33_source, &hash33_size);
    glCompileShader(hash33_handle);
#ifdef DEBUG
    printf("---> hash33 Shader:\n");
    debug(hash33_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddvoronoi3()
{
    int dvoronoi3_size = strlen(dvoronoi3_source);
    dvoronoi3_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dvoronoi3_handle, 1, (GLchar **)&dvoronoi3_source, &dvoronoi3_size);
    glCompileShader(dvoronoi3_handle);
#ifdef DEBUG
    printf("---> dvoronoi3 Shader:\n");
    debug(dvoronoi3_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddsmoothvoronoi3()
{
    int dsmoothvoronoi3_size = strlen(dsmoothvoronoi3_source);
    dsmoothvoronoi3_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dsmoothvoronoi3_handle, 1, (GLchar **)&dsmoothvoronoi3_source, &dsmoothvoronoi3_size);
    glCompileShader(dsmoothvoronoi3_handle);
#ifdef DEBUG
    printf("---> dsmoothvoronoi3 Shader:\n");
    debug(dsmoothvoronoi3_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddstar()
{
    int dstar_size = strlen(dstar_source);
    dstar_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dstar_handle, 1, (GLchar **)&dstar_source, &dstar_size);
    glCompileShader(dstar_handle);
#ifdef DEBUG
    printf("---> dstar Shader:\n");
    debug(dstar_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadsmoothmax()
{
    int smoothmax_size = strlen(smoothmax_source);
    smoothmax_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(smoothmax_handle, 1, (GLchar **)&smoothmax_source, &smoothmax_size);
    glCompileShader(smoothmax_handle);
#ifdef DEBUG
    printf("---> smoothmax Shader:\n");
    debug(smoothmax_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddstar3()
{
    int dstar3_size = strlen(dstar3_source);
    dstar3_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dstar3_handle, 1, (GLchar **)&dstar3_source, &dstar3_size);
    glCompileShader(dstar3_handle);
#ifdef DEBUG
    printf("---> dstar3 Shader:\n");
    debug(dstar3_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddhexagonpattern()
{
    int dhexagonpattern_size = strlen(dhexagonpattern_source);
    dhexagonpattern_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dhexagonpattern_handle, 1, (GLchar **)&dhexagonpattern_source, &dhexagonpattern_size);
    glCompileShader(dhexagonpattern_handle);
#ifdef DEBUG
    printf("---> dhexagonpattern Shader:\n");
    debug(dhexagonpattern_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddmercury()
{
    int dmercury_size = strlen(dmercury_source);
    dmercury_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dmercury_handle, 1, (GLchar **)&dmercury_source, &dmercury_size);
    glCompileShader(dmercury_handle);
#ifdef DEBUG
    printf("---> dmercury Shader:\n");
    debug(dmercury_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddtriangle()
{
    int dtriangle_size = strlen(dtriangle_source);
    dtriangle_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dtriangle_handle, 1, (GLchar **)&dtriangle_source, &dtriangle_size);
    glCompileShader(dtriangle_handle);
#ifdef DEBUG
    printf("---> dtriangle Shader:\n");
    debug(dtriangle_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadrot()
{
    int rot_size = strlen(rot_source);
    rot_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rot_handle, 1, (GLchar **)&rot_source, &rot_size);
    glCompileShader(rot_handle);
#ifdef DEBUG
    printf("---> rot Shader:\n");
    debug(rot_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddschnappsgirls()
{
    int dschnappsgirls_size = strlen(dschnappsgirls_source);
    dschnappsgirls_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dschnappsgirls_handle, 1, (GLchar **)&dschnappsgirls_source, &dschnappsgirls_size);
    glCompileShader(dschnappsgirls_handle);
#ifdef DEBUG
    printf("---> dschnappsgirls Shader:\n");
    debug(dschnappsgirls_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddhaujobb()
{
    int dhaujobb_size = strlen(dhaujobb_source);
    dhaujobb_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dhaujobb_handle, 1, (GLchar **)&dhaujobb_source, &dhaujobb_size);
    glCompileShader(dhaujobb_handle);
#ifdef DEBUG
    printf("---> dhaujobb Shader:\n");
    debug(dhaujobb_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddkewlers()
{
    int dkewlers_size = strlen(dkewlers_source);
    dkewlers_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dkewlers_handle, 1, (GLchar **)&dkewlers_source, &dkewlers_size);
    glCompileShader(dkewlers_handle);
#ifdef DEBUG
    printf("---> dkewlers Shader:\n");
    debug(dkewlers_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddfarbrausch()
{
    int dfarbrausch_size = strlen(dfarbrausch_source);
    dfarbrausch_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dfarbrausch_handle, 1, (GLchar **)&dfarbrausch_source, &dfarbrausch_size);
    glCompileShader(dfarbrausch_handle);
#ifdef DEBUG
    printf("---> dfarbrausch Shader:\n");
    debug(dfarbrausch_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadd5711()
{
    int d5711_size = strlen(d5711_source);
    d5711_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(d5711_handle, 1, (GLchar **)&d5711_source, &d5711_size);
    glCompileShader(d5711_handle);
#ifdef DEBUG
    printf("---> d5711 Shader:\n");
    debug(d5711_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loadsub()
{
    int sub_size = strlen(sub_source);
    sub_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sub_handle, 1, (GLchar **)&sub_source, &sub_size);
    glCompileShader(sub_handle);
#ifdef DEBUG
    printf("---> sub Shader:\n");
    debug(sub_handle);
    printf(">>>>\n");
#endif
    progress += .2/(float)nsymbols;
}
void Loaddoctahedron()
{
    int doctahedron_size = strlen(doctahedron_source);
    doctahedron_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(doctahedron_handle, 1, (GLchar **)&doctahedron_source, &doctahedron_size);
    glCompileShader(doctahedron_handle);
#ifdef DEBUG
    printf("---> doctahedron Shader:\n");
    debug(doctahedron_handle);
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
    Loadaddwindow();
    updateBar();
    Loadddeadline();
    updateBar();
    Loaddpolygon();
    updateBar();
    Loaddspacepigs();
    updateBar();
    Loadanalytical_box();
    updateBar();
    Loadhash33();
    updateBar();
    Loaddvoronoi3();
    updateBar();
    Loaddsmoothvoronoi3();
    updateBar();
    Loaddstar();
    updateBar();
    Loadsmoothmax();
    updateBar();
    Loaddstar3();
    updateBar();
    Loaddhexagonpattern();
    updateBar();
    Loaddmercury();
    updateBar();
    Loaddtriangle();
    updateBar();
    Loadrot();
    updateBar();
    Loaddschnappsgirls();
    updateBar();
    Loaddhaujobb();
    updateBar();
    Loaddkewlers();
    updateBar();
    Loaddfarbrausch();
    updateBar();
    Loadd5711();
    updateBar();
    Loadsub();
    updateBar();
    Loaddoctahedron();
    updateBar();
}
int ocean_program, ocean_handle, logo210_program, logo210_handle, graffiti_program, graffiti_handle, starsky_program, starsky_handle, text_program, text_handle, post_program, post_handle, deadline_program, deadline_handle, hydrant_program, hydrant_handle, watercubes_program, watercubes_handle, glitchcity_program, glitchcity_handle, greetings_program, greetings_handle, fractal_program, fractal_handle, voronoinet_program, voronoinet_handle;
int ocean_iTime_location,ocean_iResolution_location,ocean_iFader0_location,ocean_iFader1_location,ocean_iFader2_location,ocean_iFader3_location,ocean_iFader4_location,ocean_iFader5_location,ocean_iFader6_location,ocean_iFader7_location;
int logo210_iTime_location,logo210_iResolution_location,logo210_iFader0_location,logo210_iFader1_location,logo210_iFader2_location,logo210_iFader3_location,logo210_iFader4_location,logo210_iFader5_location,logo210_iFader6_location,logo210_iFader7_location;
int graffiti_iTime_location,graffiti_iResolution_location,graffiti_iFader0_location,graffiti_iFader1_location,graffiti_iFader2_location,graffiti_iFader3_location,graffiti_iFader4_location,graffiti_iFader5_location,graffiti_iFader6_location,graffiti_iFader7_location;
int starsky_iTime_location,starsky_iResolution_location,starsky_iFader0_location,starsky_iFader1_location,starsky_iFader2_location,starsky_iFader3_location,starsky_iFader4_location,starsky_iFader5_location,starsky_iFader6_location,starsky_iFader7_location;
int text_iFontWidth_location,text_iTime_location,text_iResolution_location,text_iChannel0_location,text_iFont_location,text_iFSAA_location,text_iFader0_location,text_iFader1_location,text_iFader2_location,text_iFader3_location,text_iFader4_location,text_iFader5_location,text_iFader6_location,text_iFader7_location;
int post_iFSAA_location,post_iResolution_location,post_iChannel0_location,post_iTime_location;
int deadline_iTime_location,deadline_iResolution_location,deadline_iFader0_location,deadline_iFader1_location,deadline_iFader2_location,deadline_iFader3_location,deadline_iFader4_location,deadline_iFader5_location,deadline_iFader6_location,deadline_iFader7_location;
int hydrant_iTime_location,hydrant_iResolution_location,hydrant_iFader0_location,hydrant_iFader1_location,hydrant_iFader2_location,hydrant_iFader3_location,hydrant_iFader4_location,hydrant_iFader5_location,hydrant_iFader6_location,hydrant_iFader7_location;
int watercubes_iTime_location,watercubes_iResolution_location,watercubes_iFader0_location,watercubes_iFader1_location,watercubes_iFader2_location,watercubes_iFader3_location,watercubes_iFader4_location,watercubes_iFader5_location,watercubes_iFader6_location,watercubes_iFader7_location;
int glitchcity_iTime_location,glitchcity_iResolution_location,glitchcity_iFader0_location,glitchcity_iFader1_location,glitchcity_iFader2_location,glitchcity_iFader3_location,glitchcity_iFader4_location,glitchcity_iFader5_location,glitchcity_iFader6_location,glitchcity_iFader7_location;
int greetings_iTime_location,greetings_iResolution_location,greetings_iFader0_location,greetings_iFader1_location,greetings_iFader2_location,greetings_iFader3_location,greetings_iFader4_location,greetings_iFader5_location,greetings_iFader6_location,greetings_iFader7_location;
int fractal_iTime_location,fractal_iResolution_location,fractal_iFader0_location,fractal_iFader1_location,fractal_iFader2_location,fractal_iFader3_location,fractal_iFader4_location,fractal_iFader5_location,fractal_iFader6_location,fractal_iFader7_location;
int voronoinet_iTime_location,voronoinet_iResolution_location,voronoinet_iFader0_location,voronoinet_iFader1_location,voronoinet_iFader2_location,voronoinet_iFader3_location,voronoinet_iFader4_location,voronoinet_iFader5_location,voronoinet_iFader6_location,voronoinet_iFader7_location;
const int nprograms = 13;

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
    ocean_iFader0_location = glGetUniformLocation(ocean_program, "iFader0");
    ocean_iFader1_location = glGetUniformLocation(ocean_program, "iFader1");
    ocean_iFader2_location = glGetUniformLocation(ocean_program, "iFader2");
    ocean_iFader3_location = glGetUniformLocation(ocean_program, "iFader3");
    ocean_iFader4_location = glGetUniformLocation(ocean_program, "iFader4");
    ocean_iFader5_location = glGetUniformLocation(ocean_program, "iFader5");
    ocean_iFader6_location = glGetUniformLocation(ocean_program, "iFader6");
    ocean_iFader7_location = glGetUniformLocation(ocean_program, "iFader7");
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
    logo210_iFader0_location = glGetUniformLocation(logo210_program, "iFader0");
    logo210_iFader1_location = glGetUniformLocation(logo210_program, "iFader1");
    logo210_iFader2_location = glGetUniformLocation(logo210_program, "iFader2");
    logo210_iFader3_location = glGetUniformLocation(logo210_program, "iFader3");
    logo210_iFader4_location = glGetUniformLocation(logo210_program, "iFader4");
    logo210_iFader5_location = glGetUniformLocation(logo210_program, "iFader5");
    logo210_iFader6_location = glGetUniformLocation(logo210_program, "iFader6");
    logo210_iFader7_location = glGetUniformLocation(logo210_program, "iFader7");
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
    graffiti_iFader0_location = glGetUniformLocation(graffiti_program, "iFader0");
    graffiti_iFader1_location = glGetUniformLocation(graffiti_program, "iFader1");
    graffiti_iFader2_location = glGetUniformLocation(graffiti_program, "iFader2");
    graffiti_iFader3_location = glGetUniformLocation(graffiti_program, "iFader3");
    graffiti_iFader4_location = glGetUniformLocation(graffiti_program, "iFader4");
    graffiti_iFader5_location = glGetUniformLocation(graffiti_program, "iFader5");
    graffiti_iFader6_location = glGetUniformLocation(graffiti_program, "iFader6");
    graffiti_iFader7_location = glGetUniformLocation(graffiti_program, "iFader7");
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
    starsky_iFader0_location = glGetUniformLocation(starsky_program, "iFader0");
    starsky_iFader1_location = glGetUniformLocation(starsky_program, "iFader1");
    starsky_iFader2_location = glGetUniformLocation(starsky_program, "iFader2");
    starsky_iFader3_location = glGetUniformLocation(starsky_program, "iFader3");
    starsky_iFader4_location = glGetUniformLocation(starsky_program, "iFader4");
    starsky_iFader5_location = glGetUniformLocation(starsky_program, "iFader5");
    starsky_iFader6_location = glGetUniformLocation(starsky_program, "iFader6");
    starsky_iFader7_location = glGetUniformLocation(starsky_program, "iFader7");
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
    glAttachShader(text_program,addwindow_handle);
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
    text_iFader0_location = glGetUniformLocation(text_program, "iFader0");
    text_iFader1_location = glGetUniformLocation(text_program, "iFader1");
    text_iFader2_location = glGetUniformLocation(text_program, "iFader2");
    text_iFader3_location = glGetUniformLocation(text_program, "iFader3");
    text_iFader4_location = glGetUniformLocation(text_program, "iFader4");
    text_iFader5_location = glGetUniformLocation(text_program, "iFader5");
    text_iFader6_location = glGetUniformLocation(text_program, "iFader6");
    text_iFader7_location = glGetUniformLocation(text_program, "iFader7");
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

void Loaddeadline()
{
    int deadline_size = strlen(deadline_source);
    deadline_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(deadline_handle, 1, (GLchar **)&deadline_source, &deadline_size);
    glCompileShader(deadline_handle);
#ifdef DEBUG
    printf("---> deadline Shader:\n");
    debug(deadline_handle);
    printf(">>>>\n");
#endif
    deadline_program = glCreateProgram();
    glAttachShader(deadline_program,deadline_handle);
    glAttachShader(deadline_program,rand_handle);
    glAttachShader(deadline_program,lfnoise_handle);
    glAttachShader(deadline_program,hash11_handle);
    glAttachShader(deadline_program,hash12_handle);
    glAttachShader(deadline_program,hash22_handle);
    glAttachShader(deadline_program,dlinesegment_handle);
    glAttachShader(deadline_program,dvoronoi_handle);
    glAttachShader(deadline_program,stroke_handle);
    glAttachShader(deadline_program,dbox_handle);
    glAttachShader(deadline_program,ddeadline_handle);
    glAttachShader(deadline_program,zextrude_handle);
    glAttachShader(deadline_program,normal_handle);
    glLinkProgram(deadline_program);
#ifdef DEBUG
    printf("---> deadline Program:\n");
    debugp(deadline_program);
    printf(">>>>\n");
#endif
    glUseProgram(deadline_program);
    deadline_iTime_location = glGetUniformLocation(deadline_program, "iTime");
    deadline_iResolution_location = glGetUniformLocation(deadline_program, "iResolution");
    deadline_iFader0_location = glGetUniformLocation(deadline_program, "iFader0");
    deadline_iFader1_location = glGetUniformLocation(deadline_program, "iFader1");
    deadline_iFader2_location = glGetUniformLocation(deadline_program, "iFader2");
    deadline_iFader3_location = glGetUniformLocation(deadline_program, "iFader3");
    deadline_iFader4_location = glGetUniformLocation(deadline_program, "iFader4");
    deadline_iFader5_location = glGetUniformLocation(deadline_program, "iFader5");
    deadline_iFader6_location = glGetUniformLocation(deadline_program, "iFader6");
    deadline_iFader7_location = glGetUniformLocation(deadline_program, "iFader7");
    progress += .2/(float)nprograms;
}

void Loadhydrant()
{
    int hydrant_size = strlen(hydrant_source);
    hydrant_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(hydrant_handle, 1, (GLchar **)&hydrant_source, &hydrant_size);
    glCompileShader(hydrant_handle);
#ifdef DEBUG
    printf("---> hydrant Shader:\n");
    debug(hydrant_handle);
    printf(">>>>\n");
#endif
    hydrant_program = glCreateProgram();
    glAttachShader(hydrant_program,hydrant_handle);
    glAttachShader(hydrant_program,rand_handle);
    glAttachShader(hydrant_program,lfnoise_handle);
    glAttachShader(hydrant_program,mfnoise_handle);
    glAttachShader(hydrant_program,hash11_handle);
    glAttachShader(hydrant_program,hash12_handle);
    glAttachShader(hydrant_program,hash21_handle);
    glAttachShader(hydrant_program,hash22_handle);
    glAttachShader(hydrant_program,hash31_handle);
    glAttachShader(hydrant_program,dvoronoi_handle);
    glAttachShader(hydrant_program,stroke_handle);
    glAttachShader(hydrant_program,dbox_handle);
    glAttachShader(hydrant_program,drhomboid_handle);
    glAttachShader(hydrant_program,dlinesegment_handle);
    glAttachShader(hydrant_program,zextrude_handle);
    glAttachShader(hydrant_program,add_handle);
    glAttachShader(hydrant_program,normal_handle);
    glAttachShader(hydrant_program,dpolygon_handle);
    glAttachShader(hydrant_program,dspacepigs_handle);
    glAttachShader(hydrant_program,analytical_box_handle);
    glLinkProgram(hydrant_program);
#ifdef DEBUG
    printf("---> hydrant Program:\n");
    debugp(hydrant_program);
    printf(">>>>\n");
#endif
    glUseProgram(hydrant_program);
    hydrant_iTime_location = glGetUniformLocation(hydrant_program, "iTime");
    hydrant_iResolution_location = glGetUniformLocation(hydrant_program, "iResolution");
    hydrant_iFader0_location = glGetUniformLocation(hydrant_program, "iFader0");
    hydrant_iFader1_location = glGetUniformLocation(hydrant_program, "iFader1");
    hydrant_iFader2_location = glGetUniformLocation(hydrant_program, "iFader2");
    hydrant_iFader3_location = glGetUniformLocation(hydrant_program, "iFader3");
    hydrant_iFader4_location = glGetUniformLocation(hydrant_program, "iFader4");
    hydrant_iFader5_location = glGetUniformLocation(hydrant_program, "iFader5");
    hydrant_iFader6_location = glGetUniformLocation(hydrant_program, "iFader6");
    hydrant_iFader7_location = glGetUniformLocation(hydrant_program, "iFader7");
    progress += .2/(float)nprograms;
}

void Loadwatercubes()
{
    int watercubes_size = strlen(watercubes_source);
    watercubes_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(watercubes_handle, 1, (GLchar **)&watercubes_source, &watercubes_size);
    glCompileShader(watercubes_handle);
#ifdef DEBUG
    printf("---> watercubes Shader:\n");
    debug(watercubes_handle);
    printf(">>>>\n");
#endif
    watercubes_program = glCreateProgram();
    glAttachShader(watercubes_program,watercubes_handle);
    glAttachShader(watercubes_program,hash22_handle);
    glAttachShader(watercubes_program,dvoronoi_handle);
    glAttachShader(watercubes_program,hash33_handle);
    glAttachShader(watercubes_program,dvoronoi3_handle);
    glAttachShader(watercubes_program,smoothmin_handle);
    glAttachShader(watercubes_program,dsmoothvoronoi3_handle);
    glAttachShader(watercubes_program,rot3_handle);
    glAttachShader(watercubes_program,add_handle);
    glAttachShader(watercubes_program,dbox3_handle);
    glAttachShader(watercubes_program,dstar_handle);
    glAttachShader(watercubes_program,smoothmax_handle);
    glAttachShader(watercubes_program,dstar3_handle);
    glAttachShader(watercubes_program,normal_handle);
    glAttachShader(watercubes_program,dbox_handle);
    glLinkProgram(watercubes_program);
#ifdef DEBUG
    printf("---> watercubes Program:\n");
    debugp(watercubes_program);
    printf(">>>>\n");
#endif
    glUseProgram(watercubes_program);
    watercubes_iTime_location = glGetUniformLocation(watercubes_program, "iTime");
    watercubes_iResolution_location = glGetUniformLocation(watercubes_program, "iResolution");
    watercubes_iFader0_location = glGetUniformLocation(watercubes_program, "iFader0");
    watercubes_iFader1_location = glGetUniformLocation(watercubes_program, "iFader1");
    watercubes_iFader2_location = glGetUniformLocation(watercubes_program, "iFader2");
    watercubes_iFader3_location = glGetUniformLocation(watercubes_program, "iFader3");
    watercubes_iFader4_location = glGetUniformLocation(watercubes_program, "iFader4");
    watercubes_iFader5_location = glGetUniformLocation(watercubes_program, "iFader5");
    watercubes_iFader6_location = glGetUniformLocation(watercubes_program, "iFader6");
    watercubes_iFader7_location = glGetUniformLocation(watercubes_program, "iFader7");
    progress += .2/(float)nprograms;
}

void Loadglitchcity()
{
    int glitchcity_size = strlen(glitchcity_source);
    glitchcity_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(glitchcity_handle, 1, (GLchar **)&glitchcity_source, &glitchcity_size);
    glCompileShader(glitchcity_handle);
#ifdef DEBUG
    printf("---> glitchcity Shader:\n");
    debug(glitchcity_handle);
    printf(">>>>\n");
#endif
    glitchcity_program = glCreateProgram();
    glAttachShader(glitchcity_program,glitchcity_handle);
    glAttachShader(glitchcity_program,hash22_handle);
    glAttachShader(glitchcity_program,hash12_handle);
    glAttachShader(glitchcity_program,dvoronoi_handle);
    glAttachShader(glitchcity_program,add_handle);
    glAttachShader(glitchcity_program,dbox3_handle);
    glAttachShader(glitchcity_program,normal_handle);
    glLinkProgram(glitchcity_program);
#ifdef DEBUG
    printf("---> glitchcity Program:\n");
    debugp(glitchcity_program);
    printf(">>>>\n");
#endif
    glUseProgram(glitchcity_program);
    glitchcity_iTime_location = glGetUniformLocation(glitchcity_program, "iTime");
    glitchcity_iResolution_location = glGetUniformLocation(glitchcity_program, "iResolution");
    glitchcity_iFader0_location = glGetUniformLocation(glitchcity_program, "iFader0");
    glitchcity_iFader1_location = glGetUniformLocation(glitchcity_program, "iFader1");
    glitchcity_iFader2_location = glGetUniformLocation(glitchcity_program, "iFader2");
    glitchcity_iFader3_location = glGetUniformLocation(glitchcity_program, "iFader3");
    glitchcity_iFader4_location = glGetUniformLocation(glitchcity_program, "iFader4");
    glitchcity_iFader5_location = glGetUniformLocation(glitchcity_program, "iFader5");
    glitchcity_iFader6_location = glGetUniformLocation(glitchcity_program, "iFader6");
    glitchcity_iFader7_location = glGetUniformLocation(glitchcity_program, "iFader7");
    progress += .2/(float)nprograms;
}

void Loadgreetings()
{
    int greetings_size = strlen(greetings_source);
    greetings_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(greetings_handle, 1, (GLchar **)&greetings_source, &greetings_size);
    glCompileShader(greetings_handle);
#ifdef DEBUG
    printf("---> greetings Shader:\n");
    debug(greetings_handle);
    printf(">>>>\n");
#endif
    greetings_program = glCreateProgram();
    glAttachShader(greetings_program,greetings_handle);
    glAttachShader(greetings_program,rand_handle);
    glAttachShader(greetings_program,lfnoise_handle);
    glAttachShader(greetings_program,dhexagonpattern_handle);
    glAttachShader(greetings_program,dbox_handle);
    glAttachShader(greetings_program,dlinesegment_handle);
    glAttachShader(greetings_program,stroke_handle);
    glAttachShader(greetings_program,addwindow_handle);
    glAttachShader(greetings_program,dpolygon_handle);
    glAttachShader(greetings_program,dmercury_handle);
    glAttachShader(greetings_program,dcircle_handle);
    glAttachShader(greetings_program,dtriangle_handle);
    glAttachShader(greetings_program,rot_handle);
    glAttachShader(greetings_program,dschnappsgirls_handle);
    glAttachShader(greetings_program,dhaujobb_handle);
    glAttachShader(greetings_program,dkewlers_handle);
    glAttachShader(greetings_program,dfarbrausch_handle);
    glAttachShader(greetings_program,d5711_handle);
    glLinkProgram(greetings_program);
#ifdef DEBUG
    printf("---> greetings Program:\n");
    debugp(greetings_program);
    printf(">>>>\n");
#endif
    glUseProgram(greetings_program);
    greetings_iTime_location = glGetUniformLocation(greetings_program, "iTime");
    greetings_iResolution_location = glGetUniformLocation(greetings_program, "iResolution");
    greetings_iFader0_location = glGetUniformLocation(greetings_program, "iFader0");
    greetings_iFader1_location = glGetUniformLocation(greetings_program, "iFader1");
    greetings_iFader2_location = glGetUniformLocation(greetings_program, "iFader2");
    greetings_iFader3_location = glGetUniformLocation(greetings_program, "iFader3");
    greetings_iFader4_location = glGetUniformLocation(greetings_program, "iFader4");
    greetings_iFader5_location = glGetUniformLocation(greetings_program, "iFader5");
    greetings_iFader6_location = glGetUniformLocation(greetings_program, "iFader6");
    greetings_iFader7_location = glGetUniformLocation(greetings_program, "iFader7");
    progress += .2/(float)nprograms;
}

void Loadfractal()
{
    int fractal_size = strlen(fractal_source);
    fractal_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fractal_handle, 1, (GLchar **)&fractal_source, &fractal_size);
    glCompileShader(fractal_handle);
#ifdef DEBUG
    printf("---> fractal Shader:\n");
    debug(fractal_handle);
    printf(">>>>\n");
#endif
    fractal_program = glCreateProgram();
    glAttachShader(fractal_program,fractal_handle);
    glAttachShader(fractal_program,rand_handle);
    glAttachShader(fractal_program,lfnoise_handle);
    glAttachShader(fractal_program,hash22_handle);
    glAttachShader(fractal_program,dvoronoi_handle);
    glAttachShader(fractal_program,add_handle);
    glAttachShader(fractal_program,sub_handle);
    glAttachShader(fractal_program,zextrude_handle);
    glAttachShader(fractal_program,dbox3_handle);
    glAttachShader(fractal_program,rot3_handle);
    glAttachShader(fractal_program,dbox_handle);
    glAttachShader(fractal_program,dstar_handle);
    glAttachShader(fractal_program,doctahedron_handle);
    glAttachShader(fractal_program,normal_handle);
    glLinkProgram(fractal_program);
#ifdef DEBUG
    printf("---> fractal Program:\n");
    debugp(fractal_program);
    printf(">>>>\n");
#endif
    glUseProgram(fractal_program);
    fractal_iTime_location = glGetUniformLocation(fractal_program, "iTime");
    fractal_iResolution_location = glGetUniformLocation(fractal_program, "iResolution");
    fractal_iFader0_location = glGetUniformLocation(fractal_program, "iFader0");
    fractal_iFader1_location = glGetUniformLocation(fractal_program, "iFader1");
    fractal_iFader2_location = glGetUniformLocation(fractal_program, "iFader2");
    fractal_iFader3_location = glGetUniformLocation(fractal_program, "iFader3");
    fractal_iFader4_location = glGetUniformLocation(fractal_program, "iFader4");
    fractal_iFader5_location = glGetUniformLocation(fractal_program, "iFader5");
    fractal_iFader6_location = glGetUniformLocation(fractal_program, "iFader6");
    fractal_iFader7_location = glGetUniformLocation(fractal_program, "iFader7");
    progress += .2/(float)nprograms;
}

void Loadvoronoinet()
{
    int voronoinet_size = strlen(voronoinet_source);
    voronoinet_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(voronoinet_handle, 1, (GLchar **)&voronoinet_source, &voronoinet_size);
    glCompileShader(voronoinet_handle);
#ifdef DEBUG
    printf("---> voronoinet Shader:\n");
    debug(voronoinet_handle);
    printf(">>>>\n");
#endif
    voronoinet_program = glCreateProgram();
    glAttachShader(voronoinet_program,voronoinet_handle);
    glAttachShader(voronoinet_program,hash22_handle);
    glAttachShader(voronoinet_program,rand_handle);
    glAttachShader(voronoinet_program,zextrude_handle);
    glAttachShader(voronoinet_program,stroke_handle);
    glAttachShader(voronoinet_program,dbox_handle);
    glAttachShader(voronoinet_program,dbox3_handle);
    glAttachShader(voronoinet_program,smoothmin_handle);
    glAttachShader(voronoinet_program,dvoronoi_handle);
    glAttachShader(voronoinet_program,analytical_box_handle);
    glAttachShader(voronoinet_program,rot3_handle);
    glAttachShader(voronoinet_program,normal_handle);
    glLinkProgram(voronoinet_program);
#ifdef DEBUG
    printf("---> voronoinet Program:\n");
    debugp(voronoinet_program);
    printf(">>>>\n");
#endif
    glUseProgram(voronoinet_program);
    voronoinet_iTime_location = glGetUniformLocation(voronoinet_program, "iTime");
    voronoinet_iResolution_location = glGetUniformLocation(voronoinet_program, "iResolution");
    voronoinet_iFader0_location = glGetUniformLocation(voronoinet_program, "iFader0");
    voronoinet_iFader1_location = glGetUniformLocation(voronoinet_program, "iFader1");
    voronoinet_iFader2_location = glGetUniformLocation(voronoinet_program, "iFader2");
    voronoinet_iFader3_location = glGetUniformLocation(voronoinet_program, "iFader3");
    voronoinet_iFader4_location = glGetUniformLocation(voronoinet_program, "iFader4");
    voronoinet_iFader5_location = glGetUniformLocation(voronoinet_program, "iFader5");
    voronoinet_iFader6_location = glGetUniformLocation(voronoinet_program, "iFader6");
    voronoinet_iFader7_location = glGetUniformLocation(voronoinet_program, "iFader7");
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
    Loaddeadline();
    updateBar();
    Loadhydrant();
    updateBar();
    Loadwatercubes();
    updateBar();
    Loadglitchcity();
    updateBar();
    Loadgreetings();
    updateBar();
    Loadfractal();
    updateBar();
    Loadvoronoinet();
    updateBar();
}
#endif
