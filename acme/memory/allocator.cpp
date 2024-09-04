//
//  _heap.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 28/02/20.
//  Refactoring 2023-11-23 05:59 <3ThomasBorregaardSoerensen!!
//
#include "framework.h"
#include "allocator.h"
#include "acme/exception/interface_only.h"


namespace heap
{


   allocator::allocator()
   {


   }


   allocator::~allocator()
   {


   }


   void allocator::initialize_allocator(::acme::acme * pacme)
   {

      m_pacme = pacme;

   }


   //void allocator::initialize_allocator(::acme::acme * pacme)
   //{

   //   m_pacme = pacme;

   //}

   //void * allocator::allocate(memsize iSize, const char * pszFile, int iLine)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void * allocator::allocate(memsize iSize, memsize * psizeAllocated, const char * pszAnnotation)
   {

      throw ::interface_only();

      return nullptr;

   }
   
   
   void allocator::free(void * p)
   {

      throw ::interface_only();

   }


   void * allocator::reallocate(void * p, memsize s, const char * pszAnnotation)
   {

      throw ::interface_only();

      return nullptr;

   }


   memsize allocator::size(void * p)
   {

      throw ::interface_only();

      return 0;

   }


   bool allocator::has_size() const
   {

      return false;

   }


} // namespace heap



