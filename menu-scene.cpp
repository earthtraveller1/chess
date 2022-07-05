#include <GLFW/glfw3.h>

#include "scene-manager.hpp"
#include "utilities.hpp"
#include "game-scene.hpp"

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
    
    auto play_button_x { (8.0f - 3.0f) / 2.0f };
    auto play_button_y { (8.0f - 1.5f) / 2.0f };
    
    renderer_t::quad_t play_button {};
    
    if (m_button_manager.is_button_hovered(play_button_x, play_button_y, 3.0, 1.5))
    {
        play_button.color = { 0.7f, 0.7f, 0.7f, 0.7f };
    }
    else 
    {
        play_button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
    }
    
    play_button.position = { play_button_x, play_button_y };
    play_button.size = { 3.0f, 1.5f };
    play_button.uv.position = { 0.0f, 0.0f };
    play_button.uv.size = { 1.0f, 1.0f };
    play_button.texture = 1;
    
    m_renderer.draw_quad(play_button);
    
    m_renderer.end();
}

void menu_scene_t::on_mouse_click(int p_button, int p_action)
{
    auto play_button_x { (8.0f - 3.0f) / 2.0f };
    auto play_button_y { (8.0f - 1.5f) / 2.0f };
    
    if (m_button_manager.is_button_hovered(play_button_x, play_button_y, 3.0, 1.5) && p_button == GLFW_MOUSE_BUTTON_LEFT && p_action == GLFW_PRESS)
    {
        m_scene_manager.set_active(std::make_shared<game_scene_t>(m_window_width, m_window_height));
    }
}

void menu_scene_t::on_mouse_move(double p_xpos, double p_ypos)
{
    m_button_manager.update_mouse_positions((p_xpos / m_window_width) * 8.0, (p_ypos / m_window_height) * 8.0);
}