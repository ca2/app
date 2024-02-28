#pragma once


CLASS_DECL_ACME void * processor_cache_oriented_memory_alloc(size_t s);
CLASS_DECL_ACME void processor_cache_oriented_memory_free(void * p);
CLASS_DECL_ACME void processor_cache_oriented_memory_reset(void);
CLASS_DECL_ACME int_bool processor_cache_oriented_set_thread_memory_pool(int iPoolIndex);
CLASS_DECL_ACME void processor_cache_oriented_destroy_all_memory_pools(void);

#define MAX_PROC_CACHE_ORIENTED_MEM_POOL 32


#if defined(__cplusplus)

class CLASS_DECL_ACME processor_cache_oriented_memory_allocator
{
public:

   inline static void * alloc(size_t iSize)
   {

      return processor_cache_oriented_memory_alloc(iSize);

   }

   inline static void _free(void * p)
   {

      processor_cache_oriented_memory_free(p);

   }

   inline static void reset()
   {

      processor_cache_oriented_memory_reset();

   }

};


#endif







