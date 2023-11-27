#version 330 core
out vec4 FragColor;

in vec2 VertexTexCoord; // Asegúrate de que coincida el nombre
in float y;

uniform sampler2D texture1;

void main()
{
    vec4 color = texture(texture1, VertexTexCoord) * sin(y);
    FragColor = color; // Asegúrate de usar VertexTexCoord
}

