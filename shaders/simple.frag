#version 330 core
//#version 400
// fragment shader

in vec4 fragColor;    // input: interpolated color as rgba-value
out vec4 finalColor;  // output: final color value as rgba-value

void main() {
  finalColor = fragColor;
}