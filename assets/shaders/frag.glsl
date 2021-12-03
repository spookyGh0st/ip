#version 460 core
out vec4 color;
uniform usamplerBuffer tapeSampler;

void main()
{
    uvec4 tape = texelFetch(tapeSampler, 0);
    color = tape;
}