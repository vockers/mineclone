#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube tex;

void main()
{    
    FragColor = texture(tex, TexCoords);
}
