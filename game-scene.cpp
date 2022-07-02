#include "option-loader.hpp"
#include <GLFW/glfw3.h>

#include "game-scene.hpp"

using chess::game_scene_t;

game_scene_t::game_scene_t(uint16_t p_window_width, uint16_t p_window_height):
    m_board(),
    m_piece_manager(m_board, option_loader_t("options.txt").get_option_value("FlipBoardOnMove") == "true"),
    m_window_width(p_window_width),
    m_window_height(p_window_height)
{
    
}

void game_scene_t::render()
{
    m_board.render();
    m_piece_manager.render_pieces();
}

void game_scene_t::on_mouse_click(int p_button, int p_action)
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

void game_scene_t::on_mouse_move(double xpos, double ypos)
{
    auto normalized_x { (xpos / m_window_height) * 8.0 };
    auto normalized_y { (ypos / m_window_height) * 8.0 };
    
    m_piece_manager.update_mouse_position(normalized_x, normalized_y);
}