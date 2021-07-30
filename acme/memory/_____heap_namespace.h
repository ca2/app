//Created by camilo on 2021-07-24 14:00 BRT <3ThomasBorregaardSørensen!!


#define __PREFIX_HEAP_NAMESPACE(name) __PREFIX_UNDERSCORE(__EVALUATE_MACRO(HEAP_NAMESPACE_PREFIX),name)
#define HEAP_NAMESPACE __PREFIX_HEAP_NAMESPACE(memory_allocate_heap)


namespace HEAP_NAMESPACE
{


   #include "__aligned_memory_allocate.h"
   #include "__unaligned_memory_allocate.h"
   #include "__memory_allocate.h"
   
   #include "__plex.h"
   #include "__plex_heap.h"
   #include "__plex_heap_impl.h"


   extern plex_heap_alloc_array* g_pheap;

   extern critical_section* g_pmutexSystemHeap;


} // namespace HEAP_NAMESPACE



