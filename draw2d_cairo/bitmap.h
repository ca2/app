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
      ::i32_size              m_size;


      bitmap();
      ~bitmap() override;


      bool LoadBitmap(const ::scoped_string & scopedstrResourceName);
      bool LoadBitmap(::u32 nIDResource);
      bool LoadOEMBitmap(::u32 nIDBitmap); // for OBM_/OCR_/OIC_
   
      bool CreateBitmap(::draw2d::graphics * pgraphics, ::i32 nWidth, ::i32 nHeight, ::u32 nPlanes, ::u32 nBitcount, const void * lpBits, ::i32 iStride);
//      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      void CreateCompatibleBitmap(::draw2d::graphics * pgraphics, ::i32 nWidth, ::i32 nHeight) override;
      void CreateDiscardableBitmap(::draw2d::graphics * pgraphics, ::i32 nWidth, ::i32 nHeight) override;
      void create_bitmap(::draw2d::graphics * pgraphics, const ::i32_size & size, image32_t **ppimage32, const ::image32_t * pimage32, ::i32 * stride) override;
      void CreateDIBitmap(::draw2d::graphics * pgraphics, ::i32 cx, ::i32 cy, ::u32 flInit, const void *pjBits, ::u32 iUsage) override;

      bool host_bitmap(::draw2d::graphics * pgraphics, ::pixmap_t * ppixmap) override;


      ::i32 stride_for_width(::i32 iWidth) override;

      //::i32 GetBitmap(BITMAP* pBitMap);


      ::u32 SetBitmapBits(::u32 dwCount, const void * lpBits) override;
      ::u32 GetBitmapBits(::u32 dwCount, void * lpBits) const override;
      ::i32_size SetBitmapDimension(::i32 nWidth, ::i32 nHeight);
      ::i32_size GetBitmapDimension() const override;

      // void dump(dump_context & dumpcontext) const override;


      virtual void attach(void * posdata) override;


      void destroy() override;
      void destroy_os_data() override;



   };


} // namespace draw2d_cairo



