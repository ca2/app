// exif_orientation_rotate_flip from aura by camilo on 2023-10-09 12:05 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_exif.h"
#include "image32.h"
#include "pixmap.h"
#include "acme/prototype/geometry2d/rectangle.h"



//void image32_t::copy(const ::int_rectangle & rectangle, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
//{
//
//   return copy(rectangle.top_left(), rectangle.size(), iStrideDst, pimage32Src, iStrideSrc);
//
//}




void image32_t::vertical_swap_copy(int cxParam, int cyParam, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

   ::image32_t * pimage32Dst = this;
   try
   {

      if (iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(::image32_t);

      }

      int wsrc = iStrideSrc;
      int wdst = iStrideDst;
      int cw = cxParam * sizeof(::image32_t);

      unsigned char * psrc = (unsigned char*)pimage32Src;
      unsigned char * pdst = ((unsigned char *)(pimage32Dst)+iStrideDst * (cyParam - 1));

      for (int i = 0; i < cyParam; i++)
      {

         ::memory_copy(pdst, psrc, cw);

         pdst -= wdst;

         psrc += wsrc;

      }

   }
   catch (...)
   {

   }


}


void image32_t::vertical_swap_copy_swap_red_blue( int cxParam, int cyParam, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

   ::image32_t * pimage32Dst = this;
   try
   {


      if (iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(::image32_t);

      }

      int wsrc = iStrideSrc / sizeof(::image32_t);
      int wdst = iStrideDst / sizeof(::image32_t);
      int cw = cxParam * sizeof(::image32_t);

      auto * psrc = pimage32Src;
      auto * pdst = (::image32_t *)((unsigned char *)(pimage32Dst)+iStrideDst * (cyParam - 1));

      for (int i = 0; i < cyParam; i++)
      {

         unsigned char * ps = (unsigned char *)psrc;

         unsigned char * pd = (unsigned char *)pdst;

         for (int j = 0; j < cxParam; j++)
         {

            pd[0] = ps[2];
            pd[1] = ps[1];
            pd[2] = ps[0];
            pd[3] = ps[3];

            pd += sizeof(::image32_t);

            ps += sizeof(::image32_t);

         }

         pdst -= wdst;

         psrc += wsrc;

      }


   }

   catch (...)
   {

   }

}


//void image32_t::copy(int cxParam, int cyParam, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
//{
//
//   ::image32_t * pimage32Dst = this;
//
//   try
//   {
//
//
//      if (pimage32Dst == nullptr)
//      {
//
//         return;
//
//      }
//
//      if (pimage32Src == nullptr)
//      {
//
//         return;
//
//      }
//
//      if (iStrideSrc <= 0)
//      {
//
//         iStrideSrc = cxParam * sizeof(::image32_t);
//
//      }
//
//      if (iStrideDst == iStrideSrc)
//      {
//
//         ::memory_copy(pimage32Dst, pimage32Src, cyParam * iStrideDst);
//
//      }
//      else
//      {
//
//         int cw = cxParam * sizeof(::image32_t);
//
//         auto psrc = (unsigned char *)pimage32Src;
//
//         auto pdst = (unsigned char *)pimage32Dst;
//
//         for (int i = 0; i < cyParam; i++)
//         {
//
//            ::memory_copy(pdst, psrc, cw);
//
//            pdst += iStrideDst;
//
//            psrc += iStrideSrc;
//
//         }
//
//      }
//
//   }
//   catch (...)
//   {
//
//   }
//
//}


