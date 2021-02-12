#include "framework.h"


#undef new


namespace draw2d_gdiplus
{


   bitmap::bitmap()
   {

      m_mem.m_bAligned = true;

      m_pbitmap   = nullptr;
      m_iStride   = 0;

   }

   bitmap::~bitmap()
   {

      destroy();

   }

   
   void bitmap::destroy()
   {

      ::acme::del(m_pbitmap);

      ::draw2d::bitmap::destroy();

   }


   bool bitmap::CreateBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight, UINT nPlanes, UINT nBitcount, const void * pBits, i32 stride)

   {

      UNREFERENCED_PARAMETER(pgraphics);

      ::acme::del(m_pbitmap);

      m_pbitmap = new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);

      m_osdata[0] = m_pbitmap;

      return true;

   }

   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP pBitmap)

   {

      UNREFERENCED_PARAMETER(pgraphics);

      return false;
   }


   bool bitmap::host_bitmap(::draw2d::graphics * pgraphics, const pixmap * ppixmap)
   {

      if (ppixmap->m_size == m_size)
      {

         return true;

      }

      UNREFERENCED_PARAMETER(pgraphics);

      ::acme::del(m_pbitmap);

      m_iStride = ppixmap->m_iScan;

      if (ppixmap->colorref() == nullptr)
      {

         return false;

      }

      m_pbitmap = new Gdiplus::Bitmap(ppixmap->width(), ppixmap->height(), m_iStride, PixelFormat32bppPARGB, (BYTE *) ppixmap->colorref());

      if (m_pbitmap == nullptr)
      {

         return false;

      }

      m_osdata[0] = m_pbitmap;

      m_size = ppixmap->m_size;

      return true;

   }


   bool bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, void **ppvBits, int * stride)
   {

      if (size == m_size)
      {

         return true;

      }

      BITMAPINFO info = {};

      info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      info.bmiHeader.biWidth = size.cx;
      info.bmiHeader.biHeight = -size.cy;
      info.bmiHeader.biPlanes = 1;
      info.bmiHeader.biBitCount = 32;
      info.bmiHeader.biCompression = BI_RGB;
      info.bmiHeader.biSizeImage = size.area() * sizeof(COLORREF);

      const BITMAPINFO * pbmi = &info;

      UNREFERENCED_PARAMETER(pgraphics);

      ::acme::del(m_pbitmap);

      m_iStride = 4 * pbmi->bmiHeader.biWidth;

      m_mem.set_size(abs(m_iStride * pbmi->bmiHeader.biHeight));

      if (m_mem.get_data() == nullptr)
      {

         return false;

      }

      m_pbitmap = new Gdiplus::Bitmap(abs(pbmi->bmiHeader.biWidth), abs(pbmi->bmiHeader.biHeight),m_iStride, PixelFormat32bppPARGB, (BYTE *)m_mem.get_data());

      if(m_pbitmap == nullptr)
      {

         return false;

      }

      if(ppvBits != nullptr)
      {

         *ppvBits = m_mem.get_data();

      }

      if(stride != nullptr)
      {

         *stride = m_iStride;

      }

      m_osdata[0] = m_pbitmap;

      m_size = size;

      return true;

   }


   bool bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, u32 flInit, const void *pjBits, UINT iUsage)
   {
      return false;
   }


   u32 bitmap::SetBitmapBits(u32 dwCount, const void * pBits)

   {

      //return ::SetBitmapBits((HBITMAP)get_handle(), dwCount, pBits);

      return 0;

   }
   u32 bitmap::GetBitmapBits(u32 dwCount, LPVOID pBits) const

   {
      //return ::GetBitmapBits((HBITMAP)get_handle(), dwCount, pBits);

      return 0;
   }
   bool bitmap::LoadBitmap(const char * pszResourceName)

   {
      //   return attach(::LoadBitmap(::aura::FindResourceHandle(
      //pszResourceName, RT_BITMAP), pszResourceName));

      return false;

   }

   size_i32 bitmap::SetBitmapDimension(i32 nWidth, i32 nHeight)
   {


      ::exception::throw_not_implemented();

      //::size_i32 size;
      //VERIFY(::SetBitmapDimensionEx((HBITMAP)get_handle(), nWidth, nHeight, &size));
      //return size;
      return ::size_i32(0, 0);

   }

   
   size_i32 bitmap::GetBitmapDimension() const
   {

      if (m_pbitmap == nullptr)
      {

         return ::size_i32(0, 0);

      }

      return ::size_i32(m_pbitmap->GetWidth(), m_pbitmap->GetHeight());

   }


   bool bitmap::LoadBitmap(UINT nIDResource)
   {
      //return attach(::LoadBitmap(::aura::FindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_BITMAP), MAKEINTRESOURCE(nIDResource)));
      return false;
   }
   bool bitmap::LoadOEMBitmap(UINT nIDBitmap)
   {
      //return attach(::LoadBitmap(nullptr, MAKEINTRESOURCE(nIDBitmap)));
      return false;
   }
   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight)
   {

      ::acme::del(m_pbitmap);

      m_pbitmap = new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);

      m_osdata[0] = m_pbitmap;

      return true;

   }
   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight)
   {

      ::acme::del(m_pbitmap);

      m_pbitmap = new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);

      m_osdata[0] = m_pbitmap;

      return true;

   }


   i32 bitmap::GetBitmap(BITMAP* pBitMap)
   {
      //   ASSERT(get_handle() != nullptr);
      // return ::GetObject(get_handle(), sizeof(BITMAP), pBitMap);
      return 0;
   }


#ifdef DEBUG
   /////////////////////////////////////////////////////////////////////////////


   void bitmap::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

      /*         if (get_handle() == nullptr)
                  return;

               if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_BITMAP)
               {
                  // not a valid object
                  dumpcontext << "has ILLEGAL HBITMAP!";
                  return;
               }*/

      /*BITMAP bm;
      VERIFY(GetObject(sizeof(bm), &bm));
      dumpcontext << "bm.bmType = " << bm.bmType;
      dumpcontext << "\nbm.bmHeight = " << bm.bmHeight;
      dumpcontext << "\nbm.bmWidth = " << bm.bmWidth;
      dumpcontext << "\nbm.bmWidthBytes = " << bm.bmWidthBytes;
      dumpcontext << "\nbm.bmPlanes = " << bm.bmPlanes;
      dumpcontext << "\nbm.bmBitsPixel = " << bm.bmBitsPixel;
      */
      dumpcontext << "\n";
   }


#endif

   bool bitmap::attach(void * posdata)
   {

      ::acme::del(m_pbitmap);

      m_pbitmap = (Gdiplus::Bitmap *) posdata;

      m_osdata[0] = m_pbitmap;

      return true;

   }

   void * bitmap::detach()
   {

      Gdiplus::Bitmap * pbitmap = m_pbitmap;

      m_pbitmap = nullptr;

      clear_os_data();

      return m_pbitmap;

   }


   HBITMAP bitmap::_GetHBITMAP()
   {

      if(m_pbitmap == nullptr)
         return nullptr;

      HBITMAP hbitmap = nullptr;

      Gdiplus::Color colorBk(0,0,0,0);

      m_pbitmap->GetHBITMAP(colorBk,&hbitmap);

      return hbitmap;

   }


   void bitmap::_ReleaseHBITMAP(HBITMAP hbitmap)
   {

      ::DeleteObject(hbitmap);

   }


} // namespace draw2d_gdiplus



