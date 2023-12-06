// Created by camilo on 2023-11-24 22:26 <3ThomasBorregaardSorensen!!
#pragma once


#include <stdlib.h>


namespace c
{


   class CLASS_DECL_ACME malloc
   {
   public:


      template < typename T >
      static T * create()
      {

         auto p = (T *) ::malloc(sizeof(T));

         ::new(p)T();

         return p;

      }


      template < typename T >
      static void destroy(T *& p)
      {

         auto pdel = p;

         p = nullptr;

         pdel->~T();

         ::free(pdel);

      }

   };


} // namespace c



