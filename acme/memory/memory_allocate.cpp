//
//  memory_allocate.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 07/12/23.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "memory_allocate.h"
#include "simple_memory_allocate.h"


CLASS_DECL_ACME void * memory_allocate(memsize size)
{
   
   ::heap::memory * pheapmemory;
   
   if(::is_set(::acme::get()) && ::is_set(::acme::get()->m_pheapmanagement))
   {
      
      pheapmemory = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main);
      
   }
   else
   {
      
      pheapmemory = nullptr;
      
   }

   void * p;

   if(::is_set(pheapmemory))
   {
   
      p = pheapmemory->allocate(size);
   
   }
   else
   {
   
      p = simple_memory_allocate(size);
   
   }

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p;

}


CLASS_DECL_ACME void * memory_reallocate(void * p, memsize size)
{

   auto p2 = simple_memory_reallocate(p, size);

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p2;

}


CLASS_DECL_ACME void memory_free(void * p)
{
   
   simple_memory_free(p);
   
}


CLASS_DECL_ACME memsize memory_size(void * p)
{
   
   auto s = simple_memory_size(p);

   return s;
   
}


CLASS_DECL_ACME void * memory_allocate_debug(memsize size, i32 nType, const char* pszFileName, i32 nLine)
{

   auto pmemoryMain = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main);

   void * p;

   if(::is_set(pmemoryMain))
   {
   
      p = pmemoryMain->allocate_debug(size, nType, pszFileName, nLine);
   
   }
   else
   {
   
      p = simple_memory_allocate(size);
   
   }

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p;

}


CLASS_DECL_ACME void * memory_reallocate_debug(void * p, memsize size, i32 nType, const char* pszFileName, i32 nLine)
{

   auto pmemoryMain = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main);

   auto pheapmemory = heap_memory_get(p);

   void * p2;
   
   if(::is_set(pmemoryMain) && pheapmemory->m_ememory == ::heap::e_memory_simple)
   {
   
      p2 = pmemoryMain->reallocate_debug(p, size, nType, pszFileName, nLine);
   
   }
   else
   {
   
      p2 = simple_memory_reallocate(p, size);
   
   }

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p2;

}


CLASS_DECL_ACME void memory_free_debug(void * p, i32 nType)
{

   auto pmemoryMain = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main);

   auto pheapmemory = heap_memory_get(p);

   if(::is_set(pmemoryMain) && pheapmemory->m_ememory == ::heap::e_memory_simple)
   {
   
      pmemoryMain->free_debug(p, nType);
   
   }
   else
   {
   
      simple_memory_free(p);
   
   }

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   //return p2;

}



