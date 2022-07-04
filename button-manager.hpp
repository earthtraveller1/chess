#ifndef AD335E88_220E_4FAE_A201_B1E8D140DFD0
#define AD335E88_220E_4FAE_A201_B1E8D140DFD0

namespace chess
{
    class button_manager_t
    {
    public:
        button_manager_t() = default;
        
        // Update the mouse positions
        inline void update_mouse_positions(double x, double y)
        {
            m_mouse_x = x;
            m_mouse_y = y;
        }
        
        // Check the mouse pointer is hovering over a button.
        inline bool is_button_hovered(double pos_x, double pos_y, double width, double height)
        {
            return ((m_mouse_x > pos_x) && (m_mouse_x < (pos_x + width))) && ((m_mouse_y > pos_y) && (m_mouse_y < (pos_y + height)));
        }
        
    private:
        // The mouse positions
        double m_mouse_x;
        double m_mouse_y;
    };
}

#endif /* AD335E88_220E_4FAE_A201_B1E8D140DFD0 */
