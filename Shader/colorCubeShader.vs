#version 330
//basic shader that take two inputs position and color
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

//this four matrix define the transformation from 3D space to 2D screen
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//send color to the fragment shader
out vec4 myColor;

void main() {
//define position in 2D space
gl_Position = projection * view * model * vec4(aPos, 1.0 );
//send color to the fragment shader
myColor = aColor;
}
