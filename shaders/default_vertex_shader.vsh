#version 320 es

in highp vec4  vertex;
in highp vec4  texture_coordinate;
in highp float haveTexture;
in highp vec4  color;

uniform   highp float dalnost;
uniform   highp float translate_X;
uniform   highp float translate_Y;
uniform   highp float translate_Z;
uniform   highp float angle_X;
uniform   highp float angle_Y;
uniform   highp float angle_Z;
uniform   highp float scale_X;
uniform   highp float scale_Y;
uniform   highp float scale_Z;
uniform int regim;

flat out int rgm;

highp mat4 rotate;
highp mat4 matrix_scale;
highp mat4 matrix_translate;


out lowp vec4 texc;
out highp vec4  clr;
out highp float hT;
out highp float angle;
highp vec4 temp_vertex;


void main(void)
{
    temp_vertex = vertex;

    if(vertex.w > 1.0){
        temp_vertex.y =temp_vertex.y + dalnost;
    }

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
    texc        = texture_coordinate;
    clr         = color;
    hT          = haveTexture;
    rgm         = regim;
    angle       = angle_Z;


}
