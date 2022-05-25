#include"LTime.h"

LTime::LTime()
{
    start_tick = 0;
    paused_tick = 0;

    is_paused_ = false;
    is_started_ = false;
}

LTime::~LTime()
{

}
void LTime::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick = SDL_GetTicks();
}

void LTime::stop()
{
    is_started_ = false;
    is_paused_ = false;
}
void LTime::paused()
{
    if(is_started_ == true && is_paused_ == false)
    {
        is_paused_ = true;
        paused_tick = SDL_GetTicks() - start_tick;
    }
}
void LTime::unpaused()
{
    if(is_paused_ == true)
    {
        is_paused_ = false;
        start_tick = SDL_GetTicks() - paused_tick;
        paused_tick = 0;
    }
}

int LTime::get_ticks()
{
    if(is_started_ == true)
    {
        if(is_paused_ == true)
        {
            return paused_tick;
        }
        else
        {
            return SDL_GetTicks() - start_tick;
        }
    }

    return 0;
}
bool LTime::is_started()
{
    return is_started_;
}
bool LTime::is_paused()
{
    return is_paused_;
}
