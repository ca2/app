//
//  acme_malloc.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 26/11/17. tbs in <3
//
#pragma once


#include "del.h"


namespace acme
{

   //    template < typename P >
   //    void free(P * & p)
   //    {
   //
   //        if(p != nullptr)
   //        {
   //
   //            ::free((void *) p);
   //
   //            p = nullptr;
   //
   //        }
   //
   //    }

   template < typename POINTER >
   class malloc
   {
   public:


      POINTER     m_p;
      i64     m_iSize;

      malloc(POINTER p = nullptr)
      {

         m_iSize = -1;
         m_p = p;

      }

      ~malloc()
      {

         free();

      }

      operator POINTER() { return (POINTER) m_p; }

      bool is_null() const {return ::is_null(m_p);}
      bool is_set() const {return ::is_set(m_p);}


      POINTER alloc(size_t size)
      {

         if(m_p != nullptr)
         {

            m_p = (POINTER) ::realloc(m_p, size);

         }
         else
         {

            m_p = (POINTER) ::malloc(size);

         }

         if (m_p != nullptr)
         {

            m_iSize = size;

         }

         return m_p;

      }

      POINTER calloc(::count c)
      {

         free();

         m_iSize = c * sizeof(*m_p);

         m_p = calloc(m_iSize);

         if (m_p == nullptr)
         {

            m_iSize = -1;

         }

         return m_p;

      }

      void free()
      {

         ::acme::free(m_p);

         m_iSize = -1;

      }

      template < typename POINTER2 >
      malloc & operator = ( POINTER2 p)
      {

         if((POINTER)p == m_p)
         {

            return *this;

         }

         free();

         m_p = (POINTER)p;

         return *this;

      }

      auto operator ->() {return m_p;}
      auto operator ->() const  {return m_p;}

      auto operator *() {return *m_p;}
      auto operator *() const  {return *m_p;}


      POINTER get() {return m_p;}
      const POINTER get() const {return m_p;}

   };


   template < typename POINTER >
   class memory_allocate
   {
   public:


      POINTER     m_p;
      memsize     m_iSize;

      memory_allocate(void * p = nullptr)
      {

         m_iSize = -1;
         m_p = (POINTER) p;

      }

      memory_allocate(memsize s)
      {

         m_iSize = 0;
         m_p = nullptr;

         alloc(s * sizeof(*m_p));

      }

      ~memory_allocate()
      {

         free();

      }

      operator POINTER() { return (POINTER)m_p; }

      operator const POINTER() const { return (const POINTER)m_p; }


      POINTER alloc(size_t size)
      {

         if (m_p != nullptr)
         {

            m_p = (POINTER) ::memory_reallocate(m_p, size);

         }
         else
         {

            m_p = (POINTER) ::memory_allocate(size);

         }

         if (m_p != nullptr)
         {

            m_iSize = size;

         }

         return m_p;

      }

      POINTER calloc(::count c)
      {

         free();

         m_iSize = c * sizeof(*m_p);

         m_p = memory_allocate(m_iSize);

         if (m_p == nullptr)
         {

            m_iSize = -1;

         }

         return m_p;

      }

      memsize get_size() const
      {

         return m_iSize;

      }

      ::count get_count() const
      {

         return get_size() / sizeof(*m_p);

      }

      void free()
      {

         ::memory_free(m_p);

         m_p = nullptr;

         m_iSize = -1;

      }

      template < typename POINTER2 >
      memory_allocate & operator = (POINTER2 p)
      {

         if ((POINTER)p == m_p)
         {

            return *this;

         }

         free();

         m_p = (POINTER)p;

         return *this;

      }

   };

} // namespace acme


// namespace str
// {

   


// } // namespace str


//template < typename POINTER >
//::acme::malloc < POINTER > __malloc(POINTER p)
//{
//
//   return ::acme::malloc < POINTER >(p);
//
//}






