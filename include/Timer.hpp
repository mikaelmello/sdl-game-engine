#ifndef TIMER_H
#define TIMER_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class Timer {
    public:
        Timer();

        void Update(float dt);

        void Restart();

        float Get();
    private:
        float time;
};

#endif
