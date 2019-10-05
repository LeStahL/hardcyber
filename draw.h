#ifndef DRAW_HEADER
#define DRAW_HEADER
if(t < t_logo210)
{
    glUseProgram(deadline_program);
    glUniform1f(deadline_iTime_location, t-t_deadline);
    glUniform2f(deadline_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(deadline_iFader0_location, fader0);
    glUniform1f(deadline_iFader1_location, fader1);
    glUniform1f(deadline_iFader2_location, fader2);
    glUniform1f(deadline_iFader3_location, fader3);
    glUniform1f(deadline_iFader4_location, fader4);
    glUniform1f(deadline_iFader5_location, fader5);
    glUniform1f(deadline_iFader6_location, fader6);
    glUniform1f(deadline_iFader7_location, fader7);
#endif
}
else if(t < t_graffiti)
{
    glUseProgram(logo210_program);
    glUniform1f(logo210_iTime_location, t-t_logo210);
    glUniform2f(logo210_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(logo210_iFader0_location, fader0);
    glUniform1f(logo210_iFader1_location, fader1);
    glUniform1f(logo210_iFader2_location, fader2);
    glUniform1f(logo210_iFader3_location, fader3);
    glUniform1f(logo210_iFader4_location, fader4);
    glUniform1f(logo210_iFader5_location, fader5);
    glUniform1f(logo210_iFader6_location, fader6);
    glUniform1f(logo210_iFader7_location, fader7);
#endif
}
else if(t < t_ocean)
{
    glUseProgram(graffiti_program);
    glUniform1f(graffiti_iTime_location, t-t_graffiti);
    glUniform2f(graffiti_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(graffiti_iFader0_location, fader0);
    glUniform1f(graffiti_iFader1_location, fader1);
    glUniform1f(graffiti_iFader2_location, fader2);
    glUniform1f(graffiti_iFader3_location, fader3);
    glUniform1f(graffiti_iFader4_location, fader4);
    glUniform1f(graffiti_iFader5_location, fader5);
    glUniform1f(graffiti_iFader6_location, fader6);
    glUniform1f(graffiti_iFader7_location, fader7);
#endif
}
else if(t < t_starsky)
{
    glUseProgram(ocean_program);
    glUniform1f(ocean_iTime_location, t-t_ocean);
    glUniform2f(ocean_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(ocean_iFader0_location, fader0);
    glUniform1f(ocean_iFader1_location, fader1);
    glUniform1f(ocean_iFader2_location, fader2);
    glUniform1f(ocean_iFader3_location, fader3);
    glUniform1f(ocean_iFader4_location, fader4);
    glUniform1f(ocean_iFader5_location, fader5);
    glUniform1f(ocean_iFader6_location, fader6);
    glUniform1f(ocean_iFader7_location, fader7);
#endif
}
else if(t < t_glitchcity)
{
    glUseProgram(starsky_program);
    glUniform1f(starsky_iTime_location, t-t_starsky);
    glUniform2f(starsky_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(starsky_iFader0_location, fader0);
    glUniform1f(starsky_iFader1_location, fader1);
    glUniform1f(starsky_iFader2_location, fader2);
    glUniform1f(starsky_iFader3_location, fader3);
    glUniform1f(starsky_iFader4_location, fader4);
    glUniform1f(starsky_iFader5_location, fader5);
    glUniform1f(starsky_iFader6_location, fader6);
    glUniform1f(starsky_iFader7_location, fader7);
#endif
}
else if(t < t_watercubes)
{
    glUseProgram(glitchcity_program);
    glUniform1f(glitchcity_iTime_location, t-t_glitchcity);
    glUniform2f(glitchcity_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(glitchcity_iFader0_location, fader0);
    glUniform1f(glitchcity_iFader1_location, fader1);
    glUniform1f(glitchcity_iFader2_location, fader2);
    glUniform1f(glitchcity_iFader3_location, fader3);
    glUniform1f(glitchcity_iFader4_location, fader4);
    glUniform1f(glitchcity_iFader5_location, fader5);
    glUniform1f(glitchcity_iFader6_location, fader6);
    glUniform1f(glitchcity_iFader7_location, fader7);
#endif
}
else if(t < t_greetings)
{
    glUseProgram(watercubes_program);
    glUniform1f(watercubes_iTime_location, t-t_watercubes);
    glUniform2f(watercubes_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(watercubes_iFader0_location, fader0);
    glUniform1f(watercubes_iFader1_location, fader1);
    glUniform1f(watercubes_iFader2_location, fader2);
    glUniform1f(watercubes_iFader3_location, fader3);
    glUniform1f(watercubes_iFader4_location, fader4);
    glUniform1f(watercubes_iFader5_location, fader5);
    glUniform1f(watercubes_iFader6_location, fader6);
    glUniform1f(watercubes_iFader7_location, fader7);
#endif
}
else if(t < t_hydrant)
{
    glUseProgram(greetings_program);
    glUniform1f(greetings_iTime_location, t-t_greetings);
    glUniform2f(greetings_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(greetings_iFader0_location, fader0);
    glUniform1f(greetings_iFader1_location, fader1);
    glUniform1f(greetings_iFader2_location, fader2);
    glUniform1f(greetings_iFader3_location, fader3);
    glUniform1f(greetings_iFader4_location, fader4);
    glUniform1f(greetings_iFader5_location, fader5);
    glUniform1f(greetings_iFader6_location, fader6);
    glUniform1f(greetings_iFader7_location, fader7);
#endif
}
else if(t < t_fractal)
{
    glUseProgram(hydrant_program);
    glUniform1f(hydrant_iTime_location, t-t_hydrant);
    glUniform2f(hydrant_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(hydrant_iFader0_location, fader0);
    glUniform1f(hydrant_iFader1_location, fader1);
    glUniform1f(hydrant_iFader2_location, fader2);
    glUniform1f(hydrant_iFader3_location, fader3);
    glUniform1f(hydrant_iFader4_location, fader4);
    glUniform1f(hydrant_iFader5_location, fader5);
    glUniform1f(hydrant_iFader6_location, fader6);
    glUniform1f(hydrant_iFader7_location, fader7);
#endif
}
else if(t < t_voronoinet)
{
    glUseProgram(fractal_program);
    glUniform1f(fractal_iTime_location, t-t_fractal);
    glUniform2f(fractal_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(fractal_iFader0_location, fader0);
    glUniform1f(fractal_iFader1_location, fader1);
    glUniform1f(fractal_iFader2_location, fader2);
    glUniform1f(fractal_iFader3_location, fader3);
    glUniform1f(fractal_iFader4_location, fader4);
    glUniform1f(fractal_iFader5_location, fader5);
    glUniform1f(fractal_iFader6_location, fader6);
    glUniform1f(fractal_iFader7_location, fader7);
#endif
}
else if(t < t_volclouds)
{
    glUseProgram(voronoinet_program);
    glUniform1f(voronoinet_iTime_location, t-t_voronoinet);
    glUniform2f(voronoinet_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(voronoinet_iFader0_location, fader0);
    glUniform1f(voronoinet_iFader1_location, fader1);
    glUniform1f(voronoinet_iFader2_location, fader2);
    glUniform1f(voronoinet_iFader3_location, fader3);
    glUniform1f(voronoinet_iFader4_location, fader4);
    glUniform1f(voronoinet_iFader5_location, fader5);
    glUniform1f(voronoinet_iFader6_location, fader6);
    glUniform1f(voronoinet_iFader7_location, fader7);
#endif
}
else {
    glUseProgram(volclouds_program);
    glUniform1f(volclouds_iTime_location, t-t_volclouds);
    glUniform2f(volclouds_iResolution_location, w, h);
#ifdef MIDI
    glUniform1f(volclouds_iFader0_location, fader0);
    glUniform1f(volclouds_iFader1_location, fader1);
    glUniform1f(volclouds_iFader2_location, fader2);
    glUniform1f(volclouds_iFader3_location, fader3);
    glUniform1f(volclouds_iFader4_location, fader4);
    glUniform1f(volclouds_iFader5_location, fader5);
    glUniform1f(volclouds_iFader6_location, fader6);
    glUniform1f(volclouds_iFader7_location, fader7);
#endif
}
#endif
