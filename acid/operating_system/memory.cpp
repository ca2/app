//
// Created by camilo on Jul/4/2023.
// <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD) || defined(__APPLE__)
#include <string.h>
#endif


CLASS_DECL_ACID ::std::strong_ordering _memory_order(const void* p1, const void* p2, memsize size)
{

   return memcmp(p1, p2, size) <=> 0;

}




