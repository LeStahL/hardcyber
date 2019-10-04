#ifndef DRAW_HEADER
#define DRAW_HEADER
if(scene_override)
{
    if(override_index == 1) t = t_now;
    else t = t_now + start_times[override_index - 2];
}

if(t < 20)
{
    glUseProgram(deadline_program);
    glUniform1f(deadline_iTime_location, t-0);
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
    if(override_index == 0)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 32)
{
    glUseProgram(logo210_program);
    glUniform1f(logo210_iTime_location, t-20);
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
    if(override_index == 1)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 42)
{
    glUseProgram(graffiti_program);
    glUniform1f(graffiti_iTime_location, t-32);
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
    if(override_index == 2)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 53)
{
    glUseProgram(ocean_program);
    glUniform1f(ocean_iTime_location, t-42);
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
    if(override_index == 3)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 73)
{
    glUseProgram(starsky_program);
    glUniform1f(starsky_iTime_location, t-53);
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
    if(override_index == 4)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 93)
{
    glUseProgram(watercubes_program);
    glUniform1f(watercubes_iTime_location, t-73);
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
    if(override_index == 5)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 103)
{
    glUseProgram(glitchcity_program);
    glUniform1f(glitchcity_iTime_location, t-93);
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
    if(override_index == 6)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 133)
{
    glUseProgram(greetings_program);
    glUniform1f(greetings_iTime_location, t-103);
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
    if(override_index == 7)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 143)
{
    glUseProgram(hydrant_program);
    glUniform1f(hydrant_iTime_location, t-133);
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
    if(override_index == 8)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 173)
{
    glUseProgram(fractal_program);
    glUniform1f(fractal_iTime_location, t-143);
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
    if(override_index == 9)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
#endif
