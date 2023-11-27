#version 330 core
out vec4 FragColor;
in float y; 

uniform vec3 backgroundColor; // Color del fondo

void main() {
    vec4 color = vec4(0, y * backgroundColor.g, 0, 1.0);
    FragColor = color;
}
