#version 130
uniform float iTime;
void scale(out float s)
{
    if(iTime >=  0.0  && iTime <  3.4286 )
    {
        s = mod(iTime+.3- 0.0 , 0.4286 )- 0.2143 ;
        s = smoothstep( -0.03571666666666667 ,0.,s)*(1.-smoothstep(0., 0.10715 ,s));
    }
    if(iTime >=  3.4286  && iTime <  16.9497 )
    {
        s = mod(iTime+.3- 3.4286 , 0.4225 )- 0.21125 ;
        s = smoothstep( -0.035208333333333335 ,0.,s)*(1.-smoothstep(0., 0.105625 ,s));
    }
    if(iTime >=  16.9497  && iTime <  30.283 )
    {
        s = mod(iTime+.3- 16.9497 , 0.416675 )- 0.2083375 ;
        s = smoothstep( -0.034722916666666666 ,0.,s)*(1.-smoothstep(0., 0.10416875 ,s));
    }
    if(iTime >=  30.283  && iTime <  41.7899 )
    {
        s = mod(iTime+.3- 30.283 , 0.410975 )- 0.2054875 ;
        s = smoothstep( -0.03424791666666666 ,0.,s)*(1.-smoothstep(0., 0.10274375 ,s));
    }
    if(iTime >=  41.7899  && iTime <  43.3899 )
    {
        s = mod(iTime+.3- 41.7899 , 0.4 )- 0.2 ;
        s = smoothstep( -0.03333333333333333 ,0.,s)*(1.-smoothstep(0., 0.1 ,s));
    }
    if(iTime >=  43.3899  && iTime <  44.9483 )
    {
        s = mod(iTime+.3- 43.3899 , 0.3896 )- 0.1948 ;
        s = smoothstep( -0.032466666666666665 ,0.,s)*(1.-smoothstep(0., 0.0974 ,s));
    }
    if(iTime >=  44.9483  && iTime <  157.4483 )
    {
        s = mod(iTime+.3- 44.9483 , 0.374975 )- 0.1874875 ;
        s = smoothstep( -0.031247916666666667 ,0.,s)*(1.-smoothstep(0., 0.09374375 ,s));
    }
    if(iTime >=  157.4483  && iTime <  169.6002 )
    {
        s = mod(iTime+.3- 157.4483 , 0.379775 )- 0.1898875 ;
        s = smoothstep( -0.031647916666666664 ,0.,s)*(1.-smoothstep(0., 0.09494375 ,s));
    }
    if(iTime >=  169.6002  && iTime <  181.9079 )
    {
        s = mod(iTime+.3- 169.6002 , 0.384625 )- 0.1923125 ;
        s = smoothstep( -0.032052083333333335 ,0.,s)*(1.-smoothstep(0., 0.09615625 ,s));
    }
    if(iTime >=  181.9079  && iTime <  194.3754 )
    {
        s = mod(iTime+.3- 181.9079 , 0.3896 )- 0.1948 ;
        s = smoothstep( -0.032466666666666665 ,0.,s)*(1.-smoothstep(0., 0.0974 ,s));
    }
    if(iTime >=  194.3754  && iTime <  222.7965 )
    {
        s = mod(iTime+.3- 194.3754 , 0.39475 )- 0.197375 ;
        s = smoothstep( -0.03289583333333333 ,0.,s)*(1.-smoothstep(0., 0.0986875 ,s));
    }
}
