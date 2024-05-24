//Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "heap_allocator.h"
#include "acid/memory/allocator.h"
#include "acid/memory/heap.h"
#include "acid/_operating_system.h"

//class CLASS_DECL_ACID clib_memory_allocator
//{
//public:
//
//   inline static void * allocate(memsize s) { return ::malloc(s); }
//   inline static void * realloc(void * p, memsize s) { return ::realloc(p, s); }
//   inline static void free(void * p) { ::free(p); }
//   inline static void zero(void * p) { throw error_unsupported_function; }
//
//};


namespace windows
{


   //class CLASS_DECL_ACID heap_allocator :
   //   virtual public ::heap::allocator
   //{
   //public:



   //   HANDLE                  m_handle;
   //   ::critical_section      m_criticalsection;


   heap_allocator::heap_allocator()
   {


   }



   heap_allocator::~heap_allocator()
   {


   }


   void heap_allocator::initialize_allocator(::acid::acid * pace)
   {

      allocator::initialize_allocator(pace);

      m_handle = ::HeapCreate(0, 0, 0);

   }


   void * heap_allocator::allocate(memsize s, const char * pszAnnotation)
   {

      raw_critical_section_lock criticalsectionlock(&m_criticalsection);

      return ::HeapAlloc(m_handle, 0, s);

   }


   void * heap_allocator::reallocate(void * p, memsize s, const char * pszAnnotation)
   {

      raw_critical_section_lock criticalsectionlock(&m_criticalsection);

      return ::HeapReAlloc(m_handle, 0, p, s);

   }


   void heap_allocator::free(void * p)
   {

      raw_critical_section_lock criticalsectionlock(&m_criticalsection);

      if (!::HeapFree(m_handle, 0, p))
      {

         DWORD dwError = ::GetLastError();

         ::acid::get()->platform()->informationf("system_heap_free : Failed to free memory");

      }

   }

   memsize heap_allocator::size(void * p)
   {

      raw_critical_section_lock criticalsectionlock(&m_criticalsection);

      SIZE_T s = ::HeapSize(m_handle, 0, p);

      if (s == (SIZE_T)-1)
      {

         ::acid::get()->platform()->informationf("os_impl_size : Failed to get memory size_i32");

      }

      return s;

   }

   bool heap_allocator::has_size() const
   {
      return true;
   }
   //inline static void zero(void * p) { ::zero(p, memory_size(p)); }


//   };


} // namespace windows


