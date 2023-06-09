//Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "string_memory_allocate.h"
#include "acme/primitive/primitive/_c_memory.h"


class CLASS_DECL_ACME string_memory_allocator
{
public:


   inline static void* allocate(memsize s) { return string_memory_allocate(s); }
   inline static void* reallocate(void* p, memsize s) { return string_memory_reallocate(p, s); }
   inline static void free(void* p) { string_memory_free(p); }
   inline static void zero(void* p) { ::zero(p, string_memory_size(p)); }
   inline static memsize size(void * p) { return string_memory_size(p); }


};



