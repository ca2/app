//
//  _heap.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 28/02/20.
//  Refactoring 2023-11-23 05:40 <3ThomasBorregaardSoerensen!!
//
#pragma once
//
//
//template < non_particle NON_PARTICLE, typename ...Args >
//inline void __on_construct(void * data, NON_PARTICLE * p, memsize s, Args &&... args)
//{
//
//#if REFERENCING_DEBUGGING
//
//   return __on_referencing_debugging_construct<NON_PARTICLE>(data, s, ::std::forward<Args>(args)...);
//
//#else
//
//   return __on_construct<NON_PARTICLE>(data, s, ::std::forward<Args>(args)...);
//
//#endif
//
//}


#include "acme/memory/allocator_base.h"


namespace heap
{


   class CLASS_DECL_ACME allocator :
      virtual public ::heap::allocator_base
   {
   protected:
      
      
      allocator();
      ~allocator();


   public:


      ::acme::acme * m_pacme;


      //template < typename T, typename ...Args >
      //inline T * __raw_allocate(Args &&... args)
      //{

      //   auto s = sizeof(T);

      //   auto data = allocate(s);

      //   auto p = ::platform::raw_allocator::__on_normal_construct< T >(data, s, ::std::forward<Args>(args)...);

      //   return p;

      //}


      //template < typename T >
      //inline void __raw_deallocate(T * p)
      //{

      //   ::platform::raw_allocator::__on_normal_destruct(p);

      //   free(p);

      //}


      //allocator(::acme::acme * pacme);
      //~allocator();
      
      //virtual void * allocate(memsize iSize, const_char_pointer  pszFile, int iLine);
      //virtual void * allocate(memsize iSize);
      //virtual void free(void * p);
      //virtual void zero(void * p);

      virtual void initialize_allocator(::acme::acme * pacme);

      // Core functions
      void * allocate(memsize size, memsize * psizeActuallyAllocated, const_char_pointer  pszAnnotation = nullptr) override;
      void * reallocate(void * p, memsize size, const_char_pointer  pszAnnotation = nullptr) override;
      void free(void * p) override;
      memsize size(void * p) override;
      bool has_size() const override;


   };


} // namespace heap



