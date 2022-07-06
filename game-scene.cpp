#include "option-loader.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#include "game-scene.hpp"

using chess::game_scene_t;

game_scene_t::game_scene_t(uint16_t p_window_width, uint16_t p_window_height):
    m_board(),
    m_piece_manager(m_board, option_loader_t("options.txt").get_option_value("FlipBoardOnMove") == "true"),
    m_renderer(8, "renderer-shader.vert", "renderer-shader.frag"),
    m_is_paused(false),
    m_window_width(p_window_width),
    m_window_height(p_window_height)
{
    m_renderer.set_texture("paused-screen-title.png", 0);
    m_renderer.set_texture("resume-button.png", 1);
    m_renderer.set_texture("restart-button.png", 2);
}

void game_scene_t::render()
{
    m_board.render();
    m_piece_manager.render_pieces();
    
    if (m_is_paused)
    {
        m_renderer.begin();
        
        renderer_t::quad_t background {};
        background.position = { 0.0f, 0.0f };
        background.size = { 8.0f, 8.0f };
        background.color = { 0.0f, 0.0f, 0.0f, 0.7f };
        background.texture = -1;
        
        m_renderer.draw_quad(background);
        
        renderer_t::quad_t title {};
        title.position = { (8.0f - 5.0f) / 2, 1.0f };
        title.size = { 5.0f, (5.0f / 4.0f) };
        title.color = { 1.0f, 1.0f, 1.0f, 1.0f };
        title.uv.position = { 0.0f, 0.0f };
        title.uv.size = { 1.0f, 1.0f };
        title.texture = 0;
        
        m_renderer.draw_quad(title);
        
        renderer_t::quad_t resume_button {};
        resume_button.position = { (8.0f - 3.0f) / 2, 3.0f };
        resume_button.size = { 3.0f, (3.0f / 4.0f) };
        
        if (m_button_manager.is_button_hovered(resume_button.position.x, resume_button.position.y, resume_button.size.x, resume_button.size.y))
        {
            resume_button.color = { 0.7f, 0.7f, 0.7f, 1.0f };
        }
        else 
        {
            resume_button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
        }
        
        resume_button.uv.position = { 0.0f, 0.0f };
        resume_button.uv.size = { 1.0f, 1.0f };
        resume_button.texture = 1;
        
        m_renderer.draw_quad(resume_button);
        
        renderer_t::quad_t restart_button {};
        restart_button.position = { (8.0f - 3.0f) / 2, 4.0f };
        restart_button.size = { 3.0f, (3.0f / 4.0f) };
        
        if (m_button_manager.is_button_hovered(restart_button.position.x, restart_button.position.y, restart_button.size.x, restart_button.size.y))
        {
            restart_button.color = { 0.7f, 0.7f, 0.7f, 1.0f };
        }
        else 
        {
            restart_button.color = { 1.0f, 1.0f, 1.0f, 1.0f };
        }
        
        restart_button.uv.position = { 0.0f, 0.0f };
        restart_button.uv.size = { 1.0f, 1.0f };
        restart_button.texture = 2;
        
        m_renderer.draw_quad(restart_button);
        
        m_renderer.end();
    }
}

void game_scene_t::on_mouse_click(int p_button, int p_action)
{
    if (!m_is_paused)
    {
        if (p_button == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (p_action == GLFW_PRESS)
            {
                m_piece_manager.set_dragging(true);
            }
            else if (p_action == GLFW_RELEASE)
            {
                m_piece_manager.set_dragging(false);
            }
        }
    }
}

void game_scene_t::on_mouse_move(double xpos, double ypos)
{
    if (!m_is_paused)
    {
        auto normalized_x{(xpos / m_window_height) * 8.0};
        auto normalized_y{(ypos / m_window_height) * 8.0};

        m_piece_manager.update_mouse_position(normalized_x, normalized_y);
    }
    else
    {
        m_button_manager.update_mouse_positions((xpos / m_window_width) * 8.0, (ypos / m_window_height) * 8.0);
    }
}

void game_scene_t::on_key_event(int p_key, int p_action)
{
    if (p_key == GLFW_KEY_ESCAPE && p_action == GLFW_PRESS)
    {
        m_is_paused = !m_is_paused;
    }
}