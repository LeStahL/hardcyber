#version 130
// Random Quadtree
void smoothmin(in float a, in float b, in float k, out float dst);
void dvoronoi(in vec2 x, out float d, out vec2 z);
void rand(in vec2 x, out float num);
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
        float dd;
            vec2 ind;
            dvoronoi(y/size/.5,dd, ind);
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
