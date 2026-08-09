//
// Created by camilo on 2023-10-06 20:16 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pixmap.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"


pixmap::pixmap()
{


}


pixmap::~pixmap()
{


}


void pixmap::create_as_descriptor(const ::i32_size & size, ::enum_flag eflagCreate, ::i32 iGoodStride)
{

   if (size == m_sizeRaw && size == m_size)
   {

      return;

   }

   destroy();

   m_sizeRaw = size;

   m_size = size;

   m_iScan = size.cx * 4;

   if (iGoodStride >= m_iScan)
   {

      m_iScan = iGoodStride;

   }

   m_eflagElement = eflagCreate;

   m_estatus = success;

}


void pixmap::create_from_data(const ::i32_size & size, const ::image32_t * pimage32, ::i32 iScan,
                              ::enum_flag eflagCreate, bool bPreserve)
{

   create_as_descriptor(size, DEFAULT_CREATE_IMAGE_FLAG, iScan);

   copy(size, pimage32, m_iScan);

}


#define byte_clip2(i) (i)
void pixmap::mult_alpha_fast()
{
   auto map = this->map();

   //::u8 *dst = (::u8 *)map.data();
   //::i64 size = scan_area();


   //  >> 2 instead of >> 2 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) *
   //  (254/255) > 255

   auto h = map.height();

   auto w = map.width();

   for (::i32 iLine = 0; iLine < map.height(); iLine++)
   {

      auto pimage32Line = map.line_data(iLine);

      auto x = map.width();

      while (x > 0)
      {
         auto dst = (::u8 *)pimage32Line;
         if (dst[3] == 0)
         {
            *((image32_t *)dst) = {};
         }
         else if (dst[3] != 255)
         {
            dst[0] = byte_clip2(((::i32)dst[0] * (::i32)dst[3]) >> 8);
            dst[1] = byte_clip2(((::i32)dst[1] * (::i32)dst[3]) >> 8);
            dst[2] = byte_clip2(((::i32)dst[2] * (::i32)dst[3]) >> 8);
         }
         x--;
         pimage32Line++;
      }
   }

   // return true;
}

bool pixmap::_is_ok() const 
{
   return ::particle::_is_ok() && pixmap_t::is_ok();
}


pixmap_lease pixmap::map(bool bApplyTransform) const 
{
   
   return {(::pixmap *)this, bApplyTransform}; 

}


pixmap_lease pixmap::map(const ::i32_rectangle & rectangle) const
{

   return { (::pixmap*)this, rectangle };

}


bool pixmap::_on_map(bool bApplyAlphaTransform)
{

   if (m_interlockedcountMap > 0)
   {

      if (!m_bMapped)
      {

         throw ::exception(error_wrong_state);

      }

   }
   
   m_interlockedcountMap++;

   if (m_bMapped)
   {

      return false;

   }

   return true;

}


void pixmap::_map(bool bApplyTransform)
{

   if (!_on_map(bApplyTransform))
   {

      return;

   }

   auto pimage32Owned = (::image32_t *)m_memoryPixmap.data();

   auto bUsingOwnedMemory =
      ::is_set(pimage32Owned)
      && m_pimage32Raw == pimage32Owned;

   if (!m_pimage32Raw
      || !m_pimage32
      || (bUsingOwnedMemory && m_memoryPixmap.size() < scan_area_in_bytes()))
   {

      m_memoryPixmap.set_size(scan_area_in_bytes());

      m_pimage32Raw = (::image32_t *)m_memoryPixmap.data();

   }

   pixmap_map();

   m_bMapped = true;

}


void pixmap::set_exif_orientation(int iExifOrientation)
{



}


void pixmap::on_load_image()
{


}


//void pixmap::defer_update_image()
//{
//
//
//}


::image::image_extension * pixmap::get_extension()
{

   return nullptr;

}


void pixmap::copy(const pixmap_t * ppixmap)
{

   create_as_descriptor(ppixmap->size());

   auto mapThis = this->map();

   mapThis.copy(ppixmap->size(), ppixmap->m_pimage32, ppixmap->m_iScan);

}


