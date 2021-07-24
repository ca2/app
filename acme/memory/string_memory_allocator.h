#pragma once


#include "string_memory_allocate.h"


class string_memory_allocator
{
public:


   inline static void* allocate(memsize s) { return string_memory_allocate(s)); }
   inline static void* reallocate(void* p, memsize s) { return string_memory_reallocate(p, s); }
   inline static void free(void* p) { string_memory_free(p); }
   inline static void zero(void* p) { ::zero(p, string_memory_size(p)); }


};



