#version 330 core
out vec4 FragColor;

in vec2 VertexTexCoord; // Asegúrate de que coincida el nombre

uniform sampler2D texture1;

void main()
{
    vec4 color = texture(texture1, VertexTexCoord);
    if (color.r == 0 && color.g == 0 && color.b == 0){
        discard;
    }else{
        FragColor = color;
    }
}

