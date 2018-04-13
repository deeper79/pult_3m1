#version 320 es
out highp vec4 texc;
flat out int rgm;

in highp vec4 vertex;
in highp vec4 texture_coordinate;

uniform   highp float angle_Z;
uniform int regim;

highp float scale_X;
highp float scale_Y;
highp float scale_Z;
highp float translate_X;
highp float translate_Y;
highp float translate_Z;

highp mat4 rotate;
highp mat4 matrix_scale;
highp mat4 matrix_translate;

highp vec4 temp_vertex;
out highp float angle_out;

void main(void)
{

    if(regim == 0){
        scale_X = 1.0;
        scale_Y = 1.0;
        scale_Z = 1.0;
        translate_X = 0.0;
        translate_Y = 0.0;
        translate_Z = 0.0;
    }else if(regim == 1){
        scale_X = 1.4;
        scale_Y = 1.4;
        scale_Z = 1.0;
        translate_X = 0.0;
        translate_Y = -1.0;
        translate_Z = 0.0;
    }
    else
    {
        scale_X = 1.0;
        scale_Y = 1.0;
        scale_Z = 1.0;
        translate_X = 0.0;
        translate_Y = 0.0;
        translate_Z = 0.0;
    }
    temp_vertex  =  vertex;
    temp_vertex.w = 1.0;

     float angle = radians(angle_Z);
        rotate = mat4(
           cos(angle),   sin(angle),   0.0, 0.0, // first column (not row!)
          -sin(angle),   cos(angle),   0.0, 0.0,// second column
                  0.0,          0.0,   1.0, 0.0, // third column
                  0.0,          0.0,   0.0, 1.0
        );

        matrix_scale = mat4(
           scale_X,   0.0,   0.0, 0.0, // first column (not row!)
             0.0, scale_Y,   0.0, 0.0,// second column
             0.0,   0.0, scale_Z, 0.0, // third column
             0.0,   0.0,   0.0, 1.0
        );

        matrix_translate = mat4(
             1.0,   0.0,   0.0, 0.0, // first column (not row!)
             0.0,   1.0,   0.0, 0.0,// second column
             0.0,   0.0,   1.0, 0.0, // third column
             translate_X,  translate_Y,  translate_Z, 1.0
        );

        gl_Position = matrix_translate*rotate*matrix_scale*temp_vertex;
        texc = texture_coordinate;

       rgm   = regim;
       angle_out = angle_Z;
}
