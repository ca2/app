//Created by camilo on 2021-07-24 14:00 BRT <3ThomasBorregaardSorensen!!


#include "memory_management.h"


//#include "acme/primitive/collection/allocator.h"


//#include "acme/primitive/collection/array.h"


#include "acme/memory/typed.h"
#include "acme/memory/typed_memory.h"


#include "acme/primitive/collection/atom_map.h"
#include "acme/exception/__string.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/platform.h"
#include "acme/parallelization/synchronous_lock.h"

//
//#define __HEAP_NAMESPACE_PREFIX(name) __PREFIX_UNDERSCORE(HEAP_NAMESPACE_PREFIX,name)
//#define __HEAP_NAMESPACE_SUFFIX(name) __PREFIX_UNDERSCORE(name,HEAP_NAMESPACE_PREFIX)
//#define HEAP_NAMESPACE __HEAP_NAMESPACE_PREFIX(memory_allocate_heap)
//#define HEAP_ENUMERATE __HEAP_NAMESPACE_SUFFIX(e_memory_heap)
//
//namespace HEAP_NAMESPACE
//{
//
//
//
////   #include "__aligned_memory_allocate.h"
////   #include "__unaligned_memory_allocate.h"
////   #include "__memory_allocate.h"
//   
//   #include "__plex.h"
//   #include "__plex_heap.h"
//   #include "__plex_heap_impl.h"
//
//
//   extern plex_heap_alloc_array* g_pheap;
//
//   extern critical_section* g_pmutexSystemHeap;
//
//
//} // namespace HEAP_NAMESPACE
//
//
//
