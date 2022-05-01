#include "window.hpp"
#include "utilities.hpp"

#include "application.hpp"

using chess::application_t;

application_t::application_t(): m_window(window_t::get_instance())
{
    m_window.show();
}

void application_t::update(double p_delta_time)
{
    UNUSED_PARAM(p_delta_time);
}

void application_t::render()
{
    m_window.update();
}

bool application_t::is_open() const
{
    return m_window.is_open();
}

application_t::~application_t()
{
    
}