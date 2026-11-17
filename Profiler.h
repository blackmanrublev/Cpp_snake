#pragma once

#include <deque>
#include <chrono>
#include <string>
#include <iostream>

class Profiler
{
    std::deque<std::chrono::steady_clock::time_point> start_times;
    std::deque<std::chrono::steady_clock::time_point> stop_times;
    std::deque<std::string> names;
    int size = 0;

    public:
        Profiler();

        void start(std::string _name);
        
        void stop();

        void report();

        void reset();
};
