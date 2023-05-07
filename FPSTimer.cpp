#include "FPSTimer.h"
#include "Commonfunc.h"

FPSTimer ::FPSTimer()
{
    start_tick = 0;
    pause_tick = 0;
    is_started = false;
    is_paused = false;
}

FPSTimer ::~FPSTimer()
{
}

void FPSTimer ::start()
{
    is_started = true;
    is_paused = false;
    start_tick = SDL_GetTicks();
}

void FPSTimer ::stop()
{
    is_started = false;
    is_paused = false;
}
void FPSTimer ::pause()
{
    if ((is_started == true) && (is_paused == false))
    {
        is_paused = true;
        pause_tick = SDL_GetTicks();
    }
}
void FPSTimer ::unpause()
{
    if (is_paused == true)
    {
        is_paused = false;
        start_tick = SDL_GetTicks() - pause_tick;
        pause_tick = 0;
    }
}
int FPSTimer ::get_stick()
{
    if (is_started == true)
    {
        if (is_paused == true)
        {
            return pause_tick;
        }
        else
        {
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}

bool FPSTimer ::get_is_started()
{
    return is_started;
}
bool FPSTimer ::get_is_paused()
{
    return is_paused;
}
