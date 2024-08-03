#version 330 core
in vec2 TexCoord;
in float TextIndex;
out vec4 FragColor;

uniform sampler2D ourTextures[5];

void main()
{
    int index = int(TextIndex);
    FragColor = texture(ourTextures[index], TexCoord);
}