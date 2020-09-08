#include "framework.h"
//#include "draw2d_object.h"
//#include "draw2d_bitmap.h"


namespace draw2d
{


   bitmap::bitmap()
   {

#ifdef WINDOWS_DESKTOP

      m_hbitmapGet            = nullptr;

#endif

      m_iStride               = 0;

   }


   bitmap::~bitmap()
   {

#ifdef WINDOWS_DESKTOP

      // Implementators (derived classes) should have released or at last nulled m_hbitmapGet to
      // indicate it is correctly Released through ReleaseHBITMAP

      if(m_hbitmapGet != nullptr)
      {

         ReleaseHBITMAP(m_hbitmapGet);

      }

#endif

   }


   bool bitmap::CreateBitmap(::draw2d::graphics* pgraphics, const ::size & size,UINT nPlanes,UINT nBitcount,const void * pBits,i32 stride)
   {

      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(nPlanes);
      UNREFERENCED_PARAMETER(nBitcount);
      UNREFERENCED_PARAMETER(pBits);

      UNREFERENCED_PARAMETER(stride);
      ::exception::throw_not_implemented();
      return false;
   }


   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics,LPBITMAP pBitmap)
   {

      UNREFERENCED_PARAMETER(pBitmap);

      ::exception::throw_not_implemented();
      return false;
   }


//   bool bitmap::CreateDIBSection(::draw2d::graphics * pgraphics,const BITMAPINFO * pbmi,UINT usage,void **ppvBits,int * stride,HANDLE hSection,u32 offset)
//   {

//      UNREFERENCED_PARAMETER(pgraphics);
//      UNREFERENCED_PARAMETER(pbmi);

