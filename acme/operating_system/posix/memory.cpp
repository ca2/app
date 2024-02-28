//
// Created by camilo on 2023-12-19 06:10 <3ThomasBorregaardSorensen!!s
//
#include "framework.h"
//#include "heap_allocator.h"
#include "acme/memory/allocator/malloc.h"
#include "acme/memory/c_malloc.h"
#include "acme/memory/management.h"


namespace heap
{


   ::heap::allocator * management::_new_allocator(::heap::enum_allocator eallocator)
   {

      return ::c::malloc::create < ::heap::malloc_allocator >();

   }


} // namespace heap



