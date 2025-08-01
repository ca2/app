//Created by camilo on 2023-11-23 23:52 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/memory/allocator.h"


namespace heap
{


   class CLASS_DECL_ACME malloc_allocator :
      virtual public ::heap::allocator
   {
   protected:
      friend class ::c::malloc;
      malloc_allocator();
      ~malloc_allocator();

   public:

      
      //::platform::platform * m_pplatform;


      //malloc_allocator(::acme::acme * pacme);
      //~malloc_allocator();

      void initialize_allocator(::acme::acme * pacme) override;

      void * allocate(memsize s, memsize * psizeAllocated, const_char_pointer  pszAnnotation) override;
      void * reallocate(void * p, memsize s, const_char_pointer  pszAnnotation) override;
      void free(void * p) override;
      memsize size(void * p) override;
      bool has_size() const override;


      void check_bounds(unsigned char * p);


   };


} // namespace heap


