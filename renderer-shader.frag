#version 330 core

out vec4 fragment_color;

in vec4 vertex_color;
in vec2 local_position;
flat in int is_a_circle;

void main()
{
    if (is_a_circle != 0)
    {
        fragment_color = vertex_color;
    }
    else
    {
        fragment_color = vertex_color;
    }
}