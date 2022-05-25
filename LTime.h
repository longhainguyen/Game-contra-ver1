#ifndef LTIME_H_
#define LTIME_H_

#include"unit.h"

class LTime
{
public:
    LTime();
    ~LTime();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();

    bool is_started();
    bool is_paused();

private:
    int start_tick;
    int paused_tick;

    bool is_paused_;
    bool is_started_;


};

#endif // LTIME_H_
