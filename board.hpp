#ifndef E942771D_AF05_461C_B90D_C920CF1D3BAF
#define E942771D_AF05_461C_B90D_C920CF1D3BAF

#include <cstdint>

namespace chess
{
class board_t
{
  public:
    board_t();

    // No copying allowed, sir
    board_t(board_t &) = delete;
    board_t &operator=(board_t &) = delete;

    void render();

    void set_flipped(bool is_flipped) noexcept;

    ~board_t();

  private:
    // The shader program used to render the board.
    uint32_t m_shader_program;

    // The mesh resources
    uint32_t m_vao;
    uint32_t m_vbo;
    uint32_t m_ebo;

    // The chessboard texture
    uint32_t m_texture;
};
} // namespace chess

#endif /* E942771D_AF05_461C_B90D_C920CF1D3BAF */
