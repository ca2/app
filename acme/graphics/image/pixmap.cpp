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

   u8 * dst = (u8 *)data();
   i64 size = m_size.area();


   //  / 255 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) / 255);
      dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) / 255);
      dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) / 255);

      dst[4 + 0] = byte_clip2(((i32)dst[4 + 0] * (i32)dst[4 + 3]) / 255);
      dst[4 + 1] = byte_clip2(((i32)dst[4 + 1] * (i32)dst[4 + 3]) / 255);
      dst[4 + 2] = byte_clip2(((i32)dst[4 + 2] * (i32)dst[4 + 3]) / 255);

      dst[8 + 0] = byte_clip2(((i32)dst[8 + 0] * (i32)dst[8 + 3]) / 255);
      dst[8 + 1] = byte_clip2(((i32)dst[8 + 1] * (i32)dst[8 + 3]) / 255);
      dst[8 + 2] = byte_clip2(((i32)dst[8 + 2] * (i32)dst[8 + 3]) / 255);

      dst[12 + 0] = byte_clip2(((i32)dst[12 + 0] * (i32)dst[12 + 3]) / 255);
      dst[12 + 1] = byte_clip2(((i32)dst[12 + 1] * (i32)dst[12 + 3]) / 255);
      dst[12 + 2] = byte_clip2(((i32)dst[12 + 2] * (i32)dst[12 + 3]) / 255);

      dst[16 + 0] = byte_clip2(((i32)dst[16 + 0] * (i32)dst[16 + 3]) / 255);
      dst[16 + 1] = byte_clip2(((i32)dst[16 + 1] * (i32)dst[16 + 3]) / 255);
      dst[16 + 2] = byte_clip2(((i32)dst[16 + 2] * (i32)dst[16 + 3]) / 255);

      dst[20 + 0] = byte_clip2(((i32)dst[20 + 0] * (i32)dst[20 + 3]) / 255);
      dst[20 + 1] = byte_clip2(((i32)dst[20 + 1] * (i32)dst[20 + 3]) / 255);
      dst[20 + 2] = byte_clip2(((i32)dst[20 + 2] * (i32)dst[20 + 3]) / 255);

      dst[24 + 0] = byte_clip2(((i32)dst[24 + 0] * (i32)dst[24 + 3]) / 255);
      dst[24 + 1] = byte_clip2(((i32)dst[24 + 1] * (i32)dst[24 + 3]) / 255);
      dst[24 + 2] = byte_clip2(((i32)dst[24 + 2] * (i32)dst[24 + 3]) / 255);

      dst[28 + 0] = byte_clip2(((i32)dst[28 + 0] * (i32)dst[28 + 3]) / 255);
      dst[28 + 1] = byte_clip2(((i32)dst[28 + 1] * (i32)dst[28 + 3]) / 255);
      dst[28 + 2] = byte_clip2(((i32)dst[28 + 2] * (i32)dst[28 + 3]) / 255);

      dst += 4 * 8;
      size -= 8 ;
   }
   while (size > 0)
   {
      dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) / 255);
      dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) / 255);
      dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) / 255);
      dst += 4;
      size--;
   }

}



void pixmap::vertical_swap()
{

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

      u8 * pline1 = (u8 *)pdata;

      u8 * pline2 = (u8 *)(pdata + (w - 1) * h);

      memory memory;

      memory.set_size(wBytes);

      u8 * pstore = memory.data();

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
