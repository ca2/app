// Created by camilo on 2024-09-01 20:10 <3ThomasBorregaardSorensen!! ThomasMonth?ThomasLikes5?
#pragma once


#include "acme/memory/memory_allocate.h"


class memory_quantum
{
public:


   memory_quantum()
   {


   }

   
   ~memory_quantum()
   {


   }


   void* operator new(size_t s)
   {

      auto p = ::memory_allocate(s);

#if REFERENCING_DEBUGGING

      ::allocator::__on_start_construct(p, s, true);

#endif

      return p;

   }



   void* operator new[](size_t s)
   {

      return ::memory_allocate(s);

   }


   void operator delete(void*p)
   {

      return ::memory_free(p);

   }


   void operator delete[](void*p)
   {

      return ::memory_free(p);

   }


};



