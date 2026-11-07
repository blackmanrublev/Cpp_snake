#pragma once

#include <deque>
#include <chrono>
#include <string>
#include <iostream>

class Profiler
{
    std::deque<std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration>> start_times;
    std::deque<std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration>> stop_times;
    std::deque<std::string> names;
    int size = 0;

    public:
        Profiler();

        void start(std::string _name);
        
        void stop();

        void report();

        void reset();
};
