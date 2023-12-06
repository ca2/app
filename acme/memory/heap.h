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


      //virtual void * allocate_debug(memsize size, int nBlockUse, const char * pszFile, int iLine);
      //virtual void * reallocate_normal(void * p, memsize size);
      //virtual memsize allocation_size(void * p);


      //virtual void * reallocate_debug(void * p, memsize size, i32 nBlockUse, const char * pszFile, i32 iLine);


      //virtual void free(void * p);


      virtual void initialize_heap(::heap::allocator * pallocator, ::heap::enum_memory ememory);

      virtual void start_heap();

      //Created by camilo on 2021-07-24 01:06 BRT <3ThomasBorregaardSorensen!!
//#include "__aligned_memory_allocate.h"
      virtual void * aligned_allocate(memsize size, memsize align = 0);
      virtual void * aligned_allocate_debug(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine, memsize align = 0);


      //Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
//#include "__unaligned_memory_allocate.h"
      virtual void * unaligned_allocate(memsize size);
      virtual void * unaligned_allocate_debug(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine);

      virtual void * count_allocate(::count count, memsize size);
      //Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSorensen!!
      //#include "__memory_allocate.h"


#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG)


      virtual void * allocate(memsize size);
      virtual void * reallocate(void * p, memsize nSize);
      virtual void      free(void * p);
      virtual memsize   size(void * p);


#endif


      virtual void * allocate_debug(memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine);
      virtual void * reallocate_debug(void * p, memsize nSize, i32 nBlockUse, const char * szFileName, i32 nLine);
      virtual void      free_debug(void * p, i32 iBlockType);
      virtual memsize   size_debug(void * p, i32 iBlockType);


   };


} // namespace heap



