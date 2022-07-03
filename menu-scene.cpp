#include "scene-manager.hpp"
#include "utilities.hpp"

#include "menu-scene.hpp"

using chess::menu_scene_t;

menu_scene_t::menu_scene_t(scene_manager_t& p_scene_manager, uint16_t p_window_width, uint16_t p_window_height):
    m_scene_manager(p_scene_manager),
    m_renderer(2, "renderer-shader.vert", "renderer-shader.frag"),
    m_window_width(p_window_width),
    m_window_height(p_window_height)
{
    m_renderer.set_texture("main-menu-background.png", 0);
    m_renderer.set_texture("play-button.png", 1);
}

void menu_scene_t::update()
{
    
}

void menu_scene_t::render()
{
    m_renderer.begin();
    
    renderer_t::quad_t background {};
    background.color = { 1.0f, 1.0f, 1.0f, 1.0f };
    background.position = { 0.0f, 0.0f };
    background.size = { 8.0f, 8.0f };
    background.uv.position = { 0.0f, 0.0f };
    background.uv.size = { 1.0f, 1.0f };
    background.texture = 0;
    
    m_renderer.draw_quad(background);
    
    renderer_t::quad_t play_button {};
    play_button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
    play_button.position = { (8.0f - 3.0f) / 2.0f, (8.0f - 1.5f) / 2.0f };
    play_button.size = { 3.0f, 1.5f };
    play_button.uv.position = { 0.0f, 0.0f };
    play_button.uv.size = { 1.0f, 1.0f };
    play_button.texture = 1;
    
    m_renderer.draw_quad(play_button);
    
    m_renderer.end();
}

void menu_scene_t::on_mouse_click(int p_button, int p_action)
{
    UNUSED_PARAM(p_button);
    UNUSED_PARAM(p_action);
}

void menu_scene_t::on_mouse_move(double p_xpos, double p_ypos)
{
    UNUSED_PARAM(p_xpos);
    UNUSED_PARAM(p_ypos);
}