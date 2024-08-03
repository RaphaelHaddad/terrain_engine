#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord1;
layout (location = 2) in vec2 aTexCoord2;

out float Height;
out vec3 Position;
out vec2 TexCoord1;
out vec2 TexCoord2;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Position = (view * model * vec4(aPos, 1.0)).xyz;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Height = (model * vec4(aPos, 1.0)).y;
    TexCoord1 = aTexCoord1;
    TexCoord2 = aTexCoord2;
}