void pixmap::copy(const ::i32_size &size, const ::image32_t *pimage32, ::i32 iScan)
{

   auto mapThis = this->map();

   mapThis.copy(size, pimage32, iScan);
   
}




void pixmap::on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan)
{

   create_as_descriptor(size, DEFAULT_CREATE_IMAGE_FLAG, iScan);

   copy(size, pimage32, iScan);

}


//
//void pixmap::unmap(bool bDoUnmap) const
//{
//
//   ((pixmap *)this)->_unmap(bDoUnmap);
//
//}


bool pixmap::_on_unmap(bool bDoUnmap)
{

   if (m_interlockedcountMap <= 0)
   {

      throw ::exception(error_wrong_state);

   }

   m_interlockedcountMap--;

   if (m_interlockedcountMap > 0)
   {

      return false;

   }

   if ((!m_bMapped || !m_pimage32Raw) && bDoUnmap)
   {

      throw ::exception(error_wrong_state);
   }

   return true;

}


void pixmap::_unmap(bool bDoUnmap)
{

   if (!_on_unmap(bDoUnmap))
   {

      return;

   }

   if (bDoUnmap)
   {

      m_pimage32Raw = nullptr;
      m_pimage32 = nullptr;

   }

   m_bMapped = false;

}


//::image::lock pixmap::lock(::i32 stride, ::image::enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
//{
//
//   //m_ppixmapLock = ppixmapLock;
//
//   m_ecopydisposition = ecopydisposition;
//
//   if (//m_ppixmapLock->m_iScan == stride 
//      m_iScan == stride
//      && m_ecopydisposition == ::image::e_copy_disposition_none)
//   {
//
//      //reference(*m_ppixmapLock);
//
//
//
//   }
//   else
//   {
//         
//      m_memoryPixmap.set_size(scan_area_in_bytes());
//
//      m_pimage32Raw = (::image32_t *) m_memoryPixmap.data();
//
//      m_pimage32 = m_pimage32Raw;
//
//      ///::pixmap_t::create(m_memory, m_ppixmapLock->size(), stride);
//
//   }
//
//   //return this;
//      
//}
//
//
//::image::lock pixmap::no_padding_lock(::image::enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
//{
//      
//   return lock(ppixmapLock->width() * 4, ecopydisposition, ppixmapLock);
//
//}
//
//
//::image::lock pixmap::source_lock(::image::enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
//{
//
//   return lock(ppixmapLock->m_iScan, ecopydisposition, ppixmapLock);
//
//}
//
//   
//void pixmap::unlock(::image::lock * pimagelock)
//{
//
//   if (pimagelock->data() != this->data())
//   {
//
//      p->pixmap_t::copy(this, m_ecopydisposition);
//
//   }
//
//}


CLASS_DECL_ACME::string _001_image32_diagnostics(const ::i32_size & size, const image32_t * pimage32, int iScan)
{

   ::string strImage32;

   strImage32.formatf("\n\n   pimage32=%p (%d,%d) scan=%d,", pimage32, size.cx, size.cy, iScan);

   auto pu8 = (::u8 *)pimage32;

   if (!pu8)
   {

      return strImage32;

   }

   ::collection::count opaqueCount = 0;
   ::collection::count transparentCount = 0;
   ::collection::count translucentCount = 0;
   ::collection::count pixelCount = 0;

   for (int i = 0; i < size.cy; i++)
   {

      auto pu8Line = pu8 + (iScan * i);

      auto p = pu8Line;

      for (int j = 0; j < size.cx; j++)
      {

         auto r = p[0];
         auto g = p[1];
         auto b = p[2];
         auto a = p[3];

         if (a == 255)
         {

            opaqueCount++;

         }
         else if (a == 0)
         {

            transparentCount++;

         }
         else
         {

            translucentCount++;

         }

         p += 4;

         pixelCount++;

      }

   }

   strImage32.append_formatf("\n   pixel=%llu opaque=%llu transp=%llu transl=%llu\n", pixelCount, opaqueCount, transparentCount, translucentCount);

   return strImage32;

}


::pixmap_pointer pixmap::get_resized_pixmap(const ::i32_size & size)
{

   return this;

}





