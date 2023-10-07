//
// Created by camilo on 2023-10-06 20:16 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pixmap.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"


CLASS_DECL_ACME void copy_image32(::image32_t * pimage32Dst, const ::point_i32 & point, const ::size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

   ::u8 * pDst = (::u8 *)pimage32Dst;

   return copy_image32((::image32_t *)pDst + point.x() * sizeof(::image32_t) + point.y() * iStrideDst, size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);

}


CLASS_DECL_ACME void copy_image32(::image32_t * pimage32Dst, const ::rectangle_i32 & rectangle, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

   return copy_image32(pimage32Dst, rectangle.top_left(), rectangle.size(), iStrideDst, pimage32Src, iStrideSrc);

}


void vertical_swap(pixmap * ppixmap)
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

      u8 * pline1 = (u8 *) pdata;

      u8 * pline2 = (u8 *) (pdata + (w - 1) * h);

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


void vertical_swap_copy_image32(::image32_t * pimage32Dst, int cxParam,int cyParam,int iStrideDst, const ::image32_t * pimage32Src,int iStrideSrc)
{

   try
   {

      if(iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(::image32_t);

      }

      int wsrc = iStrideSrc / sizeof(::image32_t);
      int wdst = iStrideDst / sizeof(::image32_t);
      int cw = cxParam * sizeof(::image32_t);

      auto * psrc = pimage32Src;
      auto * pdst = (::image32_t * )((u8 *) (pimage32Dst) + iStrideDst * (cyParam - 1));

      for(int i = 0; i < cyParam; i++)
      {

         ::memory_copy(pdst,psrc,cw);

         pdst -= wdst;

         psrc += wsrc;

      }


   }

   catch (...)
   {

   }


}


CLASS_DECL_ACME void vertical_swap_copy_image32_swap_red_blue(::image32_t * pimage32Dst, int cxParam,int cyParam,int iStrideDst, const ::image32_t * pimage32Src,int iStrideSrc)
{

   try
   {


      if(iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(::image32_t);

      }

      int wsrc = iStrideSrc / sizeof(::image32_t);
      int wdst = iStrideDst / sizeof(::image32_t);
      int cw = cxParam * sizeof(::image32_t);

      auto * psrc = pimage32Src;
      auto * pdst = (::image32_t * )((u8 *) (pimage32Dst) + iStrideDst * (cyParam - 1));

      for(int i = 0; i < cyParam; i++)
      {

         u8 * ps = (u8 *) psrc;

         u8 * pd = (u8 *) pdst;

         for(int j = 0; j < cxParam; j++)
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


void copy_image32(::image32_t * pimage32Dst, int cxParam, int cyParam, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

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

      if (iStrideDst == iStrideSrc)
      {

         ::memory_copy(pimage32Dst, pimage32Src, cyParam * iStrideDst);

      }
      else
      {

         int cw = cxParam * sizeof(::image32_t);

         auto psrc = (::u8 *) pimage32Src;

         auto pdst = (::u8 *) pimage32Dst;

         for (int i = 0; i < cyParam; i++)
         {

            ::memory_copy(pdst, psrc, cw);

            pdst += iStrideDst;

            psrc += iStrideSrc;

         }

      }

   }
   catch (...)
   {

   }

}


void copy_image32_swap_red_blue(::image32_t * pimage32Dst, int cxParam,int cyParam,int iStrideDst, const ::image32_t * pimage32Src,int iStrideSrc)
{

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

      if(iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(::image32_t);

      }

      int wsrc = iStrideSrc / sizeof(::image32_t);
      int wdst = iStrideDst / sizeof(::image32_t);
      int cw = cxParam * sizeof(::image32_t);


      auto * psrc = pimage32Src;
      auto * pdst = pimage32Dst;


      for(int i = 0; i < cyParam; i++)
      {

         u8 * ps = (u8 *) psrc;

         u8 * pd = (u8 *) pdst;

         for(int j = 0; j < cxParam; j++)
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


void _001ProperCopyColorref(::image32_t * pimage32Dst, int cxParam,int cyParam,int iStrideDst,const ::image32_t * pimage32Src,int iStrideSrc)
{

#ifdef WINDOWS_DESKTOP

   copy_image32(pimage32Dst, cxParam, cyParam, iStrideDst, pimage32Src, iStrideSrc);

#else

   vertical_swap_copy_image32(pimage32Dst, cxParam, cyParam, iStrideDst, pimage32Src, iStrideSrc);

#endif


}


void copy_image32(::image32_t * pimage32Dst, int xParam, int yParam, int cxParam,int cyParam, int iStrideDst, const ::image32_t * pimage32Src,int iStrideSrc)
{

   try
   {

      if(iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(::image32_t);

      }

      int wsrc = iStrideSrc / sizeof(::image32_t);
      int wdst = iStrideDst / sizeof(::image32_t);
      int cw = cxParam * sizeof(::image32_t);

      auto psrc = &pimage32Src[xParam + yParam * iStrideSrc / sizeof(::image32_t)];
      auto pdst = &pimage32Dst[xParam + yParam * iStrideDst / sizeof(::image32_t)];

      for(int i = 0; i < cyParam; i++)
      {

         ::memory_copy(pdst,psrc,cw);

         pdst += wdst;

         psrc += wsrc;

      }


   }

   catch (...)
   {

   }

}


CLASS_DECL_ACME void copy_image32(::image32_t * pimage32Dst, const ::size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

   copy_image32(pimage32Dst, size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);

}



