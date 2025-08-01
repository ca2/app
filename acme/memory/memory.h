//
//  _heap.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 28/02/20.
//
#pragma once


#include "acme/memory/allocator_base.h"
#include "acme/memory/management.h"


class plex_heap_alloc_array;


namespace heap
{


   class CLASS_DECL_ACME memory :
      virtual public ::heap::allocator_base
   {
   protected:


      friend class ::c::malloc;


      memory();
      virtual ~memory();


   public:


      heap *                        m_pheap;





      virtual void initialize_memory(::heap::heap * pheap);


      virtual void start_memory();


      //Created by camilo on 2021-07-24 01:06 BRT <3ThomasBorregaardSorensen!!
//#include "__aligned_memory_allocate.h"
      virtual void * aligned_allocate(memsize size, memsize * psizeAllocated, memsize align = 0, const_char_pointer pszAnnotation = nullptr);
      virtual void * aligned_allocate_debug(memsize nSize, memsize * psizeAllocated, int nBlockUse, const_char_pointer szFileName, int nLine, memsize align = 0, const_char_pointer pszAnnotation = nullptr);


      //Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
//#include "__unaligned_memory_allocate.h"
      virtual void * unaligned_allocate(memsize size, memsize * psizeAllocated, const_char_pointer pszAnnotation = nullptr);
      virtual void * unaligned_allocate_debug(memsize nSize, memsize * psizeAllocated, int nBlockUse, const_char_pointer szFileName, int nLine, const_char_pointer pszAnnotation = nullptr);

      virtual void * count_allocate(::collection::count count, memsize size, const_char_pointer pszAnnotation = nullptr);
      //Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
      //#include "__memory_allocate.h"


#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG)


      void *    allocate(memsize size, memsize * psizeActuallyAllocated, const_char_pointer pszAnnotation = nullptr) override;
      void *    reallocate(void * p, memsize nSize, const_char_pointer pszAnnotation = nullptr) override;
      void      free(void * p) override;
      bool      has_size() const override;
      memsize   size(void * p) override;


#endif


      virtual void *    allocate_debug(memsize nSize, int nBlockUse, const_char_pointer szFileName, int nLine, const_char_pointer pszAnnotation = nullptr);
      virtual void *    reallocate_debug(void * p, memsize nSize, int nBlockUse, const_char_pointer szFileName, int nLine, const_char_pointer pszAnnotation = nullptr);
      virtual void      free_debug(void * p, int iBlockType);
      virtual memsize   size_debug(void * p, int iBlockType);

   };



} // namespace heap

//
//namespace secondary_memory_allocate_heap
//{
//
//
//#include "__aligned_memory_allocate.h"
//#include "__unaligned_memory_allocate.h"
//#include "__memory_allocate.h"
//
//
//}
//
//
//namespace array_memory_allocate_heap
//{
//
//
//#include "__aligned_memory_allocate.h"
//#include "__unaligned_memory_allocate.h"
//#include "__memory_allocate.h"
//
//
//}
//
//
//
//namespace property_memory_allocate_heap
//{
//
//
//#include "__aligned_memory_allocate.h"
//#include "__unaligned_memory_allocate.h"
//#include "__memory_allocate.h"
//
//
//}
//
//
//namespace string_memory_allocate_heap
//{
//
//
//#include "__aligned_memory_allocate.h"
//#include "__unaligned_memory_allocate.h"
//#include "__memory_allocate.h"
//
//
//}
//
//
//
