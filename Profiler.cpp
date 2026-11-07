#include "Profiler.h"

Profiler::Profiler() = default;

void Profiler::start(std::string _name)
{
    size++;
    names.push_back(_name);
    start_times.push_back(std::chrono::steady_clock::now());
}

void Profiler::stop()
{
    stop_times.push_back(std::chrono::steady_clock::now());
}

void Profiler::report()
{
    
    std::cout << "- - - - - - - - - - - - - - - - - - -" << std::endl;
    for (int i = 0; i < size; i++)
    {
        auto time_taken = std::chrono::duration<double, std::milli>(stop_times[i] - start_times[i]).count();

        std::cout << names[i] << " - " << time_taken << "ms" << std::endl;
    }
}

void Profiler::reset()
{
    for (int i = 0; i < size; i++)
    {
        names.pop_front();
        start_times.pop_front();
        stop_times.pop_front();
    }  
    size = 0; 
}