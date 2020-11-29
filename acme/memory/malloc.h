//
//  acme_malloc.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 26/11/17. tbs in <3
//

#pragma once

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

   };


   template < typename POINTER >
   class memory_alloc
   {
   public:


      POINTER     m_p;
      i64     m_iSize;

      memory_alloc(void * p = nullptr)
      {

         m_iSize = -1;
         m_p = (POINTER) p;

      }

      memory_alloc(memsize s)
      {

         m_iSize = 0;
         m_p = nullptr;

         alloc(s * sizeof(*m_p));

      }

      ~memory_alloc()
      {

         free();

      }

      operator POINTER() { return (POINTER)m_p; }

      operator const POINTER() const { return (const POINTER)m_p; }


      POINTER alloc(size_t size)
      {

         if (m_p != nullptr)
         {

            m_p = (POINTER) ::memory_realloc(m_p, size);

         }
         else
         {

            m_p = (POINTER) ::memory_alloc(size);

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

         m_p = memory_alloc(m_iSize);

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
      memory_alloc & operator = (POINTER2 p)
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


namespace str
{

   template < typename POINTER >
   inline void from(string & str, const ::acme::memory_alloc < POINTER > & memoryallocpointer)
   {

      from(str, memoryallocpointer.m_p);

   }


} // namespace str



