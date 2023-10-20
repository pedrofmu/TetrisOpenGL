#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 VertexTexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos.x, aPos.y, 1.0, 1.0);
    VertexTexCoord = vec2(aTexCoord.x, aTexCoord.y); // Actualiza el nombre aquí
}
