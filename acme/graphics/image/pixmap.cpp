//
// Created by camilo on 2023-10-06 20:16 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pixmap.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"


#if defined(WINDOWS_DESKTOP)
int pixmap::g_iRedLowerDefault = 0;
#elif defined(LINUX)
int pixmap::g_iRedLowerDefault = 0;
#elif defined(FREEBSD) || defined(OPENBSD) || (defined(UNIVERSAL_WINDOWS) && OSBIT == 32)
int pixmap::g_iRedLowerDefault = 0;
#else
int pixmap::g_iRedLowerDefault = 1;
#endif


#define byte_clip2(i) (i)
void pixmap::mult_alpha()
{

   unsigned char * dst = (unsigned char *)data();
   long long size = m_size.area();


   //  / 255 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = byte_clip2(((int)dst[0] * (int)dst[3]) / 255);
      dst[1] = byte_clip2(((int)dst[1] * (int)dst[3]) / 255);
      dst[2] = byte_clip2(((int)dst[2] * (int)dst[3]) / 255);

      dst[4 + 0] = byte_clip2(((int)dst[4 + 0] * (int)dst[4 + 3]) / 255);
      dst[4 + 1] = byte_clip2(((int)dst[4 + 1] * (int)dst[4 + 3]) / 255);
      dst[4 + 2] = byte_clip2(((int)dst[4 + 2] * (int)dst[4 + 3]) / 255);

      dst[8 + 0] = byte_clip2(((int)dst[8 + 0] * (int)dst[8 + 3]) / 255);
      dst[8 + 1] = byte_clip2(((int)dst[8 + 1] * (int)dst[8 + 3]) / 255);
      dst[8 + 2] = byte_clip2(((int)dst[8 + 2] * (int)dst[8 + 3]) / 255);

      dst[12 + 0] = byte_clip2(((int)dst[12 + 0] * (int)dst[12 + 3]) / 255);
      dst[12 + 1] = byte_clip2(((int)dst[12 + 1] * (int)dst[12 + 3]) / 255);
      dst[12 + 2] = byte_clip2(((int)dst[12 + 2] * (int)dst[12 + 3]) / 255);

      dst[16 + 0] = byte_clip2(((int)dst[16 + 0] * (int)dst[16 + 3]) / 255);
      dst[16 + 1] = byte_clip2(((int)dst[16 + 1] * (int)dst[16 + 3]) / 255);
      dst[16 + 2] = byte_clip2(((int)dst[16 + 2] * (int)dst[16 + 3]) / 255);

      dst[20 + 0] = byte_clip2(((int)dst[20 + 0] * (int)dst[20 + 3]) / 255);
      dst[20 + 1] = byte_clip2(((int)dst[20 + 1] * (int)dst[20 + 3]) / 255);
      dst[20 + 2] = byte_clip2(((int)dst[20 + 2] * (int)dst[20 + 3]) / 255);

      dst[24 + 0] = byte_clip2(((int)dst[24 + 0] * (int)dst[24 + 3]) / 255);
      dst[24 + 1] = byte_clip2(((int)dst[24 + 1] * (int)dst[24 + 3]) / 255);
      dst[24 + 2] = byte_clip2(((int)dst[24 + 2] * (int)dst[24 + 3]) / 255);

      dst[28 + 0] = byte_clip2(((int)dst[28 + 0] * (int)dst[28 + 3]) / 255);
      dst[28 + 1] = byte_clip2(((int)dst[28 + 1] * (int)dst[28 + 3]) / 255);
      dst[28 + 2] = byte_clip2(((int)dst[28 + 2] * (int)dst[28 + 3]) / 255);

      dst += 4 * 8;
      size -= 8 ;
   }
   while (size > 0)
   {
      dst[0] = byte_clip2(((int)dst[0] * (int)dst[3]) / 255);
      dst[1] = byte_clip2(((int)dst[1] * (int)dst[3]) / 255);
      dst[2] = byte_clip2(((int)dst[2] * (int)dst[3]) / 255);
      dst += 4;
      size--;
   }

}



void pixmap::vertical_swap()
{

   auto ppixmap = this;

   try
   {

      int iStride = ppixmap->m_iScan;

      if (iStride <= 0)
      {

         iStride = ppixmap->width() * sizeof(::image32_t);

      }

      int w = iStride / sizeof(::image32_t);

      int h = ppixmap->height();

      int wBytes = ppixmap->width() * sizeof(::image32_t);

      auto pdata = ppixmap->image32();

      unsigned char * pline1 = (unsigned char *)pdata;

      unsigned char * pline2 = (unsigned char *)(pdata + (w - 1) * h);

      memory memory;

      memory.set_size(wBytes);

      unsigned char * pstore = memory.data();

      int halfh = h / 2;

      for (int i = 0; i < halfh; i++)
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


void pixmap::copy(const ::pixmap * ppixmapSrc)
{

   copy(size().minimum(ppixmapSrc->size()), ppixmapSrc);

}


void pixmap::copy(const ::int_size & size, const ::pixmap * ppixmapSrc)
{

   m_pimage32->copy(size, scan_size(), ppixmapSrc);

}


pixmap & pixmap::operator =(const pixmap & pixmap)
{

   if (this != &pixmap)
   {

      copy(&pixmap);

   }

   return *this;

}


::color::color pixmap::average_color()
{

   auto h = this->height();

   auto w = this->width();

   auto s = this->scan_size();

   auto data = (unsigned char *) this->m_pimage32;

   long long r = 0;
   long long g = 0;
   long long b = 0;
   long long a = 0;

   for (int n = 0; n < h; n++) {

      auto pline = data + s * n;

      for (int l = 0; l < w; l++) {

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

      double dA = ((double) a) / (double) (area);

      double dR = ((double) r) / (double) a;

      double dG = ((double) g) / (double) a;

      double dB = ((double) b) / (double) a;

      return argb(dA / 255.0, dR, dG, dB);

   }


}



