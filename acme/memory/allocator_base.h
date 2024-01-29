//
//  _heap.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2023-11-27.
//  Refactoring 2023-11-27 11:20 <3ThomasBorregaardSoerensen!!
//
#pragma once


namespace heap
{


   class allocator_base
   {
   public:


      virtual void * allocate(memsize size, const char * pszAnnotation = nullptr) = 0;
      virtual void * reallocate(void * p, memsize size, const char * pszAnnotation = nullptr) = 0;
      virtual void free(void * p) = 0;
      virtual memsize size(void * p) = 0;
      virtual bool has_size() const = 0;


   };


} // namespace heap



