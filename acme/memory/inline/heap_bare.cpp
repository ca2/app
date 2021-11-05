#include "framework.h"





void * aligned_memory_allocate(size_t size, memsize align)
{

   throw_todo();

   return system_heap_alloc(size);

}

void * unaligned_memory_allocate(size_t size)
{

   return system_heap_alloc(size);

}


void * aligned_memory_allocate_debug(size_t size, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align)
{

   throw_todo();

   return system_heap_alloc(size);

}

void * unaligned_memory_allocate_debug(size_t size, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   return system_heap_alloc(size);

}




void * memory_allocate(memsize size)
{

   return system_heap_alloc(size);

}


void * memory_allocate_no_track(size_t size)
{

   return system_heap_alloc(size);

}

void * memory_calloc(size_t size, size_t bytes)
{

   return calloc(size, bytes);

}


void * memory_allocate_debug(size_t nSize, i32 nBlockUse, const char * szFileName, i32 nLine)
{

   return system_heap_alloc(nSize);

}


void * memory_reallocate(void * pvoid, size_t nSize)
{

   return system_heap_realloc(pvoid, nSize);

}


void * memory_reallocate_debug(void * p, size_t size, i32 nBlockUse, const char * szFileName, i32 nLine)
{


   return system_heap_realloc(p, size);



}


void memory_free(void * p)
{

   return system_heap_free(p);

}


memsize memory_size(void * p)
{

#ifdef WINDOWS

   return _msize(p);

#else

   return system_heap_alloc_size(p);

#endif

}


void memory_free_debug(void * p, i32 iBlockType)
{

   memory_free(p);

}


memsize memory_size_debug(void * p, i32 iBlockType)
{

#ifdef WINDOWS

   return _msize(p);

#else

   return system_heap_alloc_size(p);

#endif

}



