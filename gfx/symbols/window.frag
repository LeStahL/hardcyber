#version 130

const vec3 c = vec3(1.,0.,-1.);

uniform float iTime;

void dhexagonpattern(in vec2 p, out float d, out vec2 ind);
void stroke(in float d0, in float s, out float d);
void lfnoise(in vec2 t, out float num);
void box(in vec2 x, in vec2 b, out float dst);
void drhomboid(in vec2 x, in vec2 b, in float tilt, out float dst);

// Fixme: Add

void window(in vec2 x, in vec2 size, in vec3 bg, in float title_index, out vec4 col)
{
//     size.x *= .5;
//     col = vec4(1., bg);
//     
//     const float cellsize = .015, bordersize = .005;
//     vec3 titlecolor = mix(vec3(0.82,0.00,0.09),vec3(0.45,0.00,0.06),.5-.5*x.y/cellsize),
//         bordercolor = vec3(1.00,0.71,0.02);
//     vec4 c2 = vec4(1., titlecolor);
//     
//     float dhx, dhy;
//     vec2 ind;
//     dhexagonpattern(72.*x,  dhx, ind);
//     stroke(dhx, .1, dhx);
//     lfnoise(ind-iTime, dhy);
//     
//     // Window background
//     box(x+.5*size*c.yx,size*vec2(1.,.5),c2.x);
//     c2.gba = mix(bg, mix(vec3(0.82,0.00,0.09),vec3(0.45,0.00,0.06),-x.y/size.y), .5+.5*dhy*step(0.,dhx));
//     add(col, c2, col);
//     
//     // Title bar
//     c2.gba = titlecolor;
//     drhomboid(x+.8*size.x*c.xy, vec2(.1*size.x,cellsize), cellsize, c2.x);
//    	add(col, c2, col);
//     drhomboid(x, vec2(.65*size.x,cellsize), cellsize, c2.x);
//    	add(col, c2, col);
//     drhomboid(x-.8*size.x*c.xy, vec2(.1*size.x,cellsize), cellsize, c2.x);
//    	add(col, c2, col);
//     
//     // Border of title bar
//     c2 = vec4(1., bordercolor);
//     stroke(col.x,bordersize,c2.x);
//     add(col,c2,col);
//     
//     // Window Border
//     dlinesegment(x, -.9*size.x*c.xy, -size.x*c.xy, c2.x);
//     float d;
//     dlinesegment(x, -size.x*c.xy, -size, d);
//     c2.x = min(c2.x, d);
//     dlinesegment(x, -size, size*c.xz, d);
//     c2.x = min(c2.x, d);
//     dlinesegment(x, size*c.xz, size*c.xy, d);
//     c2.x = min(c2.x, d);
//     dlinesegment(x, .9*size.x*c.xy, size.x*c.xy, d);
//     c2.x = min(c2.x, d);
//     stroke(c2.x,.25*bordersize,c2.x);
//     add(col, c2, col);
}
