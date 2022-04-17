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
    
    // The entire board, represented in the form a two-dimensional array.
    std::array<std::array<piece_t, 8>, 8> board;
    
    // Simple inline function to draw a shape with local coordinates
    inline void draw_local_rectangle(float p_global_x, float p_global_y, float p_local_x, float p_local_y, float p_width, float p_height, float p_red, float p_green, float p_blue)
    {
        renderer::draw_colored_rectangle(
            p_global_x + p_local_x,
            p_global_y + p_local_y,
            std::forward<float>(p_width),
            std::forward<float>(p_height),
            std::forward<float>(p_red),
            std::forward<float>(p_green),
            std::forward<float>(p_blue),
            1.0f
        );
    }
    
    // Simple inline function to draw an outline with local coordinates
    inline void draw_local_rectangle_outline(float p_global_x, float p_global_y, float p_local_x, float p_local_y, float p_width, float p_height, float p_red, float p_green, float p_blue)
    {
        draw_local_rectangle(
            std::forward<float>(p_global_x),
            std::forward<float>(p_global_y),
            p_local_x - BORDER_WEIGHT,
            p_local_y - BORDER_WEIGHT,
            p_width + BORDER_WEIGHT * 2,
            p_height + BORDER_WEIGHT * 2,
            std::forward<float>(p_red),
            std::forward<float>(p_green),
            std::forward<float>(p_blue)
        );
    }
    
    void draw_pawn(float p_x, float p_y, float p_red, float p_green, float p_blue)
    {
        renderer::draw_circle(p_x + .79f - BORDER_WEIGHT, p_y + .2f - BORDER_WEIGHT, .94f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + .95f - BORDER_WEIGHT, p_y + .96f - BORDER_WEIGHT, .63f + BORDER_WEIGHT * 2, .86f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + .38f - BORDER_WEIGHT, p_y + 1.59f - BORDER_WEIGHT, 1.75f + BORDER_WEIGHT * 2, .58f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);

        renderer::draw_circle(p_x + .79f, p_y + .2f, .94f, p_red, p_green, p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + .95f, p_y + .96f, .63f, .86f, p_red, p_green, p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + .38f, p_y + 1.59f, 1.75f, .58f, p_red, p_green, p_blue, 1.0f);
    }
    
    void draw_rook(float p_x, float p_y, float p_red, float p_green, float p_blue)
    {
        renderer::draw_colored_rectangle(p_x + 0.42f - BORDER_WEIGHT, p_y + 0.31f - BORDER_WEIGHT, 0.25f + BORDER_WEIGHT * 2, 0.34f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + 0.96f - BORDER_WEIGHT, p_y + 0.31f - BORDER_WEIGHT, 0.25f + BORDER_WEIGHT * 2, 0.34f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + 1.45f - BORDER_WEIGHT, p_y + 0.31f - BORDER_WEIGHT, 0.25f + BORDER_WEIGHT * 2, 0.34f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + 1.84f - BORDER_WEIGHT, p_y + 0.31f - BORDER_WEIGHT, 0.25f + BORDER_WEIGHT * 2, 0.34f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue, 1.0f);
        
        draw_local_rectangle(p_x, p_y, 0.41f - BORDER_WEIGHT, 0.56f - BORDER_WEIGHT, 1.68f + BORDER_WEIGHT * 2, 0.19f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue);
        draw_local_rectangle(p_x, p_y, 0.79f - BORDER_WEIGHT, 0.75f - BORDER_WEIGHT, 0.94f + BORDER_WEIGHT * 2, 1.26f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue);
        draw_local_rectangle(p_x, p_y, 0.42f - BORDER_WEIGHT, 2.01f - BORDER_WEIGHT, 1.68f + BORDER_WEIGHT * 2, 0.20f + BORDER_WEIGHT * 2, 1.0f - p_red, 1.0f - p_green, 1.0f - p_blue);
        
        renderer::draw_colored_rectangle(p_x + 0.42f, p_y + 0.31f, 0.25f, 0.34f, p_red, p_green, p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + 0.96f, p_y + 0.31f, 0.25f, 0.34f, p_red, p_green, p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + 1.45f, p_y + 0.31f, 0.25f, 0.34f, p_red, p_green, p_blue, 1.0f);
        renderer::draw_colored_rectangle(p_x + 1.84f, p_y + 0.31f, 0.25f, 0.34f, p_red, p_green, p_blue, 1.0f);
        
        draw_local_rectangle(p_x, p_y, 0.41f, 0.56f, 1.68f, 0.19f, p_red, p_green, p_blue);
        draw_local_rectangle(p_x, p_y, 0.79f, 0.75f, 0.94f, 1.26f, p_red, p_green, p_blue);
        draw_local_rectangle(p_x, p_y, 0.42f, 2.01f, 1.68f, 0.20f, p_red, p_green, p_blue);
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
        
        board[i - 1][1] = pawn;
    }
    
    // The rooks
    piece_t rook {};
    rook.army = piece_army_t::WHITE;
    rook.column = 1;
    rook.row = 8;
    rook.type = piece_class_t::ROOK;
    
    board[0][7] = rook;
    
    rook.column = 8;
    
    board[7][7] = rook;
    
    rook.army = piece_army_t::BLACK;
    rook.row = 1;
    
    board[7][0] = rook;
    
    rook.column = 1;
    
    board[0][0] = rook;
    
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
                case piece_class_t::ROOK:
                    draw_rook((piece.column * 2.5f) - 2.5f + 10.0f, (piece.row * 2.5f) - 2.5f + 5.0f, redness, greeness, blueness);
                    break;
            }
        }
    }
}