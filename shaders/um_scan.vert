#version 320 es
in highp vec4 vertex;
in highp vec4 texCoord;
uniform highp mat4 matrix;
out highp vec4 texc;

void main(void)
{


    gl_Position = matrix*vertex;
    texc = texCoord;
}

