#version 320 es
#undef lowp
#undef highp
#undef mediump
uniform sampler2D texture;
in highp vec4 texc;
out highp vec4 FragColor;


void main(void)
{
    FragColor = vec4(0.5,0.0,0.0,1.0);
}
