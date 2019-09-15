void supershape(in float phi, in vec2 ab, in float m, in vec3 n, out float r)
{
    phi *= .25*m;
    r = pow(pow(abs(1./ab.x*cos(phi)),n.y)+pow(abs(1./ab.y*sin(phi)),n.z),1./n.x);
    r = 1./r;
}
