// from acid/operating_system/windows/memory.cpp by
// camilo on 2023-12-07 00:26 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "heap_allocator.h"
#include "acid/memory/allocator/malloc.h"
#include "acid/memory/c_malloc.h"
#include "acid/memory/management.h"


namespace heap
{


   ::heap::allocator * management::_new_allocator(::heap::enum_allocator eallocator)
   {

      //if (eallocator == ::heap::e_allocator_malloc)
      //{

         return ::c::malloc::create < ::heap::malloc_allocator >();

      //}
//      else
//      {
//
//         return ::c::malloc::create < windows::heap_allocator > ();
//
//      }

   }


} // namespace heap



