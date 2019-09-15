#version 130
const float pi = acos(-1.);
void dcirclesegment(in vec2 x, in float R, in float p0, in float p1, out float d)
{
    float p = atan(x.y, x.x);
    vec2 philo = vec2(max(p0, p1), min(p0, p1));
    if((p < philo.x && p > philo.y) || (p+2.0*pi < philo.x && p+2.0*pi > philo.y) || (p-2.0*pi < philo.x && p-2.0*pi > philo.y))
        d = abs(length(x)-R);
    else d = min(
        length(x-vec2(cos(p0), sin(p0))),
        length(x-vec2(cos(p1), sin(p1)))
        );
}
