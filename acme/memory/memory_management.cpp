//Created by camilo on 2021-07-29 18:23 BRT <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "memory_management.h"
#include "memory_allocate.h"
#include "secondary_memory_allocate.h"
#include "array_memory_allocate.h"
#include "property_memory_allocate.h"
#include "string_memory_allocate.h"


memory_management g_memorymanagement;

#define DO_FOR_ALL_HEAPS(todo) \
todo(main); \
todo(secondary); \
todo(array); \
todo(property); \
todo(string)


#define DECLARE_MEMORY_HEAP(name) \
   namespace  __PREFIX_UNDERSCORE(name, memory_allocate_heap) \
{ \
   void initialize(); \
   void finalize(); \
} \
   void __PREFIX_UNDERSCORE(name, initialize_memory_management)(memory_heap * pmemoryheap)

DO_FOR_ALL_HEAPS(DECLARE_MEMORY_HEAP);
//DECLARE_INITIALIZE_MEMORY_MANAGEMENT(main);
//DECLARE_INITIALIZE_MEMORY_MANAGEMENT(secondary);
//DECLARE_INITIALIZE_MEMORY_MANAGEMENT(array);
//DECLARE_INITIALIZE_MEMORY_MANAGEMENT(property);
//DECLARE_INITIALIZE_MEMORY_MANAGEMENT(string);


#define INITIALIZE_MEMORY_MANAGEMENT(name) \
   __PREFIX_UNDERSCORE(name, initialize_memory_management)(&g_memorymanagement.m_heapa[__PREFIX_UNDERSCORE(e_memory_heap, name)]);

#define INITIALIZE_MEMORY_HEAP(name) \
   ::__PREFIX_UNDERSCORE(name, memory_allocate_heap)::initialize()

#define FINALIZE_MEMORY_HEAP(name) \
   ::__PREFIX_UNDERSCORE(name, memory_allocate_heap)::finalize()

void initialize_memory_management()
{

   DO_FOR_ALL_HEAPS(INITIALIZE_MEMORY_MANAGEMENT);
   //INITIALIZE_MEMORY_MANAGEMENT(main);
   //INITIALIZE_MEMORY_MANAGEMENT(secondary);
   //INITIALIZE_MEMORY_MANAGEMENT(array);
   //INITIALIZE_MEMORY_MANAGEMENT(property);
   //INITIALIZE_MEMORY_MANAGEMENT(string);

   DO_FOR_ALL_HEAPS(INITIALIZE_MEMORY_HEAP);

}


void finalize_memory_management()
{

   DO_FOR_ALL_HEAPS(FINALIZE_MEMORY_HEAP);

}


CLASS_DECL_ACME void * manage_memory_reallocate(enum_memory_heap ememoryheap, void* p, memsize nSize)
{

   return g_memorymanagement.m_heapa[ememoryheap].m_pfnMemoryReallocate(p, nSize);

}


CLASS_DECL_ACME void manage_memory_free(enum_memory_heap ememoryheap, void* p)
{

   g_memorymanagement.m_heapa[ememoryheap].m_pfnMemoryFree(p);

}



