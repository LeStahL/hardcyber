#version 440

precision highp float;

uniform sampler2D iData;
uniform int iDataWidth;

out vec4 oData;

void main()
{
    oData.r = texture(iData, gl_FragCoord.xy/float(iDataWidth)).r;
}
