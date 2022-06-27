#ifndef TIMER_H
#define TIMER_H


#include <chrono> // для функций из std::chrono

class Timer
{
private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer();

    void reset();

    double elapsed() const;
};


#endif // TIMER_H
