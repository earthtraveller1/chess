#version 330 core
out vec4 out_color;

in vec2 uv;

uniform sampler2D my_texture;

void main()
{
    out_color = texture(my_texture, uv);
}