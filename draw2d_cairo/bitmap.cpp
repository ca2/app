#include "framework.h"
#include "bitmap.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"


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


   bool bitmap::CreateBitmap(::draw2d::graphics * pgraphics, i32 cx, i32 cy, ::u32 nPlanes, ::u32 nBitcount, const void * pdata, i32 iStrideParam)
   {

      synchronous_lock ml(cairo_mutex());

      cy = abs(cy);

      cx = abs(cx);

      if(nPlanes != 1 || nBitcount != 32)
      {

         throw ::interface_only();

      }

      destroy();

      i32 iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cx);

      m_mem.set_size(iStride * cy);

      if(pdata == nullptr || iStrideParam <= 0)
      {

         memory_set(m_mem.get_data(), 0, m_mem.get_size());

      }
      else
      {

         if(iStrideParam != iStride)
         {

            i32 iW = cx * 4;

            for(i32 i = 0; i < cy; i++)
            {

               ::memcpy_dup(&m_mem.get_data()[iStride * i], &((byte *) pdata)[iStrideParam * i], iW);

            }

         }
         else
         {

            ::memcpy_dup(m_mem.get_data(), pdata, iStride * cy);

         }

      }

      m_psurface = cairo_image_surface_create_for_data(m_mem.get_data(), CAIRO_FORMAT_ARGB32, cx, cy, iStride);

      if(m_psurface == nullptr)
      {

         return false;

      }

      m_osdata[0] = m_psurface;

      m_size.cx = cx;

      m_size.cy = cy;

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


   void bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, void ** ppdata, int * pstride)
   {

      //try
      //{

         synchronous_lock ml(cairo_mutex());

         destroy();

         ::i32 iScanWidth = -1;

         if(pstride)
         {

            iScanWidth = *pstride / sizeof(color32_t);

         }

         if(iScanWidth < size.cx)
         {

            iScanWidth = size.cx;

         }

         ::i32 iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, iScanWidth);

#if MEMDLEAK

         m_mem.m_strTag = "image_section=" + as_string(cx) + "x" + as_string(size.ccy);

#endif

         m_mem.m_bAligned = true;

         m_mem.set_size(iStride * size.cy);

         if(*ppdata != nullptr)
         {

            if(size.cx * 4 != iStride)
            {

               i32 iW = size.cx * 4;

               for(i32 i = 0; i < size.cy; i++)
               {

                  ::memcpy_dup(&m_mem.get_data()[iStride * i], &((byte *) *ppdata)[iW * i], iW);

               }

            }
            else
            {

               ::memcpy_dup(m_mem.get_data(), *ppdata, iStride * size.cy);

            }

         }

         m_psurface = cairo_image_surface_create_for_data(m_mem.get_data(), CAIRO_FORMAT_ARGB32, size.cx, size.cy, iStride);

         int iSurfaceStatus = cairo_surface_status(m_psurface);

         if(iSurfaceStatus != CAIRO_STATUS_SUCCESS)
         {

            cairo_surface_destroy(m_psurface);

            m_psurface = nullptr;

            if(iSurfaceStatus == CAIRO_STATUS_INVALID_STRIDE)
            {

               iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, size.cx);

               m_psurface = cairo_image_surface_create_for_data(m_mem.get_data(), CAIRO_FORMAT_ARGB32, size.cx, size.cy, iStride);

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

            *ppdata = (color32_t *) m_mem.get_data();

         }

         if(pstride != nullptr)
         {

            *pstride = iStride;

         }

         m_osdata[0] = m_psurface;

         m_size = size;

         //return true;

      //}
      //catch(...)
      //{

      //}

      //destroy();

      //return false;

   }


   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, ::u32 flInit, const void *pjBits, ::u32 iUsage)
   {

      //return false;

   }


   ::u32 bitmap::SetBitmapBits(::u32 dwCount, const void * lpBits)
   {

      return 0;

   }


   ::u32 bitmap::GetBitmapBits(::u32 dwCount, void * lpBits) const
   {

      return false;

   }


   bool bitmap::LoadBitmap(const ::string & lpszResourceName)
   {

      return false;

   }


   size_i32 bitmap::SetBitmapDimension(i32 nWidth, i32 nHeight)
   {

      throw ::interface_only();

      return ::size_i32(0, 0);

   }


   size_i32 bitmap::GetBitmapDimension() const
   {

      if(m_psurface == nullptr)
      {

         return ::size_i32(0, 0);

      }

      return m_size;

   }


   bool bitmap::LoadBitmap(::u32 nIDResource)
   {

      return false;

   }


   bool bitmap::LoadOEMBitmap(::u32 nIDBitmap)
   {

      return false;

   }


   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 cx, i32 cy)
   {

      if(!CreateBitmap(pgraphics, cx, cy, 1, 32, nullptr, cx * sizeof(color32_t)))
      {

         throw ::exception(error_failed);

      }

      //return true;

   }


   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight)
   {

      //return CreateCompatibleBitmap(pgraphics, nWidth, nHeight);

      CreateCompatibleBitmap(pgraphics, nWidth, nHeight);

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   i32 bitmap::GetBitmap(BITMAP* pBitMap)
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


   void get_surface_size (cairo_surface_t * psurface, ::i32 * plongWidth, ::i32 * plongHeight)
   {

      synchronous_lock ml(cairo_mutex());

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

      synchronous_lock ml(cairo_mutex());

      destroy();

      m_psurface = (cairo_surface_t *) psurface;

      get_surface_size((cairo_surface_t *) psurface, (::i32 *) &m_size.cx, (::i32 *)&m_size.cy);

      m_osdata[0] = m_psurface;

      //return true;

   }


   void bitmap::destroy_os_data()
   {

      synchronous_lock ml(cairo_mutex());

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



