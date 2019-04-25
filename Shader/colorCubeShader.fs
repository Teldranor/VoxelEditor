#version 330
//define out color
out vec4 o_color;

//get color from the vertex shader
in vec4 myColor;

void main() {
o_color = myColor;
}
