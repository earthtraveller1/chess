#version 330 core

out vec4 fragment_color;

in vec4 vertex_color;
in vec2 local_position;
flat in int is_a_circle;

void main()
{
    if (is_a_circle > 0)
    {
        float opacity = 1.0;
        
        float my_distance = 1.0 - length(local_position);
        opacity = smoothstep(0.0, 0.01, my_distance);
        
        fragment_color = vec4(vertex_color.xyz, opacity);
    }
    else 
    {
        fragment_color = vertex_color;
    }
}