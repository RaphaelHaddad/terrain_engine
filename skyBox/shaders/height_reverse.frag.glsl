#version 330 core

out vec4 FragColor;

in float Height;
in vec2 TexCoord1;
in vec2 TexCoord2;

uniform sampler2D ourTexture;
uniform sampler2D detailTexture;

void main()
{
    if (Height > -0.0) {
        discard;}
    vec4 MapColor = texture(ourTexture, TexCoord1);
    vec4 DetailColor = texture(detailTexture, TexCoord2);
    FragColor = mix(MapColor, DetailColor, 0.5);
}