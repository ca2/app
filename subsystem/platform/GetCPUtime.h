// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

//#ifndef _GETCPUTIME_H_
//#define _GETCPUTIME_H_
#pragma once
#if defined(__APPLE__)
    #include <TargetConditionals.h>
#endif

// returns current process time of work in seconds
double getCPUTime();

// returns kernel time of work in seconds
double getKernelTime();

// returns current processor tick number
inline ::u64 rdtsc() {
  ::u32 lo, hi;
#if defined(__APPLE__)
    
    #if defined(__x86_64__) || defined(__i386__)

        // Intel Mac: use rdtsc
        //static inline uint64_t read_cycles()
        //{
            uint32_t lo, hi;

            __asm__ volatile (
                "rdtsc"
                : "=a"(lo), "=d"(hi)
            );

            return ((uint64_t)hi << 32) | lo;
        //}

    #elif defined(__aarch64__) || defined(__arm64__)

        // Apple Silicon: use virtual counter
        //static inline uint64_t read_cycles()
        //{
            uint64_t value;

            __asm__ volatile (
                "mrs %0, cntvct_el0"
                : "=r"(value)
            );

            return value;
       // }

#else

    #error Unsupported macOS architecture

#endif
#else
#ifdef __GNUC__
  asm  volatile ("rdtsc\n" : "=a" (lo), "=d" (hi));
#elif _MSC_VER
#ifdef _M_IX86
  __asm
  {
    rdtsc
    mov DWORD PTR [lo], eax
    mov DWORD PTR [hi], edx
  }
#else
  return 0;
#endif
   return ((::u64)hi << 32) | lo;
 
#else
  #error "Unsupported compiler"
#endif
#endif
return 0;
}

//#endif _GETCPUTIME_H_
