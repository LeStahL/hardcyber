#ifndef DRAW_HEADER
#define DRAW_HEADER

if(t < t_logo210)
{
    glUseProgram(shader_program_gfx_deadline.handle);
    glUniform1f(shader_uniform_gfx_deadline_iTime, t-t_deadline);
    glUniform2f(shader_uniform_gfx_deadline_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_deadline_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_deadline_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_deadline_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_deadline_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_deadline_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_deadline_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_deadline_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_deadline_iFader7, fader7);
#endif
}
else if(t < t_graffiti)
{
    glUseProgram(shader_program_gfx_logo210.handle);
    glUniform1f(shader_uniform_gfx_logo210_iTime, t-t_logo210);
    glUniform2f(shader_uniform_gfx_logo210_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_logo210_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_logo210_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_logo210_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_logo210_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_logo210_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_logo210_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_logo210_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_logo210_iFader7, fader7);
#endif
}
else if(t < t_ocean)
{
    glUseProgram(shader_program_gfx_graffiti.handle);
    glUniform1f(shader_uniform_gfx_graffiti_iTime, t-t_graffiti);
    glUniform2f(shader_uniform_gfx_graffiti_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_graffiti_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_graffiti_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_graffiti_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_graffiti_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_graffiti_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_graffiti_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_graffiti_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_graffiti_iFader7, fader7);
#endif
}
else if(t < t_starsky)
{
    glUseProgram(shader_program_gfx_ocean.handle);
    glUniform1f(shader_uniform_gfx_ocean_iTime, t-t_ocean);
    glUniform2f(shader_uniform_gfx_ocean_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_ocean_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_ocean_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_ocean_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_ocean_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_ocean_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_ocean_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_ocean_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_ocean_iFader7, fader7);
#endif
}
else if(t < t_glitchcity)
{
    glUseProgram(shader_program_gfx_starsky.handle);
    glUniform1f(shader_uniform_gfx_starsky_iTime, t-t_starsky);
    glUniform2f(shader_uniform_gfx_starsky_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_starsky_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_starsky_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_starsky_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_starsky_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_starsky_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_starsky_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_starsky_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_starsky_iFader7, fader7);
#endif
}
else if(t < t_watercubes)
{
    glUseProgram(shader_program_gfx_glitchcity.handle);
    glUniform1f(shader_uniform_gfx_glitchcity_iTime, t-t_glitchcity);
    glUniform2f(shader_uniform_gfx_glitchcity_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_glitchcity_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_glitchcity_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_glitchcity_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_glitchcity_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_glitchcity_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_glitchcity_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_glitchcity_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_glitchcity_iFader7, fader7);
#endif
}
else if(t < t_greetings)
{
    glUseProgram(shader_program_gfx_watercubes.handle);
    glUniform1f(shader_uniform_gfx_watercubes_iTime, t-t_watercubes);
    glUniform2f(shader_uniform_gfx_watercubes_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_watercubes_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_watercubes_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_watercubes_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_watercubes_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_watercubes_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_watercubes_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_watercubes_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_watercubes_iFader7, fader7);
#endif
}
else if(t < t_hydrant)
{
    glUseProgram(shader_program_gfx_greetings.handle);
    glUniform1f(shader_uniform_gfx_greetings_iTime, t-t_greetings);
    glUniform2f(shader_uniform_gfx_greetings_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_greetings_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_greetings_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_greetings_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_greetings_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_greetings_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_greetings_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_greetings_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_greetings_iFader7, fader7);
#endif
}
else if(t < t_fractal)
{
    glUseProgram(shader_program_gfx_hydrant.handle);
    glUniform1f(shader_uniform_gfx_hydrant_iTime, t-t_hydrant);
    glUniform2f(shader_uniform_gfx_hydrant_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_hydrant_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_hydrant_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_hydrant_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_hydrant_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_hydrant_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_hydrant_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_hydrant_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_hydrant_iFader7, fader7);
#endif
}
else if(t < t_voronoinet)
{
    glUseProgram(shader_program_gfx_fractal.handle);
    glUniform1f(shader_uniform_gfx_fractal_iTime, t-t_fractal);
    glUniform2f(shader_uniform_gfx_fractal_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_fractal_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_fractal_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_fractal_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_fractal_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_fractal_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_fractal_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_fractal_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_fractal_iFader7, fader7);
#endif
}
else if(t < t_volclouds)
{
    glUseProgram(shader_program_gfx_voronoinet.handle);
    glUniform1f(shader_uniform_gfx_voronoinet_iTime, t-t_voronoinet);
    glUniform2f(shader_uniform_gfx_voronoinet_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_voronoinet_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_voronoinet_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_voronoinet_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_voronoinet_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_voronoinet_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_voronoinet_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_voronoinet_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_voronoinet_iFader7, fader7);
#endif
}
else {
    glUseProgram(shader_program_gfx_volclouds.handle);
    glUniform1f(shader_uniform_gfx_volclouds_iTime, t-t_volclouds);
    glUniform2f(shader_uniform_gfx_volclouds_iResolution, w, h);
#ifdef MIDI
    glUniform1f(shader_uniform_gfx_volclouds_iFader0, fader0);
    glUniform1f(shader_uniform_gfx_volclouds_iFader1, fader1);
    glUniform1f(shader_uniform_gfx_volclouds_iFader2, fader2);
    glUniform1f(shader_uniform_gfx_volclouds_iFader3, fader3);
    glUniform1f(shader_uniform_gfx_volclouds_iFader4, fader4);
    glUniform1f(shader_uniform_gfx_volclouds_iFader5, fader5);
    glUniform1f(shader_uniform_gfx_volclouds_iFader6, fader6);
    glUniform1f(shader_uniform_gfx_volclouds_iFader7, fader7);
#endif
}
#endif
