#version 320 es
#undef lowp
#undef highp
#undef mediump
//Fshader kurs

out lowp vec4      texc;
uniform lowp sampler2D tex;
out highp vec4 FragColor;

void main(void){

    FragColor =vec4(0.0,0.0,1.0,1.0);//texture2D(tex,texc.st);

}


