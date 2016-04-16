#ifndef _TIMER_H
#define _TIMER_H

class Timer
{
    public:
        Timer();

        void start();
        void stop();
        void pause();
        void unpause();

        uint32_t getTicks();

        bool isPaused() { return paused; }
        bool isRunning() { return running; }

    private:
        // ticks since the timer was started
        uint32_t startTicks;

        // ticks since the timer was paused
        uint32_t pausedTicks;

        bool paused;
        bool running;
};

#endif