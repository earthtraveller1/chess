#ifndef BB8F30B8_A881_40E4_B62B_1F740D539CD1
#define BB8F30B8_A881_40E4_B62B_1F740D539CD1

namespace chess
{
    // Thrown when the game exits.
    struct exit_exception_t {};
    
    // A basic application class to encapsulate most 
    class application_t
    {
    public:
        application_t();
        
        void update(double delta_time);
        
        void render();
        
        void is_open() const;
        
        ~application_t();
    };
}

#endif /* BB8F30B8_A881_40E4_B62B_1F740D539CD1 */
