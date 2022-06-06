#ifndef BB8F30B8_A881_40E4_B62B_1F740D539CD1
#define BB8F30B8_A881_40E4_B62B_1F740D539CD1

#include "board.hpp"
#include "piece-manager.hpp"

namespace chess
{
    class window_t;
    
    // Thrown when the game exits.
    struct exit_exception_t {};
    
    // A basic application class to encapsulate most 
    class application_t
    {
    public:
        application_t();
        
        // Prevent copying
        application_t(application_t&) = delete;
        application_t& operator=(application_t&) = delete;
        
        void update(double delta_time);
        
        void render();
        
        bool is_open() const;
        
        ~application_t();
        
    private:
        window_t& m_window;
        
        struct context_debugger
        {
            context_debugger();
        } m_context_debugger;
        
        board_t m_board;
        
        piece_manager_t m_piece_manager;
    };
}

#endif /* BB8F30B8_A881_40E4_B62B_1F740D539CD1 */
