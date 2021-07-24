//Created by camilo on 2021-07-23 23:12 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"


CLASS_DECL_ACME void* memory_allocate(memsize size)
{

   return _memory_allocate(size);

}


CLASS_DECL_ACME void* memory_reallocate(void* p, memsize nSize)
{

   return _memory_reallocate(p, size);

}


CLASS_DECL_ACME void       memory_free(void* p)
{

   _memory_free(p);

}


CLASS_DECL_ACME memsize    memory_size(void* p)
{

   return _memory_size(p);

}
