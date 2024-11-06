#pragma once


#include "aura/graphics/draw2d/bitmap.h"
#include "acme/prototype/prototype/memory.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO bitmap :
      virtual public ::draw2d::bitmap
   {
   public:


      cairo_surface_t *       m_psurface;
      memory                  m_mem;
      ::size_i32              m_size;


      bitmap();
      ~bitmap() override;


      bool LoadBitmap(const ::string & lpszResourceName);
      bool LoadBitmap(unsigned int nIDResource);
      bool LoadOEMBitmap(unsigned int nIDBitmap); // for OBM_/OCR_/OIC_
   
      bool CreateBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight, unsigned int nPlanes, unsigned int nBitcount, const void * lpBits, int iStride);
//      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      void CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight) override;
      void CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight) override;
      void create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, void **ppvBits, int * stride) override;
      void CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int flInit, const void *pjBits, unsigned int iUsage) override;

      bool host_bitmap(::draw2d::graphics * pgraphics, ::pixmap * ppixmap) override;


      int stride_for_width(int iWidth) override;

      //int GetBitmap(BITMAP* pBitMap);


      unsigned int SetBitmapBits(unsigned int dwCount, const void * lpBits) override;
      unsigned int GetBitmapBits(unsigned int dwCount, void * lpBits) const override;
      ::size_i32 SetBitmapDimension(int nWidth, int nHeight);
      ::size_i32 GetBitmapDimension() const override;

      // void dump(dump_context & dumpcontext) const override;


      virtual void attach(void * posdata) override;


      void destroy() override;
      void destroy_os_data() override;



   };


} // namespace draw2d_cairo



