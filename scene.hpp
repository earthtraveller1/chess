#ifndef E908B7A4_6FBD_42F8_8161_D6810EE55C2E
#define E908B7A4_6FBD_42F8_8161_D6810EE55C2E

#include "utilities.hpp"

namespace chess
{
    // An interface class that all scenes will inherit
    class scene_t
    {
    public:
        scene_t() = default;
        
        virtual void update() {};
        
        virtual void render() {};
        
        virtual void on_mouse_click(int button, int action)
        {
            UNUSED_PARAM(button);
            UNUSED_PARAM(action);
        }
        
        virtual void on_mouse_move(double xpos, double ypos) 
        {
            UNUSED_PARAM(xpos);
            UNUSED_PARAM(ypos);
        }
        
        virtual void on_key_event(int, int) {}
        
        virtual ~scene_t() {}
    };
}

#endif /* E908B7A4_6FBD_42F8_8161_D6810EE55C2E */
