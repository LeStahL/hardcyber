#version 130

const vec3 c = vec3(1.,0.,-1.);

void sub(in vec2 sda, in vec2 sdb, out vec2 sdf)
{
    sdf = (sda.x>sdb.x)?abs(sda):abs(sdb)*c.zx;
}
