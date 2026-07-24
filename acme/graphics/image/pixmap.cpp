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


void pixmap::create(const ::i32_size & size, ::enum_flag eflagCreate, ::i32 iGoodStride, bool bPreserve)
{

   if (size == m_sizeRaw && size == m_size)
   {

      return;

   }

   unmap();

   m_sizeRaw = size;

   m_size = size;

   m_iScan = size.cx * 4;

   if (iGoodStride >= m_iScan)
   {

      m_iScan = iGoodStride;

   }

}


void pixmap::create_from_data(const ::i32_size & size, const ::image32_t * pimage32, ::i32 iScan,
                              ::enum_flag eflagCreate, bool bPreserve)
{

   create(size, DEFAULT_CREATE_IMAGE_FLAG, iScan);

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
   return ::particle::is_ok() && pixmap_t::is_ok();
}


pixmap_lease pixmap::map(bool bApplyTransform) const 
{
   
   return {(::pixmap *)this, bApplyTransform}; 

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

   if (!m_pimage32Raw || !m_pimage32)
   {

      m_memoryPixmap.set_size(scan_area());

      m_pimage32Raw = (::image32_t *)m_memoryPixmap.data();

      m_pimage32 = (::image32_t *)m_memoryPixmap.data();

   }

   m_bMapped = true;

}


void pixmap::set_exif_orientation(int iExifOrientation)
{



}


void pixmap::on_load_image()
{


}


void pixmap::defer_update_image()
{


}


::image::image_extension * pixmap::get_extension()
{

   return nullptr;

}


void pixmap::copy(const ::i32_size &size, const ::image32_t *pimage32, ::i32 iScan)
{

   map();

   pixmap_t::copy(size, pimage32, iScan);
   
}


void pixmap::on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan)
{

   create_from_data(size, pimage32, iScan);

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


#if defined(WINDOWS_DESKTOP)
::i32 pixmap_t::g_iRedLowerDefault = 0;
#elif defined(LINUX)
::i32 pixmap_t::g_iRedLowerDefault = 0;
#elif defined(FREEBSD) || defined(OPENBSD) || (defined(UNIVERSAL_WINDOWS) && OSBIT == 32)
::i32 pixmap_t::g_iRedLowerDefault = 0;
#else
::i32 pixmap_t::g_iRedLowerDefault = 1;
#endif




#define byte_clip2(i) (i)
void pixmap_t::mult_alpha()
{

   ::u8 * dst = (::u8 *)data();
   ::i64 size = m_size.area();


   //  / 255 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = byte_clip2(((::i32)dst[0] * (::i32)dst[3]) / 255);
      dst[1] = byte_clip2(((::i32)dst[1] * (::i32)dst[3]) / 255);
      dst[2] = byte_clip2(((::i32)dst[2] * (::i32)dst[3]) / 255);

      dst[4 + 0] = byte_clip2(((::i32)dst[4 + 0] * (::i32)dst[4 + 3]) / 255);
      dst[4 + 1] = byte_clip2(((::i32)dst[4 + 1] * (::i32)dst[4 + 3]) / 255);
      dst[4 + 2] = byte_clip2(((::i32)dst[4 + 2] * (::i32)dst[4 + 3]) / 255);

      dst[8 + 0] = byte_clip2(((::i32)dst[8 + 0] * (::i32)dst[8 + 3]) / 255);
      dst[8 + 1] = byte_clip2(((::i32)dst[8 + 1] * (::i32)dst[8 + 3]) / 255);
      dst[8 + 2] = byte_clip2(((::i32)dst[8 + 2] * (::i32)dst[8 + 3]) / 255);

      dst[12 + 0] = byte_clip2(((::i32)dst[12 + 0] * (::i32)dst[12 + 3]) / 255);
      dst[12 + 1] = byte_clip2(((::i32)dst[12 + 1] * (::i32)dst[12 + 3]) / 255);
      dst[12 + 2] = byte_clip2(((::i32)dst[12 + 2] * (::i32)dst[12 + 3]) / 255);

      dst[16 + 0] = byte_clip2(((::i32)dst[16 + 0] * (::i32)dst[16 + 3]) / 255);
      dst[16 + 1] = byte_clip2(((::i32)dst[16 + 1] * (::i32)dst[16 + 3]) / 255);
      dst[16 + 2] = byte_clip2(((::i32)dst[16 + 2] * (::i32)dst[16 + 3]) / 255);

      dst[20 + 0] = byte_clip2(((::i32)dst[20 + 0] * (::i32)dst[20 + 3]) / 255);
      dst[20 + 1] = byte_clip2(((::i32)dst[20 + 1] * (::i32)dst[20 + 3]) / 255);
      dst[20 + 2] = byte_clip2(((::i32)dst[20 + 2] * (::i32)dst[20 + 3]) / 255);

      dst[24 + 0] = byte_clip2(((::i32)dst[24 + 0] * (::i32)dst[24 + 3]) / 255);
      dst[24 + 1] = byte_clip2(((::i32)dst[24 + 1] * (::i32)dst[24 + 3]) / 255);
      dst[24 + 2] = byte_clip2(((::i32)dst[24 + 2] * (::i32)dst[24 + 3]) / 255);

      dst[28 + 0] = byte_clip2(((::i32)dst[28 + 0] * (::i32)dst[28 + 3]) / 255);
      dst[28 + 1] = byte_clip2(((::i32)dst[28 + 1] * (::i32)dst[28 + 3]) / 255);
      dst[28 + 2] = byte_clip2(((::i32)dst[28 + 2] * (::i32)dst[28 + 3]) / 255);

      dst += 4 * 8;
      size -= 8 ;
   }
   while (size > 0)
   {
      dst[0] = byte_clip2(((::i32)dst[0] * (::i32)dst[3]) / 255);
      dst[1] = byte_clip2(((::i32)dst[1] * (::i32)dst[3]) / 255);
      dst[2] = byte_clip2(((::i32)dst[2] * (::i32)dst[3]) / 255);
      dst += 4;
      size--;
   }

}



