#ifndef FPS_TIMER_H_
#define FPS_TIMER_H_

class FPSTimer
{
public:
    FPSTimer();
    ~FPSTimer();
    void start();
    void stop();
    void pause();
    void unpause();

    int get_stick();

    bool get_is_started();
    bool get_is_paused();

private:
    int start_tick;
    int pause_tick;

    bool is_started;
    bool is_paused;
};
#endif