//      UNREFERENCED_PARAMETER(usage);
//      UNREFERENCED_PARAMETER(ppvBits);
//      UNREFERENCED_PARAMETER(stride);
//      UNREFERENCED_PARAMETER(hSection);
//      UNREFERENCED_PARAMETER(offset);
//      ::exception::throw_not_implemented();
//      return false;
//   }
//
//   bool bitmap::HostDIBSection(::draw2d::graphics * pgraphics, const BITMAPINFO * pbmi, UINT usage, void * ppvBits, int stride, HANDLE hSection, u32 offset)

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
//   bool bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics,const BITMAPINFOHEADER *pbmih,u32 flInit,const void *pjBits,const BITMAPINFO *pbmi,UINT iUsage)
//   {
//      UNREFERENCED_PARAMETER(pgraphics);
//      UNREFERENCED_PARAMETER(pbmih);
//      UNREFERENCED_PARAMETER(flInit);
//      UNREFERENCED_PARAMETER(pjBits);
//      UNREFERENCED_PARAMETER(pbmi);
//      UNREFERENCED_PARAMETER(iUsage);
//      ::exception::throw_not_implemented();
//      return false;
//   }


   bool bitmap::CreateDIBSection(::draw2d::graphics * pgraphics, const ::size & size, UINT usage,void **ppvBits,int * stride,HANDLE hSection,u32 offset)
   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(usage);
      UNREFERENCED_PARAMETER(ppvBits);
      UNREFERENCED_PARAMETER(stride);
      UNREFERENCED_PARAMETER(hSection);
      UNREFERENCED_PARAMETER(offset);
      ::exception::throw_not_implemented();
      return false;
   }


   bool bitmap::HostDIBSection(::draw2d::graphics * pgraphics, const pixmap * ppixmap, UINT usage, HANDLE hSection, u32 offset)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(ppixmap);
      UNREFERENCED_PARAMETER(usage);
      UNREFERENCED_PARAMETER(hSection);
      UNREFERENCED_PARAMETER(offset);
      // callers must be prepared to cases when the
      // backend doesn't support "hosting" a portion of RAM as bitmap data
      return false;
   }

   bool bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy,u32 flInit,const void *pjBits, UINT iUsage)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(flInit);
      UNREFERENCED_PARAMETER(pjBits);
      UNREFERENCED_PARAMETER(iUsage);
      ::exception::throw_not_implemented();
      return false;
   }


   u32 bitmap::SetBitmapBits(u32 dwCount,const void * pBits)

   {
      UNREFERENCED_PARAMETER(dwCount);
      UNREFERENCED_PARAMETER(pBits);

      ::exception::throw_not_implemented();
      return 0;
   }
   u32 bitmap::GetBitmapBits(u32 dwCount,LPVOID pBits) const

   {
      UNREFERENCED_PARAMETER(dwCount);
      UNREFERENCED_PARAMETER(pBits);

      ::exception::throw_not_implemented();
      return 0;
   }

   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics,i32 nWidth,i32 nHeight)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      ::exception::throw_not_implemented();
      return false;
   }
   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics,i32 nWidth,i32 nHeight)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      ::exception::throw_not_implemented();
      return false;
   }


   void ::draw2d::bitmap::dump(dump_context & dumpcontext) const
   {

      UNREFERENCED_PARAMETER(dumpcontext);

      ::exception::throw_interface_only();

   }


   //const ::size & size bitmap::SetBitmapDimension(i32 nWidth,i32 nHeight)
   //{
   //   UNREFERENCED_PARAMETER(nWidth);
   //   UNREFERENCED_PARAMETER(nHeight);
   //   ::exception::throw_not_implemented();
   //   return ::size(0,0);
   //}


   bool bitmap::attach(void * posdata)
   {
      UNREFERENCED_PARAMETER(posdata);
      ::exception::throw_interface_only();
      return false;
   }

   void * bitmap::detach()
   {
      ::exception::throw_interface_only();
      return nullptr;
   }

   //const ::size & size bitmap::set_size(const ::size & size)
   //{


   //   return SetBitmapDimension(size.cx,size.cy);


   //}


   size bitmap::GetBitmapDimension() const
   {

      ::exception::throw_not_implemented();

      ::size sizeRet(0,0);

      return sizeRet;

   }


   size bitmap::get_size() const
   {

      return GetBitmapDimension();

   }


   size bitmap::size() const
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

      iStride = ppixmap->width() * sizeof(COLORREF);

   }

   int w = iStride / sizeof(COLORREF);

   int h = ppixmap->height();

   int wBytes = ppixmap->width() * sizeof(COLORREF);

   COLORREF * pdata = ppixmap->colorref();

   u8 * pline1 = (u8 *) pdata;

   u8 * pline2 = (u8 *) (pdata + (w - 1) * h);

   memory memory;

   memory.set_size(wBytes);

   u8 * pstore = memory.get_data();

   int halfh = h / 2;

   for (int i = 0; i < halfh; i++)
   {

      ::memcpy_dup(pstore, pline1, wBytes);

      ::memcpy_dup(pline1, pline2, wBytes);

      ::memcpy_dup(pline2, pstore, wBytes);

      pline1 += iStride;

      pline2 -= iStride;

   }


   }

   catch (...)
   {

   }

}


void vertical_swap_copy_colorref(COLORREF * pcolorrefDst, int cxParam,int cyParam,int iStrideDst,const COLORREF * pcolorrefSrc,int iStrideSrc)
{

   try
   {

   if(iStrideSrc <= 0)
   {

      iStrideSrc = cxParam * sizeof(COLORREF);

   }


   int wsrc = iStrideSrc / sizeof(COLORREF);
   int wdst = iStrideDst / sizeof(COLORREF);
   int cw = cxParam * sizeof(COLORREF);


   auto * psrc = pcolorrefSrc;
   auto * pdst = (COLORREF * )((u8 *) (pcolorrefDst) + iStrideDst * (cyParam - 1));

   for(int i = 0; i < cyParam; i++)
   {

      ::memcpy_dup(pdst,psrc,cw);

      pdst -= wdst;

      psrc += wsrc;

   }


   }

   catch (...)
   {

   }


}


