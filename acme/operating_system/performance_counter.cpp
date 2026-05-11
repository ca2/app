//
//  performance_counter.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"


#include <stdint.h>

#if defined(_WIN32)
    #define NOMINMAX
    #include <windows.h>

    inline uint64_t performance_counter()
    {
        LARGE_INTEGER v;
        QueryPerformanceCounter(&v);
        return static_cast<uint64_t>(v.QuadPart);
    }

    inline uint64_t PerfFrequency()
    {
        LARGE_INTEGER v;
        QueryPerformanceFrequency(&v);
        return static_cast<uint64_t>(v.QuadPart);
    }

#elif defined(__APPLE__)
    #include <mach/mach_time.h>

    inline uint64_t performance_counter()
    {
        return mach_absolute_time();
    }

    inline uint64_t PerfFrequency()
    {
        static mach_timebase_info_data_t info;
        mach_timebase_info(&info);

        return (1000000000ull * info.denom) / info.numer;
    }

#else
    #include <time.h>

    inline uint64_t performance_counter()
    {
        timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);

        return uint64_t(ts.tv_sec) * 1000000000ull +
               uint64_t(ts.tv_nsec);
    }

    inline uint64_t performance_counter_frequency()
    {
        return 1000000000ull;
    }

#endif
