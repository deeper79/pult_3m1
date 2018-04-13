#version 320 es
#undef lowp
#undef highp
#undef mediump
in highp  vec4  texc;
flat in int  rgm;
uniform  highp sampler2D   texture;


highp int points[15];
const highp float   PI = 3.14159265358979323846264;

out highp vec4 fragColor;
in highp float angle_out;
lowp float radius;
lowp float angl;
lowp float angle_sector;
lowp float test_angle;

void main(void)
{


    switch(rgm){
    case(0):
    {
        highp vec2 uv = texc.xy;
        uv = uv - vec2(0.5,0.5);

        highp float angle_t  = -atan(uv.y,uv.x) - PI/2.0;
                    angle_t = 0.5*angle_t/PI+0.5;

        highp float radius = sqrt(uv.y*uv.y+uv.x*uv.x);

        highp vec2 new=vec2(angle_t,radius);
        highp  float color = texture2D(texture, new).r;

        if(radius < 0.5)   fragColor = vec4(0.0,texture2D(texture, new).r,0.0,1.0);
        else fragColor = vec4(0.0,1.0,0.0,0.0);

        break;
    }
    case(1):{


        highp vec2 uv = texc.xy;
        uv = uv-vec2(0.5,0.5);//0.084
        highp float angle_t  = -atan(uv.y,uv.x) - PI/2.0 - radians(angle_out);
        angle_sector =-atan(uv.y,uv.x);
        angle_t = 0.5*angle_t/PI+0.5;
        radius = sqrt(uv.y*uv.y+uv.x*uv.x);

        highp vec2 new=vec2(angle_t,radius);
        highp float  color = texture2D(texture, new).r;

        if(radius<0.5){
            if( angle_sector  < radians(-120.0) || angle_sector > radians(-60.0)) fragColor = vec4(0.0,0.5,0.0,1.0);
            else fragColor = vec4(0.0,color,0.0,1.0);
        }else
            fragColor =vec4(0.0,0.5,0.0,0.0);
        break;
    }
    case(2):{
        fragColor = vec4(0.0,texture2D(texture, texc.st).r,0.0,1.0);
        break;
    }
    default:{
         fragColor=vec4(1.0,0.0,0.0,0.0);
        break;
    }
     //   fragColor = vec4(0.0,texture2D(texture, texc.st).r,0.0,1.0);
}
//highp float color = texture2D(texture, texc.st).r;

//fragColor = vec4(0.0,color,0.0,1.0);
}

