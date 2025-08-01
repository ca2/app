#include "framework.h"
#include "bitmap.h"
#include "draw2d.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"


namespace draw2d_cairo
{


   bitmap::bitmap()
   {

      m_pthis = this;

      m_psurface = nullptr;

   }


   bitmap::~bitmap()
   {

      destroy();

   }


   bool bitmap::CreateBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int nPlanes, unsigned int nBitcount, const void * pdata, int iStrideParam)
   {

      informationf("draw2d_cairo::bitmap::CreateBitmap : (%d, %d)", cx, cy);

      _synchronous_lock ml(::draw2d_cairo::mutex());

      cy = abs(cy);

      cx = abs(cx);

      if(nPlanes != 1 || nBitcount != 32)
      {

         informationf("draw2d_cairo::bitmap::CreateBitmap bad argument nPlanes=%d nBitcount=%d", nPlanes, nBitcount);

         throw ::interface_only();

      }

      destroy();

      int iStride = stride_for_width(cx);

      m_mem.set_size(iStride * cy);

      if(pdata == nullptr || iStrideParam <= 0)
      {

         informationf("draw2d_cairo::bitmap::CreateBitmap setting image transparent");

         memory_set(m_mem.data(), 0, m_mem.size());

      }
      else
      {

         informationf("draw2d_cairo::bitmap::CreateBitmap copying image data");

         if(iStrideParam != iStride)
         {

            int iW = cx * 4;

            for(int i = 0; i < cy; i++)
            {

               ::memory_copy(&m_mem.data()[iStride * i], &((unsigned char *) pdata)[iStrideParam * i], iW);

            }

         }
         else
         {

            ::memory_copy(m_mem.data(), pdata, iStride * cy);

         }

         informationf("draw2d_cairo::bitmap::CreateBitmap image data copied");

      }

      informationf("draw2d_cairo::bitmap::CreateBitmap cairo_image_surface_create_for_data");

      m_psurface = cairo_image_surface_create_for_data(m_mem.data(), CAIRO_FORMAT_ARGB32, cx, cy, iStride);

      if(m_psurface == nullptr)
      {

         informationf("draw2d_cairo::bitmap::CreateBitmap Cairo Surface NOT Created");

         return false;

      }

      m_osdata[0] = m_psurface;

      m_size.cx() = cx;

      m_size.cy() = cy;

      informationf("draw2d_cairo::bitmap::CreateBitmap cairo surface created : cx=%d cy=%d", cx, cy);

      return true;

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap)
//   {
//
//      return false;
//
//   }
//
//
//#endif
//
//


   void bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::int_size & size, void ** ppdata, int * pstride)
   {

      //try
      //{

#ifdef MORE_LOG

      informationf("bitmap::create_bitmap");

#endif

         _synchronous_lock ml(::draw2d_cairo::mutex());

#ifdef MORE_LOG

         informationf("bitmap::create_bitmap (1)");

#endif

         destroy();

#ifdef MORE_LOG

         informationf("bitmap::create_bitmap (2)");

#endif

         int iScanWidth = -1;

         int iSourceStride = -1;

         if(pstride)
         {

            iSourceStride = *pstride;

            iScanWidth = *pstride / sizeof(color32_t);

         }

         if(iSourceStride < 0)
         {

            iSourceStride = size.cx() * sizeof(color32_t);

         }

         if(iScanWidth < size.cx())
         {

            iScanWidth = size.cx();

         }

         int iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, iScanWidth);

#ifdef MORE_LOG

         informationf("draw2d_cairo::bitmap::create_bitmap cairo stride (andWidth): %d(%d)", iStride, iScanWidth);

#endif

#if MEMDLEAK

         m_mem.m_strTag = "image_section=" + as_string(cx) + "x" + as_string(size.ccy);

