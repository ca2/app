// Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
// Refactoring 2023-11-23 05:50 <3ThomasBorregaardSoerensen!!
#include "framework.h"

//
//class CLASS_DECL_ACME clib_memory_allocator
//{
//public:
//
//   inline static void * allocate(memsize s) { return ::malloc(s); }
//   inline static void * realloc(void * p, memsize s) { return ::realloc(p, s); }
//   inline static void free(void * p) { ::free(p); }
//   inline static void zero(void * p) { throw error_unsupported_function; }
//
//};
//
//
//namespace heap
//{
//
//   class CLASS_DECL_ACME memory_allocator :
//      virtual public allocator
//   {
//   public:
//
//      inline static void * allocate(memsize s) { return ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(s); }
//      inline static void * realloc(void * p, memsize s) { return memory_reallocate(p, s); }
//      inline static void free(void * p) { ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(p); }
//      inline static void zero(void * p) { ::zero(p, memory_size(p)); }
//
//   };
//
//
//   ::pointer < allocator > heap::_create_memory_allocator()
//   {
//
//      return __new memory_allocator();
//
//   }
//
//}//
