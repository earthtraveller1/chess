#ifndef B9A404AE_F507_4769_B0DA_4E65F8AE3E5F
#define B9A404AE_F507_4769_B0DA_4E65F8AE3E5F

#include <memory>
#include "scene.hpp"

namespace chess
{
    class scene_manager_t
    {
    public:
        inline scene_manager_t(std::shared_ptr<scene_t> p_initial_scene):
            m_active_scene(p_initial_scene)
        {
            
        }
        
        inline void set_active(std::shared_ptr<scene_t> p_new_active)
        {
            m_active_scene = p_new_active;
        }
        
        inline void update_active() const
        {
            m_active_scene->update();
        }
        
        inline void render_active() const 
        {
            m_active_scene->render();
        }
        
    private:
        std::shared_ptr<scene_t> m_active_scene;
    };
}

#endif /* B9A404AE_F507_4769_B0DA_4E65F8AE3E5F */
