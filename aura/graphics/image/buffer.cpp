// created by Camilo on 2025-06-01 01:59 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "buffer.h"


namespace image
{



   buffer::buffer()
   {

      m_ecopydisposition = e_copy_disposition_none;
      
   }

      
   buffer::~buffer()
   {

   }


   buffer * buffer::lock(int stride, enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
   {

      m_ppixmapLock = ppixmapLock;

      m_ecopydisposition = ecopydisposition;

      if (m_ppixmapLock->m_iScan == stride 
         && m_ecopydisposition == e_copy_disposition_none)
      {

         reference(*m_ppixmapLock);

      }
      else
      {

         ::pixmap::create(m_memory, m_ppixmapLock->size(), stride);

      }

      return this;
      
   }


   buffer * buffer::no_padding_lock(enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
   {
      
      return lock(ppixmapLock->width() * 4, ecopydisposition, ppixmapLock);

   }


   buffer* buffer::source_lock(enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
   {

      return lock(ppixmapLock->m_iScan, ecopydisposition, ppixmapLock);

   }

   
   void buffer::unlock()
   {

      if (m_ppixmapLock->data() != this->data())
      {

         m_ppixmapLock->copy(this, m_ecopydisposition);

      }

   }

} // namespace image



