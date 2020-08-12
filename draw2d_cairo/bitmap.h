#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO bitmap :
      virtual public ::draw2d::bitmap
   {
   public:


      cairo_surface_t *       m_psurface;
      memory                  m_mem;
      ::size                  m_size;


      bitmap();
      virtual ~bitmap();


      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_
   #ifndef ___NO_AFXCMN_SUPPORT
// xxx      bool LoadMappedBitmap(UINT nIDBitmap, UINT nFlags = 0, LPCOLORMAP lpColorMap = nullptr, i32 nMapSize = 0);
   #endif
      bool CreateBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight, UINT nPlanes, UINT nBitcount, const void * lpBits, i32 iStride);
      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      bool CreateDIBSection(::draw2d::graphics * pgraphics, const ::size & size, UINT usage, void **ppvBits, int * stride, HANDLE hSection, u32 offset);
      bool CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, DWORD flInit, const void *pjBits, UINT iUsage);


      i32 GetBitmap(BITMAP* pBitMap);


      DWORD SetBitmapBits(DWORD dwCount, const void * lpBits);
      DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) const;
      ::size SetBitmapDimension(i32 nWidth, i32 nHeight);
      ::size GetBitmapDimension() const;

      virtual void dump(dump_context & dumpcontext) const;


      virtual bool attach(void * posdata);


      virtual void destroy();



   };


} // namespace draw2d_cairo


