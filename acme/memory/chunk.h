// Created by camilo on 2021-09-18 21:32 BRT <3ThomasBorregaardSorensen!! (I need to suck you).
#pragma once


class chunk
{

   void * m_p = nullptr;

   memsize     m_size = 0;

public:


   chunk(const void * p = nullptr, memsize s = 0)
   {

      assign(p, s);
   }
   chunk(const chunk & chunk)
   {

      assign(chunk.m_p, chunk.m_size);
   }
   ~chunk()
   {

      destroy();

   }

   void destroy()
   {
      if (m_p)
      {

         memory_free(m_p);

      }
      m_p = nullptr;
      m_size = 0;

   }

   chunk & operator =(const chunk & chunk)
   {

      if (this != &chunk)
      {

         destroy();
         assign(chunk.m_p, chunk.m_size);

      }

      return *this;

   }

   memsize size()const { return m_size; }

   operator void * () { return m_p; }
   operator const void * () const { return m_p; }

   void assign(const void * p, memsize s)
   {

      if (s <= 0)
      {

         destroy();
      }

      m_p = memory_allocate(s);

      if (::is_set(m_p))
      {

         memcpy(m_p, p, s);

         m_size = s;

      }

   }

   bool operator == (const chunk & chunk) const
   {

      if (::is_null(m_p))
      {

         if (::is_null(chunk.m_p))
         {

            return true;

         }
         else
         {

            return false;

         }

      }
      else if (::is_null(chunk.m_p))
      {

         return false;

      }

      if (m_size != chunk.m_size)
      {

         return false;

      }

      return !memcmp(m_p, chunk.m_p, m_size);

   }

   bool operator !=(const chunk & chunk) const
   {

      return !operator==(chunk);

   }


};



