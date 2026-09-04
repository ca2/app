#include "platform.h"
#include "bitmap.h"
#include "graphics.h"
#include "graphics_lease.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/graphics/image/pixmap.h"
#include "aura/graphics/image/image.h"


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
      m_bHintCpuBackingEnabled      = true;
      m_iStride                     = 0;
      m_bTopLeft                    = true;

   }


   bitmap::bitmap(bitmap&& bitmap) :
      DRAW2D_OBJECT_TRANSFER(bitmap),
      m_size(bitmap.m_size),
      m_iStride(bitmap.m_iStride),
      m_memoryDraw2dBitmap(::transfer(bitmap.m_memoryDraw2dBitmap))
   {

      bitmap.m_size.Null();

      bitmap.m_iStride = 0;

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


   void bitmap::update_bitmap_as_backed_by_gpu_texture(::gpu::texture * pgputexture, ::draw2d::graphics * pdraw2graphics)
   {

      throw ::interface_only();

   }


   bool bitmap::copy_from(::draw2d::bitmap * pdraw2dbitmap)
   {

      return false;

   }


   bool bitmap::copy_from(::draw2d::bitmap * pdraw2dbitmap, const ::i32_size & size, const ::i32_point & pointDst, const ::i32_point & pointSrc)
   {

      return false;

   }


   bool bitmap::copy_from(::pixmap * ppixmap)
   {

      return false;

   }


   bool bitmap::copy_from(::pixmap * ppixmap, const ::i32_size & size, const ::i32_point & pointDst, const ::i32_point & pointSrc)
   {

      return false;

   }


   ::subparticle_pointer bitmap::clone()
   {

      auto pbitmapNew = createø<::draw2d::bitmap>();

      if (!pbitmapNew->copy_from(this))
      {

         return nullptr;

      }

      return pbitmapNew;

   }


   pixmap_t bitmap::get_pixmap()
   {

      if (m_memoryDraw2dBitmap.size() < m_size.cx * 4)
      {

         return {};
      }

      pixmap_t pixmap;

      pixmap.m_size = m_size;
      pixmap.m_sizeRaw = m_size;
      pixmap.m_pimage32 = (::image32_t *)m_memoryDraw2dBitmap.data();
      pixmap.m_pimage32Raw = (::image32_t *)m_memoryDraw2dBitmap.data();
      pixmap.m_iScan = m_iStride;
      pixmap.m_bTopLeft = m_bTopLeft;

      return pixmap;

   }


   void bitmap::create_gpu_bitmap(::draw2d::graphics * pdraw2dgraphics, const ::i32_size & size, ::pixmap * ppixmap)
   {

      throw ::interface_only();

   }


   void bitmap::CreateBitmap(::draw2d::graphics* pdraw2dgraphics, const ::i32_size & size,::u32 nPlanes,::u32 nBitcount,const void * pBits,::i32 stride)
   {

      __UNREFERENCED_PARAMETER(size);
      __UNREFERENCED_PARAMETER(nPlanes);
      __UNREFERENCED_PARAMETER(nBitcount);
      __UNREFERENCED_PARAMETER(pBits);

      __UNREFERENCED_PARAMETER(stride);
      throw ::interface_only();
      //return false;
   }


//   void bitmap::CreateBitmapIndirect(::draw2d::graphics * pdraw2dgraphics,LPBITMAP pBitmap)
//   {
//
//      __UNREFERENCED_PARAMETER(pBitmap);
//
//      throw ::interface_only();
//      return false;
//   }


//   void bitmap::CreateDIBSection(::draw2d::graphics * pdraw2dgraphics,const BITMAPINFO * pbmi,::u32 usage,void **ppvBits,::i32 * stride,HANDLE hSection,::u32 offset)
//   {

//      __UNREFERENCED_PARAMETER(pdraw2dgraphics);
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
//   void bitmap::HostDIBSection(::draw2d::graphics * pdraw2dgraphics, const BITMAPINFO * pbmi, ::u32 usage, void * ppvBits, ::i32 stride, HANDLE hSection, ::u32 offset)

//   {
//      __UNREFERENCED_PARAMETER(pdraw2dgraphics);
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
//   void bitmap::CreateDIBitmap(::draw2d::graphics * pdraw2dgraphics,const BITMAPINFOHEADER *pbmih,::u32 flInit,const void *pjBits,const BITMAPINFO *pbmi,::u32 iUsage)
//   {
//      __UNREFERENCED_PARAMETER(pdraw2dgraphics);
//      __UNREFERENCED_PARAMETER(pbmih);
//      __UNREFERENCED_PARAMETER(flInit);
//      __UNREFERENCED_PARAMETER(pjBits);
//      __UNREFERENCED_PARAMETER(pbmi);
//      __UNREFERENCED_PARAMETER(iUsage);
//      throw ::interface_only();
//      return false;
//   }


   void bitmap::update_bitmap_as_image_render_target(
      ::image::image * pimage,
      ::acme::user::interaction * pacmeuserinteractionAffinity,
      ::draw2d::graphics * pdraw2dgraphics)
   {

      //__UNREFERENCED_PARAMETER(pimage);
      //__UNREFERENCED_PARAMETER(pacmeuserinteractionAffinity);

      //throw ::interface_only();

      //auto pgraphicslease = pimage->acquire_graphics(pimage->m_pacmeuserinteractionAffinity);

      create_bitmap(
         pdraw2dgraphics,
         pimage->m_sizeRaw,
         pimage->m_ppixmapOwned);
         //pimage->m_memoryPixmap,
         //&pimage->m_iScan);

   }



   void bitmap::update_bitmap_as_source(
   ::image::image * pimage,
   ::acme::user::interaction * pacmeuserinteractionAffinity,
   ::draw2d::graphics * pdraw2dgraphics)
   {

      //__UNREFERENCED_PARAMETER(pimage);
      //__UNREFERENCED_PARAMETER(pacmeuserinteractionAffinity);

      //throw ::interface_only();

      //auto pgraphicslease = pimage->acquire_graphics(pimage->m_pacmeuserinteractionAffinity);

      create_bitmap(
         pdraw2dgraphics,
         pimage->m_sizeRaw,
         pimage->m_ppixmapOwned);
      //pimage->m_memoryPixmap,
      //&pimage->m_iScan);

   }



   void bitmap::preserve_image(const ::i32_size& size, ::image::image* pimage)
   {

      throw ::interface_only();

   }


//   void bitmap::create_bitmap(::draw2d::graphics * pdraw2dgraphics, const ::i32_size & size, ::memory & memory, ::i32 * stride)
   void bitmap::create_bitmap(::draw2d::graphics * pdraw2dgraphics, const ::i32_size & size, ::pixmap * ppixmap)
   {

      //__UNREFERENCED_PARAMETER(pdraw2dgraphics);
      //__UNREFERENCED_PARAMETER(size);
      ////__UNREFERENCED_PARAMETER(ppimage32);
      ////__UNREFERENCED_PARAMETER(pimage32);
      ////__UNREFERENCED_PARAMETER(memory);
      ////__UNREFERENCED_PARAMETER(stride);
      //__UNREFERENCED_PARAMETER(ppixmapOwned);

      //throw ::interface_only();

      ////return false;

      __UNREFERENCED_PARAMETER(pdraw2dgraphics);

      m_size = size;

      m_iStride = 4 * size.cx;

      int iScan = m_iStride;

      if (ppixmap && ppixmap->m_iScan >= iScan)
      {

         iScan = ppixmap->m_iScan;

      }

      //if (pimage32)
      //{

      //   pimage32Target->copy(size, m_iStride, pimage32, iScan);

      //}

      if (ppixmap && ppixmap->m_memoryPixmap.size() >= iScan * size.cy)
      {

         m_memoryDraw2dBitmap = ::transfer(ppixmap->m_memoryPixmap);

         //m_memoryDraw2dBitmap.set_size(abs(m_iStride * size.cy));

         //if (m_memoryDraw2dBitmap.data() == nullptr)
         //{

         //   return;

         //   //return false;

         //}

         //auto pimage32Target = (::image32_t *)m_memoryDraw2dBitmap.data();

         //if(ppixmap->m_bTopLeft)
         //{ 

         //   pimage32Target->copy(size, m_iStride, ppixmap->image32(), iScan);
         //
         //}
         //else
         //{

         //   pimage32Target->y_swap_copy(size, m_iStride, ppixmap->image32(), iScan);

         //}

         ppixmap->m_memoryPixmap.reference_data(m_memoryDraw2dBitmap);

         ppixmap->m_iScan = m_iStride;

         m_bTopLeft = ppixmap->m_bTopLeft;

      }

      //if(ppimage32 != nullptr)
      //{
      //   
      //   *ppimage32 = pimage32Target;

      //}

      //if(::is_set(ppixmap))
      //{

      //}

      //m_osdata[0] = (void *) 1;

      //return true;

   }


   bool bitmap::host_bitmap(::draw2d::graphics * pdraw2dgraphics, pixmap_t * ppixmap)
   {

      __UNREFERENCED_PARAMETER(pdraw2dgraphics);
      __UNREFERENCED_PARAMETER(ppixmap);

      // callers must be prepared to cases when the
      // backend doesn't support "hosting" a portion of RAM as bitmap data

      return false;

   }


   void bitmap::CreateDIBitmap(::draw2d::graphics * pdraw2dgraphics, ::i32 cx, ::i32 cy,::u32 flInit,const void *pjBits, ::u32 iUsage)
   {
      __UNREFERENCED_PARAMETER(pdraw2dgraphics);
      __UNREFERENCED_PARAMETER(cx);
      __UNREFERENCED_PARAMETER(cy);
      __UNREFERENCED_PARAMETER(flInit);
      __UNREFERENCED_PARAMETER(pjBits);
      __UNREFERENCED_PARAMETER(iUsage);
      throw ::interface_only();
      //return false;
   }


   ::i32 bitmap::stride_for_width(::i32 iWidth)
   {

      return iWidth * 4;

   }


   void bitmap::read_pixels(
      const ::i32_size & size,
      const ::i32_point & point,
      ::image32_t * pimage32,
      ::i32 iScan)
   {

      throw ::interface_only();

   }


   void bitmap::defer_read_pixels(
      const ::i32_size & sizeParam,
      const ::i32_point & point,
      ::image32_t * pimage32,
      ::i32 iScan)
   {

      auto size = sizeParam;

      if ((::i64)iScan < (::i64)(size.cx * sizeof(::image32_t)))
      {

         size.cx = iScan / sizeof(::image32_t);

      }

      if (size.cx <= 0 || size.cy <= 0)
      {

         return;

      }

      auto sizeBitmap = this->size();

      if (sizeBitmap.cx <= 0 || sizeBitmap.cy <= 0)
      {

         return;

      }

      auto iLeft = maximum((::i64) 0, (::i64) point.x);
      auto iTop = maximum((::i64) 0, (::i64) point.y);
      auto iRight = minimum((::i64) sizeBitmap.cx, (::i64) point.x + size.cx);
      auto iBottom = minimum((::i64) sizeBitmap.cy, (::i64) point.y + size.cy);

      if (iRight <= iLeft || iBottom <= iTop)
      {

         return;

      }

      if (!pimage32)
      {

         throw ::exception(error_null_pointer);

      }



      ::i32_size sizeClipped(
         (::i32) (iRight - iLeft),
         (::i32) (iBottom - iTop));

      ::i32_point pointClipped((::i32) iLeft, (::i32) iTop);

      auto iTargetX = (::i32) (iLeft - point.x);
      auto iTargetY = (::i32) (iTop - point.y);

      auto pimage32Shifted = (::image32_t *)
         ((::u8 *) pimage32 + (::memsize) iTargetY * iScan)
         + iTargetX;

      read_pixels(sizeClipped, pointClipped, pimage32Shifted, iScan);


   }


   bool bitmap::is_cpu_backed_by(const ::pixmap_t * ppixmap) const
   {

      __UNREFERENCED_PARAMETER(ppixmap);

      return false;

   }


   void bitmap::write_pixels(
      const ::i32_size & size,
      const ::i32_point & point,
      const ::image32_t * pimage32,
      ::i32 iScan,
      bool bTopDown)
   {

      throw ::interface_only();

   }

   
   void bitmap::defer_write_pixels(const ::i32_point & point, const ::pixmap_t & pixmap)
   {

      _defer_write_pixels(pixmap.size(), point, pixmap.image32(), pixmap.m_iScan, pixmap.m_bTopLeft);

   }


   void bitmap::defer_write_pixels(const ::pixmap_t & pixmap)
   {

      defer_write_pixels({}, pixmap);

   }


   void bitmap::_defer_write_pixels(
      const ::i32_size & size,
      const ::i32_point & point,
      const ::image32_t * pimage32,
      ::i32 iScan,
      bool bTopDown)
   {

      if (size.cx <= 0 || size.cy <= 0)
      {

         return;

      }

      auto sizeBitmap = this->size();

      if (sizeBitmap.cx <= 0 || sizeBitmap.cy <= 0)
      {

         return;

      }

      auto iLeft = maximum((::i64) 0, (::i64) point.x);
      auto iTop = maximum((::i64) 0, (::i64) point.y);
      auto iRight = minimum((::i64) sizeBitmap.cx, (::i64) point.x + size.cx);
      auto iBottom = minimum((::i64) sizeBitmap.cy, (::i64) point.y + size.cy);

      if (iRight <= iLeft || iBottom <= iTop)
      {

         return;

      }

      if (!pimage32)
      {

         throw ::exception(error_null_pointer);

      }

      if ((::i64) iScan < (::i64)( size.cx * sizeof(::image32_t)))
      {

         throw ::exception(error_bad_argument);

      }

      ::i32_size sizeClipped(
         (::i32) (iRight - iLeft),
         (::i32) (iBottom - iTop));

      ::i32_point pointClipped((::i32) iLeft, (::i32) iTop);

      auto iSourceX = (::i32) (iLeft - point.x);
      auto iSourceY = (::i32) (iTop - point.y);

      auto pimage32Shifted = (const ::image32_t *)
         ((const ::u8 *) pimage32 + (::memsize) iSourceY * iScan)
         + iSourceX;

      write_pixels(sizeClipped, pointClipped, pimage32Shifted, iScan, bTopDown);


   }


   ::u32 bitmap::SetBitmapBits(::u32 dwCount,const void * pBits)

   {
      __UNREFERENCED_PARAMETER(dwCount);
      __UNREFERENCED_PARAMETER(pBits);

      throw ::interface_only();
      return 0;
   }


   ::u32 bitmap::GetBitmapBits(::u32 dwCount,void * pBits) const
   {

      __UNREFERENCED_PARAMETER(dwCount);
      __UNREFERENCED_PARAMETER(pBits);

      throw ::interface_only();
      return 0;
   }


   ::string bitmap::_001_os_bitmap_diagnostics()
   {

      return "interface_only::not_implemented";

   }

   
   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pdraw2dgraphics,::i32 nWidth,::i32 nHeight)
   {
      __UNREFERENCED_PARAMETER(pdraw2dgraphics);
      __UNREFERENCED_PARAMETER(nWidth);
      __UNREFERENCED_PARAMETER(nHeight);
      throw ::interface_only();
      //return false;
   }


   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pdraw2dgraphics,::i32 nWidth,::i32 nHeight)
   {
      __UNREFERENCED_PARAMETER(pdraw2dgraphics);
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


   //const ::i32_size & size bitmap::SetBitmapDimension(::i32 nWidth,::i32 nHeight)
   //{
   //   __UNREFERENCED_PARAMETER(nWidth);
   //   __UNREFERENCED_PARAMETER(nHeight);
   //   throw ::interface_only();
   //   return ::i32_size(0,0);
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

   //const ::i32_size & size bitmap::set_size(const ::i32_size & size)
   //{


   //   return SetBitmapDimension(size.cx,size.cy);


   //}


//   i32_size bitmap::GetBitmapDimension() const
//   {
//
//      throw ::interface_only();
//
////      ::i32_size sizeRet(0,0);
//
//  //    return sizeRet;
//
//      return {};
//
//   }


   //i32_size bitmap::get_size() const
   //{

   //   return GetBitmapDimension();

   //}


   i32_size bitmap::size() const
   {

      return m_size;

   }


   void bitmap::set_size(const ::i32_size & size, bool bPreserve)
   {

      m_size = size;

   }


} // namespace draw2d


