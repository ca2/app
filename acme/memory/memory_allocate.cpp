//Created by camilo on 2021-07-23 23:12 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_memory_allocate.h"


CLASS_DECL_ACME void* memory_allocate(memsize size)
{

   return _memory_allocate(size);

}


CLASS_DECL_ACME void* memory_count_allocate(uptr count, memsize size)
{

   return _memory_allocate(count * size);

}


CLASS_DECL_ACME void* memory_reallocate(void* p, memsize size)
{

   return _memory_reallocate(p, size);

}


CLASS_DECL_ACME void memory_free(void* p)
{

   _memory_free(p);

}


CLASS_DECL_ACME memsize memory_size(void* p)
{

   return _memory_size(p);

}


CLASS_DECL_ACME void* memory_allocate_debug(memsize size, i32 nBlockUse, const char* szFileName, i32 nLine)
{

   return _memory_allocate_debug(size, nBlockUse, szFileName, nLine);

}


CLASS_DECL_ACME void* memory_reallocate_debug(void* p, memsize size, i32 nBlockUse, const char* szFileName, i32 nLine)
{

   return _memory_reallocate_debug(p, size, nBlockUse, szFileName, nLine);

}


CLASS_DECL_ACME void memory_free_debug(void* p, i32 nBlockUse)
{

   _memory_free_debug(p, nBlockUse);

}


CLASS_DECL_ACME memsize memory_size_debug(void* p, i32 nBlockUse)
{

   return _memory_size_debug(p, nBlockUse);

}



