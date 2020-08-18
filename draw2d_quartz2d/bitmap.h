#pragma once


namespace draw2d_quartz2d
{

   
   class CLASS_DECL_DRAW2D_QUARTZ2D bitmap : 
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::bitmap
   {
   public:
      

      memory                        m_memory;
      ::size                        m_size;
      CGContextRef                  m_pdc;
      i32                           m_iScan;
      COLORREF *                    m_pdata;
      
      
      bitmap();
      virtual ~bitmap();
      
      
      //void * get_os_data() const override;
      
      
      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_
#ifndef ___NO_AFXCMN_SUPPORT
      // xxx      bool LoadMappedBitmap(UINT nIDBitmap, UINT nFlags = 0, LPCOLORMAP lpColorMap = nullptr, i32 nMapSize = 0);
#endif
      bool CreateBitmap(::draw2d::graphics * pgraphics, const ::size & size, UINT nPlanes, UINT nBitcount, const void * lpBits, i32 iStride) override;
      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap) override;
      bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight) override;
      bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight) override;
      bool CreateDIBSection(::draw2d::graphics * pgraphics, const ::size & size, UINT usage, void **ppvBits, int * piStride, HANDLE hSection, u32 offset) override;
      bool CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, DWORD flInit, const void *pjBits, UINT iUsage) override;
      
      i32 GetBitmap(BITMAP* pBitMap);
      
      DWORD SetBitmapBits(DWORD dwCount, const void * lpBits) override;
      DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) const override;
      ::size SetBitmapDimension(i32 nWidth, i32 nHeight);
      ::size GetBitmapDimension() const override;
      
      virtual void dump(dump_context & dumpcontext) const override;
      
      virtual bool Attach(void * posdata);
      
      virtual void destroy() override;

      
   };

   
} // namespace draw2d_quartz2d




