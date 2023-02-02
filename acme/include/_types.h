// Created by camilo on 2022-11-09 02:36 <3ThomasBorregaardSørensen!!
#pragma once


// Contains a 64-bit value representing the number
// of 100-nanosecond intervals since January 1, 1601 (UTC).
typedef u64 file_time_t;


constexpr ::u64 operator "" _uintmax(unsigned long long int u) { return u << 32LL; }


#include "acme/parallelization/_types.h"



