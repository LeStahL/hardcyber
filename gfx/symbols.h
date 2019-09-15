//Generated with Symbolize (c) 2019 Alexander Kraus <nr4@z10.info>.
#ifndef SYMBOLIZE_H
#define SYMBOLIZE_H

extern float progress;int dbox3_handle, rot3_handle, stroke_handle, add_handle, rand_handle, lfnoise_handle, rshort_handle, rfloat_handle, dbox_handle, dcircle_handle, dlinesegment_handle, drhomboid_handle, dcirclesegment_handle, dglyph_handle, dstring_handle, dfloat_handle, smoothmin_handle, dint_handle, dtime_handle, window_handle, progressbar_handle, dvoronoi_handle, normal_handle;
const int nsymbols = 23;
const char *dbox3_source = "#version 130\nvoid dbox3(in vec3 x,in vec3 b,out float d){vec3 da=abs(x)-b;d=length(max(da,0.0))+min(max(da.x,max(da.y,da.z)),0.0);}\0";
const char *rot3_source = "const vec3 c=vec3 (1.,0.,-1.);void rot3(in vec3 p,out mat3 rot){rot=mat3 (c.xyyy,cos(p.x),sin(p.x),0.,-sin(p.x),cos(p.x))*mat3 (cos(p.y),0.,-sin(p.y),c.yxy,sin(p.y),0.,cos(p.y))*mat3 (cos(p.z),-sin(p.z),0.,sin(p.z),cos(p.z),c.yyyx);}\0";
const char *stroke_source = "void stroke(in float d0,in float s,out float d){d=abs(d0)-s;}\0";
const char *add_source = "void add(in vec2 sda,in vec2 sdb,out vec2 sdf){sdf=(sda.x<sdb.x)?sda:sdb;}\0";
const char *rand_source = "#version 130\nvoid rand(in vec2 x,out float n){x+=400.;n=fract(sin(dot(sign(x)*abs(x),vec2 (12.9898,78.233)))*43758.5453);}\0";
const char *lfnoise_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rand(in vec2 x,out float d);void lfnoise(in vec2 t,out float n){vec2 i=floor(t);t=fract(t);t=smoothstep(c.yy,c.xx,t);vec2 v1,v2;rand(i,v1.x);rand(i+c.xy,v1.y);rand(i+c.yx,v2.x);rand(i+c.xx,v2.y);v1=c.zz+2.*mix(v1,v2,t.y);n=mix(v1.x,v1.y,t.x);}\0";
const char *rshort_source = "#version 130\nuniform float iFontWidth;uniform sampler2D iFont;void rshort(in float off,out float val){float hilo=mod(off,2.);off*=.5;vec2 ind=(vec2 (mod(off,iFontWidth),floor(off/iFontWidth))+.05)/iFontWidth;vec4 block=texture(iFont,ind);vec2 data=mix(block.rg,block.ba,hilo);val=round(dot(vec2 (255.,65280.),data));}\0";
const char *rfloat_source = "#version 130\nvoid rshort(in float off,out float val);void rfloat(in float off,out float val){float d;rshort(off,d);float sign=floor(d/32768.),exponent=floor(d/1024.-sign*32.),significand=d-sign*32768.-exponent*1024.;if(exponent==0.){val=mix(1.,-1.,sign)*5.960464477539063e-08*significand;}else {val=mix(1.,-1.,sign)*(1.+significand*9.765625e-4)*pow(2.,exponent-15.);}}\0";
const char *dbox_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dbox(in vec2 x,in vec2 b,out float d){vec2 da=abs(x)-b;d=length(max(da,c.yy))+min(max(da.x,da.y),0.0);}\0";
const char *dcircle_source = "#version 130\nvoid dcircle(in vec2 x,out float d){d=length(x)-1.0;}\0";
const char *dlinesegment_source = "#version 130\nvoid dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d){vec2 da=p2-p1;d=length(x-mix(p1,p2,clamp(dot(x-p1,da)/dot(da,da),0.,1.)));}\0";
const char *drhomboid_source = "#version 130\nvoid dbox(in vec2 x,in vec2 b,out float dst);void drhomboid(in vec2 x,in vec2 b,in float tilt,out float dst){x.x-=tilt/2./b.y*x.y;dbox(x,b,dst);}\0";
const char *dcirclesegment_source = "#version 130\nconst float pi=acos(-1.);void dcirclesegment(in vec2 x,in float R,in float p0,in float p1,out float d){float p=atan(x.y,x.x);vec2 philo=vec2 (max(p0,p1),min(p0,p1));if((p<philo.x&&p>philo.y)||(p+2.0*pi<philo.x&&p+2.0*pi>philo.y)||(p-2.0*pi<philo.x&&p-2.0*pi>philo.y))d=abs(length(x)-R);else d=min(length(x-vec2 (cos(p0),sin(p0))),length(x-vec2 (cos(p1),sin(p1))));}\0";
const char *dglyph_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rfloat(in float off,out float val);void dbox(in vec2 x,in vec2 b,out float dst);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void dcircle(in vec2 x,out float d);void dcirclesegment(in vec2 x,in float r,in float p0,in float p1,out float d);void stroke(in float d0,in float s,out float d);void smoothmin(in float a,in float b,in float k,out float dst);void dglyph(in vec2 x,in float ordinal,in float size,out float dst){float dis;dbox(x,2.*size*c.xx,dis);if(dis>0.){dst=dis+.5*size;return ;}float nglyphs,offset=0;rfloat(1.,nglyphs);for(float i=0.;i<nglyphs;i+=1.){float ord;rfloat(2.+2.*i,ord);ord=floor(ord);if(ord==ordinal){rfloat(2.+2.*i+1.,offset);offset=floor(offset);break;}}if(offset==0.){dst=1.;return ;}float d=1.,da=1.;float nlines;rfloat(offset,nlines);nlines=floor(nlines);offset+=1.;for(float i=0.;i<nlines;i+=1.){float x1;rfloat(offset,x1);offset+=1.;float y1;rfloat(offset,y1);offset+=1.;float x2;rfloat(offset,x2);offset+=1.;float y2;rfloat(offset,y2);offset+=1.;dlinesegment(x,size*vec2 (x1,y1),size*vec2 (x2,y2),da);d=min(d,da);}stroke(d,.2*size,d);float nsmoothlines,db=1.;da=1.;rfloat(offset,nsmoothlines);nsmoothlines=floor(nsmoothlines);offset+=1.;for(float i=0.;i<nsmoothlines;i+=1.){float x1;rfloat(offset,x1);offset+=1.;float y1;rfloat(offset,y1);offset+=1.;float x2;rfloat(offset,x2);offset+=1.;float y2;rfloat(offset,y2);offset+=1.;dlinesegment(x,size*vec2 (x1,y1),size*vec2 (x2,y2),db);da=min(da,db);}stroke(da,.2*size,da);smoothmin(d,da,.1*size,d);dst=d;}\0";
const char *dstring_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rfloat(in float off,out float val);void dbox(in vec2 x,in vec2 b,out float dst);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dstring(in vec2 x,in float ordinal,in float size,out float dst){float stroff0;rfloat(0.,stroff0);stroff0=floor(stroff0);float nstrings;rfloat(stroff0,nstrings);nstrings=floor(nstrings);if(ordinal>=nstrings){dst=1.;return ;}float stroff;rfloat(stroff0+1.+2.*ordinal,stroff);stroff=floor(stroff);float len;rfloat(stroff0+2.+2.*ordinal,len);len=floor(len);vec2 dx=mod(x-size,2.*size)-size,ind=ceil((x-dx+size)/2./size);float bound;dbox(x-size*(len-3.)*c.xy,vec2 (size*len,1.*size),bound);if(bound>0.){dst=bound+.5*size;return ;}float da;rfloat(stroff+ind.x,da);da=floor(da);dglyph(dx,da,.7*size,dst);}\0";
const char *dfloat_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dfloat(in vec2 x,in float num,in float size,out float dst){float d=1.,index=0.;float sign=sign(num),exp=0.;if(sign<0.){float da;dglyph(x,45.,.7*size,da);d=min(d,da);index+=1.;num*=-1.;}for(exp=-15.;exp<15.;exp+=1.)if(floor(num*pow(10.,exp))!=0.)break;exp*=-1.;for(float i=exp;i>=max(exp-5.,-33);i-=1.){float po=pow(10.,i);float ca=floor(num/po);num-=ca*po;float da;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;if(i==exp){dglyph(x-2.*index*size*c.xy,46.,.7*size,da);d=min(d,da);index+=1.;}}float db;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,101.,.7*size,db);d=min(d,db);index+=1.;if(exp<0.){dglyph(x+.7*size*c.xy-2.*index*size*c.xy,45.,.7*size,db);d=min(d,db);index+=1.;exp*=-1.;}float ca=floor(exp/10.);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,db);d=min(d,db);index+=1.;ca=floor(exp-10.*ca);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,db);d=min(d,db);index+=1.;dst=d;}\0";
const char *smoothmin_source = "void smoothmin(in float a,in float b,in float k,out float dst){float h=max(k-abs(a-b),0.0)/k;dst=min(a,b)-h*h*h*k*(1.0/6.0);}\0";
const char *dint_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dint(in vec2 x,in float num,in float size,in float ndigits,out float dst){float d=1.,index=0.;if(num==0.){index=ndigits;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.,.7*size,dst);return ;}float sign=sign(num),exp=0.;if(sign<0.){float da;dglyph(x,45.,.7*size,da);d=min(d,da);index+=1.;num*=-1.;}for(exp=-15.;exp<15.;exp+=1.)if(floor(num*pow(10.,exp))!=0.)break;exp*=-1.;int hit=0;for(float i=ndigits;i>=0.;i-=1.){float po=pow(10.,i);float ca=floor(num/po);if(ca==0.){if(hit==0){index+=1.;continue;}}else hit=1;num-=ca*po;float da;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;}dst=d;}\0";
const char *dtime_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dtime(in vec2 x,in float num,in float size,out float dst){float d=1.,index=0.;num=floor(num);float ca=floor(num/600.),da=1.;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;num-=ca*600.;ca=floor(num/60.);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;num-=ca*60.;dglyph(x+.7*size*c.xy-2.*index*size*c.xy,58.,.7*size,da);d=min(d,da);index+=1.;ca=floor(num/10.);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);index+=1.;num-=ca*10.;ca=floor(num/1.);dglyph(x+.7*size*c.xy-2.*index*size*c.xy,48.+ca,.7*size,da);d=min(d,da);dst=d;}\0";
const char *window_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);uniform float iTime;void dhexagonpattern(in vec2 p,out float d,out vec2 ind);void stroke(in float d0,in float s,out float d);void lfnoise(in vec2 t,out float num);void box(in vec2 x,in vec2 b,out float dst);void drhomboid(in vec2 x,in vec2 b,in float tilt,out float dst);void window(in vec2 x,in vec2 size,in vec3 bg,in float title_index,out vec4 col){}\0";
const char *progressbar_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void progressbar(in vec2 x,in float width,in float progress,out vec4 col){}\0";
const char *dvoronoi_source = "#version 130\nconst vec3 c=vec3 (1.,0.,-1.);void rand(in vec2 x,out float d);void dvoronoi(in vec2 x,out float d,out vec2 z){vec2 y=floor(x);float ret=1.;vec2 pf=c.yy,p;float df=10.;for(int i=-1;i<=1;i+=1)for(int j=-1;j<=1;j+=1){p=y+vec2 (float (i),float (j));float pa;rand(p,pa);p+=pa;d=length(x-p);if(d<df){df=d;pf=p;}}for(int i=-1;i<=1;i+=1)for(int j=-1;j<=1;j+=1){p=y+vec2 (float (i),float (j));float pa;rand(p,pa);p+=pa;vec2 o=p-pf;d=length(.5*o-dot(x-pf,o)/dot(o,o)*o);ret=min(ret,d);}d=ret;z=pf;}\0";
const char *normal_source = "const vec3 c=vec3 (1.0,0.0,-1.0);void scene(in vec3 x,out vec2 s);void normal(in vec3 x,out vec3 n,in float dx){vec2 s,na;scene(x,s);scene(x+dx*c.xyy,na);n.x=na.x;scene(x+dx*c.yxy,na);n.y=na.x;scene(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}\0";
const char *logo210_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);float a=1.0;float nbeats,iScale;void dbox3(in vec3 x,in vec3 b,out float d);void rot3(in vec3 p,out mat3 rot);void stroke(in float d0,in float s,out float d);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);void dbox210(in vec3 x,in float size,out vec2 sdf){x/=size;float d=1.;dbox3(x,.2*c.xxx,sdf.x);sdf.y=1.;dbox3(x-.1*c.xyy,vec3 (.02,.3,.12),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x-.05*c.xyy-.1*c.yyx,vec3 (.07,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x,vec3 (.02,.3,.1),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.05*c.xyy+.1*c.yyx,vec3 (.07,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.1*c.xyy-.1*c.yyx,vec3 (.02,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.04*c.yyx,vec3 (.3,.02,.08),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x-.1*c.yyx,vec3 (.3,.02,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));vec3 y=vec3 (x.x,abs(x.y),x.z);dbox3(y-.05*c.yxy,vec3 (.1,.03,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(y-.1*c.yxy-.06*c.xyy,vec3 (.08,.021,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));vec3 z=vec3 (abs(x.x),x.yz);dbox3(z-.119*c.xyy,vec3 (.021,.08,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));sdf.x*=size;}mat3 R;void scene(in vec3 x,out vec2 sdf){sdf=c.xy;float d,da;rot3(vec3 (-pi/2.,0.,pi/2.),R);x=R*x;vec2 sda=c.xy;dbox210(x+.1*c.xyy,.5,sdf);rot3(vec3 (pi/2.,0.,pi/2.),R);x=R*x;dbox210(x,5.,sda);add(sdf,sda,sdf);rot3(vec3 (pi/2.,-pi/2.,pi/2.),R);x=R*x;dbox210(x-2.*c.yxy,50.,sda);add(sdf,sda,sdf);stroke(sdf.x,.001,sdf.x);dbox3(x,100.*c.xxx,sda.x);sda.y=2.;add(sdf,sda*c.zx,sdf);}void normal(in vec3 x,out vec3 n,in float dx){vec2 s,na;scene(x,s);scene(x+dx*c.xyy,na);n.x=na.x;scene(x+dx*c.yxy,na);n.y=na.x;scene(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}void mainImage(out vec4 fragColor,in vec2 fragCoord){float a=iResolution.x/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);vec3 col=c.xxx;float d=0.;vec2 s;vec3 o,t,dir,x,n;mat3 Ra;rot3(mix(c.yyy,vec3 (-5.7884463,2.4242211,0.3463173),clamp((iTime-6.)/1.5,0.,1.)),Ra);o=Ra*mix(mix(mix(c.yyy-.1*c.yxy,c.yyx,clamp(iTime/2.,0.,1.)),10.*c.yyx,clamp((iTime-2.)/2.,0.,1.)),100.*c.yyx,clamp((iTime-4.)/2.,0.,1.));t=c.yyy;int N=650,i;dir=Ra*normalize(vec3 (uv,-1.));for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=s.x;}if(s.x<1.e-4){normal(x,n,5.e-4);vec3 l=normalize(x+.1*n);if(s.y==1.){col=vec3 (0.81,0.15,0.18);col=.3*col+.4*col*abs(dot(l,n))+.6*col*abs(pow(dot(reflect(-l,n),dir),3.));}else if(s.y==2.){col=.7*c.xxx;col=.5*col+.4*col*abs(dot(l,n))+.8*col*abs(pow(dot(reflect(-l,n),dir),3.));vec3 c1=c.yyy;o=x;dir=reflect(dir,n);d=1.e-1;N=150;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=s.x;}if(s.x<1.e-4){normal(x,n,5.e-4);vec3 l=normalize(x+.1*n);if(s.y==1.){c1=vec3 (0.81,0.15,0.18);c1=.3*c1+.4*c1*abs(dot(l,n))+.6*c1*abs(pow(dot(reflect(-l,n),dir),3.));}else if(s.y==2.){c1=.7*c.xxx;c1=.5*c1+.4*c1*abs(dot(l,n))+.8*c1*abs(pow(dot(reflect(-l,n),dir),3.));}c1=clamp(c1,0.,1.);col=mix(col,c1,.2);}col=clamp(col,0.,1.);}}col=mix(col,vec3 (0.20,0.01,0.14),smoothstep(0.,1.,iTime-10.));fragColor=vec4 (clamp(col,0.,1.),1.0);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
const char *graffiti_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);float a=1.0;void rand(in vec2 x,out float n){x+=400.;n=fract(sin(dot(sign(x)*abs(x),vec2 (12.9898,78.233)))*43758.5453);}void lfnoise(in vec2 t,out float n){vec2 i=floor(t);t=fract(t);t=smoothstep(c.yy,c.xx,t);vec2 v1,v2;rand(i,v1.x);rand(i+c.xy,v1.y);rand(i+c.yx,v2.x);rand(i+c.xx,v2.y);v1=c.zz+2.*mix(v1,v2,t.y);n=mix(v1.x,v1.y,t.x);}float dist2(vec2 p0,vec2 p1,vec2 p2,vec2 x,float t){t=clamp(t,0.,1.);return length(x-pow(1.-t,2.)*p0-2.*(1.-t)*t*p1-t*t*p2);}void dspline2(in vec2 x,in vec2 p0,in vec2 p1,in vec2 p2,out float ds){vec2 E=x-p0,F=p2-2.*p1+p0,G=p1-p0;vec3 ai=vec3 (3.*dot(G,F),2.*dot(G,G)-dot(E,F),-dot(E,G))/dot(F,F);float tau=ai.x/3.,p=ai.y-tau*ai.x,q=-tau*(tau*tau+p)+ai.z,dis=q*q/4.+p*p*p/27.;if(dis>0.){vec2 ki=-.5*q*c.xx+sqrt(dis)*c.xz,ui=sign(ki)*pow(abs(ki),c.xx/3.);ds=dist2(p0,p1,p2,x,ui.x+ui.y-tau);return ;}float fac=sqrt(-4./3.*p),arg=acos(-.5*q*sqrt(-27./p/p/p))/3.;vec3 t=c.zxz*fac*cos(arg*c.xxx+c*pi/3.)-tau;ds=min(dist2(p0,p1,p2,x,t.x),min(dist2(p0,p1,p2,x,t.y),dist2(p0,p1,p2,x,t.z)));}void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d){vec2 da=p2-p1;d=length(x-mix(p1,p2,clamp(dot(x-p1,da)/dot(da,da),0.,1.)));}void stroke(in float d0,in float s,out float d){d=abs(d0)-s;}void smoothmin(in float a,in float b,in float k,out float dst){float h=max(k-abs(a-b),0.0)/k;dst=min(a,b)-h*h*h*k*(1.0/6.0);}void d_h(in vec2 x,out float d){float da;dspline2(vec2 (abs(x.x)-.1,abs(x.y)),vec2 (.15,.25),vec2 (.05,.25),vec2 (.05,0.),d);dlinesegment(x,vec2 (-.075,0.),vec2 (.075,0.),da);smoothmin(d,da,.1,d);}void d_a(in vec2 x,out float d){float da;dspline2(vec2 (abs(x.x)-.1,x.y),vec2 (.15,-.25),vec2 (.05,-.25),vec2 (.05,0.),d);dspline2(vec2 (abs(x.x)-.1,x.y),vec2 (.05,0.),vec2 (.05,.25),vec2 (-.1,.25),da);d=min(d,da);dlinesegment(x,vec2 (-.075,0.),vec2 (.075,0.),da);smoothmin(d,da,.1,d);}void d_r(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(x.y-.1)-.15),vec2 (.0,-.05),vec2 (.25,.05),vec2 (.25,-.15),da);smoothmin(d,da,.1,d);dspline2(x,vec2 (0.,-.05),vec2 (0.,-.25),vec2 (.35,-.25),da);smoothmin(d,da,.1,d);}void d_d(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(x.y)-.1),vec2 (-.05,.15),vec2 (.25,.25),vec2 (.25,-.1),da);smoothmin(d,da,.1,d);}void d_c(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(x.y)-.1),vec2 (-.05,.15),vec2 (.25,.25),vec2 (.25,0.),da);smoothmin(d,da,.1,d);}void d_y(in vec2 x,out float d){float da;dspline2(vec2 (abs(x.x)-.2,x.y),vec2 (-.05,0.25),vec2 (-.05,.1),vec2 (-.2,.1),d);dlinesegment(x,vec2 (0.,-.25),vec2 (0.,.1),da);smoothmin(d,da,.1,d);}void d_b(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(abs(x.y)-.125)-.15),vec2 (.0,-.05),vec2 (.25,.05),vec2 (.25,-.15),da);smoothmin(d,da,.1,d);}void d_e(in vec2 x,out float d){float da;dspline2(vec2 (x.x,abs(x.y)),vec2 (-.15,.25),vec2 (-.05,.25),vec2 (-.05,0.),d);dspline2(vec2 (x.x,abs(x.y)-.1),vec2 (-.05,.05),vec2 (-.05,.15),vec2 (.25,.15),da);smoothmin(d,da,.1,d);dlinesegment(x,vec2 (-.05,0.),vec2 (.15,0.),da);smoothmin(d,da,.1,d);}void dhardcyber(in vec2 x,out float d){x*=3.;float da;d_h(x+1.8*c.xy,d);d_a(x+1.3*c.xy,da);d=min(d,da);d_r(x+.9*c.xy,da);d=min(d,da);d_d(x+.4*c.xy,da);d=min(d,da);d_c(x-.1*c.xy,da);d=min(d,da);d_y(x-.6*c.xy,da);d=min(d,da);d_b(x-.925*c.xy,da);d=min(d,da);d_e(x-1.4*c.xy,da);d=min(d,da);d_r(x-1.8*c.xy,da);d=min(d,da);stroke(d,.07,d);d/=3.;}float sm(float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void palette(in float scale,out vec3 col){const int N=5;const vec3 colors[N]=vec3 [N](vec3 (0.27,0.13,0.26),vec3 (0.43,0.21,0.33),vec3 (0.69,0.36,0.42),vec3 (0.87,0.52,0.45),vec3 (0.99,0.68,0.53));float index=floor(scale*float (N)),remainder=scale*float (N)-index;col=mix(colors[int (index)],colors[int (index)+1],remainder);}void dvoronoi(in vec2 x,out float d,out vec2 z){vec2 y=floor(x);float ret=1.;vec2 pf=c.yy,p;float df=10.;for(int i=-1;i<=1;i+=1)for(int j=-1;j<=1;j+=1){p=y+vec2 (float (i),float (j));float pa;rand(p,pa);p+=pa;d=length(x-p);if(d<df){df=d;pf=p;}}for(int i=-1;i<=1;i+=1)for(int j=-1;j<=1;j+=1){p=y+vec2 (float (i),float (j));float pa;rand(p,pa);p+=pa;vec2 o=p-pf;d=length(.5*o-dot(x-pf,o)/dot(o,o)*o);ret=min(ret,d);}d=ret;z=pf;}void zextrude(in float z,in float d2d,in float h,out float d){vec2 w=vec2 (-d2d,abs(z)-0.5*h);d=length(max(w,0.0));}void scene(in vec3 x,out vec2 sdf){dhardcyber(x.xy,sdf.x);zextrude(x.z,-sdf.x,.1,sdf.x);smoothmin(sdf.x,x.z,.1,sdf.x);sdf.y=1.;stroke(sdf.x,.01,sdf.x);}void normal(in vec3 x,out vec3 n,in float dx){vec2 s,na;scene(x,s);scene(x+dx*c.xyy,na);n.x=na.x;scene(x+dx*c.yxy,na);n.y=na.x;scene(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}void colorize(in vec2 uv,inout vec3 col){vec3 c1;float d=floor(8.*(.5+.4*tanh(6.*uv.y+uv.x)))/8.;vec2 ind;float v;dvoronoi(16.*uv,v,ind);float r;rand(ind,r);d=(uv.y+.25)/.5-.2*r;palette(clamp(d,0.,1.),c1);col=(.5+.5*r)*c.xxx;dhardcyber(uv,d);col=mix(col,.7*c.xxx,sm(d-.04));col=mix(col,c1,sm(d));col=mix(col,c.yyy,sm(abs(d-.01)-.01));col=mix(col,vec3 (0.99,0.68,0.53),sm(abs(d-.005)-.005));col=mix(col,1.2*vec3 (0.99,0.68,0.53),sm(abs(d-.005)-.001));col=mix(col,c.yyy,sm(abs(v)-.02));}void main(){a=iResolution.x/iResolution.y;vec2 uv=(gl_FragCoord.xy-.5*iResolution)/iResolution.y,s;vec3 col=c.xxx,o=c.yyx+.4*c.yzy,r=c.xyy,t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x;int N=650,i;t=uv.x*r+uv.y*u;dir=normalize(t-o);vec3 c1;float d=-(o.z-.1)/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(x.z<0.){i=N;break;}d+=s.x;}if(i<N){vec3 l=x+c.yyx;normal(x,n,2.e-6);colorize(x.xy,col);col=.1*col+.1*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);}col=2.*col*col;gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *starsky_source = "#version 130\nuniform float iTime;uniform vec2 iResolution;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);float a=1.0;void rand(in vec2 x,out float n){x+=400.;n=fract(sin(dot(sign(x)*abs(x),vec2 (12.9898,78.233)))*43758.5453);}void lfnoise(in vec2 t,out float n){vec2 i=floor(t);t=fract(t);t=smoothstep(c.yy,c.xx,t);vec2 v1,v2;rand(i,v1.x);rand(i+c.xy,v1.y);rand(i+c.yx,v2.x);rand(i+c.xx,v2.y);v1=c.zz+2.*mix(v1,v2,t.y);n=mix(v1.x,v1.y,t.x);}void mfnoise(in vec2 x,in float d,in float b,in float e,out float n){n=0.;float a=1.,nf=0.,buf;for(float f=d;f<b;f*=2.){lfnoise(f*x,buf);n+=a*buf;a*=e;nf+=1.;}n*=(1.-e)/(1.-pow(e,nf));}void dvoronoi(in vec2 x,out float d,out vec2 z){vec2 y=floor(x);float ret=1.;vec2 pf=c.yy,p;float df=10.;for(int i=-1;i<=1;i+=1)for(int j=-1;j<=1;j+=1){p=y+vec2 (float (i),float (j));float pa;rand(p,pa);p+=pa;d=length(x-p);if(d<df){df=d;pf=p;}}for(int i=-1;i<=1;i+=1)for(int j=-1;j<=1;j+=1){p=y+vec2 (float (i),float (j));float pa;rand(p,pa);p+=pa;vec2 o=p-pf;d=length(.5*o-dot(x-pf,o)/dot(o,o)*o);ret=min(ret,d);}d=ret;z=pf;}float dspiral(vec2 x,float a,float d){float p=atan(x.y,x.x),n=floor((abs(length(x)-a*p)+d*p)/(2.*pi*a));p+=(n*2.+1.)*pi;return -abs(length(x)-a*p)+d*p;}float sm(float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void stroke(in float d0,in float s,out float d){d=abs(d0)-s;}void colorize(in vec2 x,inout vec3 col){float v,n=64.,r;vec2 ind;dvoronoi(n*x,v,ind);rand(ind,r);vec2 y=x-ind/n;vec3 c1;rand(ind+1337.,c1.x);rand(ind+2337.,c1.y);rand(ind+3337.,c1.z);c1*=vec3 (1.,.7,.3);c1=.5+.5*c1;c1*=vec3 (.4,.6,1.);float d=length(y)-.002*r;if(r>.75)col=mix(col,c1,sm(d));if(r>.5){col=mix(col,mix(col,2.*c1,.8),sm(d-.004*r*r));col=mix(col,mix(col,3.*c1,.4),sm(d-.01*r*r));}dvoronoi(2.*n*x,v,ind);y=x-ind/n/2.;rand(ind,r);d=length(y)-.002*r;col=mix(col,c.xxx,sm(d));lfnoise(x.xy-v*v*v,d);col=mix(col,c.yyy,.5+.5*d);col=.6*col+.3*step(.8,col);col*=2.;v=dspiral(x,.1,.01);col=mix(col,c.yyy,1.-sm(v*6.e-3));col=mix(col,2.5*col,sm(v*2.e-3));}void dbox(in vec2 x,in vec2 b,out float d){vec2 da=abs(x)-b;d=length(max(da,c.yy))+min(max(da.x,da.y),0.0);}void street(in vec2 x,out vec3 col){float dx;lfnoise(x.y*c.xx,dx);x.x+=.1*dx;col=.4*c.xxx;float da=mod(x.y,.1)-.05;dbox(vec2 (x.x,da),vec2 (.005,.025),da);col=mix(col,c.xxx,sm(da));col=mix(col,c.xxx,sm(abs(abs(x.x)-.1)-.01));float n;mfnoise(x.xy,mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),200.,.35,n);col=mix(col,.5*col,.5+.5*n);col=mix(col,.6*c.xxx,abs(n)-.1);vec2 ind;float v;dvoronoi(256.*x,v,ind);ind=x-ind/256.;col=mix(col,.0*c.xxx,sm(length(ind)-.0001));}void dbox3(in vec3 x,in vec3 b,out float d){vec3 da=abs(x)-b;d=length(max(da,0.0))+min(max(da.x,max(da.y,da.z)),0.0);}void add(in vec2 sda,in vec2 sdb,out vec2 sdf){sdf=(sda.x<sdb.x)?sda:sdb;}void scene(in vec3 x,out vec2 sdf){float dx;lfnoise(x.y*c.xx,dx);x.x+=.1*dx;sdf=c.xx;float n;mfnoise(x.xy,mix(8.,1.,smoothstep(.4,1.6,abs(x.x))),2000.,mix(.35,.45,smoothstep(.4,1.6,abs(x.x))),n);float n0=n;n=.5+.5*n;n*=smoothstep(.1,.3,abs(x.x))+smoothstep(.4,1.2,abs(x.x));sdf.x=x.z-.1*n;sdf.y=1.;float d;dbox3(x-c.yyx*.005*step(.1,abs(n0)-.01),vec3 (.1,1.e3,.001+.01*n0),d);add(sdf,vec2 (d,2.),sdf);}void normal(in vec3 x,out vec3 n,in float dx){vec2 s,na;scene(x,s);scene(x+dx*c.xyy,na);n.x=na.x;scene(x+dx*c.yxy,na);n.y=na.x;scene(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}void palette(in float scale,out vec3 col){const int N=5;const vec3 colors[N]=vec3 [N](vec3 (0.27,0.13,0.26),vec3 (0.43,0.21,0.33),vec3 (0.69,0.36,0.42),vec3 (0.87,0.52,0.45),vec3 (0.99,0.68,0.53));float index=floor(scale*float (N)),remainder=scale*float (N)-index;col=mix(colors[int (index)],colors[int (index)+1],remainder);}void main(){a=iResolution.x/iResolution.y;vec2 uv=(gl_FragCoord.xy-.5*iResolution)/iResolution.y,s;vec3 col=c.yyy,o=.3*c.yyx+c.yzy,r=c.xyy,t=c.yyy,u=cross(normalize(t-o),-r),dir,n,x;int N=250,i;t=uv.x*r+uv.y*u;dir=normalize(t-o);vec3 c1;float d=-(o.z-.2)/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-5)break;if(x.z<0.){i=N;break;}d+=s.x;}if(i<N){vec3 l=c.yyx;normal(x,n,2.e-6);if(s.y==1.){palette(x.z/.22,col);col=.1*col+.1*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);}else if(s.y==2.){street(x.xy,col);col=.1*col+.1*col*dot(l,n)+.6*col*pow(abs(dot(reflect(-l,n),dir)),2.);}else {colorize(x.xy,col);col=.1*col+.1*col*dot(l,n)+.8*col*pow(abs(dot(reflect(-l,n),dir)),2.);}if(x.z>.05)col=mix(col,3.*col,smoothstep(.95,.951,n.z));}col=12.*col*col;col=mix(col,c.yyy,tanh(2.e-1*d));vec3 c2;colorize(4.*uv,c2);col=mix(col,2.*c2,smoothstep(.3,.5,uv.y));gl_FragColor=vec4 (clamp(col,0.,1.),1.);}\0";
const char *text_source = "#version 130\nuniform float iFontWidth,iTime;uniform vec2 iResolution;uniform sampler2D iChannel0,iFont;uniform float iFSAA;out vec4 gl_FragColor;const vec3 c=vec3 (1.,0.,-1.);const float pi=acos(-1.);float a;void rand(in vec2 x,out float num);void lfnoise(in vec2 t,out float num);void rshort(in float off,out float val);void rfloat(in float off,out float val);void dbox(in vec2 x,in vec2 b,out float dst);void dcircle(in vec2 x,out float d);void dlinesegment(in vec2 x,in vec2 p1,in vec2 p2,out float d);void drhomboid(in vec2 x,in vec2 b,in float tilt,out float dst);void dcirclesegment(in vec2 x,in float r,in float p0,in float p1,out float d);void stroke(in float d0,in float s,out float d);void dglyph(in vec2 x,in float ordinal,in float size,out float dst);void dstring(in vec2 x,in float ordinal,in float size,out float dst);void dfloat(in vec2 x,in float num,in float size,out float dst);void smoothmin(in float a,in float b,in float k,out float dst);void dint(in vec2 x,in float num,in float size,in float ndigits,out float dst);void dtime(in vec2 x,in float num,in float size,out float dst);void window(in vec2 x,in vec2 size,in vec3 bg,in float title_index,out vec4 col);void progressbar(in vec2 x,in float width,in float progress,out vec4 col);float sm(float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}void dvoronoi(in vec2 x,out float d,out vec2 z);void colorize(in vec2 x,out vec3 col){vec3 c1;vec2 ind,xv,xi;float d,vs=16.,n,size=.1,xix=mod(x.x,size)-.5*size,xixj=(x.x-xix),ri,rim1,rip1,lines=8.,da,op,s;s=smoothstep(0.,.5,.5-abs(x.y));col=mix(1.e-4*c.xxx,vec3 (0.04,0.18,0.24),s);dvoronoi(vs*x,d,ind);xv=ind/vs-x;lfnoise(vec2 (3.,33.)*ind/vs-3.*iTime*c.xy,n);n=.5+.5*n;d=length(xv)-mix(.0,.35,n)/vs;col=mix(col,n*.5*vec3 (1.00,0.40,0.39),sm(d));d=abs(d-.005)-.002;col=mix(col,(1.-n)*vec3 (0.49,0.71,0.78),sm(d));for(float i=1.;i<9.;i+=1.){rand((9.-i)*c.xx,op);op=.5+.5*round(16.*op)/16.;x+=-.1+.2*op;xix=mod(x.x,size)-.5*size;xixj=(x.x-xix);lfnoise(2.e0*xixj*c.xx+14.*i,ri);lfnoise(2.e0*(xixj+size)*c.xx+14.*i,rip1);lfnoise(2.e0*(xixj-size)*c.xx+14.*i,rim1);float h=.2;ri=h*round(lines*ri)/lines;rip1=h*round(lines*rip1)/lines;rim1=h*round(lines*rim1)/lines;{dlinesegment(vec2 (xix,x.y),vec2 (-.5*size,mix(ri,rim1,.5)),vec2 (-.25*size,ri),d);dlinesegment(vec2 (xix,x.y),vec2 (-.25*size,ri),vec2 (.25*size,ri),da);d=min(d,da);dlinesegment(vec2 (xix,x.y),vec2 (.25*size,ri),vec2 (.5*size,mix(ri,rip1,.5)),da);d=min(d,da);stroke(d,.002+.002*op,d);col=mix(col,op*(1.-n)*vec3 (1.00,0.40,0.39),sm(d));lfnoise(8.*xixj*c.xx-3.*iTime*c.xy+14.*i,n);n=.5+.5*n;d=length(vec2 (xix,x.y-ri))-mix(.0,.35,n)/vs;c1=mix(vec3 (1.00,0.40,0.39),vec3 (0.85,0.87,0.89),n);col=mix(col,op*(1.-n)*c1,sm(d));stroke(d-.009,(1.-n)*.005,d);c1*=2.4;col=mix(col,op*(1.-n)*c1,sm(d));}x-=-.1+.2*op;}lfnoise(3.*x.xy-vec2 (1.,.1)*iTime,n);stroke(n,.3,n);col=mix(col,1.e-4*c.xxx,n);col=mix(col,.1*col,1.-s);col=mix(col,mix(col,vec3 (1.00,0.40,0.39),mix(.4,.8,.5+.5*x.y/.1)),sm(abs(x.y)-.1));col=mix(col,c.xxx,sm(abs(abs(x.y)-.11)-.001));col=mix(col,col*col,clamp(-x.y/.1,0.,1.));col*=col;}void mainImage(out vec4 fragColor,in vec2 fragCoord){a=iResolution.x/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);float d;vec4 old=c.yyyy,new=c.yyyy;float bound=sqrt(iFSAA)-1.;for(float i=-.5*bound;i<=.5*bound;i+=1.)for(float j=-.5*bound;j<=.5*bound;j+=1.){old.gba+=texture(iChannel0,(fragCoord+vec2 (i,j)*3./max(bound,1.))/iResolution.xy).xyz;}old.gba/=iFSAA;new=old;if(uv.y>.4){float da;dstring((uv-.45*vec2 (-.55*a,1.+4.*.008)),9.,.004,d);dstring((uv-.45*vec2 (-.55*a,1.+2.*.008)),10.,.004,da);d=min(d,da);dstring((uv-.45*vec2 (-.55*a,1.)),11.,.004,da);d=min(d,da);dstring((uv-.45*vec2 (-.55*a,1.-2.*.008)),12.,.004,da);d=min(d,da);dstring((uv-.45*vec2 (-.55*a,1.-4.*.008)),13.,.004,da);d=min(d,da);new.gba=mix(new.gba,mix(new.gba,c.xxx,.5),sm(d));dstring((uv-.45*vec2 (-.85*a,1.)),3.,.02,d);stroke(d-.002,.001,d);new.gba=mix(new.gba,vec3 (1.00,0.40,0.39),sm(d));dtime((uv-.45*vec2 (.975*a,1.05)),iTime+11.,.01,d);new.gba=mix(new.gba,c.xxx,sm(d));dint(uv-.45*vec2 (.975*a,1.0),floor(1.e3*fract(iTime)),.01,4.,d);stroke(d-.001,.0005,d);new.gba=mix(new.gba,c.xxx,sm(d));}if(iTime<0.){new.gba=old.gba;float sc=smoothstep(0.,1.,clamp(iTime+3.,0.,1.))*(1.-smoothstep(0.,1.,clamp(iTime+1.,0.,1.)));dstring((uv-vec2 (-.085,-.3)),3.,.02,d);float da;dstring((uv-vec2 (-.08,-.35)),26.,.02,da);d=min(d,da);new.gba=mix(new.gba,mix(new.gba,c.yyy,sc),sm(d));}else if(iTime<6.){vec2 dx=(.25*a+.3*c.xy)*c.xy;if(iTime<3.){float ind=mix(100000.,2.,clamp(iTime/3.,0.,1)),da;dint(uv+dx*c.xy,ind,.02,6.,d);dstring(uv+dx-2.*9.*.02*c.xy,4.,.02,da);d=min(d,da);}else if(iTime<4.){dint(uv+dx,2.,.02,6.,d);float da;dstring(uv+dx-2.*9.*.02*c.xy,4.,.02,da);d=min(d,da);}else if(iTime<5.){dint(uv+dx+.04*c.yx,1.,.02,6.,d);float da;dint(uv+dx,2.,.02,6.,da);d=min(d,da);dstring(uv+dx-2.*9.*.02*c.xy+.04*c.yx,4.,.02,da);d=min(d,da);}else if(iTime<6.){dint(uv+dx+.08*c.yx,0.,.02,6.,d);float da;dint(uv+dx+.04*c.yx,1.,.02,6.,da);d=min(d,da);dint(uv+dx,2.,.02,6.,da);d=min(d,da);dstring(uv+dx-2.*9.*.02*c.xy+.08*c.yx,4.,.02,da);d=min(d,da);}new.gba=mix(new.gba,mix(new.gba,vec3 (1.00,0.87,0.57),.7),sm(d));stroke(d-.002,.001,d);new.gba=mix(new.gba,c.xxx,sm(d));}else if(iTime<12.&&iTime>7.){float da,db;dbox(vec2 (uv.x+.75,uv.y-.35),vec2 (.013,.035),da);stroke(da,.002,da);dglyph(vec2 (uv.x+.75,uv.y-.35-.02).yx*c.zx,101.,.01,db);da=min(da,db);dglyph(vec2 (uv.x+.75,uv.y-.35),118.,.01,db);da=min(da,db);dglyph(vec2 (uv.x+.75,uv.y-.35+.02).yx*c.zx,107.,.01,db);da=min(da,db);vec2 b=vec2 (uv.x+.75,uv.y-.35+.02)-.01*c.xx-.02*c.xy,b1=mod(b,.02)-.01,b1i=floor((b-b1)/.02);if(abs(b1i.y)<=1.&&b1i.x>=0.&&b1i.x<=10.){lfnoise(b1i-12.*iTime,db);db=97.+mod(floor(26.*(.5+.5*db)),26.);dglyph(b1,db,.008,db);da=min(da,db);}dlinesegment(vec2 (uv.x+.75,uv.y-.35+.06),-.015*c.xy,.25*c.xy,db);stroke(db,.001,db);da=min(da,db);dstring(vec2 (uv.x+.75,uv.y+.35),5.,.015,db);da=min(da,db);dstring(vec2 (uv.x-.2,uv.y+.35),6.,.015,db);float dc;dbox(vec2 (uv.x-.2-.12,uv.y+.35),vec2 (.165,.015),dc);db=max(dc,-db);da=min(da,db);dstring(vec2 (uv.x+.75,uv.y+.4),7.,.015,db);da=min(da,db);dstring(vec2 (uv.x-.2,uv.y+.4),8.,.015,db);dbox(vec2 (uv.x-.2-.12,uv.y+.4),vec2 (.165,.015),dc);db=max(dc,-db);da=min(da,db);new.gba=mix(new.gba,vec3 (0.75,0.24,0.30),sm(da));}else if(iTime<28.){float da=length(uv)-.45,db;dstring((uv+.3*c.xy),2.,.0415,db);db-=.001;da=max(da,-db);da=mix(1.,da,smoothstep(0.,.5,clamp(iTime-18.5,0.,1.))*(1.-smoothstep(0.,.5,clamp(iTime-22.,0.,1.))));new.gba=mix(new.gba,vec3 (1.00,0.40,0.39),sm(da));da=length(uv-.3*c.xx)-.2,db;dstring(2.*(uv+.075*c.xy-.3*c.xx),3.,.0415,db);db-=.001;da=mix(1.,da,smoothstep(0.,.5,clamp(iTime-19.5,0.,1.))*(1.-smoothstep(0.,.5,clamp(iTime-22.,0.,1.))));db=mix(1.,db,smoothstep(0.,.5,clamp(iTime-19.5,0.,1.))*(1.-smoothstep(0.,.5,clamp(iTime-22.,0.,1.))));new.gba=mix(new.gba,vec3 (1.00,0.40,0.39)*vec3 (1.00,0.40,0.39),sm(da));new.gba=mix(new.gba,c.yyy,sm(db));dstring((uv-vec2 (-.75,-.35)).yx*c.xz,18.,.045,db);dstring((uv-vec2 (-.65,-.35)).yx*c.xz,19.,.045,da);db=min(db,da);db=mix(1.,db,smoothstep(0.,.5,clamp(iTime-24.5,0.,1.))*(1.-smoothstep(0.,.5,clamp(iTime-28.,0.,1.))));new.gba=mix(new.gba,mix(new.gba,c.xxx,.8),sm(db));stroke(db-.005,.0005,db);new.gba=mix(new.gba,mix(new.gba,vec3 (1.00,0.40,0.39),.8),sm(db));da=length((uv-vec2 (-.6,-.325)).yx*c.xz)-.1;dstring((uv-vec2 (-.6,-.35)).yx*c.xz,20.,.015,db);da=max(da,-db);da=mix(1.,da,smoothstep(0.,.5,clamp(iTime-25.5,0.,1.))*(1.-smoothstep(0.,.5,clamp(iTime-28.,0.,1.))));new.gba=mix(new.gba,mix(new.gba,c.xxx,.6),sm(da));}else if(iTime<44.){float da,db;dstring((uv-vec2 (-.3,.3)),21.,.1,da);db=abs(mod(uv.x+uv.y,.3)-.15)-.075;vec3 c1=mix(mix(new.gba,.3*c.xxx,.5),c.xxx,sm(db));db=smoothstep(33.,34.,iTime);da=mix(1.,da,db);new.gba=mix(new.gba,c1,sm(da));stroke(da-.02,.001,da);new.gba=mix(new.gba,c.xxx,sm(da));dstring(uv-vec2 (.35,.34),22.,.05,da);dbox(uv-vec2 (.35,.34),vec2 (.15,.06),db);db=max(db,-da);float mx=smoothstep(34.,35.,iTime);db=mix(1.,db,mx);new.gba=mix(new.gba,c.xxx,sm(db));dstring(uv-vec2 (.25,.24),23.,.0277,da);mx=smoothstep(35.,36.,iTime);da=mix(1.,da,mx);new.gba=mix(new.gba,.8*c.xxy,sm(da));dstring(uv-vec2 (.25,.15),22.,.05,da);mx=smoothstep(36.,37.,iTime);da=mix(1.,da,mx);new.gba=mix(new.gba,.8*c.xxy,sm(da));dstring((uv-vec2 (.45,.05)).yx*c.zx,24.,.05,da);dbox((uv-vec2 (.45,-.1)),vec2 (.05,.3),db);db=max(db,-da);mx=smoothstep(37.,38.,iTime);db=mix(1.,db,mx);new.gba=mix(new.gba,c.xxx,sm(db));dstring((uv-vec2 (.6,.1)).yx*c.zx,25.,.1,da);db=smoothstep(38.,39.,iTime);da=mix(1.,da,db);new.gba=mix(new.gba,c1,sm(da));stroke(da-.02,.001,da);new.gba=mix(new.gba,c.xxx,sm(da));}else if(iTime<60.){float da,db;db=abs(mod(uv.x+uv.y,.3)-.15)-.075;vec3 c1=mix(mix(new.gba,vec3 (0.93,0.36,0.44),.5),c.xxx,sm(db));dstring((uv-vec2 (-.3,.3)),38.,.02,da);db=smoothstep(45.,46.,iTime)-smoothstep(50.,51.,iTime);da=mix(1.,da,db);stroke(da-.005,.0025,db);new.gba=mix(new.gba,c.yyy,sm(db));new.gba=mix(new.gba,c1,sm(da-.0025));db=da+.0025;new.gba=mix(new.gba,2.*c1,sm(db));dstring((uv-vec2 (-.3,.25)),39.,.02,da);db=smoothstep(46.,47.,iTime)-smoothstep(51.,52.,iTime);da=mix(1.,da,db);stroke(da-.005,.0025,db);new.gba=mix(new.gba,c.yyy,sm(db));new.gba=mix(new.gba,c1,sm(da-.0025));db=da+.0025;new.gba=mix(new.gba,2.*c1,sm(db));dstring((uv-vec2 (-.3,.2)),40.,.02,da);db=smoothstep(47.,48.,iTime)-smoothstep(52.,53.,iTime);da=mix(1.,da,db);stroke(da-.005,.0025,db);new.gba=mix(new.gba,c.yyy,sm(db));new.gba=mix(new.gba,c1,sm(da-.0025));db=da+.0025;new.gba=mix(new.gba,2.*c1,sm(db));dstring((uv-vec2 (-.3,.15)),41.,.02,da);db=smoothstep(48.,49.,iTime)-smoothstep(53.,54.,iTime);da=mix(1.,da,db);stroke(da-.005,.0025,db);new.gba=mix(new.gba,c.yyy,sm(db));new.gba=mix(new.gba,c1,sm(da-.0025));db=da+.0025;new.gba=mix(new.gba,2.*c1,sm(db));new.gba=clamp(new.gba,0.,1.);}else if(iTime<130.){float da,db;dbox(uv-vec2 (.05,.3),vec2 (1.6,.055),da);da=mix(1.,da,smoothstep(125.,126.,iTime));new.gba=mix(new.gba,mix(new.gba,c.xxx,.5),sm(da));dstring((uv-vec2 (-.4,.3)),28.,.05,da);lfnoise(55.*uv,db);stroke(db,0.535,db);vec3 c1=mix(mix(new.gba,c.yyy,.3),c.yyy,sm(db/50.));db=smoothstep(125.,126.,iTime);da=mix(1.,da,db);new.gba=mix(new.gba,c1,sm(da));stroke(da-.01,.001,da);new.gba=mix(new.gba,c.yyy,sm(da));}else {float da;dstring(uv-vec2 (-.55,0.),27.,.025,da);da=mix(1.,da,smoothstep(172.,172.5,iTime));new.gba=mix(new.gba,c.yyy,smoothstep(172.,172.5,iTime));new.gba=mix(new.gba,vec3 (.9,.2,.03),sm(da));stroke(da-.005,.001,da);new.gba=mix(new.gba,c.xxx,sm(da));}float dc;dbox(uv,.5*vec2 (a,1.),dc);stroke(dc,.005,dc);new.gba=mix(new.gba,c.yyy,sm(dc));fragColor=vec4 (new.gba,1.);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
const char *post_source = "#version 130\nuniform float iFSAA;uniform vec2 iResolution;uniform sampler2D iChannel0;uniform float iTime;out vec4 gl_FragColor;const float pi=acos(-1.);const vec3 c=vec3 (1.,0.,-1.);float a=1.0;float lscale,rscale;float size;float nbeats;float iScale;void rand(in vec2 x,out float n);void lfnoise(in vec2 t,out float n);void stroke(in float d0,in float s,out float d);void dvoronoi(in vec2 x,out float d,out vec2 z);float sm(float d){return smoothstep(1.5/iResolution.y,-1.5/iResolution.y,d);}float dot2(in vec3 v){return dot(v,v);}void dtriangle3(in vec3 p,in vec3 v1,in vec3 v2,in vec3 v3,out float dst){vec3 v21=v2-v1;vec3 p1=p-v1;vec3 v32=v3-v2;vec3 p2=p-v2;vec3 v13=v1-v3;vec3 p3=p-v3;vec3 nor=cross(v21,v13);dst=sqrt((sign(dot(cross(v21,nor),p1))+sign(dot(cross(v32,nor),p2))+sign(dot(cross(v13,nor),p3))<2.0)?min(min(dot2(v21*clamp(dot(v21,p1)/dot2(v21),0.0,1.0)-p1),dot2(v32*clamp(dot(v32,p2)/dot2(v32),0.0,1.0)-p2)),dot2(v13*clamp(dot(v13,p3)/dot2(v13),0.0,1.0)-p3)):dot(nor,p1)*dot(nor,p1)/dot2(nor));}void rot3(in vec3 p,out mat3 rot);void dbox3(in vec3 x,in vec3 b,out float d);void add(in vec2 sda,in vec2 sdb,out vec2 sdf);mat3 R;void scene(in vec3 x,out vec2 sdf){float d;dbox3(x,.2*c.xxx,sdf.x);sdf.y=1.;dbox3(x-.1*c.xyy,vec3 (.02,.3,.12),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x-.05*c.xyy-.1*c.yyx,vec3 (.07,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x,vec3 (.02,.3,.1),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.05*c.xyy+.1*c.yyx,vec3 (.07,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.1*c.xyy-.1*c.yyx,vec3 (.02,.3,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x+.04*c.yyx,vec3 (.3,.02,.08),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(x-.1*c.yyx,vec3 (.3,.02,.02),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));vec3 y=vec3 (x.x,abs(x.y),x.z);dbox3(y-.05*c.yxy,vec3 (.1,.03,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));dbox3(y-.1*c.yxy-.06*c.xyy,vec3 (.08,.021,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));vec3 z=vec3 (abs(x.x),x.yz);dbox3(z-.119*c.xyy,vec3 (.021,.08,.3),d);sdf.x=max(-d,sdf.x);sdf.y=mix(sdf.y,2.,step(d,sdf.x));}void scene2(in vec3 x,out vec2 sdf){float v=0.;vec2 vi=c.yy;dvoronoi(x.xy/size,v,vi);vec3 y=vec3 (x.xy-vi*size,x.z);vec2 yi=vi*size;float n=0.;lfnoise(4.*(yi-.5*iTime),n);lfnoise(12.*vec2 (n,1.)*yi-(.8+.2*n)*c.xy,n);n*=iScale;sdf=vec2 (length(y-.05*n*c.yyx)-mix(.05,1.,length(texture(iChannel0,yi/vec2 (a,1.)).rgb)/sqrt(3.))*size,1.);}void normal2(in vec3 x,out vec3 n,in float dx){vec2 s,na;scene2(x,s);scene2(x+dx*c.xyy,na);n.x=na.x;scene2(x+dx*c.yxy,na);n.y=na.x;scene2(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}void scene3(in vec3 x,out vec2 sdf){vec3 y=vec3 (mod(x.xy,2.*size)-size,x.z);vec2 yi=x.xy-y.xy;float ss=mix(.0,.05,size/.01);vec2 p0=.8*size*c.xx,p1=.8*size*c.zx,p2=.8*size*c.xz;vec2 ind;float y0,y1,y2;lfnoise(4.e1*(yi+p0-.5e-4*iTime),y0);lfnoise(12.e1*vec2 (y0,1.)*(yi+p0)-1.e-4*(.8+.2*y0)*iTime*c.xy,y0);lfnoise(4.e1*(yi+p1-.5e-4*iTime),y1);lfnoise(12.e1*vec2 (y1,1.)*(yi+p1)-1.e-4*(.8+.2*y1)*iTime*c.xy,y1);lfnoise(4.e1*(yi+p2-.5e-4*iTime),y2);lfnoise(12.e1*vec2 (y2,1.)*(yi+p2)-1.e-4*(.8+.2*y2)*iTime*c.xy,y2);y0*=ss;y1*=ss;y2*=ss;dtriangle3(y,vec3 (p0,y0),vec3 (p1,y1),vec3 (p2,y2),sdf.x);float d;vec2 p3=.8*size*c.zz,p4=.8*size*c.xz,p5=.8*size*c.zx;float y3,y4,y5;lfnoise(4.e1*(yi+p3-.5e-4*iTime),y3);lfnoise(12.e1*vec2 (y3,1.)*(yi+p3)-1.e-4*(.8+.2*y3)*iTime*c.xy,y3);lfnoise(4.e1*(yi+p4-.5e-4*iTime),y4);lfnoise(12.e1*vec2 (y4,1.)*(yi+p4)-1.e-4*(.8+.2*y4)*iTime*c.xy,y4);lfnoise(4.e1*(yi+p5-.5e-4*iTime),y5);lfnoise(12.e1*vec2 (y5,1.)*(yi+p5)-1.e-4*(.8+.2*y5)*iTime*c.xy,y5);y3*=ss;y4*=ss;y5*=ss;dtriangle3(y,vec3 (p3,y3),vec3 (p4,y4),vec3 (p5,y5),d);sdf.x=min(sdf.x,d);stroke(sdf.x,.1*size,sdf.x);sdf.y=1.;}void normal3(in vec3 x,out vec3 n,in float dx){vec2 s,na;scene3(x,s);scene3(x+dx*c.xyy,na);n.x=na.x;scene3(x+dx*c.yxy,na);n.y=na.x;scene3(x+dx*c.yyx,na);n.z=na.x;n=normalize(n-s.x);}void normal(in vec3 x,out vec3 n,in float dx);void mainImage(out vec4 fragColor,in vec2 fragCoord_){vec2 fragCoord=fragCoord_;if(iTime<159.5456&&iTime>155.9092){vec2 n;lfnoise(22.*fragCoord/iResolution-3.*iTime,n.x);lfnoise(22.*fragCoord/iResolution-3.*iTime-1337.,n.y);fragCoord+=22.*n;}else if(iTime<165.&&iTime>163.182){vec2 n;lfnoise(22.*fragCoord/iResolution-3.*iTime,n.x);lfnoise(22.*fragCoord/iResolution-3.*iTime-1337.,n.y);fragCoord+=22.*n;}float a=iResolution.x/iResolution.y;vec2 uv=fragCoord/iResolution.yy-0.5*vec2 (a,1.0);nbeats=mod(iTime,60./29.);iScale=nbeats-30./29.;iScale=smoothstep(-5./29.,0.,iScale)*(1.-smoothstep(0.,15./29.,iScale));vec3 col=texture(iChannel0,fragCoord/iResolution).rgb;float delta=0.;rot3(vec3 (-2.*pi/8.,2.*pi/8.,2.*pi/4.)-iTime*vec3 (1.1,1.3,1.5),R);float d;vec2 s;vec3 o,r,u,t,ssize,dir,x,n;vec2 uv2=10.*(uv-vec2 (-.45*a,.45));o=R*c.yyx;r=c.xyy;u=c.yxy;t=c.yyy;int N=250,i;t=uv2.x*r+uv2.y*u;t=R*t;dir=normalize(t-o);ssize=.2*c.xxx;vec3 tlo=min((ssize-o)/dir,(-ssize-o)/dir);vec2 abxlo=abs(o.yz+tlo.x*dir.yz),abylo=abs(o.xz+tlo.y*dir.xz),abzlo=abs(o.xy+tlo.z*dir.xy);vec4 dn=100.*c.xyyy;dn=mix(dn,vec4 (tlo.x,c.xyy),float (all(lessThan(abxlo,ssize.yz)))*step(tlo.x,dn.x));dn=mix(dn,vec4 (tlo.y,c.yxy),float (all(lessThan(abylo,ssize.xz)))*step(tlo.y,dn.x));dn=mix(dn,vec4 (tlo.z,c.yyx),float (all(lessThan(abzlo,ssize.xy)))*step(tlo.z,dn.x));uv=(fragCoord)/iResolution.xy*vec2 (a,1.);d=dn.r;float nan;lfnoise(iTime*c.xx,nan);nan+=.5;if(nan>0.)d=3.;if(d<=2.){x=o+d*dir;scene(x,s);if(s.x>1.e-4){for(i=0;i<N;++i){x=o+d*dir;scene(x,s);if(s.x<1.e-4)break;d+=s.x;}}if(i<N){normal(x,n,5.e-4);if(s.y==1.){vec3 l=normalize(x+c.zzx*vec3 (1.3,.9,1.2));col=vec3 (0.81,0.15,0.18);col=.3*col+.4*col*abs(dot(l,n))+.6*col*abs(pow(dot(reflect(-l,n),dir),2.));}else if(s.y==2.){vec3 l=normalize(x+c.zzx*vec3 (1.3,.9,1.2));col=.7*c.xxx;col=.5*col+.4*col*abs(dot(l,n))+.8*col*abs(pow(dot(reflect(-l,n),dir),2.));}}if(iTime<0.)col=texture(iChannel0,fragCoord/iResolution).rgb;}else {iScale=nbeats-30./29.;iScale=smoothstep(-5./29.,0.,iScale)*(1.-smoothstep(0./29.,35./29.,iScale));lscale=smoothstep(0.,.5,clamp((iTime-10.),0.,1.))*(1.-smoothstep(0.,.5,clamp((iTime-18.),0.,1.)));rscale=smoothstep(167.,167.5,iTime)-smoothstep(172.,172.5,iTime);size=mix(.005,.01,rscale);size=mix(0.,size,max(rscale,lscale));if(lscale>0.){col=c.yyy;o=c.yyx+.5*vec3 (cos(iTime),sin(iTime),0.);r=c.xyy;u=c.yxy;t=c.yyy;dir=c.yyy;n=c.yyy;x=c.yyy;N=200;t=uv.x*r+uv.y*u;dir=normalize(t-o);d=-(o.z-.05-.5*size)/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene2(x,s);if(s.x<1.e-4)break;if(x.z<-.05-.5*size){col=c.yyy;i=N;break;}d+=min(s.x,1.e-3);}if(i<N){normal2(x,n,5.e-4);vec3 l=normalize(x+.5*n);if(s.y==1.){float v;vec2 vi;dvoronoi(x.xy/size,v,vi);vec3 y=vec3 (x.xy-vi*size,x.z);vec2 yi=vi*size;float bound=sqrt(iFSAA)-1.;for(float i=-.5*bound;i<=.5*bound;i+=1.)for(float j=-.5*bound;j<=.5*bound;j+=1.){col+=texture(iChannel0,yi/vec2 (a,1.)+vec2 (i,j)*3./max(bound,1.)/iResolution.xy).xyz;}col/=iFSAA;col=.4*col+.9*col*abs(dot(l,n))+.6*col*pow(abs(dot(reflect(-l,n),dir)),3.);}}else col=c.yyy;}else if(rscale>0.){col=c.yyy;o=c.yyx+.5*vec3 (-1.,-1.,0.);r=c.xyy;u=c.yxy;t=c.yyy;dir=c.yyy;n=c.yyy;x=c.yyy;N=300;t=uv.x*r+uv.y*u;dir=normalize(t-o);d=-(o.z-.05-.5*size)/dir.z;for(i=0;i<N;++i){x=o+d*dir;scene3(x,s);if(s.x<1.e-4)break;if(x.z<-.05-.5*size){col=c.yyy;i=N;break;}d+=min(s.x,1.e-3);}if(i<N){normal3(x,n,5.e-4);vec3 l=normalize(x+.5*n);if(s.y==1.){vec3 y=vec3 (mod(x.xy,size)-.5*size,x.z);vec2 yi=x.xy-y.xy;col=texture(iChannel0,yi/vec2 (a,1.)).rgb;col=.4*col+.9*col*abs(dot(l,n))+.6*col*pow(abs(dot(reflect(-l,n),dir)),3.);}}else col=c.yyy;}}col+=vec3 (0.,0.05,0.1)*sin(uv.y*1050.+5.*iTime);fragColor=vec4 (clamp(col,0.,1.),1.0);}void main(){mainImage(gl_FragColor,gl_FragCoord.xy);}\0";
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

void LoadSymbols()
{
    Loaddbox3();
    updateBar();
    Loadrot3();
    updateBar();
    Loadstroke();
    updateBar();
    Loadadd();
    updateBar();
    Loadrand();
    updateBar();
    Loadlfnoise();
    updateBar();
    Loadrshort();
    updateBar();
    Loadrfloat();
    updateBar();
    Loaddbox();
    updateBar();
    Loaddcircle();
    updateBar();
    Loaddlinesegment();
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
    Loadsmoothmin();
    updateBar();
    Loaddint();
    updateBar();
    Loaddtime();
    updateBar();
    Loadwindow();
    updateBar();
    Loadprogressbar();
    updateBar();
    Loaddvoronoi();
    updateBar();
    Loadnormal();
    updateBar();
}
int logo210_program, logo210_handle, graffiti_program, graffiti_handle, starsky_program, starsky_handle, text_program, text_handle, post_program, post_handle;
int logo210_iTime_location,logo210_iResolution_location;
int graffiti_iTime_location,graffiti_iResolution_location;
int starsky_iTime_location,starsky_iResolution_location;
int text_iFontWidth_location,text_iTime_location,text_iResolution_location,text_iChannel0_location,text_iFont_location,text_iFSAA_location;
int post_iFSAA_location,post_iResolution_location,post_iChannel0_location,post_iTime_location;
const int nprograms = 5;

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
