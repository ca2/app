// created by Camilo on 2025-06-01 01:59 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "aaa_buffer.h"


namespace image
{



   aaa_buffer::aaa_buffer()
   {

      m_ecopydisposition = e_copy_disposition_none;
      
   }

      
   aaa_buffer::~aaa_buffer()
   {

   }


   aaa_buffer * aaa_buffer::lock(::i32 stride, enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
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
         
         m_memoryPixmap.set_size(scan_area_in_bytes());

         m_pimage32Raw = (::image32_t *) m_memoryPixmap.data();

         m_pimage32 = m_pimage32Raw;

         ///::pixmap_t::create(m_memory, m_ppixmapLock->size(), stride);

      }

      return this;
      
   }


   aaa_buffer * aaa_buffer::no_padding_lock(enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
   {
      
      return lock(ppixmapLock->width() * 4, ecopydisposition, ppixmapLock);

   }


   aaa_buffer* aaa_buffer::source_lock(enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
   {

      return lock(ppixmapLock->m_iScan, ecopydisposition, ppixmapLock);

   }

   
   void aaa_buffer::unlock()
   {

      if (m_ppixmapLock->data() != this->data())
      {

         m_ppixmapLock->pixmap_t::copy(this, m_ecopydisposition);

      }

   }

} // namespace image



