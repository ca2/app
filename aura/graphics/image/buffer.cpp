// created by Camilo on 2025-06-01 01:59 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "buffer.h"


namespace image
{



   buffer::buffer()
   {
      
   }

      
   buffer::~buffer()
   {

   }


   buffer * buffer::lock(int stride, ::pixmap* ppixmapLock)
   {

      m_ppixmapLock = ppixmapLock;

      if (m_ppixmapLock->m_iScan == stride)
      {

         reference(*m_ppixmapLock);

      }
      else
      {

         ::pixmap::create(m_memory, m_ppixmapLock->size(), stride);

      }

      return this;
      
   }


   buffer * buffer::no_padding_lock(::pixmap* ppixmapLock)
   {
      
      return lock(ppixmapLock->width() * 4, ppixmapLock);

   }

   
   void buffer::unlock()
   {

      if (m_ppixmapLock->data() != this->data())
      {

         m_ppixmapLock->copy(this);

      }

   }

} // namespace image



