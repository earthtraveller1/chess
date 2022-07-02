#ifndef E0D9A764_133F_4775_AF74_EF790961EB7E
#define E0D9A764_133F_4775_AF74_EF790961EB7E

#include "scene.hpp"
#include "board.hpp"
#include "piece-manager.hpp"

namespace chess
{
    class game_scene_t: public scene_t
    {
    public:
        game_scene_t(uint16_t p_window_width, uint16_t p_window_height);
        
        void render() override;
        
        void on_mouse_click(int button, int action) override;
        
        void on_mouse_move(double xpos, double ypos) override;
        
    private:
        // Renders the chessboard background.
        board_t m_board;
        
        // Manages and renders the pieces.
        piece_manager_t m_piece_manager;
        
        // The width and height of the window (for coordinate conversion)
        uint16_t m_window_width;
        uint16_t m_window_height;
    };
}

#endif /* E0D9A764_133F_4775_AF74_EF790961EB7E */
