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

#if !defined(_WIN32)
#include <time.h>
#endif

// returns current process time of work in seconds
::f64 getCPUTime();

// returns kernel time of work in seconds
::f64 getKernelTime();

// returns current processor tick number
inline ::u64 rdtsc() {
#ifdef __GNUC__

#if defined(__aarch64__) || defined(__arm64__)

  uint64_t val;
  asm volatile("mrs %0, cntvct_el0" : "=r"(val));
  return val;

#elif defined(__i386__) || defined(__x86_64__)
  ::u32 lo, hi;
  asm  volatile ("rdtsc\n" : "=a" (lo), "=d" (hi));
  return ((::u64)hi << 32) | lo;

#else
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
  {
     return (::u64)ts.tv_sec * 1000000000ull + (::u64)ts.tv_nsec;
  }
  return 0;

#endif

#elif _MSC_VER
#ifdef _M_IX86
  ::u32 lo, hi;
  __asm
  {
    rdtsc
    mov DWORD PTR [lo], eax
    mov DWORD PTR [hi], edx
  }
  return ((::u64)hi << 32) | lo;
#else
  return 0;
#endif
#else
  #error "Unsupported compiler"
#endif
}

//#endif _GETCPUTIME_H_