void image32_t::copy_swap_red_blue( int cxParam, int cyParam, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{


   ::image32_t * pimage32Dst = this;
   try
   {

      if (pimage32Dst == nullptr)
      {

         return;

      }

      if (pimage32Src == nullptr)
      {

         return;

      }

      if (iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(::image32_t);

      }

      int wsrc = iStrideSrc / sizeof(::image32_t);
      int wdst = iStrideDst / sizeof(::image32_t);
      int cw = cxParam * sizeof(::image32_t);


      auto * psrc = pimage32Src;
      auto * pdst = pimage32Dst;


      for (int i = 0; i < cyParam; i++)
      {

         unsigned char * ps = (unsigned char *)psrc;

         unsigned char * pd = (unsigned char *)pdst;

         for (int j = 0; j < cxParam; j++)
         {

            pd[0] = ps[2];
            pd[1] = ps[1];
            pd[2] = ps[0];
            pd[3] = ps[3];

            pd += sizeof(::image32_t);

            ps += sizeof(::image32_t);

         }

         pdst += wdst;

         psrc += wsrc;

      }


   }

   catch (...)
   {

   }


}


void image32_t::swap_red_blue(int cxParam, int cyParam, int iStride)
{


   try
   {

      if (iStride <= 0)
      {

         iStride = cxParam * sizeof(::image32_t);

      }

      auto *p = this;

      for (int i = 0; i < cyParam; i++)
      {

         auto *pline = ((unsigned char *)p) + iStride * i;

         for (int j = 0; j < cxParam; j++)
         {

            ::swap(pline[0], pline[2]);

            pline += sizeof(::image32_t);

         }

      }

   }
   catch (...)
   {
   }

}


void image32_t::_001ProperCopyColorref(int cxParam, int cyParam, int iStrideDst, const ::image32_t *pimage32Src,
                                       int iStrideSrc)
{

   ::image32_t * pimage32Dst = this;

#ifdef WINDOWS_DESKTOP

   copy(cxParam, cyParam, iStrideDst, pimage32Src, iStrideSrc);

#else

   vertical_swap_copy(cxParam, cyParam, iStrideDst, pimage32Src, iStrideSrc);

#endif


}


void image32_t::copy(int cx, int cy, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

   if (iStrideSrc == iStrideDst && cy * sizeof(image32_t) == iStrideSrc)
   {

      ::memory_copy(this, pimage32Src, cy * iStrideSrc);

      return;

   }

   ::image32_t * pimage32Dst = this;

   try
   {

      if (iStrideSrc <= 0)
      {

         iStrideSrc = cx * sizeof(::image32_t);

      }

      int wsrc = iStrideSrc;
      int wdst = iStrideDst;
      int cw = cx * sizeof(::image32_t);

      auto psrc = (unsigned char*) pimage32Src;
      auto pdst = (unsigned char*) pimage32Dst;

      for (int i = 0; i < cy; i++)
      {

         ::memory_copy(pdst, psrc, cw);

         pdst += wdst;

         psrc += wsrc;

      }


   }

   catch (...)
   {

   }

}

//
//void image32_t::copy(const ::int_size & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
//{
//
//   copy(size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
//
//}


enum_rotate_flip exif_orientation_rotate_flip(int orientation)
{


   switch (orientation)
   {
   case 1:
      return e_rotate_none_flip_none;
   case 2:
      return e_rotate_none_flip_x;
   case 3:
      return e_rotate_180_flip_none;
   case 4:
      return e_rotate_180_flip_x;
   case 5:
      return e_rotate_90_flip_x;
   case 6:
      return e_rotate_90_flip_none;
   case 7:
      return e_rotate_270_flip_x;
   case 8:
      return e_rotate_270_flip_none;
   default:
      return e_rotate_none_flip_none;
   }


}


//void image32_t::copy(const ::int_size & size, int iStrideDst, const ::pixmap * ppixmapSrc)
//{
//
//   copy(size, iStrideDst, ppixmapSrc->image32(), ppixmapSrc->scan_size());
//
//}


void image32_t::set_rectangle(int x, int y, int w, int h, int s, const ::image32_t & image32Source)
{

   auto pline = ((unsigned char *) this) + s * y + x * 4;

   for (int i = 0; i < h; i++, pline += s)
   {

      auto p =(image32_t *) pline;

      for (int j = 0; j < w; j++, p++)
      {

         *p = image32Source;

      }

   }

}


void image32_t::blend_rectangle(int x, int y, int w, int h, int s, const ::image32_t & image32Source)
{

   auto pline = ((unsigned char *) this) + s * y + x * 4;

   for (int i = 0; i < h; i++, pline += s)
   {

      auto p =(image32_t *) pline;

      for (int j = 0; j < w; j++, p++)
      {

         p->m_ua[0] = image32Source.m_ua[0] + ((255 - image32Source.m_ua[3]) * p->m_ua[0] + 127) / 255;
         p->m_ua[1] = image32Source.m_ua[1] + ((255 - image32Source.m_ua[3]) * p->m_ua[1] + 127) / 255;
         p->m_ua[2] = image32Source.m_ua[2] + ((255 - image32Source.m_ua[3]) * p->m_ua[2] + 127) / 255;
         p->m_ua[3] = image32Source.m_ua[3] + ((255 - image32Source.m_ua[3]) * p->m_ua[3] + 127) / 255;

      }

   }

}


void image32_t::copy_3_channel_data(const int_size & size, int iTargetStride, const void * pdata, int iSourceStride)
{

   auto ptarget = (unsigned char *)this;

   auto psource = (const unsigned char *)pdata;

   for (int y = 0; y < size.cy(); y++)
   {

      auto ptargetLine = ptarget + (iTargetStride * y);

      auto psourceLine = psource + (iSourceStride * y);

      for (int x = 0; x < size.cx(); x++)
      {

         ptargetLine[0] = psourceLine[0];
         ptargetLine[1] = psourceLine[1];
         ptargetLine[2] = psourceLine[2];
         ptargetLine[3] = 255;

         ptargetLine += 4;
         psourceLine += 3;

      }

   }

}


void image32_t::copy_1_channel_data(const int_size &size, int stride, const void *pdata, int inputStride)
{

   auto ptarget = (const unsigned char *)this;

   auto psource = (const unsigned char *)pdata;

   for (int y = 0; y < size.cy(); y++)
   {

      auto psourceLine = psource[inputStride * y];

      auto ptargetLine = psource[inputStride * y];

      for (int x = 0; x < size.cx(); x++)
      {
      }
   }
}


image32_t *image32_t::create_copy_of(::memory &memoryAllocation, const int_size & size, int stride, const void *pdata, int channels, int inputStride)
{

   if (stride <= 0)
   {

      stride = size.cx() * 4;

   }
   else if (stride < size.cx() * 4)
   {

      throw ::exception(error_bad_argument, "stride at least hold a row with width * 4 bytes");

   }

   if (inputStride <= 0)
   {

      inputStride = size.cx() * channels;

   }

   auto imagedata = (unsigned char *)pdata;

   auto pixelCount = size.area();

   memoryAllocation.set_size(stride * size.cy());

   auto pimage32 = (image32_t *)memoryAllocation.data();

   if (channels == 4)
   {

      pimage32->copy(size, stride, (const image32_t *)pdata, inputStride);

   }
   else if (channels == 3)
   {

      pimage32->copy_3_channel_data(size, stride, pdata, inputStride);

   }
   else if (channels == 1)
   {

      pimage32->copy_1_channel_data(size, stride, pdata, inputStride);

   }
   else
   {

      throw ::exception(error_wrong_state, "Currently not supported number of channels : " + ::as_string(channels));

   }
      
   return pimage32;

}



