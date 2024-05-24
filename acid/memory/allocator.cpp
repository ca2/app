//
//  _heap.h
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 28/02/20.
//  Refactoring 2023-11-23 05:59 <3ThomasBorregaardSoerensen!!
//
#include "framework.h"
#include "allocator.h"
#include "acid/exception/interface_only.h"


namespace heap
{


   allocator::allocator()
   {


   }


   allocator::~allocator()
   {


   }


   void allocator::initialize_allocator(::acid::acid * pace)
   {

      m_pace = pace;

   }


   //void allocator::initialize_allocator(::acid::acid * pace)
   //{

   //   m_pace = pace;

   //}

   //void * allocator::allocate(memsize iSize, const char * pszFile, int iLine)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   void * allocator::allocate(memsize iSize, const char * pszAnnotation)
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



