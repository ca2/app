#pragma once


#include "memory_base.h"


class CLASS_DECL_ACID read_only_memory :
   public memory_base
{
public:


   read_only_memory(const ::block & block);

   read_only_memory(const void * p, memsize size);


};



