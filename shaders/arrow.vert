#version 320 es
in mediump vec4 vertex;
uniform mediump mat4 matrix;
uniform   mediump float angle_gr;
mediump mat4 rotate;



void main(void)
{
    float angle = radians(angle_gr);
    rotate = mat4(
       cos(angle),   sin(angle),   0.0, 0.0, // first column (not row!)
      -sin(angle),   cos(angle),   0.0, 0.0,// second column
              0.0,          0.0,   1.0, 0.0, // third column
              0.0,          0.0,   0.0, 1.0
    );
     vec4 temp =vec4(0.0,0.8,0.0,0.0);
    gl_Position = rotate*vertex - temp;
}
