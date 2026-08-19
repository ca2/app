// From pixmap.cpp on 2026-7028 18:09 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
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


void pixmap_t::initialize_pixmap(const ::i32_size & size, ::image32_t * pimage32, ::i32 iScan)
{

   //m_size = size;

   m_sizeRaw = size;

   m_pimage32 = pimage32;

   m_pimage32Raw = pimage32;

   m_iScan = iScan;

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




// ::i32_size pixmap_t::size() const noexcept
// {
//
//    auto pointTopLeft = this->top_left();
//
//    auto pointBottomRight = this->bottom_right();
//
//    return pointBottomRight - pointTopLeft;
//
// }
//
//
void pixmap_t::pixmap_map() const
{

   ((pixmap_t *)this)->m_pimage32 = m_pimage32Raw->offset(m_point.x, m_point.y, m_iScan);

}



void pixmap_t::pixmap_map(const ::i32_rectangle & rectangle)
{

   auto left = constrained(rectangle.left, 0, m_sizeRaw.cx);
   auto top = constrained(rectangle.top, 0, m_sizeRaw.cy);
   auto right = constrained(rectangle.right, 0, m_sizeRaw.cx);
   auto bottom = constrained(rectangle.bottom, 0, m_sizeRaw.cy);

   m_point = { left, top };
   m_size = { right - left, bottom - top };

   pixmap_map();

}


void pixmap_t::pixmap_unmap()
{

   m_point.clear();

   m_size = m_sizeRaw;

   m_pimage32 = m_pimage32Raw;


}


void pixmap_t::fill_byte(::u8 u)
{

   pixmap_map();

   auto p = m_pimage32;

   auto point = this->top_left();

   auto size = this->size();

   auto right = point.x + size.cx;

   auto bottom = point.y + size.cy;

   for (int i = point.y; i < bottom; i++)
   {

      auto pline = (::u8 *) p->offset(point.x, i, m_iScan);

      for (int j = point.x; j < right; j++)
      {

         pline[0] = u;
         pline[1] = u;
         pline[2] = u;
         pline[3] = u;

         pline += 4;

      }

   }

}


void pixmap_t::raw_copy(
   const ::i32_point & pointTarget,
   const ::i32_size & size,
   const ::i32_point & pointSource,
   const ::i32_size & sizeSource,
   const ::image32_t * pimage32,
   ::i32 iScan)
{

   if (!m_pimage32Raw ||
       !pimage32 ||
       m_sizeRaw.cx <= 0 ||
       m_sizeRaw.cy <= 0 ||
       sizeSource.cx <= 0 ||
       sizeSource.cy <= 0 ||
       size.cx <= 0 ||
       size.cy <= 0)
   {

      return;

   }

   ::i32 xTarget = m_point.x + pointTarget.x;
   ::i32 yTarget = m_point.y + pointTarget.y;

   ::i32 xSource = pointSource.x;
   ::i32 ySource = pointSource.y;

   ::i32 cx = size.cx;
   ::i32 cy = size.cy;


   //
   // Clip source against its left edge.
   //
   if (xSource < 0)
   {

      auto dx = -xSource;

      xSource = 0;
      xTarget += dx;
      cx -= dx;

   }


   //
   // Clip source against its top edge.
   //
   if (ySource < 0)
   {

      auto dy = -ySource;

      ySource = 0;
      yTarget += dy;
      cy -= dy;

   }


   //
   // Clip target against its left edge.
   //
   if (xTarget < 0)
   {

      auto dx = -xTarget;

      xTarget = 0;
      xSource += dx;
      cx -= dx;

   }


   //
   // Clip target against its top edge.
   //
   if (yTarget < 0)
   {

      auto dy = -yTarget;

      yTarget = 0;
      ySource += dy;
      cy -= dy;

   }


   if (cx <= 0 || cy <= 0)
   {

      return;

   }


   //
   // Clip against source right edge.
   //
   if (xSource + cx > sizeSource.cx)
   {

      cx = sizeSource.cx - xSource;

   }


   //
   // Clip against source bottom edge.
   //
   if (ySource + cy > sizeSource.cy)
   {

      cy = sizeSource.cy - ySource;

   }


   //
   // Clip against target right edge.
   //
   if (xTarget + cx > m_sizeRaw.cx)
   {

      cx = m_sizeRaw.cx - xTarget;

   }


   //
   // Clip against target bottom edge.
   //
   if (yTarget + cy > m_sizeRaw.cy)
   {

      cy = m_sizeRaw.cy - yTarget;

   }


   if (cx <= 0 || cy <= 0)
   {

      return;

   }


   m_pimage32Raw->copy(
      xTarget,
      yTarget,
      cx,
      cy,
      m_iScan,
      xSource,
      ySource,
      pimage32,
      iScan);

}




void pixmap_t::copy(
   const ::i32_point & pointTarget,
   const ::i32_size & size,
   const ::i32_point & pointSource,
   const ::pixmap_t & pixmapSource)
{

   copy(pointTarget, size, pointSource, pixmapSource.size(), pixmapSource.m_pimage32, pixmapSource.m_iScan);

}


void pixmap_t::copy(
   const ::i32_point & pointTarget,
   const ::i32_size & size,
   const ::i32_point & pointSource,
   const ::i32_size & sizeSource,
   const ::image32_t * pimage32,
   ::i32 iScan)
{

   auto sizeThis = this->size();

   if (!m_pimage32 ||
       !pimage32 ||
       sizeThis.cx <= 0 ||
       sizeThis.cy <= 0 ||
       sizeSource.cx <= 0 ||
       sizeSource.cy <= 0 ||
       size.cx <= 0 ||
       size.cy <= 0)
   {

      return;

   }

   ::i32 xTarget = pointTarget.x;
   ::i32 yTarget = pointTarget.y;

   ::i32 xSource = pointSource.x;
   ::i32 ySource = pointSource.y;

   ::i32 cx = size.cx;
   ::i32 cy = size.cy;


   //
   // Clip source against its left edge.
   //
   if (xSource < 0)
   {

      auto dx = -xSource;

      xSource = 0;
      xTarget += dx;
      cx -= dx;

   }


   //
   // Clip source against its top edge.
   //
   if (ySource < 0)
   {

      auto dy = -ySource;

      ySource = 0;
      yTarget += dy;
      cy -= dy;

   }


   //
   // Clip target against its left edge.
   //
   if (xTarget < 0)
   {

      auto dx = -xTarget;

      xTarget = 0;
      xSource += dx;
      cx -= dx;

   }


   //
   // Clip target against its top edge.
   //
   if (yTarget < 0)
   {

      auto dy = -yTarget;

      yTarget = 0;
      ySource += dy;
      cy -= dy;

   }


   if (cx <= 0 || cy <= 0)
   {

      return;

   }


   //
   // Clip against source right edge.
   //
   if (xSource + cx > sizeSource.cx)
   {

      cx = sizeSource.cx - xSource;

   }


   //
   // Clip against source bottom edge.
   //
   if (ySource + cy > sizeSource.cy)
   {

      cy = sizeSource.cy - ySource;

   }


   //
   // Clip against target right edge.
   //
   if (xTarget + cx > sizeThis.cx)
   {

      cx = sizeThis.cx - xTarget;

   }


   //
   // Clip against target bottom edge.
   //
   if (yTarget + cy > sizeThis.cy)
   {

      cy = sizeThis.cy - yTarget;

   }


   if (cx <= 0 || cy <= 0)
   {

      return;

   }


   m_pimage32->copy(
      xTarget,
      yTarget,
      cx,
      cy,
      m_iScan,
      xSource,
      ySource,
      pimage32,
      iScan);

}


void pixmap_t::fill_solid_rectangle(const ::i32_rectangle & rectangle, const ::color::color & color)
{

   if (::is_null(m_pimage32))
   {

      return;

   }

   ::image32_t image32Pixel;
   
   image32Pixel.assign(color, m_colorindexes);

   auto size = this->size();

   auto x = constrained(rectangle.left, 0, size.cx);

   auto y = constrained(rectangle.top, 0, size.cy);

   auto x2 = constrained(rectangle.right, 0, size.cx);

   auto y2 = constrained(rectangle.bottom, 0, size.cy);

   auto w = x2 - x;

   auto h = y2 - y;

   auto s = m_iScan;

   auto pline = ((::u8 *)m_pimage32) + s * y + x * 4;

   for (::i32 i = 0; i < h; i++, pline += s)
   {

      auto p = (image32_t *)pline;

      for (::i32 j = 0; j < w; j++, p++)
      {

         *p = image32Pixel;

      }

   }

}



void pixmap_t::blend_color(const ::i32_rectangle & rectangle, const ::color::color & color)
{

   if (::is_null(m_pimage32))
   {

      return;

   }

   auto size = this->size();

   auto x = constrained(rectangle.left, 0, size.cx);

   auto y = constrained(rectangle.top, 0, size.cy);

   auto x2 = constrained(rectangle.right, 0, size.cx);

   auto y2 = constrained(rectangle.bottom, 0, size.cy);

   auto w = x2 - x;

   auto h = y2 - y;

   auto s = m_iScan;

   if (w <= 0 || h <= 0)
   {

      return;

   }

   ::image32_t image32Pixel;

   // Creates a premultiplied-alpha pixel.
   image32Pixel.assign(color, m_colorindexes);

   m_pimage32->blend_rectangle(
      x,
      y,
      w,
      h,
      s,
      image32Pixel);


}