#endif

         m_mem.m_bAligned = true;

         m_mem.set_size(iStride * size.cy());

         if(*ppdata != nullptr)
         {

            if(iSourceStride != iStride)
            {

               int iW = minimum(iStride, iSourceStride);

               for(int i = 0; i < size.cy(); i++)
               {

                  ::memory_copy(&m_mem.data()[iStride * i], &((unsigned char *) *ppdata)[iSourceStride * i], iW);

               }

            }
            else
            {

               ::memory_copy(m_mem.data(), *ppdata, iStride * size.cy());

            }

         }

         m_psurface = cairo_image_surface_create_for_data(m_mem.data(), CAIRO_FORMAT_ARGB32, size.cx(), size.cy(), iStride);

         int iSurfaceStatus = cairo_surface_status(m_psurface);

         if(iSurfaceStatus != CAIRO_STATUS_SUCCESS)
         {

            informationf("draw2d_cairo::bitmap::create_bitmap cairo create image Failed %d", iSurfaceStatus);

            cairo_surface_destroy(m_psurface);

            m_psurface = nullptr;

            if(iSurfaceStatus == CAIRO_STATUS_INVALID_STRIDE)
            {

               iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, size.cx());

               m_psurface = cairo_image_surface_create_for_data(m_mem.data(), CAIRO_FORMAT_ARGB32, size.cx(), size.cy(), iStride);

               iSurfaceStatus = cairo_surface_status(m_psurface);

               if(iSurfaceStatus != CAIRO_STATUS_SUCCESS)
               {

                  cairo_surface_destroy(m_psurface);

                  m_psurface = nullptr;

                  throw ::exception(error_failed);

               }

            }
            else
            {

               throw ::exception(error_failed);

            }

         }

         if(ppdata != nullptr)
         {

            *ppdata = (color32_t *) m_mem.data();

         }

         if(pstride != nullptr)
         {

            *pstride = iStride;

         }

         m_osdata[0] = m_psurface;

         m_size = size;

#ifdef MORE_LOG

         informationf("draw2d_cairo::bitmap::create_bitmap OK");

#endif
         //return true;

      //}
      //catch(...)
      //{

      //}

      //destroy();

      //return false;

   }


   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int flInit, const void *pjBits, unsigned int iUsage)
   {

      //return false;

   }


   bool bitmap::host_bitmap(::draw2d::graphics * pgraphics, ::pixmap * ppixmap)
   {


      //try
      //{

      synchronous_lock ml(::draw2d_cairo::mutex());

      destroy();

      int iScanWidth = -1;
//
//      if(pstride)
//      {
//
//         iScanWidth = *pstride / sizeof(color32_t);
//
//      }

      if(iScanWidth < ppixmap->m_size.cx())
      {

         iScanWidth = ppixmap->m_size.cx();

      }

      //ppixmap->m_iScan = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, iScanWidth);

#if MEMDLEAK

      m_mem.m_strTag = "image_section=" + as_string(cx) + "x" + as_string(size.ccy);

#endif

      //m_mem.m_bAligned = true;

      m_mem.m_begin = (unsigned char*) ppixmap->m_pimage32Raw;
      m_mem.m_end = m_mem.m_begin + (ppixmap->m_iScan * ppixmap->m_size.cy());
      m_mem.m_bOwner = false;

//      if(*ppdata != nullptr)
//      {
//
//         if(size.cx() * 4 != iStride)
//         {
//
//            int iW = size.cx() * 4;
//
//            for(int i = 0; i < size.cy(); i++)
//            {
//
//               ::memory_copy(&m_mem.data()[iStride * i], &((unsigned char *) *ppdata)[iW * i], iW);
//
//            }
//
//         }
//         else
//         {
//
//            ::memory_copy(m_mem.data(), *ppdata, iStride * size.cy());
//
//         }
//
//      }

      m_psurface = cairo_image_surface_create_for_data(m_mem.data(), CAIRO_FORMAT_ARGB32, ppixmap->m_sizeRaw.cx(), ppixmap->m_sizeRaw.cy(), ppixmap->m_iScan);

      int iSurfaceStatus = cairo_surface_status(m_psurface);

      if(iSurfaceStatus != CAIRO_STATUS_SUCCESS)
      {

         cairo_surface_destroy(m_psurface);

         m_psurface = nullptr;

         if(iSurfaceStatus == CAIRO_STATUS_INVALID_STRIDE)
         {

            ppixmap->m_iScan = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, ppixmap->m_sizeRaw.cx());

            m_psurface = cairo_image_surface_create_for_data(m_mem.data(), CAIRO_FORMAT_ARGB32, ppixmap->m_sizeRaw.cx(), ppixmap->m_sizeRaw.cy(), ppixmap->m_iScan);

            iSurfaceStatus = cairo_surface_status(m_psurface);

            if(iSurfaceStatus != CAIRO_STATUS_SUCCESS)
            {

               cairo_surface_destroy(m_psurface);

               m_psurface = nullptr;

               throw ::exception(error_failed);

            }

         }
         else
         {

            throw ::exception(error_failed);

         }

      }

