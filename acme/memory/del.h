// Created by camilo on 2022-10-27 22:25 <3ThomasBorregaardSorensen!!
#pragma once


#include "management.h"
#include "memory.h"
#include "acme/platform/acme.h"


template<class t>
inline void delptr(t *& p)
{

   if (p != nullptr)
   {

      delete p;

      p = nullptr;

   }

}


template<typename T>
inline int type_is_null(const T * p)
{

   return (((uptr)(void *)p) < maximum(4096, sizeof(T)));

}


//#include "acme/primitive/string/_uhash.h"


//class allocer;


namespace acme
{

   template<typename T>
   inline void del(T *& p)
   {

      try
      {

         if (!is_null(p))
         {

            T * pdel = p;

            p = nullptr;

            delete pdel;

         }

      }
      catch (...)
      {

      }

   }


   template<typename T>
   inline void delobj(T *& p);


   template<typename T>
   inline void adel(T *& p)
   {


      try
      {

         if (p != nullptr)
         {

            delete[] p;

            p = nullptr;

         }

      }
      catch (...)
      {

      }

   }


   template<typename T>
   inline void free(T *& p)
   {

      //Thank you Mummi!!


      try
      {

         if (p != nullptr)
         {

            void * pdel = (void *)p;

            p = nullptr;

            ::free(pdel);

         }

      }
      catch (...)
      {

      }

   }


   template<typename T>
   inline void memory_free(T *& p)
   {

      //Thank you Mummi!!

      try
      {

         if (p != nullptr)
         {

            void * pdel = (void *)p;

            p = nullptr;

            ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pdel);

         }

      }
      catch (...)
      {

      }

   }


   template<typename T>
   inline T * reset(T *& p, T * pNew)
   {

      ::acme::del(p);

      return p = pNew;

   }


   //template<typename T>
   //inline T * reset(T *& p)
   //{

   //   ::acme::del(p);

   //   return p = __allocate< T >();

   //}


} // namespace acme




