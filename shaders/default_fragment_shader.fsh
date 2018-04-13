#version 320 es
#undef lowp
#undef highp
#undef mediump

in lowp vec4           texc;
uniform lowp sampler2D texture;
out highp vec4         FragColor;
in highp float         hT;
in highp vec4          clr;



void main(void){

    if(hT < 0.0) FragColor =texture2D(texture,texc.st);
    else  FragColor = clr;



}
