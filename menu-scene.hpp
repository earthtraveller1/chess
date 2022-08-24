#ifndef BB42151A_0746_4C10_8F47_6B3493B6D46F
#define BB42151A_0746_4C10_8F47_6B3493B6D46F

#include <cstdint>

#include "button-manager.hpp"
#include "renderer.hpp"
#include "scene.hpp"

namespace chess
{
class scene_manager_t;

class menu_scene_t : public scene_t
{
  public:
    menu_scene_t(scene_manager_t &scene_manager, uint16_t window_width,
                 uint16_t window_height);

    void update() override;

    void render() override;

    void on_mouse_click(int button, int action);

    void on_mouse_move(double xpos, double ypos);

  private:
    // The scene manager
    scene_manager_t &m_scene_manager;

    // For controlling the buttons
    button_manager_t m_button_manager;

    renderer_t m_renderer;

    uint16_t m_window_width;
    uint16_t m_window_height;
};
} // namespace chess

#endif /* BB42151A_0746_4C10_8F47_6B3493B6D46F */
