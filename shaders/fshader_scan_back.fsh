#version 320 es
#undef lowp
#undef highp
#undef mediump
in highp  vec4  texc;
uniform  highp sampler2D   texture;
out highp vec4 fragColor;
flat in int rgm;
in highp float angle_out;
highp float angle_sector;
highp float radius;


const highp float   PI = 3.14159265358979323846264;

void main(void)
{
    if(rgm == 0){
        fragColor = texture2D(texture, texc.st);

    }else if(rgm == 1){
        highp vec2 uv = texc.xy;
        uv = uv - vec2(0.5,0.5);
        angle_sector =-atan(uv.y,uv.x) - radians(angle_out);
        radius = sqrt(uv.y*uv.y+uv.x*uv.x);
        if(angle_sector <-2.0*PI) angle_sector +=2.0*PI;
        if(radius <0.5){

            if( angle_sector  < radians(-120.0) || angle_sector > radians(-60.0))  fragColor =vec4(0.0,0.5,0.0,0.0);
            else fragColor =texture2D(texture,texc.st);
         }else
        {
         fragColor =vec4(0.0,0.5,0.5,0.0);
        }

     }
    else if(rgm == 2){
        fragColor =texture2D(texture,texc.st);
    }


}
