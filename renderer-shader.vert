#version 330 core
layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_local_position;
layout (location = 2) in vec4 a_color;
layout (location = 3) in int a_circle;

out vec4 vertex_color;
out vec2 local_position;
flat out int is_a_circle;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(a_position, 0.0, 1.0);
    vertex_color = a_color;
    local_position = a_local_position;
    is_a_circle = a_circle;
}