#include "framework.h"
#include "bitmap.h"
#include "graphics.h"
#include "acme/exception/interface_only.h"
#include "acme/primitive/primitive/memory.h"
#include "aura/graphics/image/pixmap.h"


namespace draw2d
{


   bitmap::bitmap()
   {
//
//#ifdef WINDOWS_DESKTOP
//
//      m_hbitmapGet            = nullptr;
//
//#endif

      m_iStride               = 0;

   }


   bitmap::~bitmap()
   {

//#ifdef WINDOWS_DESKTOP
//
//      // Implementators (derived classes) should have released or at last nulled m_hbitmapGet to
//      // indicate it is correctly Released through ReleaseHBITMAP
//
//      if(m_hbitmapGet != nullptr)
//      {
//
//         ReleaseHBITMAP(m_hbitmapGet);
//
//      }
//
//#endif

   }


   void bitmap::CreateBitmap(::draw2d::graphics* pgraphics, const ::size_i32 & size,::u32 nPlanes,::u32 nBitcount,const void * pBits,i32 stride)
   {

      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(nPlanes);
      UNREFERENCED_PARAMETER(nBitcount);
      UNREFERENCED_PARAMETER(pBits);

      UNREFERENCED_PARAMETER(stride);
      throw ::interface_only();
      //return false;
   }


//   void bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics,LPBITMAP pBitmap)
//   {
//
//      UNREFERENCED_PARAMETER(pBitmap);
//
//      throw ::interface_only();
//      return false;
//   }


//   void bitmap::CreateDIBSection(::draw2d::graphics * pgraphics,const BITMAPINFO * pbmi,::u32 usage,void **ppvBits,int * stride,HANDLE hSection,u32 offset)
//   {

//      UNREFERENCED_PARAMETER(pgraphics);
//      UNREFERENCED_PARAMETER(pbmi);

//      UNREFERENCED_PARAMETER(usage);
//      UNREFERENCED_PARAMETER(ppvBits);
//      UNREFERENCED_PARAMETER(stride);
//      UNREFERENCED_PARAMETER(hSection);
//      UNREFERENCED_PARAMETER(offset);
//      throw ::interface_only();
//      return false;
//   }
//
//   void bitmap::HostDIBSection(::draw2d::graphics * pgraphics, const BITMAPINFO * pbmi, ::u32 usage, void * ppvBits, int stride, HANDLE hSection, u32 offset)

//   {
//      UNREFERENCED_PARAMETER(pgraphics);
//      UNREFERENCED_PARAMETER(pbmi);

//      UNREFERENCED_PARAMETER(usage);
//      UNREFERENCED_PARAMETER(ppvBits);
//      UNREFERENCED_PARAMETER(stride);
//      UNREFERENCED_PARAMETER(hSection);
//      UNREFERENCED_PARAMETER(offset);
//      // callers must be prepared to cases when the
//      // backend doesn't support "hosting" a portion of RAM as bitmap data
//      return false;
//   }
//
//   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics,const BITMAPINFOHEADER *pbmih,u32 flInit,const void *pjBits,const BITMAPINFO *pbmi,::u32 iUsage)
//   {
//      UNREFERENCED_PARAMETER(pgraphics);
//      UNREFERENCED_PARAMETER(pbmih);
//      UNREFERENCED_PARAMETER(flInit);
//      UNREFERENCED_PARAMETER(pjBits);
//      UNREFERENCED_PARAMETER(pbmi);
//      UNREFERENCED_PARAMETER(iUsage);
//      throw ::interface_only();
//      return false;
//   }


   void bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size,void **ppvBits,int * stride)
   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(ppvBits);
      UNREFERENCED_PARAMETER(stride);

      throw ::interface_only();

      //return false;

   }


   void bitmap::host_bitmap(::draw2d::graphics * pgraphics, const pixmap * ppixmap)
   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(ppixmap);

      // callers must be prepared to cases when the
      // backend doesn't support "hosting" a portion of RAM as bitmap data

      //return false;

   }


   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy,u32 flInit,const void *pjBits, ::u32 iUsage)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(flInit);
      UNREFERENCED_PARAMETER(pjBits);
      UNREFERENCED_PARAMETER(iUsage);
      throw ::interface_only();
      //return false;
   }


   u32 bitmap::SetBitmapBits(u32 dwCount,const void * pBits)

   {
      UNREFERENCED_PARAMETER(dwCount);
      UNREFERENCED_PARAMETER(pBits);

      throw ::interface_only();
      return 0;
   }


   u32 bitmap::GetBitmapBits(u32 dwCount,void * pBits) const
   {

      UNREFERENCED_PARAMETER(dwCount);
      UNREFERENCED_PARAMETER(pBits);

      throw ::interface_only();
      return 0;
   }

   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics,i32 nWidth,i32 nHeight)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw ::interface_only();
      //return false;
   }
   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics,i32 nWidth,i32 nHeight)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw ::interface_only();
      //return false;
   }


//   void ::draw2d::bitmap::dump(dump_context & dumpcontext) const
//   {
//
//      UNREFERENCED_PARAMETER(dumpcontext);
//
//      throw ::interface_only();
//
//   }


   //const ::size_i32 & size bitmap::SetBitmapDimension(i32 nWidth,i32 nHeight)
   //{
   //   UNREFERENCED_PARAMETER(nWidth);
   //   UNREFERENCED_PARAMETER(nHeight);
   //   throw ::interface_only();
   //   return ::size_i32(0,0);
   //}


   void bitmap::attach(void * posdata)
   {
      UNREFERENCED_PARAMETER(posdata);
      throw ::interface_only();
      //return false;
   }

   void * bitmap::detach()
   {
      throw ::interface_only();
      return nullptr;
   }

   //const ::size_i32 & size bitmap::set_size(const ::size_i32 & size)
   //{


   //   return SetBitmapDimension(size.cx(),size.cy());


   //}


   size_i32 bitmap::GetBitmapDimension() const
   {

      throw ::interface_only();

//      ::size_i32 sizeRet(0,0);

  //    return sizeRet;
      
      return {};

   }


   size_i32 bitmap::get_size() const
   {

      return GetBitmapDimension();

   }


   size_i32 bitmap::size() const
   {


      return GetBitmapDimension();


   }


} // namespace draw2d


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


CLASS_DECL_AURA void vertical_swap_copy_image32_swap_red_blue(::image32_t * pimage32Dst, int cxParam,int cyParam,int iStrideDst, const ::image32_t * pimage32Src,int iStrideSrc)
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


CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, const ::size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

   copy_image32(pimage32Dst, size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);

}



