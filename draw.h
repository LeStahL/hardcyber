#ifndef DRAW_HEADER
#define DRAW_HEADER
if(scene_override)
{
    if(override_index == 1) t = t_now;
    else t = t_now + start_times[override_index - 2];
}

if(t < 11)
{
    glUseProgram(logo210_program);
    glUniform1f(logo210_iTime_location, t);
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
    if(override_index == 0)
    {
        select_button(override_index);
        override_index = 0;
    }
#endif
}
else if(t < 22)
{
    glUseProgram(graffiti_program);
    glUniform1f(graffiti_iTime_location, t);
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
    glUniform1f(starsky_iTime_location, t);
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
#endif
