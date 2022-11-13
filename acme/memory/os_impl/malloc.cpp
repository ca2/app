#if defined(LINUX) || defined(FREEBSD)
#include <malloc.h>
#endif




void check_bounds(u8 * p)
{

   uptr * pinteraction = (uptr *)p;

   byte a[256];

   zero(a);

   if (__memcmp(&p[sizeof(uptr)], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption before allocation");

   }
   if (__memcmp(&p[sizeof(uptr) + 256 + *pinteraction], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption after allocation");

   }

}


void * os_impl_alloc(memsize size)
{

#ifdef WINDOWS

   return _malloc_base((size_t) size);

#else

//   if(size == 0)
//   {
//
//      size = 1;
//
//   }
//   else if(size > 2_mb)
//   {
//
//      output_debug_string("size_i32 > 2_mb");
//
//   }

   return malloc(size);

#endif

}


void * os_impl_realloc(void * p, memsize size)
{

#ifdef WINDOWS

   return _realloc_base(p, (size_t) size);

#else

   return realloc(p, size);

#endif

}


void os_impl_free(void * p)
{

#ifdef WINDOWS

   return _free_base(p);

#else

   free(p);

#endif

}


size_t os_impl_size(void * p)
{

#ifdef __APPLE__

   return malloc_size(p);

#elif defined(WINDOWS)

   return _msize(p);

#else

   return malloc_usable_size(p);

#endif

}





