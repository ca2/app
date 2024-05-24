//Created by camilo on 2023-11-23 23:52 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acid/memory/allocator.h"


namespace heap
{


   class CLASS_DECL_ACID malloc_allocator :
      virtual public ::heap::allocator
   {
   protected:
      friend class ::c::malloc;
      malloc_allocator();
      ~malloc_allocator();

   public:

      
      //::platform::platform * m_pplatform;


      //malloc_allocator(::acid::acid * pace);
      //~malloc_allocator();

      void initialize_allocator(::acid::acid * pace) override;

      void * allocate(memsize s, const char * pszAnnotation) override;
      void * reallocate(void * p, memsize s, const char * pszAnnotation) override;
      void free(void * p) override;
      memsize size(void * p) override;
      bool has_size() const override;


      void check_bounds(u8 * p);


   };


} // namespace heap


