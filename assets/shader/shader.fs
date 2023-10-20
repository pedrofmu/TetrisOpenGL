#version 330 core
out vec4 FragColor;

in vec2 VertexTexCoord; // Asegúrate de que coincida el nombre

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, VertexTexCoord); // Asegúrate de usar VertexTexCoord
}

