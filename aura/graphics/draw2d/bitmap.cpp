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

      __UNREFERENCED_PARAMETER(size);
      __UNREFERENCED_PARAMETER(nPlanes);
      __UNREFERENCED_PARAMETER(nBitcount);
      __UNREFERENCED_PARAMETER(pBits);

      __UNREFERENCED_PARAMETER(stride);
      throw ::interface_only();
      //return false;
   }


//   void bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics,LPBITMAP pBitmap)
//   {
//
//      __UNREFERENCED_PARAMETER(pBitmap);
//
//      throw ::interface_only();
//      return false;
//   }


//   void bitmap::CreateDIBSection(::draw2d::graphics * pgraphics,const BITMAPINFO * pbmi,::u32 usage,void **ppvBits,int * stride,HANDLE hSection,u32 offset)
//   {

//      __UNREFERENCED_PARAMETER(pgraphics);
//      __UNREFERENCED_PARAMETER(pbmi);

//      __UNREFERENCED_PARAMETER(usage);
//      __UNREFERENCED_PARAMETER(ppvBits);
//      __UNREFERENCED_PARAMETER(stride);
//      __UNREFERENCED_PARAMETER(hSection);
//      __UNREFERENCED_PARAMETER(offset);
//      throw ::interface_only();
//      return false;
//   }
//
//   void bitmap::HostDIBSection(::draw2d::graphics * pgraphics, const BITMAPINFO * pbmi, ::u32 usage, void * ppvBits, int stride, HANDLE hSection, u32 offset)

//   {
//      __UNREFERENCED_PARAMETER(pgraphics);
//      __UNREFERENCED_PARAMETER(pbmi);

//      __UNREFERENCED_PARAMETER(usage);
//      __UNREFERENCED_PARAMETER(ppvBits);
//      __UNREFERENCED_PARAMETER(stride);
//      __UNREFERENCED_PARAMETER(hSection);
//      __UNREFERENCED_PARAMETER(offset);
//      // callers must be prepared to cases when the
//      // backend doesn't support "hosting" a portion of RAM as bitmap data
//      return false;
//   }
//
//   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics,const BITMAPINFOHEADER *pbmih,u32 flInit,const void *pjBits,const BITMAPINFO *pbmi,::u32 iUsage)
//   {
//      __UNREFERENCED_PARAMETER(pgraphics);
//      __UNREFERENCED_PARAMETER(pbmih);
//      __UNREFERENCED_PARAMETER(flInit);
//      __UNREFERENCED_PARAMETER(pjBits);
//      __UNREFERENCED_PARAMETER(pbmi);
//      __UNREFERENCED_PARAMETER(iUsage);
//      throw ::interface_only();
//      return false;
//   }


   void bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size,void **ppvBits,int * stride)
   {

      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(size);
      __UNREFERENCED_PARAMETER(ppvBits);
      __UNREFERENCED_PARAMETER(stride);

      throw ::interface_only();

      //return false;

   }


   void bitmap::host_bitmap(::draw2d::graphics * pgraphics, const pixmap * ppixmap)
   {

      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(ppixmap);

      // callers must be prepared to cases when the
      // backend doesn't support "hosting" a portion of RAM as bitmap data

      //return false;

   }


   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy,u32 flInit,const void *pjBits, ::u32 iUsage)
   {
      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(cx);
      __UNREFERENCED_PARAMETER(cy);
      __UNREFERENCED_PARAMETER(flInit);
      __UNREFERENCED_PARAMETER(pjBits);
      __UNREFERENCED_PARAMETER(iUsage);
      throw ::interface_only();
      //return false;
   }


   u32 bitmap::SetBitmapBits(u32 dwCount,const void * pBits)

   {
      __UNREFERENCED_PARAMETER(dwCount);
      __UNREFERENCED_PARAMETER(pBits);

      throw ::interface_only();
      return 0;
   }


   u32 bitmap::GetBitmapBits(u32 dwCount,void * pBits) const
   {

      __UNREFERENCED_PARAMETER(dwCount);
      __UNREFERENCED_PARAMETER(pBits);

      throw ::interface_only();
      return 0;
   }

   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics,i32 nWidth,i32 nHeight)
   {
      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(nWidth);
      __UNREFERENCED_PARAMETER(nHeight);
      throw ::interface_only();
      //return false;
   }
   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics,i32 nWidth,i32 nHeight)
   {
      __UNREFERENCED_PARAMETER(pgraphics);
      __UNREFERENCED_PARAMETER(nWidth);
      __UNREFERENCED_PARAMETER(nHeight);
      throw ::interface_only();
      //return false;
   }


//   void ::draw2d::bitmap::dump(dump_context & dumpcontext) const
//   {
//
//      __UNREFERENCED_PARAMETER(dumpcontext);
//
//      throw ::interface_only();
//
//   }


   //const ::size_i32 & size bitmap::SetBitmapDimension(i32 nWidth,i32 nHeight)
   //{
   //   __UNREFERENCED_PARAMETER(nWidth);
   //   __UNREFERENCED_PARAMETER(nHeight);
   //   throw ::interface_only();
   //   return ::size_i32(0,0);
   //}


   void bitmap::attach(void * posdata)
   {
      __UNREFERENCED_PARAMETER(posdata);
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
      
      return nullptr;

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

         iStride = ppixmap->width() * sizeof(::color32_t);

      }

      int w = iStride / sizeof(::color32_t);

      int h = ppixmap->height();

      int wBytes = ppixmap->width() * sizeof(::color32_t);

      ::color32_t * pdata = ppixmap->colorref();

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


