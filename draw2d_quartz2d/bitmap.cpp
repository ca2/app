#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   bitmap::bitmap()
   {
      
      m_size.cx = 0;
      m_size.cy = 0;
      m_pdc = nullptr;
      m_iScan = 0;
      
   }
   
   
   bitmap::~bitmap()
   {
      
      destroy();
      
   }
   
   
   bool bitmap::CreateBitmap(::draw2d::graphics * pgraphics, const ::size & size, UINT nPlanes, UINT nBitcount, const void * pdata, i32 iStride)
   {
      
      if(nPlanes != 1 || nBitcount != 32)
      {
         
         __throw(not_implemented());
         
      }
      
      destroy();
      
      CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
      
      try
      {
      
         m_memory.set_size(size.cy * iStride);
         
      }
      catch(...)
      {
         
      }
      
      m_pdata = (COLORREF *) m_memory.get_data();
      
      if(m_pdata == nullptr)
      {
         
         return false;
         
      }
      
      m_pdc = CGBitmapContextCreate(m_pdata, size.cx, size.cy, 8, iStride, colorspace, kCGImageAlphaPremultipliedLast);
      
      CGColorSpaceRelease(colorspace);
      
      if(m_pdc == nullptr)
      {
         
         destroy();
         
         return false;
         
      }
      
      m_iScan = (int) CGBitmapContextGetBytesPerRow(m_pdc);
      
      if(m_iScan <= 0)
      {
         
         destroy();
         
         return false;
         
      }
      
      if(pdata != nullptr)
      {
      
         ::memcpy_dup(m_pdata, pdata, size.cy * iStride);
         
      }
      
      m_size = size;
      
      m_osdata[0] = m_pdc;
      
      return true;
      
   }
   
   
   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap)
   {
      
      return false;
      
   }
   
   
   bool bitmap::CreateDIBSection(::draw2d::graphics * pgraphics, const ::size & size, UINT usage, void ** ppdata, int * piStride, HANDLE hSection, u32 offset)
   {
      
      if(!CreateBitmap(pgraphics, size, 1, 32, nullptr, size.cx * sizeof(COLORREF)))
      {
         
         return false;
         
      }
      
      if(ppdata != nullptr)
      {
         
         *ppdata = m_pdata;
         
      }
      
      if(piStride)
      {
         
         *piStride = m_iScan;
         
      }
      
      return true;
      
   }
   
   
   bool bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, DWORD flInit, const void *pjBits, UINT iUsage)
   {
      
      return false;
      
   }
   
   
   DWORD bitmap::SetBitmapBits(DWORD dwCount, const void * lpBits)
   {
      
      return 0;
      
   }
   
   
   DWORD bitmap::GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
   {

      return 0;
      
   }
   
   
   bool bitmap::LoadBitmap(const char * lpszResourceName)
   {

      return false;
      
   }
   
   
   size bitmap::SetBitmapDimension(i32 nWidth, i32 nHeight)
   {
      
      return ::size(0, 0);
      
   }
   
   
   size bitmap::GetBitmapDimension() const
   {
      
      if(m_osdata[0] == nullptr)
      {

         return ::size(0, 0);

      }
      
      return m_size;
      
   }
   
   
   bool bitmap::LoadBitmap(UINT nIDResource)
   {
      
      return false;
      
   }
   
   
   bool bitmap::LoadOEMBitmap(UINT nIDBitmap)
   {

      return false;
      
   }
   
   
   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 cx, i32 cy)
   {
      
      if(!CreateBitmap(pgraphics, ::size(cx, cy), 1, 32, nullptr, cx * sizeof(COLORREF)))
      {
         
         return false;
         
      }
      
      return true;
      
   }
   
   
   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight)
   {
      
      return CreateCompatibleBitmap(pgraphics, nWidth, nHeight);
      
   }
   
   
   i32 bitmap::GetBitmap(BITMAP* pBitMap)
   {
      
      return 0;
      
   }
   

   void bitmap::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);
      
      if(m_osdata[0] == nullptr)
         return;
       
      //dumpcontext << "bm.bmType = " << bm.bmType;
      dumpcontext << "\nbm.bmHeight = " << m_size.cy;
      dumpcontext << "\nbm.bmWidth = " << m_size.cx;
      dumpcontext << "\nbm.bmWidthBytes = " << m_iScan;
      dumpcontext << "\nbm.bmPlanes = " << 1;
      dumpcontext << "\nbm.bmBitsPixel = " << 32;
      dumpcontext << "\n";
      
   }
   

//   void * bitmap::get_os_data() const
//   {
//      
//      return m_pdc;
//      
//   }
   
   
   bool bitmap::Attach(void * pbitmapcontext)
   {
      
      m_memory.set_size(0);
      
      m_pdc       = (CGContextRef) pbitmapcontext;
      
      m_size.cx   = (int) CGBitmapContextGetWidth(m_pdc);
      
      m_size.cy   = (int) CGBitmapContextGetHeight(m_pdc);
      
      m_iScan     = (int) CGBitmapContextGetBytesPerRow(m_pdc);
      
      m_pdata     = (COLORREF *) CGBitmapContextGetData(m_pdc);
      
      return true;
      
   }
   
   
   void bitmap::destroy()
   {
      
      if(m_pdc != nullptr)
      {
         
         CGContextRelease(m_pdc);
         
         m_pdc = nullptr;
         
      }
      
      //m_pdata = nullptr;
      
      m_size.cx = 0;
      
      m_size.cy = 0;
      
      m_iScan = 0;
      
   }
   
   
} // namespace draw2d_quartz2d







