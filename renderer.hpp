#ifndef C9ED662A_A3A4_4703_96CE_E18151D35843
#define C9ED662A_A3A4_4703_96CE_E18151D35843

#include <cstdint>

namespace renderer
{
    // Initialize the renderer
    void init();
    
    // Start rendering
    void begin();
    
    // Draw a solid colored rectangle
    void draw_colored_rectangle(float left, float up, float right, float bottom, float red, float green, float blue, float alpha);
    
    // Draw a circle.
    void draw_circle(float radius, float red, float green, float blue, float alpha);
    
    // Draw an ellipse.
    void draw_ellipse(float left, float up, float right, float bottom, float red, float green, float blue, float alpha);
    
    // Stop drawing.
    void end();
}

#endif /* C9ED662A_A3A4_4703_96CE_E18151D35843 */
