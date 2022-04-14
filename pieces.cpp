#include "renderer.hpp"

#include <vector>
#include <array>

#include "pieces.hpp"

namespace 
{
    constexpr auto BORDER_WEIGHT { 0.1f };
    
    enum class piece_class_t
    {
        BLANK, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
    };
    
    enum class piece_army_t
    {
        WHITE, BLACK
    };
    
    // A struct to represent a single piece.
    struct piece_t
    {
        uint8_t column;
        uint8_t row;
        piece_class_t type;
        piece_army_t army;
    };
    
    std::vector<piece_t> vector_of_pieces;
    
    // The entire board, represented in the form a two-dimensional array.
    std::array<std::array<piece_t, 8>, 8> board;
    
    void draw_pawn(float p_x, float p_y, float p_red, float p_green, float p_blue)
    {
        renderer::draw_circle(p_x + .79f - BORDER_WEIGHT, p_y + .2f - BORDER_WEIGHT, .94f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + .95f - BORDER_WEIGHT, p_y + .96f - BORDER_WEIGHT, .63f + BORDER_WEIGHT * 2, .86f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + .38f - BORDER_WEIGHT, p_y + 1.59f - BORDER_WEIGHT, 1.75f + BORDER_WEIGHT * 2, .58f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);

        renderer::draw_circle(p_x + .79f, p_y + .2f, .94f, p_red, p_green, p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + .95f, p_y + .96f, .63f, .86f, p_red, p_green, p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + .38f, p_y + 1.59f, 1.75f, .58f, p_red, p_green, p_blue, 1.0f);
    }
}

void pieces::init()
{
    // Create the white pawns
    for (auto i { static_cast<uint8_t>(1) }; i <= 8; i++)
    {
        piece_t pawn {};
        pawn.army = piece_army_t::WHITE;
        pawn.column = i;
        pawn.row = 7;
        pawn.type = piece_class_t::PAWN;
        
        vector_of_pieces.push_back(pawn);
        
        board[i - 1][6] = pawn;
    }
    
    // Create the black pawns
    for (auto i { static_cast<uint8_t>(1) }; i <= 8; i++)
    {
        piece_t pawn {};
        pawn.army = piece_army_t::BLACK;
        pawn.column = i;
        pawn.row = 2;
        pawn.type = piece_class_t::PAWN;
        
        vector_of_pieces.push_back(pawn);
        
        board[i - 1][1] = pawn;
    }
    
    return;
}

void pieces::draw_pieces()
{
    for (const auto& column: board)
    {
        for (const auto& piece: column)
        {
            auto redness = 0.0f;
            auto greeness = 0.0f;
            auto blueness = 0.0f;
            
            switch (piece.army)
            {
                case piece_army_t::WHITE:
                    redness = 1.0f;
                    greeness = 1.0f;
                    blueness = 1.0f;
                    break;
                case piece_army_t::BLACK:
                    redness = 0.0f;
                    greeness = 0.0f;
                    blueness = 0.0f;
                    break;
            }
            
            switch (piece.type)
            {
                case piece_class_t::PAWN:
                    draw_pawn((piece.column * 2.5f) - 2.5f + 10.0f, (piece.row * 2.5f) - 2.5f + 5.0f, redness, greeness, blueness);
                    break;
            }
        }
    }
}