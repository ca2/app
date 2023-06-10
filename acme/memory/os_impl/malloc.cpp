#if defined(LINUX) || defined(FREEBSD)
#include <malloc.h>
#endif


#ifdef WINDOWS_DESKTOP


::std::strong_ordering memory_order(const void * m1, const void * m2, memsize s)
{

   if(::is_null(m1))
   {

      if(::is_null(m2))
      {

         return ::std::strong_ordering::equal;

      }
      else
      {

         return ::std::strong_ordering::less;

      }

   }
   else if(::is_null(m2))
   {

      return ::std::strong_ordering::greater;

   }
   else if(s == 0)
   {

      return ::std::strong_ordering::equal;

   }

   return memcmp(m1, m2, s) <=> 0;

}


#endif // WINDOWS_DESKTOP


void check_bounds(u8 * p)
{

   uptr * pinteraction = (uptr *)p;

   ::u8 a[256];

   zero(a);

   if (memory_order(&p[sizeof(uptr)], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption before allocation");

   }

   if (memory_order(&p[sizeof(uptr) + 256 + *pinteraction], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption after allocation");

   }

}


void * operating_system_memory_allocate(memsize size)
{

#ifdef WINDOWS

   return _malloc_base((size_t) size);

#else

   return malloc(size);

#endif

}


void * operating_system_memory_reallocate(void * p, memsize size)
{

#ifdef WINDOWS

   return _realloc_base(p, (size_t) size);

#else

   return realloc(p, size);

#endif

}


void operating_system_memory_free(void * p)
{

#ifdef WINDOWS

   return _free_base(p);

#else

   free(p);

#endif

}


memsize operating_system_memory_size(void * p)
{

#ifdef __APPLE__

   return malloc_size(p);

#elif defined(WINDOWS)

   return _msize(p);

#else

   return malloc_usable_size(p);

#endif

}



