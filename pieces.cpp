#include "renderer.hpp"

#include "pieces.hpp"

void pieces::draw_pawn(float p_x, float p_y)
{
    renderer::draw_circle(p_x + .79f, p_y + .2f, .94f, 1.0f, 1.0f, 1.0f, 1.0f);
    renderer::draw_colored_rectangle(p_x + .95f, p_y + .96f, .63f, .86f, 1.0f, 1.0f, 1.0f, 1.0f);
    renderer::draw_colored_rectangle(p_x + .38f, p_y + 1.59f, 1.75f, .58f, 1.0f, 1.0f, 1.0f, 1.0f);
}