#include "framework.h"
#include "acme/memory/allocator/malloc.h"
#include "acme/platform/system.h"
#if defined(OPENBSD)
#include <sys/types.h>
#include <sys/malloc.h>
#elif defined(LINUX) || defined(__BSD__)
#include <malloc.h>
#elif defined(__APPLE__)
#include <malloc/malloc.h>
#endif


namespace heap
{


   malloc_allocator::malloc_allocator()
   {


   }


   malloc_allocator::~malloc_allocator()
   {


   }


   void malloc_allocator::initialize_allocator(::acme::acme * pacme)
   {

      allocator::initialize_allocator(pacme);

   }

   void * malloc_allocator::allocate(memsize s, memsize * psizeAllocated, const_char_pointer pszAnnotation)
   {

#ifdef WINDOWS

      auto p = _malloc_base((size_t)s);

#else

      auto p = ::malloc(s);


#endif

      if (psizeAllocated)
      {

         auto sizeAlloc = size(p);

         if (sizeAlloc <= 0)
         {

            *psizeAllocated = s;

         }
         else
         {

            *psizeAllocated = sizeAlloc;

         }

      }

      return p;

   }


   void * malloc_allocator::reallocate(void * p, memsize s, const_char_pointer pszAnnotation)
   {
#ifdef WINDOWS

      return _realloc_base(p, (size_t)s);

#else

      return ::realloc(p, s);

#endif
   }


   void malloc_allocator::free(void * p)
   {

#ifdef WINDOWS

      return _free_base(p);

#else

      ::free(p);

#endif

   }


   memsize  malloc_allocator::size(void * p)
   {

      //{

#if defined(OPENBSD) || defined(NETBSD)

      return 0;

#elif defined(__APPLE__)

      return malloc_size(p);

#elif defined(WINDOWS)

      return _msize(p);

#else

      return malloc_usable_size(p);

#endif

      //}

   }


   bool  malloc_allocator::has_size() const
   {

      return true;

   }


   //
   //
   //void * operating_system_memory_allocate(memsize size)
   //{
   //
   //
   //}
   //
   //
   //void * operating_system_memory_reallocate(void * p, memsize size)
   //{
   //
   //
   //}


   //void operating_system_memory_free(void * p)
   //{
   //
   //
   //}

   //
   //memsize operating_system_memory_size(void * p)
   //{
   //
   //#ifdef __APPLE__
   //
   //   return malloc_size(p);
   //
   //#elif defined(WINDOWS)
   //
   //   return _msize(p);
   //
   //#else
   //
   //   return malloc_usable_size(p);
   //
   //#endif
   //
   //}
   //
   void malloc_allocator::check_bounds(unsigned char * p)
   {

      uptr * pinteraction = (uptr *)p;

      unsigned char a[256];

      zero(a);

      if (memory_order(&p[sizeof(uptr)], a, sizeof(a)) != 0)
      {

         informationf("memory corruption before allocation");

      }

      if (memory_order(&p[sizeof(uptr) + 256 + *pinteraction], a, sizeof(a)) != 0)
      {

         informationf("memory corruption after allocation");

      }

   }


} // namespace heap



