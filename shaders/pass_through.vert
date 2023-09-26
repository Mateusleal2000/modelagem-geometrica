#version 400
//#version 330 core
// vertex shader

// input:  attribute named 'position' with 3 floats per vertex
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 fragColor;


//uniform mat4 samuel;
//uniform mat4 matrix = mat4(
//    vec4(1.0f, 0.0f, 0.0f, 0.0f),
//    vec4(0.0f, 0.81f, 0.5f, 0.0f),
//    vec4(0.0f, -0.5f, 0.81f, 0.0f),
//    vec4(0.0f, 0.0f, 0.0f, 1.0f)
//);

//uniform mat4 matrixz = mat4(
//    vec4(0.81f, 0.0f, -0.5f, 0.0f),
//    vec4(0.0f, 1.0f, 0.0f, 0.0f),
//    vec4(0.5f, 0.0f, 0.81f, 0.0f),
//    vec4(0.0f, 0.0f, 0.0f, 1.0f)
//);

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
void main() {
  //gl_Position = matrix * matrixz * vec4(position, 1.0);
  
  //gl_Position = matrix * vec4(position, 1.0);
  
  gl_Position =   projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
  fragColor = vec4(color, 1.0);
}