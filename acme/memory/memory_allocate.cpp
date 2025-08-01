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


CLASS_DECL_ACME void * memory_allocate(memsize size, memsize * psizeAllocated, const_char_pointer pszAnnotation)
{
   
   ::heap::memory * pmemory;
   
   if(::is_set(::acme::get()) && ::is_set(::acme::get()->m_pheapmanagement))
   {
      
      pmemory = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main);
      
   }
   else
   {
      
      pmemory = nullptr;
      
   }

   if(::is_set(pszAnnotation))
   {

      information() << "memory_allocate annotation : " << pszAnnotation;

   }

   void * p;

   if(::is_set(pmemory))
   {
   
      p = pmemory->allocate(size, psizeAllocated, pszAnnotation);
   
   }
   else
   {
   
      p = simple_memory_allocate(size, pszAnnotation);

      if (psizeAllocated)
      {

         *psizeAllocated = size;

      }
   
   }

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p;

}


CLASS_DECL_ACME void * memory_reallocate(void * p, memsize size, const_char_pointer pszAnnotation)
{

   auto p2 = simple_memory_reallocate(p, size, pszAnnotation);

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


CLASS_DECL_ACME void * memory_allocate_debug(memsize size, int nType, const_char_pointer pszFileName, int nLine, const_char_pointer pszAnnotation)
{

   auto pmemoryMain = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main);

   void * p;

   if(::is_null(pszAnnotation))
   {

      information() << "memory_allocate_debug annotation : " << pszAnnotation;

   }

   if(::is_set(pmemoryMain))
   {
   
      p = pmemoryMain->allocate_debug(size, nType, pszFileName, nLine, pszAnnotation);
   
   }
   else
   {
   
      p = simple_memory_allocate(size, pszAnnotation);
   
   }

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p;

}


CLASS_DECL_ACME void * memory_reallocate_debug(void * p, memsize size, int nType, const_char_pointer pszFileName, int nLine, const_char_pointer pszAnnotation)
{

   auto pmemoryMain = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main);

   auto pheapmemory = heap_memory_get(p);

   if(::is_null(pszAnnotation))
   {

      information() << "memory_reallocate_debug annotation : " << pszAnnotation;

   }

   void * p2;
   
   if(::is_set(pmemoryMain) && pheapmemory->m_ememory == ::heap::e_memory_main)
   {
   
      p2 = pmemoryMain->reallocate_debug(p, size, nType, pszFileName, nLine, pszAnnotation);
   
   }
   else
   {
   
      p2 = simple_memory_reallocate(p, size, pszAnnotation);
   
   }

//#if REFERENCING_DEBUGGING
//
//   task_on_operator_new(p, nSize);
//
//#endif

   return p2;

}


CLASS_DECL_ACME void memory_free_debug(void * p, int nType)
{

   auto pmemoryMain = ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main);

   auto pheapmemory = heap_memory_get(p);

   if(::is_set(pmemoryMain) && pheapmemory->m_ememory == ::heap::e_memory_main)
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



