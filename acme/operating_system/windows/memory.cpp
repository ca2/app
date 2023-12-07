#include "framework.h"
#include "heap_allocator.h"
#include "acme/memory/allocator/malloc.h"
#include "acme/memory/c_malloc.h"
#include "acme/memory/management.h"


namespace heap
{


   ::heap::allocator * management::_new_allocator(::heap::enum_allocator eallocator)
   {

      if (eallocator == ::heap::e_allocator_malloc)
      {

         return ::c::malloc::create < ::heap::malloc_allocator >();

      }
      else
      {

         return ::c::malloc::create < windows::heap_allocator > ();

      }

   }


} // namespace heap



