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
else if(t < 33)
{
    glUseProgram(starsky_program);
    glUniform1f(starsky_iTime_location, t-22);
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
    if(override_index == 2)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 42)
{
    glUseProgram(graffiti_program);
    glUniform1f(graffiti_iTime_location, t-33);
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
    if(override_index == 3)
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
    if(override_index == 4)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
#endif
