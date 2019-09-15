#version 130

const vec3 c = vec3(1.,0.,-1.);

void progressbar(in vec2 x, in float width, in float progress, out vec4 col)
{
//     const float cellsize = .015, bordersize = .005;
//     vec3 titlecolor = mix(vec3(0.82,0.00,0.09),vec3(0.45,0.00,0.06),.5-.5*x.y/cellsize),
//         bordercolor = vec3(1.00,0.71,0.02), bg = c.yyy;
//     vec4 c2 = vec4(1., titlecolor);
//     
//     // Window background
//     box(x+.5*width*c.yx,width*c.xy,c2.x);
//     c2.gba = mix(bg, mix(vec3(0.82,0.00,0.09),vec3(0.45,0.00,0.06),-x.y/cellsize), .5);
//     add(col, c2, col);
//     
//     // Bar background
//     c2.gba = titlecolor;
//     drhomboid(x, vec2(.5*width,cellsize), cellsize, c2.x);
//    	add(col, c2, col);
//     
//     // Border
//     c2.gba = bordercolor;
//     stroke(c2.x,.5*bordersize,c2.x);
//     add(col, c2, col);
//     
//     // Progress
//     float wc = width/cellsize;
//     x.x -= .5*x.y;
//     vec2 y = vec2(mod(x.x, 1.2*cellsize)-.6*cellsize, x.y),
//         index = (x-y)/.6/cellsize;
//     if(abs(index.x) < .8*wc && -index.x > .8*wc*(1.-2.*progress))
//     {
//         box(y, vec2(.5*cellsize, .8*cellsize), c2.x);
//         add(col, c2, col);
//     }
}