void pixmap_t::vertical_swap()
{

   auto ppixmap = this;

   try
   {

      ::i32 iStride = ppixmap->m_iScan;

      if (iStride <= 0)
      {

         iStride = ppixmap->width() * sizeof(::image32_t);

      }

      ::i32 w = iStride / sizeof(::image32_t);

      ::i32 h = ppixmap->height();

      ::i32 wBytes = ppixmap->width() * sizeof(::image32_t);

      auto pdata = ppixmap->image32();

      ::u8 * pline1 = (::u8 *)pdata;

      ::u8 * pline2 = (::u8 *)(pdata + (w - 1) * h);

      memory memory;

      memory.set_size(wBytes);

      ::u8 * pstore = memory.data();

      ::i32 halfh = h / 2;

      for (::i32 i = 0; i < halfh; i++)
      {

         ::memory_copy(pstore, pline1, wBytes);

         ::memory_copy(pline1, pline2, wBytes);

         ::memory_copy(pline2, pstore, wBytes);

         pline1 += iStride;

         pline2 -= iStride;

      }

   }
   catch (...)
   {

   }

}


void pixmap_t::copy(const ::pixmap_t *ppixmapSrc) {

   copy(size().minimum(ppixmapSrc->size()), ppixmapSrc);

}


void pixmap_t::y_swap_copy(const ::pixmap_t *ppixmapSrc)
{

   y_swap_copy(size().minimum(ppixmapSrc->size()), ppixmapSrc);

}


void pixmap_t::copy(const ::i32_size &size, const ::pixmap_t *ppixmapSrc)
{

   m_pimage32->copy(size, scan_size(), ppixmapSrc);

}


void pixmap_t::copy(const ::i32_size &size, const ::image32_t *pimage32, ::i32 iScan)
{

   m_pimage32->copy(size, scan_size(), pimage32, iScan);

}


void pixmap_t::y_swap_copy(const ::i32_size &size, const ::pixmap_t *ppixmapSrc)
{

   m_pimage32->vertical_swap_copy(size, scan_size(), ppixmapSrc->data(), ppixmapSrc->m_iScan);

}


void pixmap_t::copy(const ::pixmap_t *ppixmapSrc, const ::image::enum_copy_disposition &ecopydisposition)
{
   
   if (ecopydisposition == ::image::e_copy_disposition_y_swap)
   {

      y_swap_copy(ppixmapSrc);

   }
   else
   {

      copy(ppixmapSrc);

   }

}



pixmap_t &pixmap_t::operator=(const pixmap_t &pixmap)
{

   if (this != &pixmap)
   {

      copy(&pixmap);

   }

   return *this;

}


::color::color pixmap_t::average_color()
{

   auto h = this->height();

   auto w = this->width();

   auto s = this->scan_size();

   auto data = (::u8 *) this->m_pimage32;

   ::i64 r = 0;
   ::i64 g = 0;
   ::i64 b = 0;
   ::i64 a = 0;

   for (::i32 n = 0; n < h; n++) {

      auto pline = data + s * n;

      for (::i32 l = 0; l < w; l++) {

         a += pline[3];
         r += pline[2];
         g += pline[1];
         b += pline[0];

         pline += 4;

      }

   }

   if (a == 0) {

      return ::color::transparent;

   } else {

      auto area = w * h;

      ::f64 dA = ((::f64) a) / (::f64) (area);

      ::f64 dR = ((::f64) r) / (::f64) a;

      ::f64 dG = ((::f64) g) / (::f64) a;

      ::f64 dB = ((::f64) b) / (::f64) a;

      return argb(dA / 255.0, dR, dG, dB);

   }


}



bool pixmap_t::create(::memory &memory, const ::i32_size &size, ::i32 stride)
{

   if (stride < 0)
   {

      stride = size.cx * 4;

   }
   else if (stride < size.cx * 4)
   {

      throw ::exception(::error_bad_argument);

   }

   m_iScan = stride;

   memory.set_size(m_iScan * size.cy);

   m_sizeRaw = size;

   m_size = size;

   m_pimage32Raw = (::image32_t*)memory.data();

   m_pimage32 = (::image32_t*)memory.data();

   return true;

}


void pixmap_t::reference(const pixmap_t &pixmap) {

   memcpy((void *) this, &pixmap, sizeof(*this));

}



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
