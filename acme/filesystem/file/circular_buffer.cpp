#include "framework.h"
#include "circular_file.h"
////#include "acme/exception/exception.h"


namespace file
{

   circular_file::circular_file(memsize size) :
      m_max(size),
      m_q(0),
      m_b(0),
      m_t(0),
      m_count(0)
   {

      m_memory.set_size(size * 2);

   }

   circular_file::circular_file(const circular_file& buffer)
   {
      operator =(buffer);
   }

   circular_file::~circular_file()
   {
   }


   void circular_file::write(const void * pdata, memsize l)
   {

      const char * s = (const char *) pdata;

      m_count += (memsize) l;

      if (m_t + l > m_max) // block crosses circular border
      {
         auto l1 = m_max - m_t; // size_i32 left until circular border crossing
         // always copy full block to buffer(m_memory.data()) + top pointer(m_t)
         // because we have doubled the buffer size_i32 for performance reasons
         ::memcpy_dup(m_memory.data() + m_t, s, l);
         ::memcpy_dup(m_memory.data(), s + l1, l - l1);
         m_t = l - l1;
         m_q += l;
      }
      else
      {
         ::memcpy_dup(m_memory.data() + m_t, s, l);
         ::memcpy_dup(m_memory.data() + m_max + m_t, s, l);
         m_t += l;
         if (m_t >= m_max)
            m_t -= m_max;
         m_q += l;
      }

   }


   memsize circular_file::read(void * pbuffer, memsize l)
   {

      u8 * s = (u8 *) pbuffer;


      if (l > m_q)
      {
         throw ::exception(error_io, "circular_file::read");
      }

      if (m_b + l > m_max) // block crosses circular border
      {

         auto l1 = m_max - m_b;


         if(s != nullptr)
         {

            ::memcpy_dup(s, m_memory.data() + m_b, l1);

            ::memcpy_dup(s + l1, m_memory.data(), l - l1);

         }

         m_b = l - l1;

         m_q -= l;

      }
      else
      {

         if(s != nullptr)
         {

            ::memcpy_dup(s, m_memory.data() + m_b, l);

         }

         m_b += l;

         if (m_b >= m_max)
            m_b -= m_max;

         m_q -= l;

      }

      if (!m_q)
      {

         m_b = m_t = 0;

      }

      return l;

   }


   bool circular_file::erase(memsize l)
   {

      try
      {

         return read(nullptr, l) == l;

      }
      catch(...)
      {

         return false;

      }

   }


   filesize circular_file::get_length() const
   {

      return m_q;

   }


   const char *circular_file::GetStart()
   {

      return (const char * ) (m_memory.data() + m_b);

   }


   memsize circular_file::GetL()
   {

      return (m_b + m_q > m_max) ? m_max - m_b : m_q;

   }


   memsize circular_file::Space()
   {
      return m_max - m_q;
   }


   memsize circular_file::ByteCounter(bool clear)
   {
      if (clear)
      {
         memsize x = m_count;
         m_count = 0;
         return x;
      }
      return m_count;
   }


   string circular_file::read_string(memsize l)
   {
      
      memory mem;
      
      mem.set_size(l + 1);

      if (!read(mem.data(), l)) // failed, debug printout in read() method
      {
      
         return "";

      }

      mem.data()[l] = '\0';

      return (const char * ) mem.data();

   }

   circular_file& circular_file::operator=(const circular_file& buffer)
   {
      if(&buffer != this)
      {
         m_memory = buffer.m_memory;
         m_q = buffer.m_q;
         m_b = buffer.m_b;
         m_t = buffer.m_t;
         m_count = buffer.m_count;
      }
      return *this;
   }


} // namespace file



