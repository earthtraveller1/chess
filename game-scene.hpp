#ifndef E0D9A764_133F_4775_AF74_EF790961EB7E
#define E0D9A764_133F_4775_AF74_EF790961EB7E

#include "board.hpp"
#include "button-manager.hpp"
#include "piece-manager.hpp"
#include "renderer.hpp"
#include "scene.hpp"

namespace chess
{
class scene_manager_t;

class game_scene_t : public scene_t
{
  public:
    game_scene_t(scene_manager_t &scene_manager, uint16_t p_window_width,
                 uint16_t p_window_height);

    void render() override;

    void on_mouse_click(int button, int action) override;

    void on_mouse_move(double xpos, double ypos) override;

    void on_key_event(int key, int action) override;

  private:
    // Renders the chessboard background.
    board_t m_board;

    // For restarting the scene.
    scene_manager_t &m_scene_manager;

    // Manages and renders the pieces.
    piece_manager_t m_piece_manager;

    // Renders pretty much everything else.
    renderer_t m_renderer;

    // For handling the buttons.
    button_manager_t m_button_manager;

    // Is the game paused?
    bool m_is_paused;

    // The width and height of the window (for coordinate conversion)
    uint16_t m_window_width;
    uint16_t m_window_height;
};
} // namespace chess

#endif /* E0D9A764_133F_4775_AF74_EF790961EB7E */
