#pragma once


class clib_memory_allocator
{
public:

   inline static void* allocate(memsize s) { return ::malloc(s); }
   inline static void* realloc(void* p, memsize s) { return ::realloc(p, s); }
   inline static void free(void* p) { ::free(p); }
   inline static void zero(void* p) { throw error_unsupported_function; }

};


class memory_allocator
{
public:

   inline static void* allocate(memsize s) { return memory_alloc(s); }
   inline static void* realloc(void* p, memsize s) { return memory_realloc(p, s); }
   inline static void free(void* p) { memory_free(p); }
   inline static void zero(void* p) { ::zero(p, memory_size(p)); }

};

