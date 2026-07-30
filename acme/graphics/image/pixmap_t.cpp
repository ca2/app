// From pixmap.cpp on 2026-7028 18:09 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "pixmap_t.h"

#if defined(WINDOWS_DESKTOP)
::i32 pixmap_t::g_iRedLowerDefault = 0;
#elif defined(LINUX)
::i32 pixmap_t::g_iRedLowerDefault = 0;
#elif defined(FREEBSD) || defined(OPENBSD) || (defined(UNIVERSAL_WINDOWS) && OSBIT == 32)
::i32 pixmap_t::g_iRedLowerDefault = 0;
#else
::i32 pixmap_t::g_iRedLowerDefault = 1;
#endif


void pixmap_t::fill_byte(::u8 byte)
{

   if (m_size == m_sizeRaw)
   {

      memset(m_pimage32Raw, byte, scan_area_in_bytes());

   }
   else
   {
      
      for (int i = 0; i < m_size.cy; i++)
      {

         auto pline = line_data(i);

         memset(m_pimage32, byte, m_size.cx * 4);

      }

   }

}


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

      ::i32 h = ppixmap->height();

      ::i32 width = ppixmap->width();

      auto pdata = (::u8 *)ppixmap->image32();

      if (!pdata ||
         width <= 0 ||
         h <= 1 ||
         width > I32_MAXIMUM / (::i32)sizeof(::image32_t))
      {

         return;

      }

      ::i32 iRowBytes =
         width * (::i32)sizeof(::image32_t);

      ::i32 iStride = ppixmap->m_iScan;

      if (iStride <= 0)
      {

         iStride = iRowBytes;

      }

      if (iStride < iRowBytes)
      {

         return;

      }

      ::u64 uBottomOffset =
         (::u64)iStride * (::u64)(h - 1);

      if (uBottomOffset > (::u64)IPTR_MAXIMUM)
      {

         return;

      }

      ::u8 * pline1 = pdata;

      ::u8 * pline2 =
         pdata + (::memsize)uBottomOffset;

      memory memory;

      memory.set_size(iRowBytes);

      ::u8 * pstore = memory.data();

      ::i32 halfh = h / 2;

      for (::i32 i = 0; i < halfh; i++)
      {

         ::memory_copy(pstore, pline1, iRowBytes);

         ::memory_copy(pline1, pline2, iRowBytes);

         ::memory_copy(pline2, pstore, iRowBytes);

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



//bool pixmap_t::create(::memory &memory, const ::i32_size &size, ::i32 stride)
//{
//
//   if (stride < 0)
//   {
//
//      stride = size.cx * 4;
//
//   }
//   else if (stride < size.cx * 4)
//   {
//
//      throw ::exception(::error_bad_argument);
//
//   }
//
//   m_iScan = stride;
//
//   memory.set_size(m_iScan * size.cy);
//
//   m_sizeRaw = size;
//
//   m_size = size;
//
//   m_pimage32Raw = (::image32_t*)memory.data();
//
//   m_pimage32 = (::image32_t*)memory.data();
//
//   return true;
//
//}


void pixmap_t::reference(const pixmap_t &pixmap) {

   memcpy((void *) this, &pixmap, sizeof(*this));

}





