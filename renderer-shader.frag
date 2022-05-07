#version 330 core
out vec4 out_color;

in vec2 uv;
in vec4 color;
in float texture_unit;

uniform sampler2D texture_samplers[32];

void main()
{
    if (texture_unit != -1.0)
    {
        out_color = texture(texture_samplers[(int)texture_unit], uv) * color;
    }
    else 
    {
        out_color = color;
    }
}