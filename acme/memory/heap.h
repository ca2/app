//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2023-11-23 17:17
#pragma once


namespace heap
{


   class CLASS_DECL_ACME heap
   {
   protected:
      
      
      friend class ::c::malloc;


      heap();
      ~heap();


   public:


      //::heap::allocator * m_pallocator;
      //::acme::acme * m_pacme;
      ::heap::enum_memory m_ememory;
      ::heap::allocator * m_pallocator;


      //virtual void * allocate_debug(memsize size, int nBlockUse, const_char_pointer pszFile, int iLine);
      //virtual void * reallocate_normal(void * p, memsize size);
      //virtual memsize allocation_size(void * p);


      //virtual void * reallocate_debug(void * p, memsize size, int nBlockUse, const_char_pointer pszFile, int iLine);


      //virtual void free(void * p);


      virtual void initialize_heap(::heap::allocator * pallocator, ::heap::enum_memory ememory);

      virtual void start_heap();

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


      virtual void * allocate(memsize size, memsize * psizeAllocated, const_char_pointer pszAnnotation = nullptr);
      virtual void * reallocate(void * p, memsize nSize, const_char_pointer pszAnnotation = nullptr);
      virtual void      free(void * p);
      virtual memsize   size(void * p);


#endif


      virtual void * allocate_debug(memsize nSize, int nBlockUse, const_char_pointer szFileName, int nLine, const_char_pointer pszAnnotation = nullptr);
      virtual void * reallocate_debug(void * p, memsize nSize, int nBlockUse, const_char_pointer szFileName, int nLine, const_char_pointer pszAnnotation = nullptr);
      virtual void      free_debug(void * p, int iBlockType);
      virtual memsize   size_debug(void * p, int iBlockType);


   };


} // namespace heap



