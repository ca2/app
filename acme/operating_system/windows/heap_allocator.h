//Created by camilo on 2023-11-23 15:56 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/memory/allocator.h"
#include "acme/memory/heap.h"
#include "acme/_operating_system.h"


namespace windows
{


   class CLASS_DECL_ACME heap_allocator :
      virtual public ::heap::allocator
   {
   protected:
      friend class ::c::malloc;
      heap_allocator();
      ~heap_allocator();
   public:


      HANDLE                  m_handle;
      ::critical_section      m_criticalsection;


      void initialize_allocator(::acme::acme * pacme) override;


      void * allocate(memsize s) override;
      void * reallocate(void * p, memsize s) override;
      void free(void * p) override;
      memsize size(void * p) override;
      bool has_size() const override;

   };


} // namespace windows


