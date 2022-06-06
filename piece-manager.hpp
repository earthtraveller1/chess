#ifndef D3B264AE_83D2_4309_85D9_5D151A9D9EB3
#define D3B264AE_83D2_4309_85D9_5D151A9D9EB3

#include <array>

#include "renderer.hpp"
#include "move-checker.hpp"
#include "piece.hpp"
#include "piece-position.hpp"

namespace chess
{
    class board_t;
    
    class piece_manager_t
    {
    public:
        friend class move_checker_t;
        
        // Constructor
        piece_manager_t(board_t& board);
        
        // Start dragging if not already dragging, stop dragging if already dragging
        void set_dragging(bool dragging) noexcept;
        
        inline void set_board_orientation(bool is_black) noexcept {
            m_flipped = is_black;
        }
        
        // Update the mouse position (needed for dragging)
        void update_mouse_position(double x, double y);
        
        // Render the pieces
        void render_pieces();
        
    private:
        // The renderer used to render the stuff.
        renderer_t m_renderer;
        
        // The board that the pieces sits on
        board_t& m_board;
        
        // Dragging information
        bool m_is_dragging;
        piece_t m_dragged_piece;
        // The cursor positions are in a custom coordinate going from 0.0 to 7.0.
        double m_cursor_x;
        double m_cursor_y;
        
        // Is the board flipped?
        bool m_flipped;
        
        // A 2D array representing the entire array of pieces on the board.
        std::array<std::array<piece_t, 8>, 8> m_pieces;
        
        // The object that's responsible for checking moves.
        move_checker_t m_move_checker;
        
        // Get a piece from a specific location on the board
        inline piece_t& get_piece(const piece_position_t& position)
        {
            return m_pieces[position.column][position.row];
        }
        
        // Utility functions for drawing pieces
        void draw_piece(const piece_t& piece);
        
        // Utility function for drawing dragged piece
        void draw_dragged_piece();
        
        // Put pieces back into their starting place.
        void put_pieces_to_starting_place();
    };
}

#endif /* D3B264AE_83D2_4309_85D9_5D151A9D9EB3 */
