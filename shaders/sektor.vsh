#version 320 es
//vshader kurs
in highp vec4 vertex;
in highp vec4 textCoord;

in highp float num_vertex;

uniform   highp float trsX;
uniform   highp float trsY;
uniform   highp float trsZ;
uniform   highp float angle_gr;
uniform   highp float scale;

highp mat4 rotate;
highp mat4 matrix_scale;
highp mat4 matrix_translate;

out highp vec4 texc;

void main(void)
{

    float angle = radians(angle_gr);
    rotate = mat4(
       cos(angle),   sin(angle),   0.0, 0.0, // first column (not row!)
      -sin(angle),   cos(angle),   0.0, 0.0,// second column
              0.0,          0.0,   1.0, 0.0, // third column
              0.0,          0.0,   0.0, 1.0
    );

    matrix_scale = mat4(
       scale,   0.0,   0.0, 0.0, // first column (not row!)
         0.0, scale,   0.0, 0.0,// second column
         0.0,   0.0, scale, 0.0, // third column
         0.0,   0.0,   0.0, 1.0
    );

    matrix_translate = mat4(
         1.0,   0.0,   0.0, 0.0, // first column (not row!)
         0.0,   1.0,   0.0, 0.0,// second column
         0.0,   0.0,   1.0, 0.0, // third column
         trsX,  trsY,  trsZ, 1.0
    );

    gl_Position = matrix_translate*rotate*matrix_scale*vertex;
    texc = textCoord;

}