void vertical_swap_copy_colorref_swap_red_blue(COLORREF * pcolorrefDst, int cxParam,int cyParam,int iStrideDst, const COLORREF * pcolorrefSrc,int iStrideSrc)
{

   try
   {


   if(iStrideSrc <= 0)
   {

      iStrideSrc = cxParam * sizeof(COLORREF);

   }

   int wsrc = iStrideSrc / sizeof(COLORREF);
   int wdst = iStrideDst / sizeof(COLORREF);
   int cw = cxParam * sizeof(COLORREF);

   auto * psrc = pcolorrefSrc;
   auto * pdst = (COLORREF * )((u8 *) (pcolorrefDst) + iStrideDst * (cyParam - 1));

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

         pd += sizeof(COLORREF);

         ps += sizeof(COLORREF);

      }

      pdst -= wdst;

      psrc += wsrc;

   }


   }

   catch (...)
   {

   }

}


void copy_colorref(COLORREF * pcolorrefDst, int cxParam, int cyParam, int iStrideDst, const COLORREF * pcolorrefSrc, int iStrideSrc)
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

         iStrideSrc = cxParam * sizeof(COLORREF);

      }

      if (iStrideDst == iStrideSrc)
      {

         ::memcpy_dup(pcolorrefDst, pcolorrefSrc, cyParam * iStrideDst);

      }
      else
      {

         int wsrc = iStrideSrc / sizeof(COLORREF);
         int wdst = iStrideDst / sizeof(COLORREF);
         int cw = cxParam * sizeof(COLORREF);


         auto psrc = pcolorrefSrc;
         auto pdst = pcolorrefDst;

         for (int i = 0; i < cyParam; i++)
         {

            ::memcpy_dup(pdst, psrc, cw);

            pdst += wdst;

            psrc += wsrc;

         }

      }

   }

   catch (...)
   {

   }

}


void copy_colorref_swap_red_blue(COLORREF * pcolorrefDst, int cxParam,int cyParam,int iStrideDst, const COLORREF * pcolorrefSrc,int iStrideSrc)
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

      iStrideSrc = cxParam * sizeof(COLORREF);

   }

   int wsrc = iStrideSrc / sizeof(COLORREF);
   int wdst = iStrideDst / sizeof(COLORREF);
   int cw = cxParam * sizeof(COLORREF);


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

         pd += sizeof(COLORREF);

         ps += sizeof(COLORREF);

      }

      pdst += wdst;

      psrc += wsrc;

   }


   }

   catch (...)
   {

   }


}


void _001ProperCopyColorref(COLORREF * pcolorrefDst, int cxParam,int cyParam,int iStrideDst,const COLORREF * pcolorrefSrc,int iStrideSrc)
{

#ifdef WINDOWS_DESKTOP

   copy_colorref(pcolorrefDst, cxParam, cyParam, iStrideDst, pcolorrefSrc, iStrideSrc);

#else

   vertical_swap_copy_colorref(pcolorrefDst, cxParam, cyParam, iStrideDst, pcolorrefSrc, iStrideSrc);

#endif


}


void copy_colorref(COLORREF * pcolorrefDst, int xParam, int yParam, int cxParam,int cyParam, int iStrideDst, const COLORREF * pcolorrefSrc,int iStrideSrc)
{

   try
   {

   if(iStrideSrc <= 0)
   {

      iStrideSrc = cxParam * sizeof(COLORREF);

   }

   int wsrc = iStrideSrc / sizeof(COLORREF);
   int wdst = iStrideDst / sizeof(COLORREF);
   int cw = cxParam * sizeof(COLORREF);


   auto psrc = &pcolorrefSrc[xParam + yParam * iStrideSrc / sizeof(COLORREF)];
   auto pdst = &pcolorrefDst[xParam + yParam * iStrideDst / sizeof(COLORREF)];

   for(int i = 0; i < cyParam; i++)
   {

      ::memcpy_dup(pdst,psrc,cw);

      pdst += wdst;

      psrc += wsrc;

   }


   }

   catch (...)
   {

   }

}




