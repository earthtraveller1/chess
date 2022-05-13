#ifndef D3B264AE_83D2_4309_85D9_5D151A9D9EB3
#define D3B264AE_83D2_4309_85D9_5D151A9D9EB3

#include <map>
#include <vector>

#include "renderer.hpp"

namespace chess
{
    class piece_manager_t
    {
    public:
        // Constructor
        piece_manager_t();
        
        // Render the pieces
        void render_pieces();
        
    private:
        // The renderer used to render the stuff.
        renderer_t m_renderer;
        
        // The pieces that can be renderered by the renderer.
        renderer_t::quad_t m_pawn;
        
        // The position of a piece
        struct piece_position_t
        {
            piece_position_t() {}
            
            int row { 0 };
            int column { 0 };
        };
        
        // A piece
        struct piece_t
        {
            piece_t() {}
            
            piece_position_t position;
            
            enum army_e
            {
                WHITE, BLACK
            } army;
            
            enum role_e
            {
                PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
            } role;
        };
        
        // A map of all the positions to the index in the array.
        std::map<piece_position_t, uint8_t> m_piece_indices;
        
        // A list of all the pieces.
        std::vector<piece_t> m_pieces;
    };
}

#endif /* D3B264AE_83D2_4309_85D9_5D151A9D9EB3 */
