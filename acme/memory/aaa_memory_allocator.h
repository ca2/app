////Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
//#pragma once
//
//
//class CLASS_DECL_ACME clib_memory_allocator
//{
//public:
//
//   inline static void* allocate(memsize s) { return ::malloc(s); }
//   inline static void* realloc(void* p, memsize s) { return ::realloc(p, s); }
//   inline static void free(void* p) { ::free(p); }
//   inline static void zero(void* p) { throw error_unsupported_function; }
//
//};
//
//
//class CLASS_DECL_ACME memory_allocator
//{
//public:
//
//   inline static void* allocate(memsize s) { return ::heap::management::memory(::heap::e_memory_main)->allocate(s); }
//   inline static void* realloc(void* p, memsize s) { return memory_reallocate(p, s); }
//   inline static void free(void* p) { ::heap::management::memory(::heap::e_memory_main)->free(p); }
//   inline static void zero(void* p) { ::zero(p, memory_size(p)); }
//
//};
//
//
