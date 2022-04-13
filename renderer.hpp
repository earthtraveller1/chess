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
    void draw_colored_rectangle(float pos_x, float pos_y, float width, float height, float red, float green, float blue, float alpha);
    
    // Draw a solid colored rectangle that's rotated.
    void draw_rotated_colored_rectangle(float pos_x, float pos_y, float width, float height, float angle, float red, float green, float blue, float alpha);
    
    // Draw a circle.
    void draw_circle(float x, float y, float radius, float red, float green, float blue, float alpha);
    
    // Draw an ellipse.
    void draw_ellipse(float pos_x, float pos_y, float width, float height, float red, float green, float blue, float alpha);
    
    // Draw an ellipse.
    void draw_rotated_ellipse(float pos_x, float pos_y, float width, float height, float angle, float red, float green, float blue, float alpha);
    
    // Stop drawing.
    void end();
    
    // Deallocate resources used by the renderer.
    void cleanup();
}

#endif /* C9ED662A_A3A4_4703_96CE_E18151D35843 */