//      if(ppdata != nullptr)
//      {
//
//         *ppdata = (color32_t *) m_mem.data();
//
//      }
//
//      if(pstride != nullptr)
//      {
//
//         *pstride = iStride;
//
//      }

      m_osdata[0] = m_psurface;

      m_size = ppixmap->m_size;

      return true;

      //}
      //catch(...)
      //{

      //}

      //destroy();

      //return false;


   }



   int bitmap::stride_for_width(int iWidth)
   {

      return cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, iWidth);

   }


   unsigned int bitmap::SetBitmapBits(unsigned int dwCount, const void * lpBits)
   {

      return 0;

   }


   unsigned int bitmap::GetBitmapBits(unsigned int dwCount, void * lpBits) const
   {

      return false;

   }


   bool bitmap::LoadBitmap(const ::scoped_string & scopedstrResourceName)
   {

      return false;

   }


   int_size bitmap::SetBitmapDimension(int nWidth, int nHeight)
   {

      throw ::interface_only();

      return ::int_size(0, 0);

   }


   int_size bitmap::GetBitmapDimension() const
   {

      if(m_psurface == nullptr)
      {

         return ::int_size(0, 0);

      }

      return m_size;

   }


   bool bitmap::LoadBitmap(unsigned int nIDResource)
   {

      return false;

   }


   bool bitmap::LoadOEMBitmap(unsigned int nIDBitmap)
   {

      return false;

   }


   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int cx, int cy)
   {

      if(!CreateBitmap(pgraphics, cx, cy, 1, 32, nullptr, cx * sizeof(color32_t)))
      {

         throw ::exception(error_failed);

      }

      //return true;

   }


   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight)
   {

      //return CreateCompatibleBitmap(pgraphics, nWidth, nHeight);

      CreateCompatibleBitmap(pgraphics, nWidth, nHeight);

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   int bitmap::GetBitmap(BITMAP* pBitMap)
//   {
//
//      return 0;
//
//   }
//
//
//#endif
//
//
//   void bitmap::dump(dump_context & dumpcontext) const
//   {
//
//      object::dump(dumpcontext);
//
//      //dumpcontext << "\n";
//
//   }


   void get_surface_size (cairo_surface_t * psurface, int * plongWidth, int * plongHeight)
   {

      synchronous_lock ml(::draw2d_cairo::mutex());

      if(plongWidth != nullptr)
      {

         *plongWidth = cairo_image_surface_get_width(psurface);

      }

      if(plongHeight != nullptr)
      {

         *plongHeight = cairo_image_surface_get_height(psurface);

      }

   }


   void bitmap::attach(void * psurface)
   {

      synchronous_lock ml(::draw2d_cairo::mutex());

      destroy();

      m_psurface = (cairo_surface_t *) psurface;

      get_surface_size((cairo_surface_t *) psurface, (int *) &m_size.cx(), (int *)&m_size.cy());

      m_osdata[0] = m_psurface;

      //return true;

   }


   void bitmap::destroy_os_data()
   {

      _synchronous_lock ml(::draw2d_cairo::mutex());

      if (m_psurface == nullptr)
      {

         //return ::success_none;

         return;

      }

      cairo_surface_destroy(m_psurface);

      m_psurface = nullptr;

      //return ::success;

   }


   void bitmap::destroy()
   {

      destroy_os_data();

      ::draw2d::bitmap::destroy();

      //return ::success;

   }


} // namespace draw2d_cairo



