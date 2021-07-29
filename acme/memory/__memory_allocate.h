//Created by camilo on 2021-07-24 01:05 BRT <3ThomasBorregaardSørensen!!
#pragma once


#if !defined(MCHECK) && !defined(__VLD) && !defined(__MCRTDBG)


   CLASS_DECL_ACME void* _memory_allocate(memsize size);
   CLASS_DECL_ACME void* _memory_reallocate(void* p, memsize nSize);
   CLASS_DECL_ACME void       _memory_free(void* p);
   CLASS_DECL_ACME memsize    _memory_size(void* p);


#endif


   CLASS_DECL_ACME void* _memory_allocate_debug(memsize nSize, i32 nBlockUse, const char* szFileName, i32 nLine);
   CLASS_DECL_ACME void* _memory_reallocate_debug(void* p, memsize nSize, i32 nBlockUse, const char* szFileName, i32 nLine);
   CLASS_DECL_ACME void       _memory_free_debug(void* p, i32 iBlockType);
   CLASS_DECL_ACME memsize    _memory_size_debug(void* p, i32 iBlockType);




