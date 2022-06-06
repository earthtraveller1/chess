#version 330 core
layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_uv;

out vec2 uv;

uniform bool flipped;

float flip(float p_original, float p_pivot)
{
    float distance_from_pivot = abs(p_pivot - p_original);
    
    if (p_original < p_pivot)
    {
        return p_pivot + distance_from_pivot;
    }
    else if (p_original > p_pivot)
    {
        return p_pivot - distance_from_pivot;
    }
    else 
    {
        return 0.0;
    }
}

void main()
{
    if (flipped)
    {
        gl_Position = vec4(a_position.x, flip(a_position.y, 0.0), 0.0, 1.0);
    }
    else 
    {
        gl_Position = vec4(a_position, 0.0, 1.0);
    }
    
    uv = a_uv;
}