void vertical_swap_copy_colorref(::color32_t * pcolorrefDst, int cxParam,int cyParam,int iStrideDst, const ::color32_t * pcolorrefSrc,int iStrideSrc)
{

   try
   {

   if(iStrideSrc <= 0)
   {

      iStrideSrc = cxParam * sizeof(::color32_t);

   }

   int wsrc = iStrideSrc / sizeof(::color32_t);
   int wdst = iStrideDst / sizeof(::color32_t);
   int cw = cxParam * sizeof(::color32_t);

   auto * psrc = pcolorrefSrc;
   auto * pdst = (::color32_t * )((u8 *) (pcolorrefDst) + iStrideDst * (cyParam - 1));

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


CLASS_DECL_AURA void vertical_swap_copy_colorref_swap_red_blue(::color32_t * pcolorrefDst, int cxParam,int cyParam,int iStrideDst, const ::color32_t * pcolorrefSrc,int iStrideSrc)
{

   try
   {


   if(iStrideSrc <= 0)
   {

      iStrideSrc = cxParam * sizeof(::color32_t);

   }

   int wsrc = iStrideSrc / sizeof(::color32_t);
   int wdst = iStrideDst / sizeof(::color32_t);
   int cw = cxParam * sizeof(::color32_t);

   auto * psrc = pcolorrefSrc;
   auto * pdst = (::color32_t * )((u8 *) (pcolorrefDst) + iStrideDst * (cyParam - 1));

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

         pd += sizeof(::color32_t);

         ps += sizeof(::color32_t);

      }

      pdst -= wdst;

      psrc += wsrc;

   }


   }

   catch (...)
   {

   }

}


void copy_colorref(::color32_t * pcolorrefDst, int cxParam, int cyParam, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc)
{

   try
   {


      if (pcolorrefDst == nullptr)
      {

         return;

      }

      if (pcolorrefSrc == nullptr)
      {

         return;

      }

      if (iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(::color32_t);

      }

      if (iStrideDst == iStrideSrc)
      {

         ::memory_copy(pcolorrefDst, pcolorrefSrc, cyParam * iStrideDst);

      }
      else
      {

         int cw = cxParam * sizeof(::color32_t);

         auto psrc = (byte *) pcolorrefSrc;

         auto pdst = (byte *) pcolorrefDst;

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


void copy_colorref_swap_red_blue(::color32_t * pcolorrefDst, int cxParam,int cyParam,int iStrideDst, const ::color32_t * pcolorrefSrc,int iStrideSrc)
{

   try
   {

   if (pcolorrefDst == nullptr)
   {

      return;

   }

   if (pcolorrefSrc == nullptr)
   {

      return;

   }

   if(iStrideSrc <= 0)
   {

      iStrideSrc = cxParam * sizeof(::color32_t);

   }

   int wsrc = iStrideSrc / sizeof(::color32_t);
   int wdst = iStrideDst / sizeof(::color32_t);
   int cw = cxParam * sizeof(::color32_t);


   auto * psrc = pcolorrefSrc;
   auto * pdst = pcolorrefDst;


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

         pd += sizeof(::color32_t);

         ps += sizeof(::color32_t);

      }

      pdst += wdst;

      psrc += wsrc;

   }


   }

   catch (...)
   {

   }


}


void _001ProperCopyColorref(::color32_t * pcolorrefDst, int cxParam,int cyParam,int iStrideDst,const ::color32_t * pcolorrefSrc,int iStrideSrc)
{

#ifdef WINDOWS_DESKTOP

   copy_colorref(pcolorrefDst, cxParam, cyParam, iStrideDst, pcolorrefSrc, iStrideSrc);

#else

   vertical_swap_copy_colorref(pcolorrefDst, cxParam, cyParam, iStrideDst, pcolorrefSrc, iStrideSrc);

#endif


}


void copy_colorref(::color32_t * pcolorrefDst, int xParam, int yParam, int cxParam,int cyParam, int iStrideDst, const ::color32_t * pcolorrefSrc,int iStrideSrc)
{

   try
   {

   if(iStrideSrc <= 0)
   {

      iStrideSrc = cxParam * sizeof(::color32_t);

   }

   int wsrc = iStrideSrc / sizeof(::color32_t);
   int wdst = iStrideDst / sizeof(::color32_t);
   int cw = cxParam * sizeof(::color32_t);

   auto psrc = &pcolorrefSrc[xParam + yParam * iStrideSrc / sizeof(::color32_t)];
   auto pdst = &pcolorrefDst[xParam + yParam * iStrideDst / sizeof(::color32_t)];

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


CLASS_DECL_AURA void copy_colorref(::color32_t * pcolorrefDst, const ::size_i32 & size, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc)
{

   copy_colorref(pcolorrefDst, size.cx(), size.cy(), iStrideDst, pcolorrefSrc, iStrideSrc);

}



