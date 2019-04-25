#version 330
//this shader take two inputs
//the first input is the position of the current vertex
layout (location = 0) in vec3 aPos;
//the second input is the normal of the vertex depending of the face he compose
layout (location = 1) in vec3 aNormal;

//this four matrix define the transformation from 3D space to 2D screen
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//send the position of the vertex (to calculate lights) to the fragment vertex
out vec3 FragPos;
//send the normal (to calculate lights) to the framgent shader
out vec3 Normal;

void main() {
//calculate position on 2D screen
//the aPos is in the local space of the object
//the model matrix change from local space to world space
//the view matrix change from world space to camera space
//the projection matrix change from camera space to 2D screen
gl_Position = projection * view * model * vec4(aPos, 1.0 );
//send the position of the point in the 3D space
FragPos = vec3(model * vec4(aPos, 1.0));
//send the normal of the point transformed into worls space
Normal = mat3(transpose(inverse(model))) * aNormal;
}
