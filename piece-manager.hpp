#ifndef D3B264AE_83D2_4309_85D9_5D151A9D9EB3
#define D3B264AE_83D2_4309_85D9_5D151A9D9EB3

#include <array>

#include "renderer.hpp"

namespace chess
{
    class piece_manager_t
    {
    public:
        // Constructor
        piece_manager_t();
        
        // The position of a piece
        struct piece_position_t
        {
            uint8_t column { 0 };
            uint8_t row { 0 };
            
            inline bool operator!=(const piece_position_t& b)
            {
                return ((column != b.column) || (row != b.row));
            }
        };
        
        // A piece
        struct piece_t
        {
            piece_t() {}
            
            // Is the piece empty?
            bool is_empty { true };
            
            // Has the peice moved at all yet?
            bool has_moved { false };
            
            piece_position_t position;
            
            enum class army_e
            {
                WHITE = 0, BLACK
            } army { army_e::WHITE };
            
            enum class role_e
            {
                PAWN = 0, ROOK, KNIGHT, BISHOP, QUEEN, KING
            } role { role_e::PAWN };
        };
        
        // Start dragging if not already dragging, stop dragging if already dragging
        void set_dragging(bool dragging) noexcept;
        
        // Update the mouse position (needed for dragging)
        void update_mouse_position(double x, double y);
        
        // Render the pieces
        void render_pieces();
        
    private:
        // The renderer used to render the stuff.
        renderer_t m_renderer;
        
        // Dragging information
        bool m_is_dragging;
        piece_t m_dragged_piece;
        // The cursor positions are in a custom coordinate going from 0.0 to 7.0.
        double m_cursor_x;
        double m_cursor_y;
        
        // A 2D array representing the entire array of pieces on the board.
        std::array<std::array<piece_t, 8>, 8> m_pieces;
        
        // Get a piece from a specific location on the board
        inline piece_t& get_piece(const piece_position_t& position)
        {
            return m_pieces[position.column][position.row];
        }
        
        // Utility functions for drawing pieces
        void draw_piece(const piece_t& piece);
        
        // Utility function for drawing dragged piece
        void draw_dragged_piece();
        
        // Validate the move of a pawn (moved to a function since it's mechanic is so complicated)
        bool is_pawn_move_legal(piece_t::army_e army, bool has_moved, const piece_position_t& current_position, const piece_position_t& previous_position);
        
        // Returns if the specified move is legal or not.
        bool is_move_legal(const piece_t& piece, const piece_position_t& previous_position);
        
        // Returns if there's any non-empty pieces between two positions
        bool check_space_in_between(const piece_position_t& a, const piece_position_t& b);
        
        // Put pieces back into their starting place.
        void put_pieces_to_starting_place();
    };
}

#endif /* D3B264AE_83D2_4309_85D9_5D151A9D9EB3 */
