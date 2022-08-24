#ifndef B9A404AE_F507_4769_B0DA_4E65F8AE3E5F
#define B9A404AE_F507_4769_B0DA_4E65F8AE3E5F

#include "scene.hpp"
#include <memory>

namespace chess
{
class scene_manager_t
{
  public:
    inline scene_manager_t(std::shared_ptr<scene_t> p_initial_scene)
        : m_active_scene(p_initial_scene)
    {
    }

    inline void set_active(std::shared_ptr<scene_t> p_new_active)
    {
        m_active_scene = p_new_active;
    }

    inline void update_active() const { m_active_scene->update(); }

    inline void render_active() const { m_active_scene->render(); }

    inline void active_on_mouse_click(int p_button, int p_action)
    {
        m_active_scene->on_mouse_click(p_button, p_action);
    }

    inline void active_on_mouse_move(double p_xpos, double p_ypos)
    {
        m_active_scene->on_mouse_move(p_xpos, p_ypos);
    }

    inline void active_on_key_event(int key, int action)
    {
        m_active_scene->on_key_event(key, action);
    }

  private:
    std::shared_ptr<scene_t> m_active_scene;
};
} // namespace chess

#endif /* B9A404AE_F507_4769_B0DA_4E65F8AE3E5F */
