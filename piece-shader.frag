#version 410 core
out vec4 out_color;

in vec2 uv;
in vec4 color;
in float texture_unit;

uniform sampler2D texture_samplers[32];

float invert_value(float p_value)
{
    if (p_value < 0.5)
    {
        return 0.5 + (0.5 - p_value);
    }
    else if (p_value > 0.5)
    {
        return 0.5 - (p_value - 0.5);
    }
}

vec4 invert_color(vec4 p_original)
{
    return vec4(invert_value(p_original.x), invert_value(p_original.y), invert_value(p_original.z), p_original.w);
}

void main()
{
    if (texture_unit >= 0.0)
    {
        vec4 texture_color = texture(texture_samplers[int(texture_unit)], uv);
        
        if (color.x < 0.5)
        {
            out_color = texture_color;
        }
        else if (color.y > 0.5)
        {
            out_color = invert_color(texture_color);
        }
    }
    else 
    {
        out_color = color;
    }
}