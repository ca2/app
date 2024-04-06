#include "framework.h"
#include "acme/memory/allocator/malloc.h"
#include "acme/platform/system.h"
#if defined(LINUX) || defined(FREEBSD)
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

   void * malloc_allocator::allocate(memsize s, const char * pszAnnotation)
   {

#ifdef WINDOWS

      return _malloc_base((size_t)s);

#else

      return ::malloc(s);

#endif
   }


   void * malloc_allocator::reallocate(void * p, memsize s, const char * pszAnnotation)
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

#ifdef __APPLE__

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
   void malloc_allocator::check_bounds(u8 * p)
   {

      uptr * pinteraction = (uptr *)p;

      ::u8 a[256];

      zero(a);

      if (memory_order(&p[sizeof(uptr)], a, sizeof(a)) != 0)
      {

         m_pacme->m_pplatform->informationf("memory corruption before allocation");

      }

      if (memory_order(&p[sizeof(uptr) + 256 + *pinteraction], a, sizeof(a)) != 0)
      {

         m_pacme->m_pplatform->informationf("memory corruption after allocation");

      }

   }


} // namespace heap



