#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 VertexTexCoord;

uniform mat4 transform;

void main()
{
  vec4 position =  transform * vec4(aPos.x, aPos.y, 0.0, 1.0);

  gl_Position = position;
  
  VertexTexCoord =  vec2(aTexCoord.x, aTexCoord.y);
}
