//
//  performance_counter.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "performance_counter.h"

#include <stdint.h>

#if defined(_WIN32)
    #define NOMINMAX
    #include <windows.h>

    ::u64 performance_counter()
    {
        LARGE_INTEGER v;
        QueryPerformanceCounter(&v);
        return static_cast<uint64_t>(v.QuadPart);
    }

    ::u64 PerfFrequency()
    {
        LARGE_INTEGER v;
        QueryPerformanceFrequency(&v);
        return static_cast<uint64_t>(v.QuadPart);
    }

#elif defined(__APPLE__)
    #include <mach/mach_time.h>

    ::u64 performance_counter()
    {
        return mach_absolute_time();
    }

::u64 PerfFrequency()
    {
        static mach_timebase_info_data_t info;
        mach_timebase_info(&info);

        return (1000000000ull * info.denom) / info.numer;
    }

#else
    #include <time.h>

    ::u64 performance_counter()
    {
        timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);

        return uint64_t(ts.tv_sec) * 1000000000ull +
               uint64_t(ts.tv_nsec);
    }

    ::u64 performance_counter_frequency()
    {
        return 1000000000ull;
    }

#endif
