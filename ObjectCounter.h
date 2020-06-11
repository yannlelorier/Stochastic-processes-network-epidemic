/*------------------------------------------------- ObjectCounter.h ------
    |   Purpose: Useful counter used by the gillespie.cpp function to
    |       set boundaries for some functions.
    |
    |   Developers:  
    |       Carlos García - https://github.com/cxrlos
    |       Victor Coeto - https://github.com/vcoetoG
    |       Yann Le Lorier - https://github.com/yannlelorier
    |
    *-------------------------------------------------------------------*/

#ifndef OBJECT_COUNTER_H
#define OBJECT_COUNTER_H

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <math.h>
#include <random>
#include <fstream>
#include <string>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <csignal>

template<typename T>
class Counter {
    public:
        Counter() { ++count; }
        Counter(const Counter&) { ++count; }
        ~Counter() { --count; }

        static size_t howMany()
        { return count; }
    private:
        static size_t count;
};

template<typename T>
size_t 
Counter<T>::count = 0;

#endif
