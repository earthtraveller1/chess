#version 410 core
out vec4 out_color;

in vec2 uv;
in vec4 color;
in float texture_unit;

uniform sampler2D texture_samplers[32];

void main()
{
    if (texture_unit >= 0.0)
    {
        vec4 texture_color = texture(texture_samplers[int(texture_unit)], uv);
        
        if (texture_color.x < 0.5)
        {
            out_color = texture_color + color;
        }
        else if (texture_color.x > 0.5)
        {
            out_color = texture_color - color;
        }
    }
    else 
    {
        out_color = color;
    }
}